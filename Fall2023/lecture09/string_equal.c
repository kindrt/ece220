#include <stdio.h>

/* function prototype */
int string_equal(char const* s1, char const* s2);

int main()
{
	char* w = "word1";
	char* x = "word2";

	printf("%d\n", string_equal(w, x));

	printf("%s %s\n", w, x);

	return 0;
}

/* function implementation */
int string_equal(char const* s1, char const* s2)
{
	while ('\0' != *s1) {
		if (*s1 != *s2) { return 0; }
			s1++;
			s2++;
	}
	
	return ('\0' == *s2);
}

