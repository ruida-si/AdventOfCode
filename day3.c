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
int		get_string(char *s, char *last, int *sum2);
int		check_dont(char *dest, char *comp, int *sum2, int index);

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
	while (b_read)
	{
		b_read = read(fd, s, 30);
		if (b_read <= 0)
			break ;
		s[b_read] = '\0';
		sum += get_string(s, last, &sum2);
		last = copy_last(s);
	}
	free(last);
	printf("\033[1;32mFirst answer:\033[0m %i\n", sum);
	printf("\033[1;32mSecond answer:\033[0m %i\n", sum - sum2);
	close(fd);
}

int	get_string(char *s, char *last, int *sum2)
{
	int sum = 0;
	static int n;
	static int dont;
	char *dest = NULL;

	if (!n)
	{
		sum += get_line(s);
		n = 1;
	}
	else
	{
		dest = join(last, s);
		sum += get_line(dest);
		if (dont)
		{
			if(check_dont(dest, "do()", sum2, 1))
				dont = 0;
			*sum2 += sum;
		}
		else
		{
			if (check_dont(dest, "don't()", sum2, 2))
				dont = 1;
		}
		free(dest);
		free(last);
	}
	return (sum);
}

int	check_dont(char *dest, char *comp, int *sum2, int index)
{
	while (*dest)
	{
		if (compare(comp, dest))
		{
			if (index == 2)
				*sum2 += get_line(dest);
			if (index == 1)
				*sum2 -= get_line(dest);
			return (1);
		}
		dest++;
	}
	return (0);
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
	if (get_line(last))
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