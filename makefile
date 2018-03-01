############################
# Project: num2cast_3.0     #
############################

####################
# Variables        #
####################

INCS     = -I.
SRCS     = ./num2cast.c ./num2cast.h
OBJS     = ./num2cast.o 
LIBS     = 
BINS     = ./num2cast.a
EXES     = ./clinum
SRCEXE   = ./cliente.c

RM       = rm -f
CC       = gcc
CFLAGS   = -Wall -O2 -D no__DEBUG
LD       = gcc
LFLAGS   =    
#-lm

####################
# Rules            #
####################

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BINS) $(EXES) all-after

clean: clean-custom
	${RM} $(OBJS) $(BINS)

$(BINS): $(OBJS)
	ar cr $(BINS) $(OBJS)
	ranlib $(BINS)

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) $(INCS) -c $(SRCS) $(LFLAGS)

$(EXES): $(BINS) $(SRCEXE)
	gcc $(SRCEXE) -o $(EXES) -I. -L. $(BINS)
