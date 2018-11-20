#include "shell.h"

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

int main(){
	// Initalization 

	// Execution Loop

	// Exit Program
	return 0;
}