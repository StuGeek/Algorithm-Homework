#include "source.h"
#include <stdio.h>
#include <string.h>

int main()
{
  int t;
  scanf("%d", &t);
  while(t--)
  {
    // Prompt the user to enter a string
    printf("Enter the first string: ");
    char s1[10000];
    scanf("%s",s1);
    // Prompt the user to enter a string
    printf("Enter the second string: ");
    char s2[10000];
    scanf("%s",s2);
    printf("%d\n", indexOf(s1, s2));
  }
  return 0;
}
