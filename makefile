CC = gcc
EXEC = Threads
FILE = writeRandomNumberInFile

all : $(EXEC) $(FILE)
	./$(FILE)

$(EXEC) : Threads.c
	$(CC) -o $(EXEC) Threads.c -lpthread

$(FILE) : writeRandomNumberInFile.c
	$(CC) -o $(FILE) writeRandomNumberInFile.c

clean :
	rm -rf *.o
