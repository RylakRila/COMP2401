#include <stdio.h>
#include <string.h>

int isPalindrome(char s[]) {
	for (int i=0; i<strlen(s) ; i++) {
		if (s[i] != s[strlen(s)-1-i])
			return 0;
	}
	return 1;
}


int main() {
	char s1[] = "this is one";
	char s2[] = "this is another";
	char s3[] = {'k','a','y','a','k', '\0'};
	char s4[] = "abba";
	char s5[] = "roar";
	char s6[] = "racecar";
	char s7[] = "x";

	printf("%s\n%s\n%s\n\n", s1, s2, s3);
	
	if (isPalindrome(s1)) printf("yes\n"); else printf("no\n");
	if (isPalindrome(s2)) printf("yes\n"); else printf("no\n");
	if (isPalindrome(s3)) printf("yes\n"); else printf("no\n");
	if (isPalindrome(s4)) printf("yes\n"); else printf("no\n");
	if (isPalindrome(s5)) printf("yes\n"); else printf("no\n");
	if (isPalindrome(s6)) printf("yes\n"); else printf("no\n");
	if (isPalindrome(s7)) printf("yes\n"); else printf("no\n");
}

