#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *strjoin(char *s1, char *s2)
{
	int l1;
	int l2;
	int l;
	char *s;
	int i;

	l1 = (s1 == NULL) ? 0 : strlen(s1);
	l2 = (s2 == NULL) ? 0 : strlen(s2);
	l = l1 + l2; 

	s = (char*)malloc(sizeof(char) * l + 1);
	if (s == NULL)
		return NULL;
	s[l] = '\0';

	i = 0;
	while (s1 != NULL && s1[i] != '\0') {
		s[i] = s1[i];
		i++;
	}
	while (s2 != NULL && s2[i - l1] != '\0') {
		s[i] = s2[i - l1];
		i++;
	}

	return s;
}

char *itoa(int n)
{
	char *s;
	int numLen;

	if (n == 0) {
		s = (char*)malloc(sizeof(char) * 2);
		if (s == NULL)
			return NULL;
		s[0] = '0';
		s[1] = '\0';
		return s;		
	}

	int i = 0;
	int aux = n;
	while (aux != 0) {
		aux = aux / 10;
		i++;
	}
	numLen = i;

	s = (char*)malloc(sizeof(char) * numLen + 1);
	if (s == NULL)
		return NULL;
	s[numLen] = '\0';

	i = 1;
	while (n != 0) {
		s[numLen - i] = '0' + (n % 10);
		n = n / 10;
		i++;
	}

	return s;
}
