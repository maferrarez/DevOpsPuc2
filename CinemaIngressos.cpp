#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<locale.h>
#include<conio.h>
#include<time.h>
#include <windows.h>
#include<ctype.h>
#include "MyBibTrab.h"

struct cadastroF{
	char nome[100], cpf[12], telefone[16];
	int id, pontos, status, idade;
};

struct salas{
	char matrix[5][10];
	int salaCadeiras;
};

	////////////////////// FUNÇOES ////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	int verificaCadastroCPF(struct cadastroF cf[], char cpf[12] ,int cont){
		int resp = 0, i;
		for(i = 0; i < cont; i++){
			if(strcmp(cf[i].cpf, cpf) == 0){
				resp = 1;
			}
		}
		return resp;
	}
	
	int cadastroFidelidade(struct cadastroF cf[], int contF){
		contF = contF - 1;
		int verificaCPF;
		
		cf[contF].id = contF+1;
		cf[contF].status = 1;
		cf[contF].pontos = 0;
		varrer();
		printf("\n\tInforme o nome: ");
		gets(cf[contF].nome);
		varrer();		
		
		do{
			
			printf("\n\tInforme o CPF: ");
			gets(cf[contF].cpf);
			varrer();
			
  			verificaCPF = verificaCadastroCPF(cf, cf[contF].cpf ,contF);
  			
		}while(verificaCPF == 1);
		
		printf("\n\tInforme o telefone: ");
		gets(cf[contF].telefone);
		varrer();
		
		printf("\n\tInforme a idade: ");
		scanf("%d", &cf[contF].idade);
		varrer();
		
		return contF;
	}
	
	void printfCliente(struct cadastroF cf[], int i){
		printf("Cliente\t      ID: %i\n", cf[i].id);
		printf("\t    NOME: %s\n", cf[i].nome);
		printf("\t     CPF: %s\n", cf[i].cpf);
		printf("\tTELEFONE: %s\n", cf[i].telefone);
		printf("\t   IDADE: %i\n", cf[i].idade);
		printf("\t  PONTOS: %i\n", cf[i].pontos);
		printf("\t  STATUS: %i", cf[i].status);
	}
	
	void listarClientes(struct cadastroF cf[], int contF){
		int i;
		
		for(i = 0; i < contF; i++){
			linha();
			printfCliente(cf, i);
		}
		
		linha();
	}
	
	int buscarAtivos(struct cadastroF cf[], int cont){
		limpar();
		int j = 0;
		for(int i = 0; i < cont; i++){
			if(cf[i].status == 1){
				linha();
				printfCliente(cf, i);
				// caso houver um cliente cadastrado, ele nao printa o que esta ali embaixo
				j = 1;
			}
		}
		if(j == 0){
			printf("\nNão há cadastros ativos!\n");
		}else{
			linha();
		}
		return j;
	}
	
	int buscarInativos(struct cadastroF cf[], int cont){
		limpar();
		int j = 0;
		for(int i = 0; i < cont; i++){
			if(cf[i].status == 0){
				linha();
				printfCliente(cf, i);
				j = 1;
			}
		}
		if(j == 0){
			printf("\nNão há cadastros inativos!\n");
		}else{
			linha();
		}
		return j;
	}
	