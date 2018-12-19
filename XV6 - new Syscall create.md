xv6 is a reimplementation of the Unix sixth edition in order to use as a learning tool. xv6 was developed by MIT as a teaching operating system for their “6.828” course. A vital fact about xv6 is that it contains all the core Unix concepts and has a similar structure to Unix even though it lacks some functionality that you would expect from a modern operating system. This is a lightweight operating system where the time to compile is very low and it also allows remote debugging.

The source code of xv6 can be cloned to your machine as follows.

`git clone git://github.com/mit-pdos/xv6-public.git xv6`

# Creating a User program
## Step 1: Write a simple C program

First of all, create a C program as follows and save it inside the xv6 operating system folder. This can be named `myprogram.c`

```C
include "types.h"
include "stat.h"
include "user.h"
 
int
main(void)
{
  printf(1, "My first xv6 program\n");
  exit();
}
```

## Step 2: Edit the Makefile
The `Makefile` needs to be edited to make our program available for the xv6 source code for compilation.

``shell
gedit Makefile
``

This line of code would open the Makefile in the Gedit text editor. Next, the following sections of the Makefile needs to be edited to add your program `myprogram.c`

```
UPROGS=\
_cat\
_crash\
_echo\
_factor\
_forktest\
_grep\
_hello\
_init\
_kill\
_ln\
_ls\
_mkdir\
_null\
_rm\
_sh\
_share\
_stressfs\
_usertests\
_wc\
_zombie\
_myprogram\
```

```
EXTRA=\
 mkfs.c ulib.c user.h cat.c echo.c forktest.c grep.c kill.c\
 ln.c ls.c mkdir.c rm.c stressfs.c usertests.c wc.c zombie.c\
 myprogram.c\
 printf.c umalloc.c\
 README dot-bochsrc *.pl toc.* runoff runoff1 runoff.list\
 .gdbinit.tmpl gdbutil\
 ```
 
Once these changes are made, the user program is ready to be tested.

Run the following commands to compile the source code of xv6. This would compile the whole system.

```
make clean
make
```

Now you could go to QEMU through the command

```
make qemu
```

and then type the name of the program. This would print the statement “My first xv6 program” in the QEMU emulator window.
