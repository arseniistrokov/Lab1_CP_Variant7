# Сборка программ лабораторной работы №1 (Вариант 7)
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2
LDFLAGS = -lm

all: my ai

my: step1/my/my.c
	$(CC) $(CFLAGS) step1/my/my.c -o step1/my/my $(LDFLAGS)

ai: step1/ai/ai.c
	$(CC) $(CFLAGS) step1/ai/ai.c -o step1/ai/ai $(LDFLAGS)

clean:
	rm -f step1/my/my step1/ai/ai
