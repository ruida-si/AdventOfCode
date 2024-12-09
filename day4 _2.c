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
int		find_xmas(char *s, char *xmas);
char	**create_array(int array, int n);
void	fill_array(char **av, char *s);
void	free_mem(char **av, int i);
int		check_array(char **av, int n);
void	fill_diagonal(char **diag, int n, char **av, int option);
int		check_diagonal(char **av);
int		check_diagonal2(char **av);
void	fill_diagonal2(char **diag, int n, char **av, int option);

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
	char **av = create_array(140, 141);
	if (!av)
		return (1);
	while (b_read)
	{
		b_read = read(fd, s, 141);
		if (b_read <= 0)
			break ;
		s[140] = '\0';
		fill_array(av, s);
	}
	sum += check_diagonal2(av);
	free_mem(av, 139);
	printf("%i\n", sum);
	close(fd);
}

int	check_diagonal2(char **av)
{
	int sum = 0;
	char **diag = create_array(273, 141);
	if (!diag)
		return (0);
	int j = 136;
	while (j >= 0)
	{
		fill_diagonal2(diag, j, av, 1);
		j--;
	}
	j = 1;
	while (j < 137)
	{
		fill_diagonal2(diag, j, av, 2);
		j++;
	}
	sum = check_array(diag, 273);
	free_mem(diag, 272);
	return (sum);
}

void	fill_diagonal2(char **diag, int n, char **av, int option)
{
	static int j;
	int i = 0;
	if (option == 1)
	{		
		while (i < 140 - n)
		{
			diag[j][i] = av[i][n + i];
			i++;
		}
	}
	else
	{
		while (i < 140 - n)
		{
			diag[j][i] = av[n + i][i];
			i++;		
		}
	}
	j++;
}

int	check_diagonal(char **av)
{
	int sum = 0;	
	char **diag = create_array(273, 141);
	if (!diag)
		return (0);
	int j = 3;
	while (j < 140)
	{
		fill_diagonal(diag, j, av, 1);
		j++;
	}
	j = 139;
	while (j > 3)
	{
		fill_diagonal(diag, j, av, 2);
		j--;
	}
	sum = check_array(diag, 273);
	free_mem(diag, 272);
	return (sum);
}

void	fill_diagonal(char **diag, int n, char **av, int option)
{
	static int j;
	int i = 0;
	if (option == 1)
	{		
		while (i <= n)
		{
			diag[j][i] = av[i][n - i];
			i++;
		}
	}
	else
	{
		while (i < n)
		{
			diag[j][i] = av[140 - n + i][139 - i];
			i++;		
		}
	}
	j++;
}

int	check_array(char **av, int n)
{
	int sum = 0;
	int i = 0;
	while (i < n)
	{
		sum += check_for_xmas(av[i]);
		i++;
	}
	return (sum);
}

char **create_array(int array, int n)
{
	int i = 0;
	char **av = malloc(array * sizeof(char *));
	if (!av)
		return (NULL);
	while (i < array)
	{
		av[i] = malloc(n);
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
	while (*s)
	{
		if (find_xmas(s, xmas) || find_xmas(s, xmas2))
		{
			sum += 1;
		}
		s++;
	}
	return (sum);
}

void	fill_array(char **av, char *s)
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