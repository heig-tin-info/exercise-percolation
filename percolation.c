#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/**
 * ANSI color sequences
 * http://www.lihaoyi.com/post/BuildyourownCommandLinewithANSIescapecodes.html
 */
#define WATER "\e[48;5;75m"
#define GROUND "\e[48;5;94m"
#define AIR "\e[48;5;136m"
#define RESET "\e[0m"

/**
 * Symbol used to display the matrix
 */
const char *symbols[3] = {AIR " " RESET, GROUND " " RESET, WATER " " RESET};

bool animate = true;

/**
 * Génère une matrice aléatoire
 */
void generate(int *matrix, int length, double permeability) {
  int(*m)[length][length] = (int(*)[length][length])matrix;
  for (int row = 0; row < length; row++)
    for (int col = 0; col < length; col++)
      (*m)[row][col] = rand() > (double)RAND_MAX / permeability;
}

/**
 * Affiche la matrice
 */
void display(int *matrix, int length) {
  int(*m)[length][length] = (int(*)[length][length])matrix;
  for (int row = 0; row < length; row++) {
    for (int col = 0; col < length; col++)
      printf("%s%s", symbols[(*m)[row][col] % 3], symbols[(*m)[row][col] % 3]);
    printf("\n");
  }
}

void animation(int *matrix, int length) {
  display(matrix, length);
  printf("\e[H");
  usleep(100000);
}

/**
 * Propage l'eau dans un étage donné.
 */
void propagate(int *matrix, int length, int row) {
  int(*a)[length][length] = (int(*)[length][length])matrix;
  bool modified = false;

  do {
    modified = false;
    for (int i = 0; i < length; i++) {
        if ((*a)[row][i] == 2) {
            if (i > 0 && (*a)[row][i-1] == 0) {
                (*a)[row][i-1] = 2;
                modified = true;
            }
            if (i < length && (*a)[row][i+1] == 0) {
                (*a)[row][i+1] = 2;
                modified = true;
            }
        }
    }
    if (modified) {
        if(animate) animation(matrix, length);
    }
  } while (modified);
}

/**
 * Propage l'eau dans la matrice.
 */
bool percolate(int *matrix, int length) {
  int(*m)[length][length] = (int(*)[length][length])matrix;
  // Première ligne
  for (int col = 0; col < length; col++) {
    if ((*m)[0][col] == 0)
      (*m)[0][col] = 2;
  }

  if(animate) animation(matrix, length);
  // Propage l'eau
  for (int row = 1; row < length; row++) {
    for (int col = 0; col < length; col++) {
      if ((*m)[row][col] == 0 && (*m)[row - 1][col] == 2) {
        (*m)[row][col] = 2;
      }
    }
    if(animate) animation(matrix, length);
    propagate(matrix, length, row);
  }

  // Test si la matrice percole
  bool does_percolate = false;
  int row = length - 1;
  for (int col = 0; col < length; col++) {
    does_percolate |= (*m)[row][col] == 2;
  }
  return does_percolate;
}

int main(int argc, char *argv[]) {
  int length = argc > 1 ? atoi(argv[1]) : 30;
  double permeability = argc > 2 ? atof(argv[2]) : 1.6;
  int *m = calloc(length * length, sizeof(int));

  srand(time(NULL));
  generate(m, length, permeability);
  bool does_percolate = percolate(m, length);
  display(m, length);

  printf("La matrice %s !\n", does_percolate ? "percole" : "ne percole pas");
}
