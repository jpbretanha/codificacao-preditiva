#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

//descompressão
char* descomprime(char *residuo) {
	int limite = 512 * 512 * 1;
	int tamBloco = 8;
	char *raw = new char[limite];

	for (int i = 0; i < limite; i+=tamBloco) {
		raw[i] = residuo[i];
		for (int j = 1; j < tamBloco; j++) {
			raw[i + j] = residuo[i + j] + raw[i];
		}
	}
	return raw;
}


int main()
{
  	FILE *fd = fopen("residuos.raw", "rb");
	char *matriz = new char[512*512*1];
	int limite = 512*512*1;
	if(!fd) {
		return 1;
	}else {
		char c;
		int i=0;
		while (i < limite)
		{
			fread(&c, sizeof(char), 1, fd);
			matriz[i] = (unsigned char)c;
			i++;
		}
		fclose(fd);
	}
	char *matrizDec = descomprime(matriz);
	cout << "Descompressao realizada com sucesso!\n";
	system("pause");
	return 0;
}

