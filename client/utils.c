#include <string.h>
#include <stdlib.h>
#include <stdio.h>

unsigned char	*my_join(unsigned char *str1, unsigned char *str2, unsigned int len1, unsigned int len2)
{
	unsigned char	*temp;
	int				i;

	temp = malloc(sizeof(unsigned char) * (len1 + len2));
	if (!temp)
	{
		printf("Error: my_strjoin(): malloc()\n");
		exit(1);
	}
	for (i = 0; i < len1; i++)
		temp[i] = str1[i];
	for (int j = 0;j < len2; j++)
		temp[i + j] = str2[j];
	free(str1);
	return (temp);
}
