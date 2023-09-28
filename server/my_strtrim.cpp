#include <cstdlib>
#include <iostream>

/* input str_len must be longer than len */

unsigned char	*my_strtrim(unsigned char *str, unsigned int len)
{
	unsigned char	*temp;

	temp = (unsigned char *)malloc(sizeof(unsigned char) * len);
	if (!temp)
	{
		std::cout << "Error: my_strtrim(): malloc()" << std::endl;
		exit(1);
	}
	for (int i = 0; i < len; i++)
		temp[i] = str[i];

	return (temp);
}
