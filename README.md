# Sea-Shell
by Robin Han and Steven Liu

## Features:
  Forks and executes commands.  
	Parses multiple commands on one line  
  Supports arguements for commands  
  Catches CTRL + C  
  
## Attempted:
  Did not get pipes to work.  
	Could not disply current path directory, just displays $BASH for now  
  Will try to color code.  
  Didn't handle invalid user input.  

## Bugs:
  None so far.
	
## Files & Function Headers:
### shell.c  
*=============================================================================*  
#### parse_args()
##### Inputs:   
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;char *line  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;char **args  
##### Outputs:  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;void  
  
This is used to read user input from stdin (terminal)
*===============================================================================*
#### parse_arargs()
##### Inputs:   
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;char *line  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;char **args  
##### Outputs:  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;void  
  
This is also used to read user inpur from stdin (terminal) but seperates based on semi-colon first
*===============================================================================*
#### execute()
##### Inputs:     
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;char **args  
##### Outputs:   
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;void    
  
Executes the call to system fuctions with exit returning 0 and cd calling chdir()
*===============================================================================*
