#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

unsigned char	*my_strjoin(unsigned char *str1, unsigned char *str2, unsigned int len1, unsigned int len2)
{
	unsigned char	*temp;
	int				i;

	temp = (unsigned char *)malloc(sizeof(unsigned char) * (len1 + len2 + 1));
	if (!temp)
	{
		std::cout << "Error: my_strjoin(): malloc()" << std::endl;
		exit(1);
	}
	for (i = 0; i < len1; i++)
		temp[i] = str1[i];
	for (int j = 0;j < len2; j++)
		temp[i + j] = str2[j];
	free(str1);
	return (temp);
}
