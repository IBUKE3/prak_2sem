CC = gcc
CFLAGS = -Wall -Werror -std=c11 -fsanitize=undefined,address -lm -MMD
# -MMD: Генерировать .d файлы с зависимостями в процессе компиляции

# CFLAGS = -Wall -O2 -Werror -std=c11 -fsanitize=undefined,address -ftrapv -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op -Wstrict-prototypes -Wold-style-declaration -Wold-style-definition -Wmissing-parameter-type -Wmissing-field-initializers -Wnested-externs -Wno-pointer-sign -lm -MMD

TARGET = my_program
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

-include $(DEPS)

clean:
	rm -f $(OBJS) $(TARGET) $(DEPS)

.PHONY: clean
