#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "historia.h"
#include "profiles.h"

//Função nova historia
perfil* novahistoria(historia vh[], int p, perfil *vp, int *c){ //Ela muda o valor da estruta perfil (XP)
	int op,  per, resp; //per = pegar o perfil | resp = pegar a respost das alternativas
	int teste_p = 0, teste_h=0; // teste_p = verficar se achou o perfil (bool) | teste_h = verificar se achou a historia (bool)
	printf("Digite o ID do Perfil que deseja iniciar a historia \n>");
	scanf("%d", &per); //Primeiro pega-se o perfil
	do{
		if(*c > 0){ //Teste saber se a perfis disponiveis
			for(int k=0;k<*c;k++){ //Pecorre todos os perfis atras do ultimo "per" digitado
				if(vp[k].id == per){ //Se o perfil for encontrado
					printf("Perfil Encontrado!\n");
					teste_p = 1; //Teste recebe true
					int ident;
					//Listando as historias
					printf("\n+----------------------------------------------GAMES---------------------------------------------+\n\n");
					for(int j=0;j<p;j++){
						printf("Historia: %s\n", vh[j].titulo);
						printf("ID Historia: %d\n", vh[j].id);
						printf("XP: ** %d **\n", vh[j].xp_h);
						if(vp[k].xp >= vh[j].desblock){
							printf("Status: Desbloqueada");
						}else{
							printf("Status: Bloqueada\n");
							printf("Quantidade de XP para desbloquear: %d", vh[j].desblock - vp[k].xp);
						}
						printf("\n\n+------------------------------------------------+\n\n");
					}
					//Escolhendo a historia por meio do ID -> ident
					printf("Escolha a historia \n>");
					scanf("%d", &ident);
					for(int j=0;j<p;j++){
						if(ident == vh[j].id && vp[k].xp >= vh[j].desblock){
							teste_h = 1; //teste de historia recebe true
							imprimeHistoria(vh,j); //Chama a função imprimir

							printf("+-------------------------------------------------------------------------------------------------------+\n");
							printf("Qual opcao eh a verdadeira? \n> ");
							scanf("%d", &resp); //Recebe a resposta
							if(resp == vh[j].resposta){ //Compara a resposta
								//Se for igual recebe o xp
								vp[k].xp += vh[j].xp_h;
								printf("Parabens %s voce acertou!\n", vp[k].nome);
								printf("XP Ganho: **%d**\n", vh[j].xp_h);
							}else{ //Se não errou
								printf("Voce errou\n");
								break;
							}
						}	
					} //Se pecorreu todas as historias e ficou com teste_h = false, faca:
					if(teste_h == 0){
						printf("Historia nao encontrada ou Historia está bloqueada\n");
						break;
					}
				}
			}
			//Se pecorreu todas as historias e ficou com teste_p = false, faça
			if(teste_p == 0){
				printf("Perfil Não encontrado!\n");
			}
		}//Se não tem nenhum perfil no vetor de perfis, aborte a missão
		else{
			printf("Nenhum Perfil Encontrado\n");
			printf("Faça um perfil na opcao = Inserir Perfil!\n");
		}
		//Ao final ou incia uma historia nova ou sai
		printf("\n[1] - Escolher Nova Historia\n");
		printf("[0] - Sair\n>");
		scanf("%d", &op);
	}while(op != 0);

	return vp;
}

//Funcao para imprimar a arte
void artAscii(){
		//File recebe ponteiro 
		FILE *arq;
		char linha[100];
		char *conseguiuLer;
        //Testando erro ao abrir arquivo
        if((arq = fopen("arquivos-txt/logo.txt", "r")) == NULL){
            printf("Houve um erro ao abrir o arquivo. O programa sera fechado\n");
            system("pause");
            exit(1);
        }
        //Lendo e imprimindo as infomracao�es na tela
        while(!feof(arq)){
			conseguiuLer = fgets(linha, 100, arq);
			if(conseguiuLer){
				printf("%s", linha);
			}
		}
        //Fechando o arquivo da imagem
        fclose(arq);
        printf("\n");
}

int main(){
	//Declarando vetor para os perfis e iniciando com 0
	int i=0, j=0, oper;
	perfil *lista = 0;
	historia *conjunto = 0;
	
	lista = importarLista(lista,&i);
	conjunto = importarConjunto(conjunto,&j);
	
	while(1){
		//comando para limpar o display
		system("clear");
		artAscii();
		
		//Menu de opcao
		printf(" [1] - Novo Perfil\n");
		printf(" [2] - Remover Perfil\n");
		printf(" [3] - Lista de Perfis\n");
		printf(" [4] - Iniciar jogo\n");
		printf(" [5] - Sair\n");
		printf("+-----------------------------------------------------------------------------------------------+");

		int controller = 0;
		printf("\n>");
		scanf("%d",&oper);
		
		switch(oper){
			//1 para chamar funcao inserirPerfil, passando como parametro o vetor e o tamanho
			case 1: {
				system("clear");
				artAscii();
				lista = inserirPerfil(lista,&i);
				
				break;
			}
			//2 para chamar a funcao removerPerfil, passando como parametro vetor e tamnho, com a lista de perfis
			case 2: {
				system("clear");
				artAscii();
				listarPerfis(lista, i);
				lista = removerPerfil(lista,&i);
				break;
			}
			//3 para chamar a a funcao listar todos os perfis, passando como parametro vetor e tamnho
			case 3: {
				system("clear");
				artAscii();
				listarPerfis(lista, i);
				break;
			}
			case 4: {
				system("clear");
				artAscii();
				listarPerfis(lista, i);
				lista = novahistoria(conjunto, j, lista, &i);
				break;
			}
			//5 para sair
			case 5: {
				controller=1;
				break;
			}
			//Se n�o for nenhum dos casos, a operacao � invalida
			default: {
				system("clear");
				artAscii();
				printf("Operacao nao existente");
				break;
			}
		}
		
		if(controller == 1){
			break;
		}
	}
	perfisParaArquivo(lista, i);
	
	free(lista);
	free(conjunto);
}
