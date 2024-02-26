#include <stdio.h>
#include <string.h>

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\n')
		return (1);
	if (c == '\v' || c == '\t')
		return (1);
	if (c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	res;
	int	i;
	unsigned char ret;

	i = 0;
	sign = 1;
	res = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	if (ft_strlen(nptr) == 1 && ft_isdigit(nptr[0]) == 0)
		return (-2);
	while (ft_isdigit(nptr[i]) != 0)
		res = res * 10 + nptr[i++] - '0';
	if (ft_strlen(nptr) != i)
		return (-2);
	ret = (res * sign) % 256;
	return (ret);
}


int main() {
    long input;
	char str[1024];
    unsigned char result;

    // Eingabeaufforderung
    printf("Geben Sie eine Zahl ein: ");
    scanf("%1023s", str);

    // Umwandlung zu einem Wert im Bereich 0-255
	
	input = ft_atoi (str);
    result = input % 256 ;//% 256;

    // Ausgabe des Ergebnisses
    printf("Der umgewandelte Wert ist: %li\n", input);

    return 0;
}