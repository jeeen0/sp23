STATIC_SRCS = static_main.c 
DYNAMIC_SRCS = dynamic_main.c
LIBSRCS = open.c close.c set.c get.c 
STATIC_TARG = kvs_static
DYNAMIC_TARG = kvs_dynamic

CC = gcc
OPTS = -Wall -g
LIBS = -L. -lkvs

STATIC_OBJS = $(STATIC_SRCS:.c=.o)
DYNAMIC_OBJS = $(DYNAMIC_SRCS:.c=.o)
LOBJS = $(LIBSRCS:.c=.o)
STATIC_LARS = libkvs.a
DYNAMIC_LARS = libkvs.so

all: static dynamic

static: $(STATIC_TARG) # make static 실행하면 static 타겟 실행됨 

$(STATIC_TARG) : $(STATIC_OBJS) $(STATIC_LARS)
	$(CC) -o $(STATIC_TARG) $(STATIC_OBJS) $(LIBS) 

$(STATIC_LARS) : $(LOBJS)
	ar rs $(STATIC_LARS) $(LOBJS)

dynamic: $(DYNAMIC_TARG) # make dynamic 실행하면 dynamic 타겟 실행됨

$(DYNAMIC_TARG) : $(DYNAMIC_OBJS) $(DYNAMIC_LARS)
	$(CC) -o $(DYNAMIC_TARG) $(DYNAMIC_OBJS) $(LIBS)

$(DYNAMIC_LARS) : $(LOBJS)
	$(CC) -shared -o $(DYNAMIC_LARS) $(LOBJS)
	
%.o: %.c
	$(CC) $(OPTS) -c $< -o $@

clean: # 모두 제거됨 
	rm -f $(STATIC_OBJS) $(DYNAMIC_OBJS) $(LOBJS) $(STATIC_LARS) $(DYNAMIC_LARS) $(STATIC_TARG) $(DYNAMIC_TARG)  

