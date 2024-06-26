# Project name
NAME = minishell

# Readline name
READLINE = readline

# Compilator
CC = cc

# Compilator flags
INC_DIRS = -I./includes -I./$(LIBS_DIR)/$(READLINE)/include
CFLAGS = -Wall -Wextra -Werror $(INC_DIRS) #-g3 -fsanitize=address

# Libraries
LIBS_DIR = libraries
READLINE_LIB_PATH = $(LIBS_DIR)/readline/lib

# Headers
HEADERS = 	includes/minishell.h \
			includes/tokenization.h \
			includes/utilities.h \
			includes/builtin.h \
			includes/syntaxer.h \
			includes/executor.h \
			includes/pipex.h

# Source directory
SRCS_DIR = sources/

# Objects directory
OBJS_DIR = objects/

# Source file names
SRCS_NAME = minishell.c \
			tokenization/tokenization.c \
			tokenization/token_type_defining.c \
			tokenization/tokens_list_utils.c \
			tokenization/tokens_splitting.c \
			syntaxer/validation.c \
			syntaxer/quoter.c \
			syntaxer/quoter_2.c \
			syntaxer/quoter_3.c \
			utilities/utilities_1.c \
			utilities/utilities_2.c \
			utilities/utilities_3.c \
			utilities/utilities_4.c \
			utilities/utilities_5.c \
			utilities/utilities_6.c \
			utilities/pipex_utils1.c \
			utilities/pipex_utils2.c \
			utilities/split.c \
			environment/environment.c \
			builtin/export.c \
			builtin/export_2.c \
			builtin/export_3.c \
			builtin/export_4.c \
			builtin/pwd.c \
			builtin/cd.c \
			builtin/cd_1.c \
			builtin/exit.c \
			builtin/echo.c \
			executor/executor.c \
			executor/tokens_to_cmds.c \
			executor/signals.c \
			pipex/pipex.c \
			pipex/pipes.c \
			pipex/processes.c
			

# Objects file names
OBJS = $(addprefix $(OBJS_DIR), $(OBJS_NAME))
OBJS_NAME = $(SRCS_NAME:.c=.o)

# Compilation process
all: $(LIBS_DIR)/$(READLINE) $(NAME)

linux_minishell: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -l$(READLINE)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -l$(READLINE) -L$(READLINE_LIB_PATH)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADERS) Makefile
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/tokenization
	@mkdir -p $(OBJS_DIR)/utilities
	@mkdir -p $(OBJS_DIR)/environment
	@mkdir -p $(OBJS_DIR)/builtin
	@mkdir -p $(OBJS_DIR)/syntaxer
	@mkdir -p $(OBJS_DIR)/executor
	@mkdir -p $(OBJS_DIR)/pipex
	$(CC) $(CFLAGS) -c $< -o $@

# Configuring readline
$(LIBS_DIR)/$(READLINE):
	./$(LIBS_DIR)/config_readline readline

# Cleaning
clean:
	@$(RM) $(OBJS)

# Force cleaning
fclean: clean
	@$(RM) $(NAME)
	@$(RM) linux_minishell
	rm -rf $(LIBS_DIR)/$(READLINE)
	rm -rf $(OBJS_DIR)
	make clean -C $(LIBS_DIR)/readline-8.2

# Remaking
re: fclean all

# PHONY files
.PHONY: all clean fclean re
