/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:53:06 by ruida-si          #+#    #+#             */
/*   Updated: 2024/12/04 12:53:09 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

void	fill_zero(int *numbers);
void	get_line(char *s, char **av);
void	allocate(char **av);
int		get_numbers(char **av, int *sum2);
int		check_numbers(int *numbers);
int		increase(int *numbers, int i);
int		decrease(int *numbers, int i);
void	free_mem(char **av, int i);
int		double_check(int *numbers);

int main()
{
	char s[25];
	int fd = open("input2", O_RDONLY);
	if (fd < 0)
	{
		printf("Open fd error\n");
		return (1);
	}
	char **av = malloc(sizeof(char *) * 1000);
	if (!av)
		return (1);
	allocate(av);
	int b_read = 1;
	while (b_read)
	{
		b_read = read(fd, s, 24);
		if (b_read <= 0)
			break ;
		s[b_read] = '\0';
		get_line(s, av);
	}
	close(fd);
	int sum2 = 0;
	int sum = get_numbers(av, &sum2);
	printf("First answer: %i\n", sum);
	printf("Second answer: %i\n", sum2 + sum);
	free_mem(av, 999);
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

int	get_numbers(char **av, int *sum2)
{
	int i = 0;
	int sum = 0;
	int numbers[10];
	fill_zero(numbers);
	while (i < 1000)
	{
		int j = 0;
		int k = 0;
		while (av[i][k])
		{
			int n = 0;
			while (av[i][k] >= '0' && av[i][k] <= '9')
			{
				n = n * 10 + (av[i][k] - '0');
				k++;
			}
			numbers[j] = n;
			j++;
			k++;
		}
		sum += check_numbers(numbers);
		if (!check_numbers(numbers))
			*sum2 += double_check(numbers);
		fill_zero(numbers);
		i++;
	}
	return (sum);
}

int	double_check(int *numbers)
{
	int	n[10];
	fill_zero(n);
	int k = 0;
	while (numbers[k] != 0)
	{
		int i = 0;
		int a = 0;
		while (numbers[a] != 0)
		{
			if (k == i)
				a++;
			n[i] = numbers[a];
			i++;
			a++;
		}
		if (check_numbers(n))
			return (1);
		k++;
	}
	return (0);
}

int	check_numbers(int *numbers)
{
	int i = 1;
	if (numbers[i] > numbers[i -1])
		return (increase(numbers, i));
	else if (numbers[i] < numbers[i -1])
		return (decrease(numbers, i));
	else
		return (0);
}

int	increase(int *numbers, int i)
{
	while (numbers[i] > numbers[i -1] && numbers[i] != 0)
	{
		if (numbers[i] - numbers[i -1] > 3)
			return (0);
		i++;
	}
	if (numbers[i] == 0)
		return (1);
	else
		return (0);
}

int	decrease(int *numbers, int i)
{
	while (numbers[i] < numbers[i -1] && numbers[i] != 0)
	{
		if (numbers[i] - numbers[i -1] < -3)
			return (0);
		i++;
	}
	if (numbers[i] == 0)
		return (1);
	else
		return (0);
}

void	allocate(char **av)
{
	int i = 0;
	while (i < 1000)
	{
		av[i] = malloc(25);
		if (!av[i])
		{
			free_mem(av, i -1);
			return ;
		}
		i++;
	}
}

void fill_zero(int *numbers)
{
	int i = 0;
	while (i < 10)
	{
		numbers[i] = 0;
		i++;
	}
}

void get_line(char *s, char **av)
{
	int k = 0;
	static int j;
	static int i;
	while (s[k])
	{
		while (s[k] != '\n' && s[k])
		{
			av[i][j++] = s[k++];
		}
		if (s[k] == '\n')
		{
			i++;
			j = 0;
			k++;
		}
	}
	return ;
}
