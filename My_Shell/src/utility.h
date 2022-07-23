/* 
Welcome to my shell, Here are some of the functions:
cd - changes directory
help - brings up the help screen, more sections brings up the manual
clr - clears the screen
quit - exits from the program
env - prints environment strings
pause - pauses the shell
mkdir - makes a new directory
echo - echo on display followed by a newline
dir - lists the contents of the directory

********************************************************************
version: Jordan's Shell
date:    February 2021
author:  Jordan Ukawoko
student number: 20353751
Dublin City University
Bachelor of Science in CASE
jordan.ukawoko2@mail.dcu.ie
Code follows rules of DCU Plagiarism - References supplied
*******************************************************************/




#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_BUFFER 1024                        // max line buffer
#define MAX_ARGS 64                            // max # args
#define SEPARATORS " \t\n"                     // token sparators

/*
Funtion Callouts
*/

void greeting();                    // Greets the user - fun little message
int hasampersand(char *args[]);     // Hasampersand used for background
char **split(char *line);           // Splits the inpit
void prompt();                      // Prints out current working directory
int external_exe(char *args[]);     // function forks to create a child process and runs execvp on the given command
int exec(char **args);              // User inputted commands
int backgr_exe(char **args);        // Background excecution


/*
Shell is capable of using background excecution
*/

int hasampersand(char *args[])
{
    int last=0;

    // loops through the different tokanized variables
    for(int i=1; args[i]; i++)
    {
        last++;
    }

    // if the last token is an & symbol return 1 else return 0
    if(!strcmp(args[last], "&")) // The "&" symbol is needed for background commands
    {
    	return 1;
    }
    else
    {
        return 0;
    }
}

void greeting() 
{  
    printf("+============================+\n");
    printf("| Welcome to Jordan's Shell!!! |\n");
    printf("| This is a CA216 Assignment!  |\n");
    printf("| Student number: 20353751     |\n");
    printf("|   February 2022              |\n");
    printf("+============================+ |\n");
    sleep(1);
    char* username = getenv("USER"); // Something I thought was cool - getting the current username e.g jordan (name of my laptop)  :)
    printf("\n\n\nUSER is: @%s", username); 
    sleep(1);
    printf("\nUse \"help\" to access the shell's user manual.");
    printf("\n"); 
    sleep(1); 
}




// prints out the CWD
void prompt()
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd)); // gets the current working directory
    printf("\n%s\n -> ", cwd); // Nice little "->"
}

//This function is used to split input
char **split(char *line)
{
  int bufsize = MAX_ARGS, position = 0; //The bufsize starts at 64
  char **tokens = malloc(bufsize * sizeof(char*)); //We are using dynamic allocation here
  char *token;

  if (!tokens)
  {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, SEPARATORS);
  while (token != NULL) //while lthe token is not nul
  {
    tokens[position] = token;  //Takes the token string at the position
    position++;

    if (position >= bufsize) //if position > memory allocated
    {
      bufsize += MAX_ARGS; //This is when we will increase the buffsize by 64
      tokens = realloc(tokens, bufsize * sizeof(char*)); //Reallocating the memory
      if (!tokens)
      {
        fprintf(stderr, "lsh: allocation error\n"); 
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, SEPARATORS);
  }
  tokens[position] = NULL; //end of use of tokens
  return tokens; //Finally we are returning the final string
}


/*
Shell is capable of using external excecutions
*/
// function forks to create a child process and runs execvp on the given command
// here we wait for the child process to finish
int external_exe(char *args[])
{
    char *command = args[0]; // user commands that were made e.g cd, help
    char *cmd[3]; // array of the different commands
    cmd[0]=args[1], cmd[1]=args[2], cmd[2]=NULL;

    pid_t pid = fork(); // -> We are now creating the child proccess create child process

    // fork error handling
    if(pid == -1)
    {
        printf("Error: fork failed."); // Error message is displayed
    }
    else if(pid == 0)
    {
        printf("%s", command);
        execvp(command, cmd);
    }

    wait(NULL); // wait for child process to end
    return 0;
}

/*
User inputted commands
*/

int exec(char **args)
{
    // a char array of the possible internal commands a user can give
    char *internal_cmds[] = {
        "quit",
        "clr",
        "mkdir",
        "help",
        "dir",
        "echo",
        "environ",
        "cd",
    };
    

    // array of all the different command functions
    int (*commands[]) (char **) = {
        &quit,
        &clr,
        &makedir,
        &help,
        &dir,
        &echo,
        &env,
        &cd,
    };

    int foundInt=0;

    if(args[0] == NULL) // We are checking if the user has given a certain command
    {
        // Only return 1 if the user has not entered a command
        return 1;
    }
    else
    {
        for(int i=0; i<(sizeof(internal_cmds) / sizeof(char *)); i++) // Now we loop through arrays of all the different commands
        {
            if(!strcmp(args[0], internal_cmds[i])) // finds the command that matches the user's input
            {
                foundInt++; // if the command is found to be an internal command increment foundInt(ernal)
                return (*commands[i])(args); // executes the given command
            }
        }

        // if we could not find an internal command matching the users input we run the external command function to handle the non-built-in
        // command, so long as it is a valid command
        if(foundInt==0)
        {
            external_exe(args);
        }
        return 0;
    }
}

/*
Background Excecution in action
*/



// // function to find and execute command provided by user in the background
// we do not wait for the child process to finish before returning to parent as we want the child process to run in the background of the parent process
int backgr_exe(char **args)
{
    // a char array of the possible internal commands a user can give
    char *internal_cmds[] = {
        "quit",
        "clr",
        "mkdir",
        "help",
        "dir",
        "echo",
        "environ",
        "cd",
    };
    

    // array of command's functions
    int (*commands[]) (char **) = {
        &quit,
        &clr,
        &makedir,
        &help,
        &dir,
        &echo,
        &env,
        &cd,
    };

    int foundInt=0;

    if(args[0] == NULL) // check if user has given a command
    {
        // user entered no command i.e. an empty command input
        return 1;
    }
    else
    {

        pid_t pid = fork(); // Over here we are forking and creating a child proccess

        for(int i=0; i<(sizeof(internal_cmds) / sizeof(char *)); i++) // We are looping through the array of internal commands
        {
            if(!strcmp(args[0], internal_cmds[i])) // finds the command that matches the user's input
            {
                if(pid == -1)
                {
                    printf("Error: fork failed.");
                }
                else if(pid == 0)
                {
                    return (*commands[i])(args); // executes the given command
                }
            }
        }

    }
    return 0;
}

/*
End of Utility file
*/
