#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<locale.h>
#include<curses.h>
#include<time.h>
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

	void editarCadastro(struct cadastroF cf[], int i, int contF){ // recebe a struct e a posição do cadastro
		int opEditar, confirmar, idade, verificaCPF = 0;
		char nome[100], cpf[12], telefone[16];
		do{
			limpar();
			printfCliente(cf, i);
			menuOpcoesEdicao();
			scanf("%i", &opEditar);
			varrer();
			switch(opEditar){
				case 0:
					confirmar = 0;
					saindo();
				break;

				case 1:
					confirmar = confirmarEdicao();
					if(confirmar == 1){
						if(cf[i].status == 1){
							cf[i].status = 0;
						}

						else if(cf[i].status == 0){
							cf[i].status = 1;
						}
					}
				break;

				case 2:

					printf("\nInforme o novo nome: ");
					gets(nome);
					varrer();

					confirmar = confirmarEdicao();

					if(confirmar == 1){
						strcpy(cf[i].nome, nome);
					}

				break;

				case 3:
					do{
						if(verificaCPF == 1){
							printf("\n\nCPF já cadastrado. Tente Novamente!\n\n");
						}

						printf("\nInforme o novo cpf: ");
						varrer();
						gets(cpf);
						varrer();

			  			verificaCPF = verificaCadastroCPF(cf, cpf , contF);

					}while(verificaCPF == 1);

					if(verificaCPF == 0){
						confirmar = confirmarEdicao();
						if(confirmar == 1){
							strcpy(cf[i].cpf, cpf);
						}
					}

				break;

				case 4:

					printf("\nInforme o novo telefone: ");
					gets(telefone);
					varrer();

					confirmar = confirmarEdicao();

					if(confirmar == 1){
						strcpy(cf[i].telefone, telefone);
					}

				break;

				case 5:

					printf("\nInforme a nova idade: ");
					scanf("%d", &idade);
					varrer();

					confirmar = confirmarEdicao();

					if(confirmar == 1){
						cf[i].idade = idade;
					}

				break;
			}
		}while(confirmar != 0);
	}

	void buscaCPF(struct cadastroF cf[], int cont){

		char cpf[12];
		int i;

		printf("\nInforme o CPF para busca: ");
		gets(cpf);
		varrer();

		for(i = 0; i < cont; i++){
			if(strcmp(cf[i].cpf, cpf) == 0){
				limpar();
				printfCliente(cf, i);
				editarCadastro(cf, i, cont);
				i = cont;
			}
		}
	}

	int buscaConfirmaCadastro(struct cadastroF cf[], int cont, char cpf[12]){

		int resposta = 0, i, existe = -1;
		char reativacao;

		for(i = 0; i < cont; i++){
			if(strcmp(cf[i].cpf, cpf) == 0){
				existe = 1;
				if(cf[i].status == 1){
					cf[i].pontos = cf[i].pontos + 200;
				}else{
					printf("\n\tConta encontrada está atualmente desativada, deseja reativá-la? S | N\n\n\t");
					scanf("%c", &reativacao);
					varrer();

					reativacao = toupper(reativacao);

					if(reativacao == 'S'){
						cf[i].status = 1;
						cf[i].pontos = cf[i].pontos + 200;
					}
					printf("\nObrigado por comprar seu ingressos na MBM CINEMAX!\n");
					Sleep(1500);
				}

				i = cont;
			}
		}
		return existe;
	}

	void mostrarTodasCadeiras(struct salas s[]){
		for(int i = 0; i < 4; i++){
			printf("\n\nSala %d \n\n", i+1);
			for(int l = 0; l < 5; l++){
				printf("\n\t   ._______________________________________.");
				printf("\n\t   |   |   |   |   |   |   |   |   |   |   |\n");
				printf("\t%d  | ", l+1);
				for(int c = 0; c < 10; c++){
					printf("%c | ", s[i].matrix[l][c]);
				}
			}
		}
		pausar();
	}
	void mostrarSessao(struct salas s[], int sessao){
			printf("\n\n\n\t    ");
			for(int j = 0; j < 10; j++){
					printf(" %d  ", j+1);
				}
			for(int l = 0; l < 5; l++){
				printf("\n\t   ._______________________________________.");
				printf("\n\t   |   |   |   |   |   |   |   |   |   |   |\n");
				printf("\t%d  | ", l+1);
				for(int c = 0; c < 10; c++){
					printf("%c | ", s[sessao].matrix[l][c]);
				}
			}
			printf("\n\n\n\t\t\t     TELA");
			printf("\n         \\___________________________________________/");

	}

	void compraCadeiras(struct salas s[], int sessao,int qntdIngressos){

		int linha, coluna, reserva, l, c, verificaCadeira;

		reserva = qntdIngressos;

		if(reserva > 0){
			do{
				system("cls");
				sessaoEscolhida(sessao+1);
				mostrarSessao(s, sessao);

				printf("\n\nInforme a linha: ");
				varrer();
				scanf("%d", &linha);
				varrer();
				printf("\nInforme a coluna: ");
				scanf("%d", &coluna);
				varrer();
				if(s[sessao].matrix[linha-1][coluna-1] == ' '){
					s[sessao].matrix[linha-1][coluna-1] = 'X';
					verificaCadeira = 1;
					reserva = reserva - 1;
				}else{
					verificaCadeira = 0;
					printf("\nCadeira já ocupada!\n");
					Sleep(800);
				}
		}while(verificaCadeira == 0 || reserva > 0);
		system("cls");
		mostrarSessao(s, sessao);
	}


	}

	////////////////////// FUNÇOES ////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(){

    setlocale(LC_ALL, "Portuguese");
    SetConsoleOutputCP (28591); // leitura da tabela Latina (escrita)
    SetConsoleCP(28591);//Acentuação para funções (leitura) funções na bib windows

    ////////////////////// VARIAVEIS ////////////////////////////////////////////////////////////////////////////////////////////////////////

    int opEdicao;
    // cinema / ingressos
    int qntdIngressos;
	char confirmar;

	// fidelidade
	int contFidelidade;
	struct cadastroF cf[500];
	char novoCadastro;

	struct salas s[4];

	// busca
	int opBusca;
	char cpfBusca[12];

    // vars escolhas / switch
    int escolhaMenu, escolhaSessao;
    // vars de verificação
    int verificaSessao, verificaBusca, verificaCPF;

    char confirmarCadastro;
    ////////////////////// VARIAVEIS ////////////////////////////////////////////////////////////////////////////////////////////////////////

	int i;

    for(i = 0; i < 4; i++){
    	s[i].salaCadeiras = 50;
		for(int l = 0; l < 5; l++){
			for(int c = 0; c < 10; c++){
				s[i].matrix[l][c] = ' ';
			}
		}
	}
