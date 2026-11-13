/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmesci <fmesci@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 12:23:18 by fmesci            #+#    #+#             */
/*   Updated: 2026/11/13 15:14:54 by fmesci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	count_words(const char *str, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (i == 0 && str[i] != c)
			count++;
		else if (str[i] != c && str[i - 1] == c)
			count++;
		i++;
	}
	return (count);
}

static int	word_len(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	return (i);
}

static char	*create_word(const char *str, char c)
{
	int		len;
	char	*word;
	int		i;

	i = 0;
	len = word_len(str, c);
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (word == NULL)
		return (NULL);
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	free_words(char **arr, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(arr[i]);
		i++;
	}
	free (arr);
}

char	**ft_split(const char *str, char c)
{
	char	**arr;
	int		i;
	int		words;

	words = count_words(str, c);
	i = 0;
	arr = (char **)malloc(sizeof(char *) * (words + 1));
	if (arr == NULL)
		return (NULL);
	while (i < words)
	{
		while (*str == c)
			str++;
		arr[i] = create_word(str, c);
		if (arr[i] == NULL)
		{
			free_words(arr, i);
			return (NULL);
		}
		str += word_len(arr[i], c);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
