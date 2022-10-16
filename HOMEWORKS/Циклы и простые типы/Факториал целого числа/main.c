#include <stdio.h>

int CalcFactorial(int n) {
	int fact = 1;
	while (n > 1) {
		fact *= n;
		n -= 1;
	}
	return fact;
}

int main(){
  int n;
  assert(scanf("%d", &n) == 1);
  printf("%d", CalcFactorial(n));
  return 0;
}
