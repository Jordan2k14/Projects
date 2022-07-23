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
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>


extern char **environ;  // used to get environ strings

//Command Functions Calls
int clr();                     // Clears the terminal
int makedir(char *args[]);    // Makes a new directory
int dir();                   // Lists the contents within the directory
int env(char **args);       // Shows the environment
void pause_shell();        // Pauses the shell (user must enter input to unpause)
int cd(char *args[]);     // Changes directory
int echo(char *args[]);  // Allows us to print an argument e.g "Jordan is my name"
int quit();



// This is used to quit the shell
int quit()
{
    printf("Goodbye\n"); // Goodbye message
    exit(0);
}


// clears shell terminal
int clr()
{
    system("clear"); //calling the system "clear"
    return 0;
}


// function takes a dirname from the user and creates a new directory with that name
int makedir(char *args[])
{

    // if no dirname given print an error message
    if(args[1] == NULL)
    {
        printf("Error: No directory name given.");
        return 0;
    }
    // else create a directory in the cwd with the given name
    else
    {
        // use inbuilt mkdir function to create a new directory. Command defaults to the creating the directory in the cwd.
        // result is stored in check. if successful it returns 0 else it returns -1
        int check = mkdir(args[1], 0777);

        // checking if the directory has been created
        if(check == 0)
        {
            printf("Directory created successfully!"); // Success message for if directory has been created
        }
        else
        {
            printf("Error in creating directory."); // Error message if the shell for some reason cannot make a directory OR no directory name given
            exit(1);
        }
        return 0;
    }
}

// lists contents of current directory (think of ls command)

int dir()
{
    DIR *dir;
    struct dirent *files;
    struct stat mystats;

    dir = opendir(".");

    if (dir == NULL)
    {
        printf("Directory cannot be opened!" );
    }
    else
    {
        while ((files = readdir(dir)))
        {
            stat(files->d_name, &mystats);
            printf("%lld ", mystats.st_size);
            printf("%s\n", files->d_name);
        }
    }
    return 0;
    closedir(dir);
}

// We are printing the environment variables
int env(char **args)
{
    int i;
    for (i = 0; environ[i] != NULL; i++)  //simple for loop to list environ strings
        printf("%s\n", environ[i]); // environ in action
    printf("\n");
    return 1;
}


// Pauses the shell
void pause_shell()
{
    printf("Shell has been paused, press enter to unpause...");
    getchar(); // wait for the user to enter an input to unpause the shell
}




int cd(char *args[])
{
    char cwd[1024]; //gets CWD
    getcwd(cwd, sizeof(cwd)); // Firstly we are getting the CWD (Current Working Directry)

    // if no directory provided print the the current working directory
    if(args[1] == NULL)
    {
        printf("%s\n", cwd);
    }
    else
    {
        chdir(args[1]); // CD in Action
        getcwd(cwd, sizeof(cwd)); // CD in Action - Gets the new current working directory
        putenv("PWD=cwd"); // set the PWD environment varable to the new cwd
    }
    return 0;
}

// print an argument if given e.g "my name is jordan" - will print my name is jordan
int echo(char *args[])
{

    // loops through the array of a split input
    for(int i=1; args[i]; i++)
    {
        printf("%s ", args[i]);
    }
    
    printf("\n");
    return 0;
}

// displays the user manual "readme" found in the manual directory to the user using the more filter
int help()
{
    chdir(getenv("shell")); // change directory
    system("more ../manual/readme.md"); 
    return 0;  // The manual has now been accessed!!
}


/*
End of commands file
utility.h is used for all the functionality of the shell
*/
