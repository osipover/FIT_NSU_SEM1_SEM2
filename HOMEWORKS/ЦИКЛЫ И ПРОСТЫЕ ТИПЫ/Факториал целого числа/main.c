#include <stdio.h>

int Factorial(int n) {
	int fact = 1;
	while (n > 1) {
		fact *= n;
		n -= 1;
	}
	return fact;
}

int main(){
  int n;
  if (scanf("%d", &n) != 1)
    return 1;
  printf("%d", Factorial(n));
  return 0;
}
