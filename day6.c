/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day6.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 16:45:56 by ruida-si          #+#    #+#             */
/*   Updated: 2024/12/26 16:46:00 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	find_patrol();
void	get_start(int i, int j);
int		check(int i, int j);
int		fill_k(int i, int j);

char av[130][130];
int a = 1;
int p[7000][2];

int main()
{
	int fd = open("input6", O_RDONLY);
	if (fd < 0)
	{
		printf("Could not open file\n");
		return (1);
	}
	int b_read = 1;
	char s[132];
	int i = 0;
	while (b_read)
	{
		b_read = read(fd, s, 131);
		s[130] = '\0';
		int j = 0;
		while (s[j])
		{
			av[i][j] = s[j];
			j++;			
		}
		i++;
	}
	close(fd);
	find_patrol();
	printf("First answer is %i\n", a);
}

void	find_patrol()
{
	int i = 0;
	while (i < 130)
	{
		int j = 0;
		while (j < 130)
		{
			if (av[i][j] == '^')
			{
				get_start(i, j);
			}
			j++;
		}
		i++;
	}
}

void	get_start(int i, int j)
{
	p[0][0] = 0;
	p[0][1] = 0;
	while (check(i, j))
	{
		while (av[i -1][j] != '#' && check(i, j))
		{
			if (fill_k(i -1, j))
				a++;
			i--;
		}
		while (av[i][j +1] != '#' && check(i, j))
		{
			if (fill_k(i, j +1))
				a++;
			j++;
		}
		while (av[i +1][j] != '#' && check(i, j))
		{
			if (fill_k(i +1, j))
				a++;
			i++;
		}
		while (av[i][j -1] != '#' && check(i, j))
		{
			if (fill_k(i, j -1))
				a++;
			j--;
		}
	}	
}

int	fill_k(int i, int j)
{
	static int k;
	int b = k;
	while (b >= 0)
	{
		if (p[b][0] == i && p[b][1] == j)
			return (0);
		b--;
	}
	k++;
	p[k][0] = i;
	p[k][1] = j;
	return (1);
}

int	check(int i, int j)
{
	if (i == 0 || i == 129 || j == 0 || j == 129)
		return (0);
	return (1);
}
