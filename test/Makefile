#
# Makefile for test
#
# 2014.04.25 W.J@Shanghai
#

MODULE_NAME = test

#CFLAGS = -I 
LDFLAGS = -g -O2 -Wall
LIBS = -lpthread -lm
CC = gcc#arm-none-linux-gnueabi-gcc
LD = $(CC)

DEPEND_FILES = $(patsubst %.c, %.o, $(wildcard *.c))

.PHONY:all clean

all:$(MODULE_NAME)
$(MODULE_NAME):$(DEPEND_FILES)
	@echo "	compile $(MODULE_NAME)"
	@$(LD) $(LDFLAGS) -o $@ $(DEPEND_FILES) $(LIBS)
	
$(DEPEND_FILES):%.o:%.c
#	@echo "	compile $?"
	@$(CC) $(CFLAGS) -c $^
	
clean:
	@echo "	clean $(MODULE_NAME)"
	@rm -f $(MODULE_NAME) *.o
