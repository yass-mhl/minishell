#include "../includes/minishell.h"

int nb_words(char *str)
{
	int	i;
	int nw;

	i = 0;
	nw = 0;

	while (str[i])
	{
			while (str[i] && str[i] == ' ')
				i++;
			if (str[i] && str[i] != '<' && str[i] != '>')
				nw++;
			while (str[i] && str[i] != ' ' && str[i] != '>' 
				&& str[i] != '<')
				i++;
			if (str[i] == '<' || str[i] == '>')
				nw++;
			while (str[i] == '<' || str[i] == '>')
				i++;
			printf("%d : %d\n", i,  nw);
	}
	return (nw);
}

int	ft_create_word(char *str, char **tab, int i)
{
	int len;
	int j;
	int k;

	j = 0;
	k = 0;
	len = 0;
	if(*str == '<' || *str == '>')
	{
		while (str[len] == '<' || str[len] == '>')
			len++;
		tab[i] = malloc(sizeof(char) * len + 1);
		while (j < len)
			tab[i][j++] = str[k++];
		tab[i][j] = '\0'; 
	}
	else
	{
		while (str[len] != ' ' && str[len] != '>' 
				&& str[len] != '<')
			len++;
		tab[i] = malloc(sizeof(char) * len + 1);
		while (j < len)
			tab[i][j++] = str[k++];
		tab[i][j] = '\0'; 
	}
	return (len);
}

char **ft_dark_split_token(char *str)
{
	char	**tab;
	int	i;
	int	j;

	i = 0;
	j = 0;
	tab = malloc(sizeof(char *) * nb_words(str));

	while(str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		i += ft_create_word(&str[i], tab, j++);
	}
	tab[j] = NULL;
	return (tab);
}
