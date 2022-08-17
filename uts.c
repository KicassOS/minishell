
#include "pipex.h"
#include "libft.h"
#include <stdio.h>
char	*path_join (char *path, char *bin)
{
	char	*joined;
	int		i;
	int		j;

	joined = malloc(sizeof(char) * (str_ichr(path, 0) + str_ichr(bin, 0) + 2));
	i = 0;
	j = 0;
	while (path[j])
		joined[i++] = path[j++];
	joined[i++] = '/';
	j = 0;
	while (bin[j])
		joined[i++] = bin[j++];
	joined[i] = 0;
	return (joined);
}

int	str_ncmp (char *str1, char *str2, int n)
{
	while (--n > 0 && *str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*str2 - *str1);
}

int	str_ichr (char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (i);
	return (-1);
}

char	*str_ndup (char *str, unsigned int n)
{
	char				*duped;
	unsigned int		i;
	unsigned int		j = 0;

	i = 0;
	duped = malloc(sizeof(char) * (n + 1));
	while (i < n)
	{
		if (str[i] != ' ')
		{
			duped[j] = str[i];
			j++;
		}
		i++;
	}
	duped[n] = 0;
	return (duped);
}

/*char	**str_split (char *str, char sep)
{
	char	**tab;
	int		count;
//	int		i;
	int		j;
//	int		s;
	(void) sep;
	count = 0;
	j = 0;
//	while (str[j] && str[j] == ' ')
//		j++;
	tab = ft_split(str, ' ');
	while (str[j])
	{
		if (str[j++] == sep)
			count++;
	}
//	printf("str = %s", str);
//	printf("count = %d\n", count);
//	if (str[j - 1] == sep)
//		count--;
///	if (str[0] == sep)
//		count--;
	tab = malloc(sizeof(char *) * (count + 2));
	tab[count + 1] = NULL;
	i = 0;
	while (i < count + 1)
	{
		j = 0;
		while (str[j] && str[j] == ' ')
			str++;
		while (str[j] && str[j] != sep)
		{
//			s++;
			j++;
		}
		tab[i++] = str_ndup(str, j);
		str = str + j;
	}
	return (tab);
}*/
