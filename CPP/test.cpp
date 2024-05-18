
#include <iostream>
#include <string>

// usage  ./test afds😀fas 1%42sfdg%agbd%C2%A3pound%E2%82%ACeuro


int	ok_mini_stoi(std::string hex)
{
	int	res;

	if (hex[0] > '9')
	{
		hex[0] &= '_';
		hex[0] -= 7;
	}
	if (hex[1] > '9')
	{
		hex[1] &= '_';
		hex[1] -= 7;
	}
	res = (hex[0] - '0') * 16 + (hex[1] - '0');
	return (res);
}

static const std::string HEXA = "0123456789abcdefABCDEF";

std::string	ok_decode(std::string code, int *i)
{
	std::string	res;

	if (HEXA.find(code[0]) == std::string::npos
		|| HEXA.find(code[1]) == std::string::npos)
		return ("%");
	*i += 2;
	res = ok_mini_stoi(code);
	return (res);
}

std::string	ok_decrypt(std::string test)
{
	std::string	res;
	int			i;

	i = -1;
	while (test[++i])
	{
		if (test[i] == '%')
		{
			res += ok_decode(test.substr(i + 1, 2), &i);
		}
		else
			res += test[i];
	}
	return (res);
}


int main (int argc, char *argv[])
{
	int			i = 0;
	std::string	test;

	if (argc == 1)
		std::cerr << "Not enough arguments" << std::endl;
	while (argv[++i])
	{
		std::cout << ok_decrypt(argv[i]) << std::endl;
	}
	return (0);
}
