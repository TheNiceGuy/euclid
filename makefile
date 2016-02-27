ifndef $(CC)
	CC=gcc
endif

ifndef $(LD)
	LD=gcc
endif

ifndef $(DB)
	DB=valgrind
endif

ifndef $(EXECCMD)
	EXECCMD=exec
endif

CCFLAGS+=-I./src/ -Wall -g -D__LINUX__
LDFLAGS+=-lm

EXEC=euclid
BINDIR=/usr/bin
SRCDIR=src

OBJECTS=$(SRCDIR)/main.o \
        $(SRCDIR)/euclid.o

all: $(EXEC)

$(EXEC): $(OBJECTS)
	@printf "\tLD %s\n" bin/$(EXEC)
	@$(LD) -o bin/$(EXEC) $(OBJECTS) $(LDFLAGS)

%.o: %.c
	@printf "\tCC %s\n" $@
	@$(CC) -o $@ -c $< $(CCFLAGS)

mkdir:
	@mkdir -p bin

clean:
	rm -rf $(OBJECTS)
	rm -rf ./bin/$(EXEC)

run: $(EXEC)
	$(EXECCMD) ./bin/$(EXEC) $(ARGS)

debug: $(EXEC)
	$(DB) bin/$(EXEC)
