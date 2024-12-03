/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruida-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:07:56 by ruida-si          #+#    #+#             */
/*   Updated: 2024/12/03 17:07:59 by ruida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

void	sort(int *numbers);
void	get_numbers(int *numbers1, int *numbers2, char *s, int index);
int	get_sum(int *numbers1, int *numbers2);
int	check_dup(int *numbers1, int *numbers2);

int main()
{
	char s[15];
	int numbers1[1000];
	int numbers2[1000];
	int fd = open("input", O_RDONLY);
	int b_read = 1;
	int index = 0;
	while (b_read)
	{
		b_read = read(fd, s, 14);
		if (b_read <= 0)
			break ;
		s[b_read] = '\0';
		get_numbers(numbers1, numbers2, s, index);
		index++;
	}
	sort(numbers1);
	sort(numbers2);
	int sum = get_sum(numbers1, numbers2);
	printf("First answer is: %i\n", sum);
	int dup = check_dup(numbers1, numbers2);
	printf("Second answer is: %i\n", dup);
}

int	check_dup(int *numbers1, int *numbers2)
{
	int index = 0;
	int n = 0;
	int sum = 0;
	int i = 0;
	while (index < 1000)
	{
		i = 0;
		n = 0;
		while (i < 1000)
		{
			while (numbers1[index] != numbers2[i] && i < 1000)
				i++;
			if (i == 1000)
				break ;
			n++;
			i++;
		}
		sum += numbers1[index] * n;
		index++;
	}
	return (sum);
}

void	sort(int *numbers)
{
	int index = 1;
	int temp;

	while (index < 1000)
	{
		if (numbers[index -1] > numbers[index])
		{
			temp = numbers[index -1];
			numbers[index -1] = numbers[index];
			numbers[index] = temp;
			index = 0;
		}
		index++;
	}
}

void	get_numbers(int *numbers1, int *numbers2, char *s, int index)
{
	int i = 0;
	int n = 0;
	int flag = 0;
	while (s[i])
	{
		n = 0;
		while (s[i] >= '0' && s[i] <= '9')
		{
			n = n * 10 + (s[i] - '0');
			i++;
		}
		if (!flag)
			numbers1[index] = n;
		else
			numbers2[index] = n;
		while (s[i] < 33 && s[i])
			i++;
		flag++;
	}
}

int	get_sum(int *numbers1, int *numbers2)
{
	int sum = 0;
	int index = 0;
	while (index < 1000)
	{
		int n = numbers1[index] - numbers2[index];
		if ( n < 0)
			sum -= n;
		else
			sum += n;
		index++;
	}
	return (sum);
}

