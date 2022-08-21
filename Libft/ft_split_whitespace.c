#include "libft.h"

static size_t	ft_word_count(char const *s)
{
	size_t	word_count;
	size_t	i;

	word_count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] && ft_is_space(s[i]))
			i++;
		if (s[i] && !ft_is_space(s[i]))
		{
			word_count++;
			while (s[i] && !ft_is_space(s[i]))
				i++;
		}
	}
	return (word_count);
}

static char	*ft_alloc_and_copy_str(char const *s)
{
	char	*str;
	size_t	i;

	i = 0;
	while (s[i] && !ft_is_space(s[i]))
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s, i + 1);
	return (str);
}

static void	ft_free_all_substrs(char **strings_ptr, size_t current_index)
{
	if (!strings_ptr)
		return ;
	if (current_index == 0)
	{
		free(strings_ptr);
		return ;
	}
	while (current_index > 0)
	{
		current_index--;
		free(strings_ptr[current_index]);
	}
	free(strings_ptr);
}

char	**ft_split_whitespace(char *s)
{
	char		**strings;
	size_t		i;
	size_t		strings_length;

	if (!s)
		return (NULL);
	strings_length = ft_word_count(s);
	strings = malloc(sizeof(char *) * (strings_length + 1));
	if (!strings)
		return (NULL);
	i = -1;
	while (++i < strings_length)
	{
		while (ft_is_space(*s))
			s++;
		strings[i] = ft_alloc_and_copy_str(s);
		if (!strings[i])
		{
			ft_free_all_substrs(strings, i);
			return (NULL);
		}
		s += ft_strlen(strings[i]);
	}
	strings[i] = NULL;
	return (strings);
}