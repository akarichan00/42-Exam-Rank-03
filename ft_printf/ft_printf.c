#include <stdarg.h>
#include <unistd.h>

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}
int	ft_strlen(char *str)
{
	int		len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	put_int(int n, char *base)
{
	int		count;
	int		base_len;
	long	number;

	number = (long)n;
	base_len = ft_strlen(base);
	count = 0;
	if (number < 0)
	{
		ft_putchar('-');
		number *= -1;
		count++;
	}
	if (number < base_len)
		count += ft_putchar(base[number]);
	else
	{
		count += put_int((number / base_len), base);
		count += ft_putchar(base[number % base_len]);
	}
	return (count);
}

int	put_str(char *str)
{
	int		count;

	count = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[count])
		ft_putchar(str[count++]);
	return (count);
}

int	put_x(unsigned int number, char *base)
{
	int				count;
	unsigned int	base_len;

	base_len = ft_strlen(base);
	count = 0;
	if (number < base_len)
		count += ft_putchar(base[number]);
	else
	{
		count += put_x((number / base_len), base);
		count += ft_putchar(base[number % base_len]);
	}
	return (count);
}


static int	check_format(char c)
{
	if (c == 's' || c == 'd' || c == 'x')
		return (1);
	return (0);
}

static int	handle_format(va_list args, char format)
{
	int	count;

	count = 0;
	if (format == 'd')
		count += put_int(va_arg(args, int), "0123456789");
	else if (format == 'x')
		count += put_x(va_arg(args, unsigned int), "0123456789abcdef");
	else if (format == 's')
		count += put_str(va_arg(args, char *));
	else
		count += ft_putchar(format);
	return (count);
}
int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, s);
	while (*s)
	{
		if (*s == '%' && *(s + 1) == '\0')
			return (count);
		if (*s == '%' && *(s + 1) != '\0')
		{
			s++;
			if (check_format(*s))
				count += handle_format(args, *s);
			else 
				count += ft_putchar(*s);
			s++;
		}
		else
			count += ft_putchar(*s++);
	}
	va_end(args);
	return (count);
}

int main()
{
	ft_printf("apah: %s\n", "meaw meaw nigga");
}
