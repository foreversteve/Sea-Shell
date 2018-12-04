  #include "shell.h"
  
 //  static void sighandler(int signo){
	// if (signo == SIGINT){
	// 	printf("This doesn't work here :/ \n");
	// 	printf("\n");
	// }
 //  }

  void parse_args(char *line,char **args){
  	// char **ans = calloc(100,sizeof(char*));
  	// printf("ran HERE HELLO?");
  	if (line[0] == 'c' && line[1] == 'd'){
  		char *path = calloc(100,sizeof(char));
  		line +=3;
  		strcpy(path,line);
  		args[0] = "cd";
  		args[1] = path;
  		return;
  	}
	char **temp = &line;
	for (int i = 0; i < 100; i++){
	  if (! *temp){
		args[i] = NULL;
		return;
	  }
	  args[i] = strsep(temp," ");
	}
	return;
  }

  void parse_arargs(char *line,char **ararg){
	char **temp = &line;
	for (int i = 0; i < 100; i++){
	  if (! *temp){
		ararg[i] = NULL;
		return;
	  }
	  ararg[i] = strsep(temp,";");
	  int len = strlen(ararg[i]);
	  // printf("It is:%s!\n",ararg[i]);
	  // printf("length is: %d\n", len);
	  if (ararg[i][0] == ' '){
	  	ararg[i]+=1;
	  }
	  if (ararg[i][len-1] == ' '){
	  	ararg[i][len-1] = '\0';
	  }
	}
	return;
  }

  void parse_redirects(char *line, int *input, int *output){
  	char *copy = calloc(sizeof(char),100);
  	char *temp;
  	char *cmd;
  	//Remembering original pointer
  	char *liberty = copy;

  	strcpy(copy,line);
  	// printf("copy is: %s\n",copy);
  	temp = strsep(&copy,">");
  	if (copy != NULL){
  		copy+=1;
  		*output = open(copy,O_TRUNC|O_WRONLY|O_CREAT, 0666);
  		// printf("opened out.txt:%s, fid is %d\n",copy,*output);
  	}

  	// printf("temp is:%s!\n",temp);
  	cmd = strsep(&temp,"<");
  	if (temp != NULL){
  		temp +=1;
  		int len = strlen(temp);
  		if (temp[len-1] == ' '){
  			temp[len-1] = '\0';
  		}
  		*input = open(temp,O_RDONLY);
  		// printf("opened in.txt:%s, fid is %d\n",temp,*input);
  	}
  	// printf("copy is:%s!\n",copy);

  	strcpy(line,cmd);

	free(liberty);
  }

  int print_string(char *s){
  	int count = 0;
  	while (*s){
  		printf("%c",*s);
  		s++;
  		count+=1;
  	}
  	printf("!\n");
  	return count;
  }
  void println(char **sarray){
  	char *temp = sarray[0];
  	int i = 0;
  	while (temp != NULL){
  		printf("%s\n",temp);
  		i+=1;
  		temp = sarray[i];
  	}
  }
  void execute_pipe(char *cmd){
  	char *front = strsep(&cmd,"|");
  	char ** ararg0 = calloc(20,sizeof(char*));
  	char ** ararg1 = calloc(20,sizeof(char*));

	// printf("cmd is: %s\n",cmd);
	// strcat(cmd,"\0");
	int numtok = 1;
	parse_arargs(front,ararg0);
	parse_arargs(cmd,ararg1);
	
  	int fds[2];
	char line[100];
	int f;

	pipe(fds);
	f = fork();
	if (!f){

	    char **args = calloc(100,sizeof(char*));
		parse_args(ararg0[0],args);
		int new = dup(STDOUT_FILENO);
	    dup2(fds[1], STDOUT_FILENO);

	    execute(args);
	    dup2(new,STDOUT_FILENO);
	    free(args);
	    return;

	} else {
	    // dup2(fds[0], STDIN_FILENO);
	    char s[1024];
	    char **args = calloc(100,sizeof(char*));
		parse_args(ararg1[0],args);

	    int size = read(fds[0], s, sizeof(s));
	    s[size] = 0;
	    // printf(s);
	    int output = open("temp.txt",O_TRUNC|O_WRONLY|O_CREAT, 0666);

	    write(output,s,strlen(s));
	    close(output);

	    int input = open("temp.txt",O_RDONLY);

	    int new = dup(STDIN_FILENO);
	    dup2(input,STDIN_FILENO);
	 //    printf("STDOUT IS:%d\n",STDOUT_FILENO);
		// printf("STDIN IS:%d\n",input);
	    execute(args);
	 //    printf("STDOUT IS:%d\n",STDOUT_FILENO);
		// printf("STDIN IS:%d\n",STDIN_FILENO);
	    dup2(new,STDIN_FILENO);
	 //    printf("STDOUT IS:%d\n",STDOUT_FILENO);
		// printf("STDIN IS:%d\n",new);
	    args[0] = "rm";
	    args[1] = "temp.txt";
	    args[2] = 0;
	    execute(args);
	    free(args);
	}

  }
  int execute(char **args){
  	if (!strcmp(args[0],"exit")){
  		return 0;
  	}
  	if (!strcmp(args[0],"cd")){
  		chdir(args[1]);
  		return 1;
  	}
	int f;
	f = fork();
	if (!f){
	  execvp(args[0], args);
	  return 1;
	}
	else{
	  int status;
	  wait(&status);
	  return 1;
	}
  }

  int main(){
 
	// Initalization 
	char cwd[PATH_MAX];
	getcwd(cwd, sizeof(cwd));

	char cmd[100];
	char ** args = calloc(100,sizeof(char*));
	char ** ararg = calloc(20,sizeof(char*));

	int input = 0;
	int output = 0;

	int newin = 0;
	int newout = 0;
	// char *input = calloc(100,sizeof(char));
	// char *output = calloc(100,sizeof(char));

	int numtok = 0;

	int print_again = 1;
	// Execution Loop
	while (1){
	  // signal(SIGINT,sighandler);
	  if (print_again){
	  	printf("%s: ","~BASH$");
	  	print_again = 0;
	  }
	  fgets(cmd,100,stdin);
	  // cmd[6] = NULL;
	  strtok(cmd, "\n");
	  strcat(cmd,"\0");
	  // printf("cmd is:%s!\n",cmd);
	  // printf("Command was:%s",cmd);
	  char *temp = cmd;
	  //Check if pipe exists
	  int count = 0;
	  while (*temp){
	  	if (*temp == '|'){
	  		count +=1;
	  	}
	  	temp +=1;
	  }
	  if (count){
	  	execute_pipe(cmd);
	  	print_again = 1;
	  	input = 0;
		output = 0;

	  	continue;
	  }
	  parse_redirects(cmd,&input,&output);
	  // printf("cmd is: %s\n",cmd);
	  // strcat(cmd,"\0");
	  parse_arargs(cmd,ararg);
	  for (int i = 0; i < 100; i++){
	  	if (!ararg[i]){
	  		numtok = i;
	  		break;
	  	}
	  }
	  if (output){
		newout = dup(STDOUT_FILENO);
		// printf("dup of stdout:%d\n",new);
	    dup2(output,STDOUT_FILENO);
	  }
	  if (input){
		newin = dup(STDIN_FILENO);
		// printf("dup of stdout:%d\n",new);
	    dup2(input,STDIN_FILENO);
	  }
	  // printf("argument was %s\n",args[0]);
	  // printf("Args[0] was:");
	  // printf("Length was %d\n",print_string(args[0]));
	  
	  // printf("Args[1] was %s\n",args[1]);
	 
	  // printf("Args[2] was %s\n",args[2]);
	  // execvp(args[0],args);

	  for (int i = 0; i < numtok; i++){
	  	parse_args(ararg[i],args);
		if (!execute(args)){
			printf("Hasta la vista!\n");
			return 0;
		}
		//return output to stdout
		if (output){
			dup2(newout,STDOUT_FILENO);
			input = 0;
			output = 0;
		}
		if (input){
			dup2(newin,STDIN_FILENO);
			input = 0;
			output = 0;
		}
	  }
	  print_again = 1;
	}
	// Exit Program
	return 0;
  }

