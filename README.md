# as2
## Makefile
The Makefile is used to build the C program and output the executable as main. It defines two variables: CC for the C compiler (gcc) and CFLAGS for the compiler flags, including warnings (-Wall and -Wextra) and debugging information (-g), which can be removed now that it isn’t being developed anymore. The Makefile has three main targets: all, main, and the object files (main.o and functions.o). The default(all) target, depends on the main target. The main target depends on main.o and functions.o, and it compiles the source files (main.c and functions.c) along with the header file (functions.h) to create the executable main. We use the -c flag to specify that it only needs to be compiled, we translate the files into object files so that we can insert them modularly wherever we want, for example we wanted to use functions in main so we added functions.o as a dependency there. The clean target is also provided to remove the generated executable and object files when make clean is executed.
	To compile the program start with “make clean” just in case if there’s anything messed up, the files may not be compiled correctly or something, and then “make” to compile and create the main exe, which can then be executed with “./main”. 
So, 	1.	“make clean”
	2.	“make”
	3.	“./main”
OR	
1.	“gcc -g -c main.c”
	2.	“gcc -g -c functions.c”
	3.	“gcc -g main.o functions.o readFile_randWord.c -o main”
	4.	“./main”


## OTHER IMPORTANT THINGS (functions.c)
Auto vs Manual (Line 268)
	I didn’t understand if the second part needed to be executed automatically or not, so I made it capable of doing both- it is called automatic afterall-. To change between manual and automatic entries for all but last attempts. Change in “functions.c” Line 268, comment out the one that you don’t want anymore, and uncomment the one that needs to be used. There are comments explaining it as well. If I realized about this earlier i would’ve made it better, either swap by user input or change a #define at the top of the file

How many hints? (Line 286)
	From the example in the assignment it looked like the hints should only be displayed once, and I thought that they should only be displayed once so that they don’t clutter too much, but in scenarios where there are a lot of words left to guess you might want to see hints after each guess on the last attempt, so in “functions.c” Line 286, comment or uncomment that line if the hints should be displayed every time or only once. By default it is every time right now.


