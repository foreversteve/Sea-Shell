#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/*
Exec family <unistd.h>:
	-- A group of c functions that can be used to run other programs
	-- Replaces the current process with the new program

	Execl(path, command, arg0, arg1..., NULL);
		-- Path: path to program "/bin/ls"
		-- Command: "ls"
		-- Arg0: each argument u wish to provide to the program

	Execlp(path, command, arg0, arg1..., NULL);
		-- Works like execl, except it uses the $path environment variable for commands
		-- You can use "ls" as the path instead of "/bin/ls"
		# Forgot what $Path was? try ~$ echo $PATH
	
	Execvp(path, argument_array);
		-- Argument_array: array of strings containing the arguments to the command
			* argument_array[0] must be name of program, and the last entry must be NULL
*/

int main(){
	// Stuff for execvp
	char *args[3];
	char temp[2];
	temp[0] = 'l';
	temp[1] = 's';
	args[0] = temp;
	args[1] = "-a";
	args[2] = NULL;

	// Example of execl
	// execl("/bin/ls","ls",NULL);

	// // Example of execlp
	// execlp("ls","ls","-a",NULL);

	// Example of execvp
	int fid = open("out.txt",O_TRUNC|O_WRONLY|O_CREAT, 0666);
	printf("fid of out.txt:%d\n",fid);
	int new = dup(STDOUT_FILENO);
	printf("dup of stdout:%d\n",new);
	dup2(fid,STDOUT_FILENO);
	int f;
	f = fork();
	if (!f){
	  // printf("Process %d is running...\n",getpid());
	  // println(args);
	  execvp(args[0],args);
	  return 1;
	}
	else{
	  int status;
	  wait(&status);
	  dup2(new,STDOUT_FILENO);
	  printf("STDOUT is back to normal\n");
	  close(fid);
	  // printf("Parent waited for child...exit status was %d \n",WEXITSTATUS(status));
	  return 1;
	}

	// execvp(cmd);

	return 0;
}

