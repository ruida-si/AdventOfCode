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

void	get_numbers(char *s, int *i, int *j);
void	get_numbers2(int fd);
void	fill_zero(int **p);

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
		get_numbers(s, &p[i][0], &p[i][1]);
		i++;
	}
	get_numbers2(fd);
	close(fd);
}

void	get_numbers(char *s, int *i, int *j)
{
	while (*s)
	{
		*i = 0;
		*j = 0;
		while (*s >= '0' && *s <= '9')
		{			
			*i = *i * 10 + (*s - '0');
			s++;
		}
		s++;
		while (*s >= '0' && *s <= '9')
		{			
			*j = *j * 10 + (*s - '0');
			s++;
		}
	}
}

void	get_numbers2(int fd)
{
	int b_read = 1;
	char s[70];
	char p[210][70];
	int j = 0;
	while (b_read)
	{
		b_read = read(fd, s, 69);
		if (b_read <= 0)
			break ;
		int i = 0;
		static int k;		
		while (s[i])
		{
			if (s[i] != '\n')
			{	
				p[j][k] = s[i];
				k++;
				i++;
			}
			else
			{
				p[j][k] = '\0';
				j++;
				k = 0;
				i++;
			}					
		}
	}
	printf(".%s.\n", p[0]);
}

void	fill_zero(int **p)
{
	int i = 0;
	int j;
	while (i < 210)
	{
		j = 0;
		while (j < 23)
		{
			p[i][j] = 0;
			j++;
		}
		i++;
	}
}
