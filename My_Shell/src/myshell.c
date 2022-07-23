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
Dublin City University
student number: 20353751
Bachelor of Science in CASE
jordan.ukawoko2@mail.dcu.ie
Code follows rules of DCU Plagiarism - References supplied
*******************************************************************/


#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include "commands.h"
#include "utility.h"

#define MAX_BUFFER 1024                        // max line buffer
#define MAX_ARGS 64                            // max # args
#define SEPARATORS " \t\n"                     // token sparators

// Function Callouts

void greeting(); // Greets the user
void batch_file(int argc, char **argv); // Batch file in action
void my_shell(int argc, char **argv, char *out_file); // My actual shell

//This is the main function that puts everything into action
int main(int argc, char ** argv, char *envp[])
{

/*
Batch File in Action
MyShell is capable of using batchfiles
*/

/*
I/O Redirection IS SOMEWHAT WORKING
What's Working - Input is working
What's Not Working - Output is NOT Working!!
*/
if (argc == 2
      && !(!strcmp (argv[1], ">")

      || !strcmp (argv[1], ">>")
      
      || !strcmp (argv[1], "<")))
    {
      batch_file (argc, argv);
    }
  else
    {				
      int input = 1; // Activates my shell
      char *in_file = "";
      char *out_file = "";
      char *activated[MAX_ARGS];
      int activated_count = 0;

      for (int i = 1; i < argc; i++)
	{
	  // Opening output file
	  if (!strcmp (argv[i], ">"))
	    {
	      if (argv[i + 1] != NULL)
		{

		  fopen (argv[i + 1], "w+");
		  strcpy (out_file, argv[i + 1]);	// This checks if there is a file
		}
	      else
		{
		  fputs ("File does not exist", stdout);
		}


	    }
	  else if (!strcmp (argv[i], ">>"))
	    {
	      if (argv[i + 1] != NULL)
		{
		  fopen (argv[i + 1], "a");	// Appends to file
		  strcpy (out_file, argv[i + 1]);
		}
	      else
		{
		  fputs ("File does not exist", stdout);
		}


	    }
	  else if (!strcmp (argv[i], "<"))
	    {
	      if (argv[i + 1] != NULL)
		{
		  // Input file
		  input = 0;
		  strcpy (in_file, argv[i + 1]);
		}
	      else
		{
		  fputs ("File does not exist", stdout);	// Input file
		}
	    }
	  else
	    {
	      activated[activated_count] = argv[i];
	      activated_count++;
	    }
	}
      if (activated_count > 0)
	{
	  if (input == 0)
	    {
	      activated[activated_count] = "<";
	      activated[activated_count + 1] = in_file;
	    }
	  execvp (activated[0], activated);
	}

      my_shell (argc, argv, out_file);
    }

  return 0;
}


// Batchfile / I/O End

/*
This is the function used for the batchfile
*/

void my_shell(int argc, char **argv, char *out_file) {

    char buf[MAX_BUFFER];
    char ** args;
    char shell[1024];      // Holds the shell environment

    strcat(shell, getenv("PWD")); // Gets the printing working directory
    strcat(shell, "/myshell"); // "myshell" - when you start the shell
    setenv("SHELL", shell, 1); // Adds to environment variables

    greeting(); //Welcomes the user to the shell
    while(!feof(stdin))
    {

        // prints out prompt
       prompt();

       if(fgets(buf, MAX_BUFFER, stdin)) // reads user input
       {
        // We are splitting the input

            args = split(buf); // tokenizes user input using the split command
            

            // use exec (execute) function if the line is not empty!
            if(args[0] != NULL)
            {
                if(hasampersand(args) == 1) // hasampersand (background execution) in action
                {
                    backgr_exe(args); // hasampersand in action
                }
                else
                {
                    // Pause is used to pause the shell
                    if(!strcmp(args[0], "pause"))
                    {
                        pause_shell();
                    }
                    // enviro function is used for the environ command
                    else if(!strcmp(args[0], "environ"))
                    {
                        env(args);
                    }
                     else if(!strcmp(args[0], "quit")) // Break shell when we call the quit command
                    {
                        printf("Goodbye\n"); // Goodbye message
                        break;
                    }
                    else
                    {
                        exec(args);
                    }
                }
            }  
        }
    }

}


void batch_file(int argc, char **argv)
{
    FILE *batchfile; //batchfile
    char c[100];

    batchfile = fopen(argv[1], "r"); // Firstly, we open the batchfile
    if(batchfile == NULL) // If the batch file is empty then inform the user that there are no commands
        {
            printf("Error: no commands supplied.");
        }
        else
        {
            while(fgets(c, sizeof(c), batchfile) != NULL) // while loop in action
            {
                char ** command = split(c); // parse the line using the split function as if the command was taken from the shell prompt
                exec(command); // run the exec function to run the commands on each line
                printf("\n");
            }
        }

        fclose(batchfile); // Finally we close the batch file
}

/*
End of shell file
commands.h is used for all the commands
*/
