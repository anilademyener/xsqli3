CC = gcc
ID = xsqli3
PARAMS = -l sqlite3 -std=c17
MAIN_C = xsqli3.c

build:
	@$(CC) $(MAIN_C) $(PARAMS) -o $(ID).o
