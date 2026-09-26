#include <stdio.h>

/*
    Task:
    Write a function `long long factorial(int n)` that computes n!
    using a loop (not recursion).

    In main():
     - Ask user for an integer n
     - If n is negative, print an error and exit
     - Otherwise, call factorial and print the result
*/

long long factorial(int n) {
  long long fact = 1;

  for (int i = 1; i <= n; i++) {
    fact = fact * i;
  }

  return fact;
}

int main(void) {
  int n;

  printf("Enter a non-negative integer n: ");
  scanf("%d", &n);

  if (n < 0) {
    printf("Error: Number cannot be negative.\n");
  } else {
    long long result = factorial(n);
    printf("The factorial of %d is %lld\n", n, result);
  }

  return 0;
}