# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gansard <gansard@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/17 09:59:39 by ymehlil           #+#    #+#              #
#    Updated: 2023/04/30 20:43:43 by gansard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

SRCS	= minishell.c signal.c\
			builtins/cd.c builtins/echo.c builtins/env.c builtins/init_env.c builtins/pwd.c builtins/utils_env.c builtins/unset.c builtins/export.c builtins/exit.c builtins/env_utils.c builtins/utils_export.c\
			execution/util_exec.c execution/util_exec2.c execution/execution.c execution/redir.c execution/single_exec.c execution/util_exec3.c execution/utils_exec4.c\
			parse/dark_split/dark_utils.c parse/dark_split/dark_split.c parse/dark_split/dark_split_token.c\
			free/free_utils.c free/free.c\
			parse/tokenisation_utils.c parse/parse.c parse/tokenisation.c parse/utils_token.c parse/expend.c parse/args.c parse/here_doc.c parse/expend_util.c parse/here_doc_utils.c parse/expend_d.c parse/here_doc_utils2.c\

SRCSD	= srcs/

OBJSD	= objs/

GNL_PATH	= get_next_line/
GNL_SRCS	= get_next_line.c get_next_line_utils.c 
GNL_OBJS	= $(addprefix $(OBJSD), $(GNL_SRCS:.c=.o))
OBJS	= $(addprefix $(OBJSD), $(SRCS:.c=.o))

LIBFT_A	= libft/libft.a
PRINTF_A = ft_printf/libftprintf.a

CC = cc -c -o
LINKER = cc -o 
FLAGS = -Wall -Wextra -Werror -g3
LIB =  -L/usr/include -lreadline

# Couleurs
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
RESET = \033[0m

ASCII_ART = \
"███╗░░░███╗██╗███╗░░██╗██╗░██████╗██╗░░██╗███████╗██╗░░░░░██╗░░░░░\n████╗░████║██║████╗░██║██║██╔════╝██║░░██║██╔════╝██║░░░░░██║░░░░░\n██╔████╔██║██║██╔██╗██║██║╚█████╗░███████║█████╗░░██║░░░░░██║░░░░░\n██║╚██╔╝██║██║██║╚████║██║░╚═══██╗██╔══██║██╔══╝░░██║░░░░░██║░░░░░\n██║░╚═╝░██║██║██║░╚███║██║██████╔╝██║░░██║███████╗███████╗███████╗\n╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝╚═════╝░╚═╝░░╚═╝╚══════╝╚══════╝╚══════╝"\

all: $(NAME)
	@echo "$(GREEN)Compilation réussie!$(RESET)"
	@echo $(ASCII_ART)

#...

$(LIBFT_A):
	@echo "$(YELLOW)Compilation de libft...$(RESET)"
	@make -C libft > /dev/null
	@echo "$(GREEN)Libft compilé avec succès!$(RESET)"

$(PRINTF_A):
	@echo "$(YELLOW)Compilation de ft_printf...$(RESET)"
	@make -C ft_printf > /dev/null
	@echo "$(GREEN)Ft_printf compilé avec succès!$(RESET)"

$(NAME): $(OBJS) $(PRINTF_A) $(GNL_OBJS) $(LIBFT_A) 
	@$(LINKER) $@ $^ $(LIB) > /dev/null
	@echo "$(CYAN)[$(NAME)]$(RESET) $(GREEN)Liaison des objets réussie.$(RESET)"

$(OBJSD)%.o: $(SRCSD)%.c
	@mkdir -p $(dir $@) > /dev/null
	@echo "$(CYAN)[$@]$(RESET) $(BLUE)Compilation...$(RESET)" 
	@$(CC) $@ $^ $(FLAGS) > /dev/null

$(OBJSD)%.o: $(GNL_PATH)%.c
	@echo "$(CYAN)[$@]$(RESET) $(BLUE)Compilation...$(RESET)"
	@$(CC) $@ $< $(FLAGS) > /dev/null

clean:
	@rm -rf $(OBJSD) > /dev/null
	@make -C libft clean > /dev/null
	@make -C ft_printf clean > /dev/null
	@echo "$(MAGENTA)Suppression des fichiers objets terminée.$(RESET)"

fclean: clean
	@make -C libft fclean > /dev/null
	@make -C ft_printf fclean > /dev/null
	@rm -rf $(NAME) > /dev/null
	@echo "$(MAGENTA)Nettoyage complet effectué.$(RESET)"
	
re: fclean all

.PHONY: all clean fclean re
