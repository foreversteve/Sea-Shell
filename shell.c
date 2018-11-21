  #include "shell.h"
  
  char **strsep(char **source, char *delimiter){
    char *temp = *source;
    int c = 0;
    while (temp[c]){
      // printf("%c\n",temp[c]);
      if (temp[c] == *delimiter){
        temp[c] = 0;
        *source = temp+c+1;

        return &temp;
      }
      c+=1;
    }

    return &temp;
  }

  char **parse_args(char *line){
    char **temp = &line;
    char **ans = calloc(5,sizeof(char*));
    for (int i = 0; i < 5; i++){
      if (! *temp){
        return ans;
      }
      ans[i] = *strsep(temp," ");
    }
    return ans;
  }
  int lsh_cd(char **args)
  {
    if (args[1] == NULL) {
      fprintf(stderr, "lsh: expected argument to \"cd\"\n");
    } else {
      if (chdir(args[1]) != 0) {
        perror("lsh");
      }
    }
    return 1;
  }

  // Not sure why this is necessay
  int lsh_exit(char **args){
    return 0;
  }

  void execute(char **args){
    int f;
    f = fork();
    if (!f){
      printf("Process %d is running...\n",getpid());
      args[2] = NULL;
      printf("Args were %s %s %s\n",args[0],args[1],args[2]);
      execvp(args[0], args);
      return;
    }
    else{
      int status;
      int pid = wait(&status);
      printf("Parent Process Complete... Process %d slept for %d seconds\n",pid,WEXITSTATUS(status));
      return;
    }
  }
  int main(){
    // Initalization 
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));

    char cmd[100];
    char ** args;
  	// Execution Loop
    while (1){
      printf("%s:",cwd);
      fgets(cmd,10,stdin);
      printf("Command was:%s",cmd);
      args = parse_args(cmd);
      execute(args);
      // execute();
    }
  	// Exit Program
  	return 0;
  }

