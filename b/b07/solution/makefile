CC = gcc

SANITIZERS = -fsanitize=address -fsanitize=undefined

CFLAGS = -Wall -O2 -Werror -std=gnu11 -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op -Wstrict-prototypes -Wold-style-declaration -Wold-style-definition -Wmissing-parameter-type -Wmissing-field-initializers -Wnested-externs -Wno-pointer-sign -ftrapv $(SANITIZERS)

LDFLAGS = $(SANITIZERS) -lm

EXEC = solution

all: $(EXEC)

$(EXEC): stack.o poliz.o $(EXEC).o

clean:
		rm -f $(EXEC) *.o

test:
		echo Running $(EXEC) ...
			./$(EXEC)

# phony target is not a file in file system, always execute it
# .PHONY: clean
