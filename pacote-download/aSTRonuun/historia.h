#ifndef HISTORIA_H
#define HISTORIA_H

typedef struct{
	int id;
	int resposta;
	int xp_h;
	int desblock;
	int status;
	char titulo[40];
	char texto[1000];
	char respota_texto[1000];
}historia;

historia* importarConjunto(historia *v,int *c);
void imprimeHistoria(historia v[],int p);
void imprimeResposta(historia v[], int p);

#endif