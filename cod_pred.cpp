#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <unistd.h>
#include <string.h>


using namespace std;


static void lerMatriz(const char *filename) {

	FILE *fd = fopen(filename, "rb");
	if(!fd) {
		return;
	}else {
		unsigned int c;
		int contador =0;

		while (!feof(fd))
		{
			char num;
			fread(&num, sizeof(char), 1, fd);
			printf("%d\n", (int)num);
			contador++;

		}
		printf("%d\n", contador);

		fclose(fd);
	}
}

int main()
{
  lerMatriz("lena.raw");
  return 0;
}

