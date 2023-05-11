Simple Shell
-------------
* Simple Shell is a team project using C language.

0x16. C - Simple Shell
-----------------------

Resources
----------
Read or watch:
--------------
* Unix shell
* Thompson shell
* Ken Thompson
* Everything you need to know to start coding your own shell concept page

man or help:
-------------
* sh (Run sh as well)

General
--------
* Who designed and implemented the original Unix operating system
* Who wrote the first version of the UNIX shell
* Who invented the B programming language
  (the direct predecessor to the C programming language)
* Who is Ken Thompson
* How does a shell work
* What is a pid and a ppid
* How to manipulate the environment of the current process
* What is the difference between a function and a system call
* How to create processes
* What are the three prototypes of main
* How does the shell use the PATH to find the programs
* How to execute another program with the execve system call
* How to suspend the execution of a process until
  one of its children terminates
* What is EOF / “end-of-file”?

List of allowed functions and system calls
-------------------------------------------
* access (man 2 access)
* chdir (man 2 chdir)
* close (man 2 close)
* closedir (man 3 closedir)
* execve (man 2 execve)
* exit (man 3 exit)
* _exit (man 2 _exit)
* fflush (man 3 fflush)
* fork (man 2 fork)
* free (man 3 free)
* getcwd (man 3 getcwd)
* getline (man 3 getline)
* getpid (man 2 getpid)
* isatty (man 3 isatty)
* kill (man 2 kill)
* malloc (man 3 malloc)
* open (man 2 open)
* opendir (man 3 opendir)
* perror (man 3 perror)
* read (man 2 read)
* readdir (man 3 readdir)
* signal (man 2 signal)
* stat (__xstat) (man 2 stat)
* lstat (__lxstat) (man 2 lstat)
* fstat (__fxstat) (man 2 fstat)
* strtok (man 3 strtok)
* wait (man 2 wait)
* waitpid (man 2 waitpid)
* wait3 (man 2 wait3)
* wait4 (man 2 wait4)
* write (man 2 write)

Tasks
------
0. Betty would be proud #mandatory
	- Write a beautiful code that passes the Betty checks
	- Repo: GitHub repository: simple_shell
1. Simple shell 0.1 #mandatory
	- Write a UNIX command line interpreter.
		* Usage: simple_shell
	- Repo: GitHub repository: simple_shell
2. Simple shell 0.2 #mandatory
	- Simple shell 0.1 +
		* Handle command lines with arguments
	- Repo: GitHub repository: simple_shell
3. Simple shell 0.3 #mandatory
	- Simple shell 0.2 +
		* Handle the PATH
		* fork must not be called if the command doesn’t exist
	- Repo: GitHub repository: simple_shell
4. Simple shell 0.4 #mandatory
	- Simple shell 0.3 +
		* Implement the exit built-in, that exits the shell
		* Usage: exit
		* You don’t have to handle any argument to the built-in exit
	- Repo: GitHub repository: simple_shell
5. Simple shell 1.0 #mandatory
	- Simple shell 0.4 +
		* Implement the env built-in, that prints current environment
	- Repo: GitHub repository: simple_shell
6. Simple shell 0.1.1 #advanced
	- Simple shell 0.1 +
		* Write your own getline function
		* Use a buffer to read many chars at once
		  call the least possible the read system call
	- Repo: GitHub repository: simple_shell
7. Simple shell 0.2.1 #advanced
	- Simple shell 0.2 +
		* You are not allowed to use strtok
	- Repo: GitHub repository: simple_shell
8. Simple shell 0.4.1 #advanced
	- Simple shell 0.4 +
		* handle arguments for the built-in exit
		* Usage: exit status, where it is an int used to exit shell
	- Repo: GitHub repository: simple_shell
9. setenv, unsetenv #advanced
	- Simple shell 1.0 +
	- Implement the setenv and unsetenv builtin commands
	- Repo: GitHub repository: simple_shell
10. cd #advanced
	- Simple shell 1.0 +
	- Implement the builtin command cd
	- man chdir, man getcwd
	- Repo: GitHub repository: simple_shell
11. ; #advanced
	- Simple shell 1.0 +
		* Handle the commands separator ;
	- Repo: GitHub repository: simple_shell
12. && and || #advanced
	- Simple shell 1.0 +
		* Handle the && and || shell logical operators
	- Repo: GitHub repository: simple_shell
13. alias #advanced
	- Simple shell 1.0 +
		* Implement the alias builtin command
		* Usage: alias [name[='value'] ...]
	- Repo: GitHub repository: simple_shell
14. Variables #advanced
	- Simple shell 1.0 +
		* Handle variables replacement
		* Handle the $? variable
		* Handle the $$ variable
	- Repo: GitHub repository: simple_shell
15. Comments #advanced
	- Simple shell 1.0 +
		* Handle comments (#)
	- Repo: GitHub repository: simple_shell
16. File as input #advanced
	- Simple shell 1.0 +
		* Usage: simple_shell [filename]
		* Your shell can take a file as a command line argument
		* The file contains all the commands
		  that your shell should run before exiting
		* The file should contain one command per line
		* In this mode, the shell should not print a prompt
		  and should not read from stdin
	- Repo: GitHub repository: simple_shell
