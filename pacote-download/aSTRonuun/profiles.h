#ifndef PROFILES_H
#define PROFILES_H

//Estrutura Perfil
typedef struct{
	char nome[50];
	int id;
	int atual[3];
	int xp;
}perfil;


perfil* importarLista(perfil *v,int *c);
perfil* inserirPerfil(perfil *v, int *i);
perfil* removerPerfil(perfil *v, int *i);
void listarPerfis(perfil v[], int i);
void perfisParaArquivo(perfil v[], int i);

#endif