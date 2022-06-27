#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

void	*ft_memset(void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*z;

	z = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		z[i] = (unsigned char)c;
		i++;
	}
	return (str);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long int	nn;
	int			i;
	char		c;

	nn = n;
	i = 0;
	if (nn < 0)
	{
		ft_putchar_fd('-', fd);
		nn = -nn;
	}
	if (nn > 9)
	{
		ft_putnbr_fd(nn / 10, fd);
		ft_putnbr_fd(nn % 10, fd);
	}
	if (nn < 10)
	{
		c = nn + '0';
		ft_putchar_fd(c, fd);
	}
}

void	signal_handler(int signal)
{
	static int	i = 0;
	static int	bit = 128;
	static char	final_char = 0;

	if (signal == SIGUSR1)
	{
		final_char += bit;
		bit /= 2;
		i++;
		usleep(10);
	}
	else if (signal == SIGUSR2)
	{
		bit /= 2;
		i++;
		usleep(10);
	}
	if (i == 8)
	{
		write(1, &final_char, 1);
		usleep(20);
		bit = 128;
		i = 0;
		final_char = 0;
	}
}

int	main(void)
{
	struct sigaction	act_one;

	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	ft_memset(&act_one, 0, sizeof(act_one));
	act_one.sa_handler = &signal_handler;
	while (1)
	{
		sigaction(SIGUSR1, &act_one, NULL);
		sigaction(SIGUSR2, &act_one, NULL);
		usleep(20);
	}
	return (0);
}
