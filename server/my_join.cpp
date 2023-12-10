#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

char	*my_strjoin(char *str1, char *str2, unsigned int len1, unsigned int len2)
{
	char	*temp;
	int		i;

	temp = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
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
