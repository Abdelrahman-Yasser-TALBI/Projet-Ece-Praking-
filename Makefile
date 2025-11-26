# Makefile pour Parking Intelligent

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I.
TARGET = parking
SOURCES = main.c gestion_voitures.c menu_logique.c statistiques.c
OBJECTS = $(SOURCES:.c=.o)

# Règle par défaut
all: $(TARGET)

# Compilation du programme
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "✅ Compilation réussie ! Lancez avec: ./$(TARGET)"

# Compilation des fichiers objets
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "🧹 Fichiers nettoyés"

# Recompilation complète
rebuild: clean all

# Test rapide
test: all
	./$(TARGET)

# Afficher l'aide
help:
	@echo "Commandes disponibles:"
	@echo "  make         - Compile le programme"
	@echo "  make clean   - Supprime les fichiers compilés"
	@echo "  make rebuild - Recompile tout"
	@echo "  make test    - Compile et lance le programme"

.PHONY: all clean rebuild test help
