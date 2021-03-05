#
# Andrew Kolarits makefiel for Lab3
#

all:  tags headers 

headers: *.c tags
	headers.sh

tags: *.c
	ctags -R .

listproto: listproto.o
	gcc -g -o $@ $^ -L. -lfire -lncurses -llinkedlist

# ***CREATING THE LAB EXECUTABLE***
lab3: lab3.o dynamicMemory.o listMachine.o structures.o output.o skyMath.o bitShifting.o
	gcc -g -o $@ $^ -lncurses -L. -lfire -llinkedlist

# ***PROTOTYPES***

# **GRADE**
# testing bitshifting and masking since did not do it on lab2
shiftMaskTest: shiftMaskTest.o
	gcc -g -o $@ $^ -L. -lfire -lncurses

# **DO NOT GRADE**
# testing the creation, input and output of a struct 
structTest: structTest.o
	gcc -g -o $@ $^ -L. -lfire -lncurses

# **GRADE**
# testing a new scanf loop using firework struct
# as well as passing a pointer of the read struct to a print function
scanfTest: scanfTest.o
	gcc -g -o $@ $^ -L. -lfire -lncurses

# **DO NOT GRADE**
# testing iterate, insert and sort  using the linked list library
lListInsItrTest: lListInsItrTest.o
	gcc -g -o $@ $^ -L. -lfire -lncurses -llinkedlist

# **GRADE**
# testing specifically deleteSome and least, but also with insert and interate.
# using the linked list library
lListLeastDelTest: lListLeastDelTest.o
	gcc -g -o $@ $^ -L. -lfire -lncurses -llinkedlist

# **GRADE**
# testing proper text output using the newly made scanf loop using pointers
textOutputTest: textOutputTest.o
	gcc -g -o $@ $^ -L. -lfire -lncurses

# this is our master compiler rule to generate .o files.
# It needs all 4 warnings

%.o:%.c *.h
	gcc -ansi -pedantic -Wimplicit-function-declaration -Wreturn-type -g -c $< -o $@

# *** BUILDING THE ZIP FILE ***

# build zip file
lab3.zip: makefile README_LAB3 *.c *.h libfire.a liblinkedlist.a
	zip $@ $^
	
	# removing old install folder
	zm -rf unzipTest
	# create new install folder
	mkdir unztipTest
	# unzip to install folder
	unzip lab3.zip -d unzipTest
	# make the lab3 target
	make -C unztipTest lab3
