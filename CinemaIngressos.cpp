#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<locale.h>
#include<curses.h>
#include<time.h>
#include<ctype.h>
#include<unistd.h>
#include<iostream>
#include<array>
#include<cstdio>
#include<cstring>
#include<thread>
#include "MyBibTrab.h"
using namespace std;



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
		cin >> cf[contF].nome;
		varrer();		
		
		do{
			
			printf("\n\tInforme o CPF: ");
			cin >> cf[contF].cpf;
			varrer();
			
  			verificaCPF = verificaCadastroCPF(cf, cf[contF].cpf ,contF);
  			
		}while(verificaCPF == 1);
		
		printf("\n\tInforme o telefone: ");
		cin >> cf[contF].telefone;
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
					cin >>nome;
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
						cin >> cpf;
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
					cin >> telefone;
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
		cin >> cpf;
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
					sleep(1500);
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
		//pausar();
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
					sleep(800);
				}
		}while(verificaCadeira == 0 || reserva > 0);
		system("cls");
		mostrarSessao(s, sessao);
	}


	}

	////////////////////// FUNÇOES ////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(){

    setlocale(LC_ALL, "Portuguese");
    //SetConsoleOutputCP (28591); // leitura da tabela Latina (escrita)
    //SetConsoleCP(28591);//Acentuação para funções (leitura) funções na bib windows

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


    strcpy(cf[contFidelidade].nome, "Bruno");
	strcpy(cf[contFidelidade].cpf, "11259285901");
	strcpy(cf[contFidelidade].telefone, "(41)98846-6530");
	cf[contFidelidade].idade = 22;
	cf[contFidelidade].id = 1;
	cf[contFidelidade].status = 0;
	cf[contFidelidade].pontos = 0;
	contFidelidade = 1;

	strcpy(cf[contFidelidade].nome, "Marina Super Muito Tonga");
	strcpy(cf[contFidelidade].cpf, "123456789");
	strcpy(cf[contFidelidade].telefone, "(41)98846-6530");
	cf[contFidelidade].idade = 22;
	cf[contFidelidade].id = 2;
	cf[contFidelidade].status = 1;
	cf[contFidelidade].pontos = 0;
	contFidelidade = 2;

	strcpy(cf[contFidelidade].nome, "Mariana");
	strcpy(cf[contFidelidade].cpf, "1234512345");
	strcpy(cf[contFidelidade].telefone, "(41)98846-6530");
	cf[contFidelidade].idade = 22;
	cf[contFidelidade].id = 3;
	cf[contFidelidade].status = 1;
	cf[contFidelidade].pontos = 0;
	contFidelidade = 3;

    do{
    	limpar();
		// printar o menu principal
	    menuPrincipal();
	    // receber a resposta
	    scanf("%d", &escolhaMenu);
	    varrer(); // limpa o lixo do teclado
	    limpar(); // limpa a tela

	    switch(escolhaMenu){
	    	case 0:
	    		// case 0 apenas para evitar que o switch caia no default
	    	break;

	    	case 1:
	    		// Case 1 - Comprar ingresso
	    		// usuario devera escolher uma sessao que exista, caso contrario ele entra em um looping
	    		// enquanto verificaSessao for == 0, programa não continua, entra no loop de escolher a sessao
	    		do{
	    			verificaSessao = -1;
					printf("\n\tCOMPRA DE INGRESSOS");

					menuFilmes();
					printf("\n\n\tSessão escolhida: ");
					scanf("%d", &escolhaSessao);
					varrer();
					if(escolhaSessao < 0){
						verificaSessao = 0;
					}else if(escolhaSessao == 0){
						verificaSessao = -1;
						saindo();
					}else if(escolhaSessao > 0){
						// printar e receber o numero da sessao como retorno/ caso informe um valor invalido, retorno = 0
						verificaSessao = sessaoEscolhida(escolhaSessao);
					}
				}while( verificaSessao == 0);

				// verificar se há cadeiras na sessao-1(posição no vetor) escolhida
				if(s[verificaSessao-1].salaCadeiras > 0){
					do{
						limpar();
						// printar na tela a sessao escolhida
						sessaoEscolhida(verificaSessao);
						printf(" - Ingressos Restantes: %d", s[verificaSessao-1].salaCadeiras);

						mostrarSessao(s, verificaSessao - 1);

						printf("\n\n\tInforme a quantidade de ingressos?\n\t");
						scanf("%d", &qntdIngressos);
						varrer();

						// caso seja informado um valor negativo, mostra erro.
						if(qntdIngressos < 0){
							printf("\n\tFavor informar um valor valido!\n");
							sleep(800);
						}else if(qntdIngressos == 0){

							saindo();

						}else if(qntdIngressos > 0){
							// verificar se a quantidade de cadeiras restantes - qntd de ingressos informados, sao maiores ou igual a 0
							// ex: 4 cadeiras restantes - 6 ingressos a serem comprados = nao entra no if, pois a sessao nao possui 6 cadeiras restantes
							if(s[verificaSessao-1].salaCadeiras - qntdIngressos >= 0){
								//funcao para comprar as cadeiras desejadas
								compraCadeiras(s, verificaSessao-1, qntdIngressos);
								// decremento nas cadeiras da sessao
								s[verificaSessao-1].salaCadeiras = s[verificaSessao-1].salaCadeiras - qntdIngressos;

								sessaoEscolhida(verificaSessao);
								mostrarSessao(s, verificaSessao - 1);

								printf("\n\n\n\tPossui cadastro fidelidade? S | N\n\n\t");
								varrer();
								scanf("%c", &confirmarCadastro);
								//varrer;

								confirmarCadastro = toupper(confirmarCadastro);

								int vefificaBuscaCPF = 0;

								if(confirmarCadastro == 'S'){

									do{
										if(vefificaBuscaCPF == -1){
											printf("\nCPF não encontrado. Tente novamente.\n\n");
										}

										printf("\n\tInforme o CPF: ");
										varrer();
										cin >> cpfBusca;
										varrer();

										vefificaBuscaCPF = buscaConfirmaCadastro(cf, contFidelidade, cpfBusca);

									}while(vefificaBuscaCPF <= 0);

								}else{
									printf("\n\n\tDeseja efetuar um novo cadastro? S | N\n\t");
									varrer();
									scanf("%c", &novoCadastro);
									varrer();
									novoCadastro = toupper(novoCadastro);
									if(novoCadastro == 'S'){
										contFidelidade++;
										int posicao = cadastroFidelidade(cf, contFidelidade);
										cf[posicao].pontos = cf[posicao].pontos + 200;
										limpar();
									}

								}

							}else{
								qntdIngressos = -1;
								printf("Quantidade de ingressos indisponivel. Restam apenas %d", s[verificaSessao-1].salaCadeiras);
								//pausar();
							}
						}
					// verificar, caso entre com numero negativo ou entrar com um numero maior que o numero de cadeiras total da sessao, entra em um loop
					}while(qntdIngressos < 0);
				}
			break;

			case 2:
				limpar();
				printf("\nCadastro Cliente Fidelidade!\n");

				// sempre ir aumentando o tamanho do vetor dinamicamente
				contFidelidade = contFidelidade + 1;

				// chama a funcao para cadastrar, passa cf(struct) e contFidelidade(tamanho do vetor)
				cadastroFidelidade(cf, contFidelidade);

			break;

			// listar todos os cadastros
			case 3:

				if(contFidelidade > 0){

					limpar();
					printf("\n\tLista de clientes cadastrados\n\n");
					printf("Total de clientes: %d", contFidelidade);

					listarClientes(cf, contFidelidade);
					//pausar();
				}
			break;

			case 4:
				do{
					limpar();
					printf("\n\tBUSCA / EDIÇÃO\n\n");
					menuBusca();
					printf("Informe a opção de busca: ");
					scanf("%d", &opBusca);
					varrer();

					switch(opBusca){
						case 0:
							saindo();
						break;
						case 1:
							printf("\tCADASTROS ATIVOS\n");
							verificaBusca = buscarAtivos(cf, contFidelidade);

						break;
						case 2:
							printf("\tCADASTROS INATIVOS\n");
							verificaBusca = buscarInativos(cf, contFidelidade);

						break;
						case 3:
							listarClientes(cf, contFidelidade);
							verificaBusca = 1;
						break;
						default:
							printOpInva();
							opBusca = -1;
						break;

					}

					if((opBusca == 1 || opBusca == 2 || opBusca == 3) && verificaBusca == 1){
						printf("Para EDITAR digite 1 / Para SAIR digite 0\n");
						scanf("%i", &opEdicao);
						varrer();

						if(opEdicao == 1){
							buscaCPF(cf, contFidelidade);
						}
					}

				}while(opBusca == -1);
			break;

			case 5:
				limpar();
				menuInicio();
			break;

			default:
				printOpInva();
			break;
		}

    }while(escolhaMenu != 0);

    saindo();

    return 0;
}
