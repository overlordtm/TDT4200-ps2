#Basic makefile. Change name of TARGETS to suit the project.
#Note the -std=c99 flag, and the warning flags -Wall and -pedantic.
#It is strongly recommended that at least -Wall is used, while
#the particular dialect of C and the -pedantic option is up to you.

#Set the compiler. mpicc is a wrapper for compiling MPI programs.
CC=mpicc

#Extra options to the compiler.
CFLAGS+=-std=c99 -Wall -pedantic -O2
#LDFLAGS+=-lm
#All targets listed here.
ALL = pi token

#Build all targets
all: $(ALL)

#Running "make clean" removes the files created above
clean:
	rm -f $(ALL)
