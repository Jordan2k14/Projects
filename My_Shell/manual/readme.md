# MyShell


Welcome to the manual for MyShell. This shell is a simple shell written in the C programming language which is a procedural computing programming language. The shell supports a number of built-in commands, batchfile execution / batch mode, I/O Redirection, external command functionality and background execution functionality. This shell will help the user understand the shell.

## List of Commands & What they do

```bash
cd - Change the current default directory, by taking an argument and a path
clr - Clears the screen
dir - Lists the contents of the directory
environ - Lists all the environment strings
echo - Echo on display followed by a newline
help - Displays all the built in commands
pause - Pauses the operation of the shell, user must press enter to start the shell again
manual - Displays the user manual
mkdir - Allows the user to create a new directory
```

## Usage

To use the commands, simply type them into the command prompt on your system and press 'Enter'. Each command will do something different etc mkdir will make a new directory.

## Example Usage
```bash
cd ca216
 - This will change current directory to the ca216 directory

echo hello world
- this will print the message "hello world"

mkdir ca284
- This will create the ca284 directory

```

## Environment Concepts

- Environmental variables are variables that are defined for the current shell and are inherited by any child shells or processes. Environmental variables are used to pass information into processes that are spawned from the shell.
- This shell contains a certain command that has the ability to list all the current environment variables, it is named
'environ' under the commands section above.
- This command stores specific system values that can help the system install other programs.


## I/O Redirection

- Linux is fascinating in a way, you can make a command get its input from a file and then send its output to another file. This is what is known as input/output (I/O Redirection). I/O redirection allows you to alter the input source of a command as well as where its output and error messages are sent to. And this is made possible by the “<” and “>” redirection operators.

 - For example, cat < input.txt, in this command we are redirected to the contents of the input.txt file to the cat command. To save the output of a command in a file, redirect the standard output to a file. 

- Another example would be the input.txt > output.txt, as you can see it's similar, in this command we redirected the contents of input.txt to output.txt

- My shell is capable of using I/O Redirection in some fashion

## Example Usage

```bash
./myshell < inputfile
``` 

My Shell is also capable of using a batchfile
```bash
./myshell <batchfile name>
```

## Background Execution
- My shell is capable of running both foreground and background execution

## Example Usage

```bash
Foreground Execution:
<command <arguments>
``` 

```bash
Background Execution:
<command> <arguments> &
``` 

1. Background processes typically run with little or no user interaction, they interact with the system instead. Foreground processes are what the user interacts with.

2. Background processes, unless explicitly ran so, run with non-admin permissions.

3. A foreground process has access to the terminal (standard input and output), while the background process does not.

4. A background process runs without being connected to your keyboard. If the background process requires any keyboard input, it waits.
## References

Stephen, G (2015), Programming in C -  Input and Output Operations in C

Lars, K (1999),  C/C++ Annotated Archives - Strings & Arrays

Stephen, B (2015), Tutorial - Write a C Shell, [Online] - 
https://brennan.io/2015/01/16/write-a-shell-in-c/

Graham, H (2021), CA216 Operating Systems Lecturer - Lecture & Lab Notes, Dublin City University [University Notes]

## Author
 Student Name: Jordan Ukawoko

Student Number: 20353751

I am aware of the DCU integrity policy, all the code and text written in this assignment and manual was done by me, properly commented and referenced where possible.

