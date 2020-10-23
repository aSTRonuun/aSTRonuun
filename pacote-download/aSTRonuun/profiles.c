#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "profiles.h"

perfil* importarLista(perfil *v,int *c){
	int f_len, posiAtual;
	FILE *f = fopen("perfis.txt","r");
	if(f == NULL){
		printf("ERROR: não foi possivel abrir aquivo");
		exit(1);
	}
	posiAtual = ftell(f);
	//Teste para saber se o arquivo esta fazio
	fseek(f, 0, SEEK_END);
	f_len = ftell(f); //retorna o tamanho do arquivo
	printf("%d", f_len);
	fseek(f, posiAtual, SEEK_SET);
	if(f_len == 0){
		fclose(f);
		return 0;
	}
	//Se não estiver fazio realloc
	else{
		while(!feof(f)){ //Funçao para ir até o final do arquivo
			(*c)++;
			v = (perfil*) realloc(v, *c * sizeof(perfil));
			if(v == 0){
				printf("Nao foi possivel realizar inserir Perfil");
			}
			fscanf(f,"\n%s",v[*c-1].nome);
			fscanf(f,"%d\n",&v[*c-1].id);
			for(int i=0;i<3;i++){
				fscanf(f, "%d ", &v[*c-1].atual[i]);
			}
			fscanf(f, "%d", &v[*c-1].xp);
		}
	fclose(f);
	return v;
	}
	getchar();
}

//Funcao Inserir Perfil
perfil* inserirPerfil(perfil *v, int *i){
	int op;
	do{	
		//Lendo Perfil
		perfil p;
		printf("Insira o nome do seu perfil:\n> ");
		scanf("%s[\n]",p.nome);
		printf("Insira o ID do seu perfil:\n> ");
		scanf("%d",&p.id);
		time_t date = time(0);
		struct tm *t = gmtime(&date);
		p.atual[0] = t->tm_mday;
		p.atual[1] = t->tm_mon+1;
		p.atual[2] = t->tm_year+1900;
		p.xp = 0;

		//Acresentando +1 Perfil
		*i = *i+1;
		v = (perfil*) realloc(v, *i * sizeof(perfil));
		
		//Teste para acresentar o novo vetor
		if(v == 0){
		printf("Nao foi possivel inserir Perfil");
		}
		//Se ocorreu bem, executa a realoc
		else{
			v[*i-1] = p;
		}
		printf("\nPerfil salvo com sucesso!\n");
		//Op��es para o usuario
		printf("\n [1] - Adicionar novo Perfil");
		printf("\n [0] - Sair\n> ");
		scanf("%d", &op);

	}while(op != 0);
	
	//retorna o vetor
	return v;
}

//Funcao para remover perfil
perfil* removerPerfil(perfil *v, int *i){
	int op = 0;
	do{
		//Declarando Id e a flag para remo��o 
		int id,flag=0;
		printf("Digite o ID do personagem que deseja remover:\n");
		scanf("%d",&id);
	
		//for para pecorrer o vetor e achar o id com a flag
		for(int j=0;j<*i;j++){
			if(v[j].id == id){
				flag=1;
			}
			/* Se a flag estiver levantada e o j for menor do que i-1,(j� que dentro da condi��o,
			se utiliza um valor � frente no vetor (j+1)), j = j+i para se igualar a i. 
			*/
			if(flag==1 && j<*i-1){
				v[j]=v[j+1];
			}
		}
		// Se a flag estiver levatanda execute realoc.
		if(flag==1){
			*i = *i-1;
			//Se estiver somente uma posi��o remova utilizando realoc
			if(*i == 0){
				free(v);
				v = 0;
				printf("Perfil Removido\n\n");
			}
			//Se nao, se tiver mais que dois perfis reomva utilizando realoc
			else{
				v = (perfil*) realloc(v, *i * sizeof(perfil));
				if(v == 0){
					free(v);
					v = 0;
					printf("Nao foi possivel remover perfil\n\n");
				}
				else{
					printf("Perfil removido\n\n");
				}
			}
		}
		//se n�o encontrar o perfil, imprima
		else{
			printf("Perfil nao encontrado\n\n");
		}
		//Opcoes do usuario
		printf("[1] - Remover outro Perfil\n");
		printf("[0] - Sair\n> ");
		scanf("%d", &op);

	}while(op != 0);
	
	return v;
}

//Funcapara listar perfil
void listarPerfis(perfil v[], int i){
	int op;
	do{
		printf("+-------------------------------------------Perfis----------------------------------------------+\n");
		//Se houver perfis pecorra o vetor e imprima os perfis
		if(i > 0){
			for(int j=0;j<i;j++){
				printf("Nome do Personagem: %s\nId: %d\nData: %d/%d/%d\n", v[j].nome, v[j].id, v[j].atual[0],v[j].atual[1],v[j].atual[2]);
				printf("XP: %d", v[j].xp);
				printf("\n+------------------------------------------------+\n");
			}
		}
		//Se n�o houver nenhum imprima
		else{
			printf("Nenhum perfil encontrado\n\n");
		}
		printf("Pressione [1] para continuar\n>");
		scanf("%d", &op);
	}while(op != 1);
}

//Funcao para persistencia de dados em arquivos
void perfisParaArquivo(perfil v[], int i){
	
	FILE *f = fopen("perfis.txt", "w");
	if(f == 0){
		printf("ERRO ao abrir o arquivo");
		return;
	}
	for(int j=0;j<i;j++){
		fprintf(f, "\n%s\n%d\n%d %d %d\n%d", v[j].nome, v[j].id, v[j].atual[0], v[j].atual[1], v[j].atual[2], v[j].xp);
	}
	fclose(f);
}
