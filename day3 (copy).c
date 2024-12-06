/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:47:39 by ruida-si          #+#    #+#             */
/*   Updated: 2024/12/05 14:47:41 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int		get_line(char *s);
int		check_mult(char *s);
int		get_numbers(char *s, int *i);
int		compare(char *comp, char *s);
char	*copy_last(char *s);
char	*join(char *last, char *s);
int		get_string(char *s, char *last, char *last2, int *sum2);
int		get_do(char *s, char *comp, int *i);
char	*copy_last2(char *s);

int	main()
{
	int sum = 0;
	int sum2 = 0;
	char s[31];
	int fd = open("input3", O_RDONLY);
	if (fd < 0)
	{
		printf("Could not open the file\n");
		return (1);
	}
	int b_read = 1;
	char *last = NULL;
	char *last2 = NULL;
	while (b_read)
	{
		b_read = read(fd, s, 30);
		if (b_read <= 0)
			break ;
		s[b_read] = '\0';
		sum += get_string(s, last, last2, &sum2);
		last = copy_last(s);
		last2 = copy_last2(s);
	}
	free(last);
	free(last2);
	printf("%i\n", sum);
	printf("%i\n", sum - sum2);
	close(fd);
}

char *copy_last2(char *s)
{
	char *last = malloc(7);
	if (!last)
		return (NULL);
	int i = 14;
	int j = 0;
	while(s[i])
	{
		last[j++] = s[i++];
	}
	last[j] = '\0';
	return (last);
}

int	get_do(char *s, char *comp, int *i)
{
	while (s[*i])
	{
		if (s[*i] == 'd')
		{
			if (compare(comp, &s[*i]))
				return (1);
		}
		(*i)++;
	}
	return (0);
}

int	get_string(char *s, char *last, char *last2, int *sum2)
{
	int i = 0;
	int sum = 0;
	static int n;
	static int dont = 0;
	char *dest = NULL;
	char *dest2 = NULL;

	if (!n)
	{
		sum += get_line(s);
		n = 1;
	}
	else
	{
		dest = join(last, s);
		dest2 = join(last2, s);
		sum += get_line(dest);
		if (dont)
		{
			*sum2 += sum;
		}
		if (get_do(dest2, "don't()", &i))
		{
			*sum2 += get_line(dest2+i);
			dont = 1;
		}		
		if (get_do(dest2, "do()", &i))
		{
			dont = 0;
			dest2[i] = '\0';
			*sum2 += get_line(dest);
		}		
		free(dest);
		free(dest2);
		free(last);
		free(last2);
	}	
	return (sum);
}

char *copy_last(char *s)
{
	char *last = malloc(12);
	if (!last)
		return (NULL);
	int i = 19;
	int j = 0;
	while(s[i])
	{
		last[j++] = s[i++];
	}
	last[j] = '\0';
	if (check_mult(last))
	{
		last[0] = '\0';
	}
	return (last);
}

char *join(char *last, char *s)
{
	char *dest = malloc(42);
	if (!dest)
		return (NULL);
	int i = 0;
	while (*last)
	{
		dest[i++] = *last++;
	}
	while (*s)
	{
		dest[i++] = *s++;
	}
	dest[i] = '\0';
	return (dest);
}

int	get_line(char *s)
{
	int sum = 0;
	while (*s)
	{
		if (*s == 'm')
			sum += check_mult(s);
		s++;
	}
	return (sum);
}

int	check_mult(char *s)
{
	int n;
	int n2;
	char comp[5] = "mul(";
	if (!compare(comp, s))
		return (0);
	int i = 4;
	n = get_numbers(s, &i);
	if (n == 0)
		return (0);
	if (s[i] != ',')
		return (0);
	i++;
	n2 = get_numbers(s, &i);
	if (n2 == 0)
		return (0);
	if (s[i] != ')')
		return (0);
	return (n * n2);
}

int	get_numbers(char *s, int *i)
{
	int n = 0;
	while (s[*i] && s[*i] >= '0' && s[*i] <= '9')
	{
		n = n * 10 + (s[*i] - '0');
		(*i)++;
	}
	return (n);
}

int	compare(char *comp, char *s)
{
	int i = 0;
	while (comp[i] && s[i] && comp[i] == s[i])
		i++;
	if (!comp[i])
		return (1);
	else
		return (0);
}