#include <stdio.h>

int	compare(char *comp, char *s);
int	get_numbers(char *s, int *i);

int	check_mult(char *s)
{
	int n;
	int n2;
	char comp[5] = "mul(";
	if (!compare(comp, s))
		return (0);
	else
	{
		int i = 4;
		n = get_numbers(s, &i);
		if (n == 0)
			return (0);
		if (s[i] != ',')
			return (0);
		i++;
		n2 = get_numbers(s, &i);
		printf("%i\n", i);
	}
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

int main()
{
	int n = check_mult("mul(5,5)");
	printf("%i\n", n);
}