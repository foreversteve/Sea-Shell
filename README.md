# Sea-Shell

## Features:

* Forks and executes commands

* Parses multiple commands on one line

* Redirects using ```<```, ```>```

* Piping 

* Handles directory changing

* Catches ```Ctrl-C```

## Attempted:

* Using redirection with pipes

## Bugs and Issues:

## Files and Function Headers:

shell.c

```
	============     void parse_args(char *line,char **args)    =============

	inputs: char *line, char **args

	returns: void

	=========     void parse_arargs(char *line,char **ararg)    ===========

	inputs: char *line, char **ararg
  
	returns: void

	============     void parse_redirects(char *line, int *input, int *output)     ==============  

	inputs: char *line, int *input, int *output

	returns: void

	=======    void execute_pipe(char *cmd)    ========

	inputs: char *cmd
  
	returns: void
  
	=========     int execute(char **args)     ===========

	inputs: char **args

	returns: int status
  
	=========     void println(char **sarray)     ===========

	inputs: char **sarray

	returns: void
  
	=========     int print_string(char *s)     ===========

	inputs: char *s

	returns: int numArgs
