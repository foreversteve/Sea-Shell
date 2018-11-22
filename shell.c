  #include "shell.h"
  

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
	}
	return;
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
	  // printf("Process %d is running...\n",getpid());
	  // println(args);
	  execvp(args[0], args);
	  return 1;
	}
	else{
	  int status;
	  wait(&status);
	  // printf("Parent waited for child...exit status was %d \n",WEXITSTATUS(status));
	  return 1;
	}
  }
  // int main(){
  // 	char line[] = "Test this stupid program";
  // 	char **args = parse_args(line);
  // 	println(args);
  // 	return 0;
  // }
  int main(){
  	// char *line;
  	// strcpy(line,"cd ..");
  	// char *path = calloc(100,sizeof(char));
  	// line +=3;
  	// print_string(line);
  	// strcpy(path,line);
  	// printf("%s\n",path);
  	// return 0;
	// Initalization 
	char cwd[PATH_MAX];
	getcwd(cwd, sizeof(cwd));

	char cmd[100];
	char ** args = calloc(100,sizeof(char*));
	char ** ararg = calloc(20,sizeof(char*));
	int numtok = 0;

	// Execution Loop
	while (1){
	  printf("%s: ","~BASH$");
	  fgets(cmd,100,stdin);
	  // cmd[6] = NULL;
	  strtok(cmd, "\n");
	  strcat(cmd,"\0");
	  // printf("Command was:%s",cmd);
	  parse_arargs(cmd,ararg);
	  for (int i = 0; i < 100; i++){
	  	if (!ararg[i]){
	  		numtok = i;
	  		break;
	  	}
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
			printf("Hasta la vista BABY\n");
			return 0;
		}
	  }
	}
	// Exit Program
	return 0;
  }

