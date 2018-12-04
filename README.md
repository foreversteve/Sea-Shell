# Sea-Shell

## Features:

* Forks and executes commands

* Parses multiple commands on one line

* Redirects using ```<```, ```>```

* Piping 

* Handles directory changing


## Attempted:

* Displaying current directory after the $.

* Attempted to implement terminal colors but looks too messy.

## Bugs and Issues:

* File prints $bash multiple times upon exiting (Possibly fork error).

## Files and Function Headers:

shell.c

```
	============     void parse_args(char *line,char **args)    =============

	inputs: char *line, char **args

	returns: void
	
	-- Given a line, parses the commands into a char* array for execution.

	=========     void parse_arargs(char *line,char **ararg)    ===========

	inputs: char *line, char **ararg
  
	returns: void

	-- Seperates a line based on semi-colons and parses it into ararg.
	
	============     void parse_redirects(char *line, int *input, int *output)     ==============  

	inputs: char *line, int *input, int *output

	returns: void
	
	-- Given a line, opens the input and output files, parses the file descriptors to input and output, leaving the line  
	pointer with the remaining command.

	=======    void execute_pipe(char *cmd)    ========

	inputs: char *cmd
  
	returns: void
	
	-- Runs the program when | is found. Calls execute on strings located on either side of ```|``` . Works like the  
	pipe in bash.
  
	=========     int execute(char **args)     ===========

	inputs: char **args

	returns: int status
	
	-- Forks to child processes, calls execvp on the parsed argument arrays.
  
	=========     void println(char **sarray)     ===========

	inputs: char **sarray

	returns: void
	
	-- Helper function that prints a char* array.
  
	=========     int print_string(char *s)     ===========

	inputs: char *s

	returns: int numArgs
	
	-- Helper function that prints a char* (string).
