# Dossiers
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

# Sources et objets
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Compilateur et flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR)
DEPFLAGS = -MMD -MP

# Nom de l'exécutable
NAME = corewar

all: $(NAME)

# Règle de compilation des objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

# Création du dossier obj si nécessaire
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Linking
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Inclusion automatique des dépendances
-include $(OBJS:.o=.d)

# Nettoyage
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
