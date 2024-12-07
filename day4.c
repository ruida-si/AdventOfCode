/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 16:57:25 by ruida-si          #+#    #+#             */
/*   Updated: 2024/12/07 16:57:29 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int		check_for_xmas(char *s);
int		look_horizontal(char *s, char *xmas, char *xmas2);
int		find_xmas(char *s, char *xmas);
char	**create_array();
void	fill_vertical(char **av, char *s);
void	free_mem(char **av, int i);
int		check_vertical(char **av);

int	main()
{
	int sum = 0;
	int fd = open("input4", O_RDONLY);
	if (fd < 0)
	{
		printf("Could not open file\n");
		return (1);		
	}
	char s[142];
	int b_read = 1;
	char **av = create_array();
	if (!av)
		return (1);
	while (b_read)
	{
		b_read = read(fd, s, 141);
		if (b_read <= 0)
			break ;
		s[b_read] = '\0';
		sum += check_for_xmas(s);
		fill_vertical(av, s);
	}
	sum += check_vertical(av);
	free_mem(av, 139);
	printf("%i\n", sum);
	close(fd);
}

int	check_vertical(char **av)
{
	int sum = 0;
	int i = 0;
	while (i < 140)
	{
		sum += check_for_xmas(av[i]);
		i++;
	}
	return (sum);
}

char **create_array()
{
	int i = 0;
	char **av = malloc(141 * sizeof(char *));
	if (!av)
		return (NULL);
	while (i < 140)
	{
		av[i] = malloc(141);
		if (!av[i])
		{
			free_mem(av, i -1);
			return (NULL);
		}
		i++;
	}
	return (av);
}

int	check_for_xmas(char *s)
{
	int sum = 0;
	char xmas[5] = "XMAS";
	char xmas2[5] = "SAMX";
	sum += look_horizontal(s, xmas, xmas2);
	return (sum);
}

void	fill_vertical(char **av, char *s)
{
	int i = 0;
	static int n;
	
	while (i < 140)
	{
		av[i][n] = s[i];
		i++;
	}
	n++;
}

void	free_mem(char **av, int i)
{
	while (i >= 0)
	{
		free(av[i]);
		i--;
	}
	free(av);
}

int	look_horizontal(char *s, char *xmas, char *xmas2)
{
	int sum = 0;
	while (*s)
	{
		if (find_xmas(s, xmas) || find_xmas(s, xmas2))
			sum += 1;
		s++;
	}
	return (sum);
}

int	find_xmas(char *s, char *xmas)
{
	int i = 0;
	while (xmas[i] && s[i] && xmas[i] == s[i])
	{
		i++;
	}
	if (!xmas[i])
		return (1);
	return (0);
}