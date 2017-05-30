#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <string.h>
#include <fstream>

bool jo_write_jpg(const char *filename, const void *data, int width, int height, int comp, int quality);
using namespace std;


void geraJpeg(char *matriz) {
	jo_write_jpg("saida/imagemGerada.jpg", matriz, 512, 512, 1, 90);
}

void geraImagemRaw(char *image) {
	ofstream ofs;
	ofs.open("saida/residuos.raw", ios::out);
	ofs.write(image, 512*512*1);
	ofs.close();
}
//Predição 
char* calculaPredicao(char *imagem) {
	int matrizCalc = 512 * 512 * 1;
	char *predicao = new char[matrizCalc];
	int bloco = 8;
	for (int i = 0; i < matrizCalc; i += bloco) {
		for (int j = 0; j < bloco; j++) {
			predicao[i + j] = imagem[i];
		}
	}

	return predicao;
}

//calcula residuo 
char* calculaResiduo(char *entradaOriginal, char *entradaPredita) {
	int matrizCalc = 512 * 512 * 1;
	int bloco = 8;
	char *residuo = new char[matrizCalc];
	for (int i = 0; i < matrizCalc; i+=bloco) {
		residuo[i] = entradaPredita[i];
		for (int j = 1; j < bloco; j++) {
			residuo[i + j] = entradaOriginal[i + j] - entradaPredita[i + j];
		}
	}
	
	return residuo;
}

int main()
{
  	FILE *fd = fopen("lena.raw", "rb");
	char *matriz = new char[512*512*1];
	int matrizCalc = 512*512*1;
	if(!fd) {
		return 1;
	}else {
		char c;
		int i=0;
		while (i < matrizCalc)
		{
			fread(&c, sizeof(char), 1, fd);
			matriz[i] = (unsigned char)c;
			i++;
		}
		fclose(fd);
	}
	char *matrizPred = calculaPredicao(matriz);
	char *residuo = calculaResiduo(matriz, matrizPred);
	geraJpeg(matrizPred);
	geraImagemRaw(matrizPred);
	cout << "Compressao por cópia simples realizada com sucesso!\nArquivos gerados na pasta saida\n";
	system("pause");
	return 0;
}

