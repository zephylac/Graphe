# Valeurs possibles : yes , no  
DEBUG=yes
# Valeurs possibles : apple , linux 
ARCH=linux

ifeq ($(DEBUG),no)
         CFLAGS=-Wall -g -D_DEBUG_
else
         CFLAGS=-Wall 
endif


ifeq ($(ARCH),apple)

        ifeq ($(DEBUG),yes)
              CFLAGS=-Wall -g -D_DEBUG_ -D_APPLE_
        else
              CFLAGS=-Wall -D_APPLE_
        endif
endif

ifeq ($(ARCH),linux)
        LIBMATH=-lm

        ifeq ($(DEBUG),yes)
              CFLAGS=-Wall -g -D_DEBUG_ -D_LINUX_
        else
              CFLAGS=-Wall -D_LINUX_
        endif
endif

CC = gcc
LDFLAGS = 
 
SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)
AOUT = prog

 
all : $(AOUT) 
 
prog : $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBMATH)
%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<
clean :
	@rm *.o
cleaner : clean
	@rm $(AOUT)
