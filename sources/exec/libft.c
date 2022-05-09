
#include "pruebas_bash.h"

size_t	ft_strlen(const char *s)
{
	int	c;

	c = 0;
	while (s[c] != 0)
		c++;
	return (c);
}

void print_error(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

char	*ft_strdup(const char *s1)
{
	char	*cpy;
	int		i;

	cpy = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (cpy == NULL)
		return (cpy);
	i = 0;
	while (s1[i])
	{
		cpy[i] = s1[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}


size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (!src || !dst)
		return (0);
	if (dstsize == 0)
		return (ft_strlen(src));
	i = 0;
	while (i < (dstsize - 1) && src[i] != 0)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}


size_t	ft_count_strings(char const *s, char c)
{
	int		new_str;
	size_t	str_n;

	new_str = 0;
	str_n = 0;
	while (*s)
	{
		if (*s != c && new_str == 0)
		{
			new_str = 1;
			str_n++;
		}
		else if (*s == c)
			new_str = 0;
		s++;
	}
	return (str_n);
}

size_t	ft_count_chrs(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (*s && *s++ != c)
		len++;
	return (len);
}

void	ft_free_tab(char **tab, size_t n)
{
	if (!tab[n])
	{
		while (n > 0)
			free(tab[n--]);
		free(tab);
	}
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	str_n;
	size_t	n;
	size_t	len;

	if (!s)
		return (0);
	str_n = ft_count_strings(s, c);
	split = malloc(sizeof(char *) * (str_n + 1));
	if (split == NULL)
		return (split);
	n = 0;
	while (n < str_n)
	{
		while (*s == c)
			s++;
		len = ft_count_chrs(s, c);
		split[n] = malloc(sizeof(char) * (len + 1));
		ft_free_tab(split, n);
		ft_strlcpy(split[n], s, len + 1);
		s = s + len;
		n++;
	}
	split[str_n] = 0;
	return (split);
}


int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n)
	{
		if (s1[i] == s2[i] && s1[i] != 0 && s2[i] != 0)
			i++;
		else
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}


t_def	*ft_lstnew(void *content, int *array)
{
	t_def	*a;

	a = malloc(sizeof(t_def));
	if (a == 0)
		return (0);
	a->argv = ft_split(content, ' ');
	a->type = array;
	a->next = 0;
	return (a);
}


void	ft_lstadd_back(t_def **lst, t_def *new)
{
	t_def	*p;

	if (!*lst)
		*lst = new;
	else
	{
		p = ft_lstlast(*lst);
		p -> next = new;
	}
}

t_def	*ft_lstlast(t_def *lst)
{
	if (!lst)
		return (0);
	while (lst -> next)
		lst = lst -> next;
	return (lst);
}

int	ft_lstsize(t_def *lst)
{
	int	i;

	i = 1;
	if (!lst)
		return (0);
	while (lst -> next)
	{
		lst = lst -> next;
		i++;
	}
	return (i);
}
