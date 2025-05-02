#include "ANSI-color-codes.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int m, n;

// DFS
void dfs(char mat[m][n], int row, int col, int visited[m][n]) {
  if (row < 0 || row >= m) {
    return;
  } else if (col < 0 || col >= n) {
    return;
  } else if (mat[row][col] == 'W') {
    return;
  } else if (visited[row][col] == 1) {
    return;
  } else {
    visited[row][col] = 1;
    // Check for surroundings
    dfs(mat, row - 1, col - 1, visited);
    dfs(mat, row - 1, col, visited);
    dfs(mat, row - 1, col + 1, visited);
    dfs(mat, row, col - 1, visited);
    dfs(mat, row, col + 1, visited);
    dfs(mat, row + 1, col - 1, visited);
    dfs(mat, row + 1, col, visited);
    dfs(mat, row + 1, col + 1, visited);
  }
}

int island(char mat[m][n]) {
  // Create a matrix to keep track of visited lands
  int visited[m][n];
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      visited[i][j] = 0;
    }
  }

  int count = 0;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (mat[i][j] == 'L' && visited[i][j] == 0) {
        visited[i][j] = 1;
        // Check for surroundings
        dfs(mat, i - 1, j - 1, visited);
        dfs(mat, i - 1, j, visited);
        dfs(mat, i - 1, j + 1, visited);
        dfs(mat, i, j - 1, visited);
        dfs(mat, i, j + 1, visited);
        dfs(mat, i + 1, j - 1, visited);
        dfs(mat, i + 1, j, visited);
        dfs(mat, i + 1, j + 1, visited);
        // Count it as island
        count++;
      }
    }
  }
  return count;
}

int main() {
  printf("Enter rows and columns\n");
  char *buf;
  size_t bufsize = 10;
  buf = malloc(bufsize * sizeof(char));
  if (buf == NULL) {
    perror("Unable to allocate buffer");
    exit(1);
  }
  getline(&buf, &bufsize, stdin);
  m = atoi(buf);
  getline(&buf, &bufsize, stdin);
  n = atoi(buf);

  if (m < 0 || n < 0) {
    return 0;
  }

  // Water body
  char mat[m][n];

  // Input body
  printf("Enter bodies\n");
  for (int i = 0; i < m; i++) {
    char *buf;
    size_t bufsize = n;
    buf = malloc(sizeof(char) * bufsize);
    getline(&buf, &bufsize, stdin);
    memcpy(mat[i], buf, n);
    for (int j = 0; j < n; j++) {
      if (mat[i][j] != 'W' && mat[i][j] != 'L') {
        return 0;
      }
    }
  }

  printf("Matrix:\n");
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (mat[i][j] == 'W') {
        printf(BLU "󰝤 " reset);
      } else {
        printf(GRN "󰝤 " reset);
      }
    }
    printf("\n");
  }

  printf("No. of islands are: %d", island(mat));
  free(buf);
  return EXIT_SUCCESS;
}
