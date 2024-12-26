/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day5.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:44:31 by ruida-si          #+#    #+#             */
/*   Updated: 2024/12/24 16:44:33 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void	get_numbers(char *s, int p[1176][2], int i);

void	second_parsing(int fd);
void	get_string(char *s);
void	get_numbers2();

void	check_numbers(int p[1176][2]);
int		check_order(int i, int j, int p[1176][2]);
int		count(int i);

char str[211][70];
int p2[210][24];
int sum = 0;

int main()
{
	int fd = open("input5", O_RDONLY);
	if (fd < 0)
	{
		printf("FILE not found\n");
		return (1);
	}
	int b_read = 1;
	char s[7];
	int p[1176][2];
	int i = 0;
	while (b_read && i < 1176)
	{
		b_read = read(fd, s, 6);
		s[5] = '\0';
		get_numbers(s, p, i);
		i++;
	}
	second_parsing(fd);
	close(fd);
	get_numbers2();
	check_numbers(p);	
	printf("First answer is %i\n", sum);
}

void	get_numbers(char *s, int p[1176][2], int i)
{
	while (*s)
	{
		p[i][0] = 0;
		p[i][1] = 0;
		while (*s >= '0' && *s <= '9')
		{			
			p[i][0] = p[i][0] * 10 + (*s - '0');
			s++;
		}
		s++;
		while (*s >= '0' && *s <= '9')
		{			
			p[i][1] = p[i][1] * 10 + (*s - '0');
			s++;
		}
	}
}

void	check_numbers(int p[1176][2])
{
	int i = 0;
	while (i < 210)
	{
		int j = 0;
		int flag = 0;	
		while (p2[i][j] != 0)
		{
			if (!check_order(i, j, p))
			{
				flag = 1;
				break ;
			}			
			j++;
		}
		if (!flag)
			sum += count(i);
		i++;
	}	
}

int	count(int i)
{
	int j = 0;

	while (p2[i][j] != 0)
		j++;
	int a = j / 2;
	return (p2[i][a]);
}

int	check_order(int i, int j, int p[1176][2])
{
	int c = j +1;
	while (p2[i][c] != 0)
	{
		int k = 0;
		while (k < 1176)
		{
			if (p[k][0] == p2[i][c] && p[k][1] == p2[i][j])
				return (0);
			k++;
		}
		c++;
	}
	return (1);
}

void	get_numbers2()
{
	int i = 1;
	while (i < 211)
	{
		int j = 0;
		int k = 0;
		while (str[i][j])
		{			
			p2[i -1][k] = 0;			
			while (str[i][j] >= '0' && str[i][j] <= '9')
			{
				p2[i -1][k] = p2[i -1][k] * 10 + (str[i][j] - '0');
				j++;
			}
			k++;
			j++;
		}
		p2[i -1][k] = 0;
		i++;
	}
}

void	second_parsing(int fd)
{
	int b_read = 1;
	char s[70];	
	while (b_read)
	{
		b_read = read(fd, s, 69);
		if (b_read <= 0)
			break ;
		s[b_read] = '\0';
		get_string(s);
	}
}

void	get_string(char *s)
{
	static int j;
	static int k;
	int i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
		{	
			str[j][k] = '\0';
			k = 0;
			j++;
		}
		else
		{
			str[j][k] = s[i];
			k++;
		}
		i++;				
	}
}
