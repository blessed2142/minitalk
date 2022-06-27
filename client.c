#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	z;

	i = 0;
	z = 1;
	res = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i] < 27 || (str[i] > 27 && str[i] < 33))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			z = -1;
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		res = res * 10;
		res = res + str[i] - 48;
		i++;
	}
	return (res * z);
}

void	ft_error(int code)
{
	if (code == 1)
	{
		write(1, "Usage: ./client <PID> <TEXT>\n", 29);
		exit (0);
	}
	if (code == 2)
	{
		write(1, "Error.\n", 7);
		exit(0);
	}
}

void	send(int pid, int signal)
{
	if (kill(pid, signal) == -1)
		ft_error(2);
}

void	sender(int pid, char *str)
{
	int		j;
	int		i;
	char	c;

	j = 0;
	i = 128;
	while (str[j] != '\0')
	{
		c = str[j];
		i = 128;
		while (i >= 1)
		{
			if (i & c)
				send(pid, SIGUSR1);
			else
				send(pid, SIGUSR2);
			i /= 2;
			usleep(100);
		}
		j++;
	}
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*str;

	if (argc != 3)
		ft_error(1);
	pid = ft_atoi(argv[1]);
	str = argv[2];
	sender(pid, str);
	return (0);
}
