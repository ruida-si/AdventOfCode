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

int	get_line(char *s);
int	check_mult(char *s);
int	get_numbers(char *s, int *i);
int	compare(char *comp, char *s);

int	main()
{
	int sum = 0;
	char s[21];
	int fd = open("input3", O_RDONLY);
	if (fd < 0)
	{
		printf("Could not open the file\n");
		return (1);		
	}
	int b_read = 1;
	while (b_read)
	{
		b_read = read(fd, s, 20);
		if (b_read <= 0)
			break ;
		sum += get_line(s);
	}
	printf("%i\n", sum);
	close(fd);
}

int	get_line(char *s)
{
	int sum = 0;
	int j = 0;
	char mult[13];
	static int i;
	while (s[j])
	{
		if (s[j] == 'm' || i > 0)
		{
			int a = j;
			while (s[a] && i < 12)
			{
				mult[i] = s[a];
				i++;
				a++;
			}
			if (i == 12)
			{
				sum += check_mult(mult);
				i = 0;
				j++;
			}
		}
		else
			j++;
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
	while (comp[i] && comp[i] == s[i])
		i++;
	if (!comp[i])
		return (1);
	else
		return (0);
}