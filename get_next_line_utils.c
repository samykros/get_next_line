/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spascual <spascual@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/1 18:49:27 by spascual           #+#    #+#             */
/*   Updated: 2023/10/1 14:11:37 by spascual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *src)
{
	char	*temp;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (src[len])
		len++;
	temp = (char *)malloc(len * sizeof(char) + 1);
	if (!temp)
		return (NULL);
	while (i < len)
	{
		temp[i] = src[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	strlen;
	size_t	size;
	size_t	i;
	char	*ptr;

	strlen = ft_strlen(s);
	i = 0;
	if (start >= strlen || s[0] == '\0')
		size = 0;
	else
		size = strlen - start;
	if (len >= size)
		ptr = (char *)malloc((size + 1) * sizeof(char));
	else
		ptr = (char *)malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (i < size && i < len)
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	char_c;

	i = 0;
	char_c = (char)c;
	while (str[i])
	{
		if (str[i] == char_c)
			return ((char *) &str[i]);
		i++;
	}
	if (char_c == '\0')
		return ((char *) &str[i]);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = (char *)malloc((ft_strlen(s1)+ ft_strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}