#include <stdio.h>
#include <stdlib.h>

long long A(long long m, long long n) {
	if (m == 0) {
		return n + 1;
	}
	else if (n == 0) {
		return A(m - 1, 1);
	}
	else {
		return A(m - 1, A(m, n - 1));
	}
}

int main(void) {
	printf("%lld", A(3, 2));
}