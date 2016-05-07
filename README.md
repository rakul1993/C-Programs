#**C-Programs**

These C porgrams focus on the principles, theory and features of multi-user, multi-tasking operating systems. It covers processes, scheduling, input/output, memory management, file systems and system management. These concepts are illustrated by studying the operation of the UNIX operating system in detail. All Unix commands are basically C programs or shell scripts. Bellow I have listed a discription of each Unix based C program:

###Lab1
1. simpleGetopt.c: A C program that capsures and displays the following flags for the egrep command "egrep  -A num  -B num  -c  –i   -v     		pattern   fileList".


###Lab2
####Part1:
1. book_order.h: Displays the size and offset of each of the individual fields in a BOOK_ORDER structure  
2. book_order.c: Adds and modifies book elements to the BOOK_ORDER structure and creates an octal dump file of the contents

####Part2:
1. catDemo3.c: Another getopt program used to simulate some of the functionalities of the cat command
2. fread.c: Reads the contents of a file created called freadDemo.c
3. octalDump.c: Another getopt program used to simulate some of the functionalities of the octalDump command


###Lab3
####Part1:
1. getOptLong.c: A C program that capsures and displays the following flags for the egrep command "egrep  -A num  -B num  -c  –i   -v     		pattern   fileList". Also supports long options.

####Part2:
1. ansi.h:
2. createPeople.c: creates randomly generated persons records
3. fileDiscriptor.c: creates specified file and writes specified contents using file descriptors
4. findPerson.c: Program will prompt you for a record number using random access it will retrieve the specified record
5. originalQsort.c: This program uses the PERSON data structure used in createPerson.c and findPerson.c to sort and diplays the data based on specified field.
6. person.h: Person structure
7. qsortDemo.c: Same as originalQsort.c but uses file descriptors rather than FILE pointers
8. test.c: creates specified file and writes specified contents using file pointers

####Part3:
1. dirStat.c: This program reads through the current directory and prints out the file name, the name of the owner, and the group name ownership of the file.
2. displayDirDemo.c: Displays directory file belongs to.
3. fstatDemo.c: Displays file metadata.
4. group.c: Prints out a list of groups and their members 

####Part4:
1. wordEXP.c: This program reads in a shell pattern for a file name and uses wordexp to expand it. Then stat each of the file names in the expansion and count each of the following features: files  that are executable by any of user, group or other, hidden files  (files who’s name starts with a period), directories, files where the last modified time is equal to the last accessed time.
2. wordexpDemo.c: Using wordexp to and stat to match file names. Enter any shell expression to expand a name, ie: [a-m]*.txt ~/???.c   $TZ/*    $(whoami)/abc
3. rand.c: - 


###Lab4
####Part1:
1. createPeople.c: Same as specified in Lab3 part 2
2. crypt.c: Sample password encryption using crypt
3. findPerson.c: Same as specified in Lab3 part 2
4. person.h: Same as specified in Lab3 part 2

####Part2:
1. 2.c:This program enables users to enter a group name and a string to use as salt. Then the program extract all the password records for the memebers of that group; encryps the GECOS field and stores the rcords in a file. 
2. crypt.c: -
3. fGetPWnam.c: Read the password record froma specified file.
4. group.c: -
5. lookupPassword.c: Concatinates passwd and uid field and seaches the passwd file.
6. smaple1.c: copies contents of group file to a new file
7. searchPassword.c: search and identify a user and thier password, and reject bad combinations  

####Part3:
1. question3a.c: a signal handler for SIGUSR1 what uses popen to run a shell command that determines the number of processes on the system. Print that value out to the terminal.  
2. question3b.c: Open two files at the beginning of the program. When you send the program SIGINT (<ctrl>c) have it display the real names of all the open files in the directory /proc/pid/fd using readdir.
3. question3c.c: Use SIGHUP to reinitialize a program.


###Lab5
####Part1:
1. octalDump.c: 

####Part2:
1. orphanProcess.c: This short program that creates a single child. Have the main process die right away but leave the child still executing in an infinite loop. 
2. reapingProcess.c: This short program creates a single child. The child will output its process id and the name and exit  with a status code. The parent will wait for child to die and display status.
3. sample.c: -
4. zombieProcess.c: This program creates a single child. The child process dies right away but leaves  the parent running in a loop or an extended sleep.

####Part3:
1. 1.c:
2. execDemo3.c:
3. myDemo.c
4. myScript.sh:
5. mytime.c:
6. scriptReader.c: 


###Lab6:
1. dAte.c:
2. historyDemo.c:
3. modForkingShell.c:
4. myTee.c:
5. popenCmd.c:
6. printRev.c:
7. printRev.c:
8. teeCmd.c:
9. timeDemo2.c:



