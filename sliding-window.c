#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n;

int windowSum(int arr[n], int k) {
  int sum = 0, maxSum = 0;
  for (int i = 0; i < k; i++) {
    // Calculate sum of initial window
    sum += arr[i];
  }
  if (maxSum < sum) {
    maxSum = sum;
  }
  for (int i = k; i < n; i++) {
    // Omit one and add the next
    sum = sum - arr[i - k] + arr[i];
    if (maxSum < sum) {
      maxSum = sum;
    }
  }
  return maxSum;
}

int main(void) {
  int k;
  char *buf;
  size_t bufsize = 10;
  buf = malloc(sizeof(char) * bufsize);
  if (buf == NULL) {
    perror("Out of memory :(");
    return EXIT_FAILURE;
  }
  printf("Enter array size\n");
  getline(&buf, &bufsize, stdin);
  n = atoi(buf);

  printf("Enter window size\n");
  getline(&buf, &bufsize, stdin);
  k = atoi(buf);

  printf("Enter numbers seperated by ,\n");
  getline(&buf, &bufsize, stdin);
  char *token = strtok(buf, ",");

  int *arr = malloc(n * sizeof(int));
  int size = 0;
  while (token != NULL && size < n) {
    // Initialize array with each integer
    arr[size++] = atoi(token);
    token = strtok(NULL, ",");
  }

  printf("Max window sum: %d", windowSum(arr, k));
  free(buf);
  free(arr);
  return EXIT_SUCCESS;
}
