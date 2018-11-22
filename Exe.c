#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
	execvp(args[0],args);
	// execvp(cmd);

	return 0;
}

