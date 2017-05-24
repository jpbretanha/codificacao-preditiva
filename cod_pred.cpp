#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <string.h>
#include <fstream>

bool jo_write_jpg(const char *filename, const void *data, int width, int height, int comp, int quality);
using namespace std;


void geraJpeg(char *matriz) {
	jo_write_jpg("foo.jpg", matriz, 512, 512, 1, 90);
}

void geraImagemRaw(char *image) {
	ofstream ofs;
	ofs.open("saida.raw", ios::out);
	ofs.write(image, 512*512*1);
	ofs.close();
}
//média aritmética
char* calculaPredicao(char *imagem) {
	int limite = 512 * 512 * 1;
	char *imagemP = new char[limite];
	int tamBloco = 8;
	int i = 0;
	for (; (i + tamBloco) < limite; i += tamBloco) {
		char media = (imagem[i] + imagem[i + tamBloco]) / 2;
		imagemP[i] = imagem[i];
		for (int j = 1; j < tamBloco; j++) {
			imagemP[i + j] = media;
		}
	}

	char media = (imagem[i] + imagem[limite - 1]) / 2;
	imagemP[i] = imagem[i];
	imagemP[limite - 1] = imagem[limite - 1];
	i++;
	for (; i < limite; i++) {
		imagemP[i] = media;
	}

	return imagemP;
}

//calcula residuo por media aritimética
char* calculaRes(char *imagemOriginal, char *imagemP) {
	int limite = 512 * 512 * 1;
	int tamBloco = 8;
	char *residuo = new char[limite];

	int i = 0;
	for (; (i + tamBloco) < limite; i += tamBloco) {
		residuo[i] = imagemP[i];
		for (int j = 1; j < tamBloco; j++) {
			residuo[i + j] = imagemOriginal[i + j] - imagemP[i + j];
		}
	}
	
	residuo[i] = imagemP[i];
	residuo[limite - 1] = imagemP[limite - 1];
	i++;
	for (; i < limite; i++) {
		residuo[i] = imagemOriginal[i] - imagemP[i];
	}

	return residuo;
}

int main()
{
  	FILE *fd = fopen("lena.raw", "rb");
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
	char *matrizPred = calculaPredicao(matriz);
	char *residuo = calculaRes(matriz, matrizPred);
	geraJpeg(matrizPred);
	geraImagemRaw(matrizPred);
	system("pause");
	return 0;
}

