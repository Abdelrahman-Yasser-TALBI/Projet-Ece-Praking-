CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = parking_final.exe
# On liste ici les 4 fichiers .c
SRC = main.c gestion.c files_stats.c menu.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)
	@echo Compilation OK. Lancez avec: make run

run: all
	./$(TARGET)

clean:
	@if exist $(TARGET) del /Q $(TARGET)
	@echo Nettoyage OK.

reset:
	@if exist parking.txt del /Q parking.txt
	@echo Donnees effacees.