#SRCS = $(wildcard *.c)
VPATH = $(shell ls -AxR ./ | grep ":" | grep -v "\.svn" | tr -d ':')
SOURCEDIRS = $(VPATH)
SRCS =  $(foreach subdir,$(SOURCEDIRS),$(wildcard $(subdir)/*.c))
OBJS = $(SRCS:.c=.o)
CC = gcc
CC_SRCS =  $(foreach subdir,$(SOURCEDIRS),$(wildcard $(subdir)/*.cc))
OBJS += $(CC_SRCS:.cc=.o)
CCP = g++
INCLUDES = -I./cjson -I./include 
LIBS = -lz -ldl -lstdc++ -lm -lpthread    -lrt  -L ./ 
STATIC_LIBS =  
CCFLAGS = -g -Wall -O0

test : $(OBJS)
	@$(CC) $^ -o $@ $(INCLUDES) $(LIBS) $(STATIC_LIBS)

%.o : %.c
	@$(CC) -c $< $(CCFLAGS) -o $@ $(INCLUDES)

%.o : %.cc
	@$(CC) -c $< $(CCFLAGS) -o $@ $(INCLUDES) $(LIBS)
	
clean:
	@-rm $(OBJS) test
	
.PHONY:clean
