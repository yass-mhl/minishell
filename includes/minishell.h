/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:02:21 by ymehlil           #+#    #+#             */
/*   Updated: 2023/03/19 18:37:01 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../ft_printf/ft_printf.h"
# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <unistd.h>

enum				type
{
	NONE,
	ARG,          //word
	FILE_IN,      //word == '<'
	HERE_DOC,     // word == '<<'
	FILE_OUT,     //word == '>'
	FILE_OUT_SUR, //word == '>>'
	OPEN_FILE,    // word following '<'
	LIMITOR,      // word following '<<'
	EXIT_FILE,    // word followinf '>'
	EXIT_FILE_RET // word following '>>'
};

typedef struct token
{
	char			*word;
	enum type		type;
	struct token	*next;
}					t_token;

typedef struct cmd_line
{
	char			*cmd;
	struct token	**token;
	struct cmd_line	*next;
}					t_cmds;

int					main(int ac, char **av, char **env);

void				ft_tokenise(t_cmds **cmd_line);
void				ft_lstadd_back_token(t_token **lst, t_token *new);

char				**ft_dark_split(char *str, char sep);
char				**ft_dark_split_token(char *str);

t_token				**ft_create_token(char *str);
t_token				*ft_lstnew_token(char *word);
t_token				*ft_lstlast_token(t_token *lst);

t_cmds				*ft_create_cmd_line(char *str);
t_cmds				**ft_parse_line(char *str);

char				**ft_dark_split_token(char *str);

#endif
