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
void	fill_null(char **av);
int		check_array(char **av, int n);
void	free_mem(char **av, int i);

void	fill_diagonal(char **diag, int n, char **av, int option);
int		check_diagonal(char **av);

void	fill_diagonal2(char **diag, int n, char **av, int option);
int		check_diagonal2(char **av);

int		find_a(char **av);
int		get_mas(char **av, int i , int j, int option);

int	main()
{
	int sum = 0;
	int sum2 = 0;
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
		sum += check_for_xmas(s);
		fill_array(av, s);		
	}
	fill_null(av);
	sum2 = find_a(av);
	sum += check_array(av, 140);
	sum += check_diagonal(av);
	sum += check_diagonal2(av);
	free_mem(av, 139);
	printf("First answer: %i\n", sum);
	printf("Second answer: %i\n", sum2);
	close(fd);
}

int	find_a(char **av)
{
	int	i;
	int	j;
	int	sum;

	sum = 0;
	i = 1;	
	while (i < 139)
	{
		j = 1;
		while (j < 139)
		{
			if (av[i][j] == 'A')
			{
				if (get_mas(av, i , j, 1) && get_mas(av, i , j, 0))
					sum++;	
			}
			j++;
		}
		i++;		
	}
	return (sum);
}

int	get_mas(char **av, int i , int j, int option)
{
	int c;
	char s1[4];

	c = 0;
	while (c < 3)
	{
		if (option)
		{
			s1[c++] = av[i -1][j +1];
			i++;
			j--;
		}
		else
		{
			s1[c++] = av[i +1][j +1];
			i--;
			j--;
		}
	}
	s1[c] = '\0';
	if (find_xmas(s1, "MAS") || find_xmas(s1, "SAM"))
		return (1);
	return(0);
}

void	fill_null(char **av)
{
	int i = 0;
	while (i < 140)
	{
		av[i][140] = '\0';
		i++;
	}
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
		diag[j][i] = '\0';
	}
	else
	{
		while (i < 140 - n)
		{
			diag[j][i] = av[n + i][i];
			i++;		
		}
		diag[j][i] = '\0';
	}
	j++;
}

int	check_diagonal(char **av)
{
	int sum = 0;
	int j = 3;
	char **diag = create_array(273, 141);
	if (!diag)
		return (0);
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
		diag[j][i] = '\0';
	}
	else
	{
		while (i < n)
		{
			diag[j][i] = av[140 - n + i][139 - i];
			i++;		
		}
		diag[j][i] = '\0';
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