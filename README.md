# SUM & MEAN

## simple terminal app example
## in c language

![sum & mean execution](./sumean.png "SUM & MEAN running")

This programming example accepts in input a list of positive integers
and computes their sum and average, showing them as output. 

The list can be read from standard input 
(keyboard or [file redirection](https://en.wikipedia.org/wiki/Standard_streams)).

The [log](https://en.wikipedia.org/wiki/Logging_\(software\)) of what's going on with the computation
is printed on the standard error output stream,
while the actual numerical output is printed
on the standard output at the end.
This allows to use the app output as input
of a following app, that read from the standard input.
The output created on the standard input and/or
the output created on the standard error 
can be also saved in different text files.

_The following instructions are given supposing 
you're yousing the GNU [gcc](https://gcc.gnu.org/) c language compiler._

### to compile on linux/MacOS/MS-Win+msys2:
make sumean

### to compile on MSwin mingw32:
mingw32-make sumean

### to run on linux/MacOS/MS-Win+msys2
./sumean

### to run on linux/MacOS/MS-Win+msys2
### saving the results on an output file
./sumean >out.asc

### to run on linux/MacOS/MS-Win+msys2 & logging
__saving the instructions on an output file err.log
saving the results on an output file out.asc 
this implies you giving input without hints (blind mode)__

./sumean 2>err.log >out.asc

### to remove all created files in GNU-linux/MacOS/MS-win+msys2
rm sumean.o sumean \*.log \*.asc

### to run on MS-Win cmd shell
sumean

### to remove all created files in MS-Win cmd shell
del sumean.o sumean \*.log \*.asc

### Running the app using file explorer and mouse
### sumeanp.c

the source file sumeanp.c is just the same app code
with added a feature useful to run the app from file explorer
graphical user interface. The p at the end of the
file name means pause. After compiling you can just
click on the sumeanp exe. It is named sumeanp.exe but
take in mind that in MS win file explorer the extension
is written in a different column in the details view,
or you can distinguish the file type from the different
icon.

Just compile the source:

### to compile on GNU-Linux/MacOS:
make sumeanp

### to compile on MS-Win:
mingw32-make sumeanp
