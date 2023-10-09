CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
SOURCES = my_mastermind.c
TARGET = my_mastermind

$(TARGET):$(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: fclean

fclean:
	@rm -r $(TARGET)