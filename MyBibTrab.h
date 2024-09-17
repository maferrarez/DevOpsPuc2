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

void saindo(){
	printf("\nSaindo");
	sleep(300);
	printf(".");
	sleep(300);
	printf(".");
	sleep(300);
	printf(".");
	sleep(300);
}

void linha(){
	printf("\n\n----------------------------------------------------------------\n\n");
}

void limpar(){
	system("cls");
}

void varrer(){
	fflush(stdin);
}

void pausar(){
	getch();
}

void printOpInva(){
	printf("\n\tOpção inválida! Tente novamente");
	sleep(1000);
	limpar();
}

void menuPrincipal(){
	printf(	"1 - Comprar Ingresso\n"
			"2 - Cadastro Fidelidade\n"
			"3 - Listar cadastrados\n"
			"4 - Buscar / Editar \n"
			"5 - Status das sessões\n"
			"\n0 - Sair\n\n");
}

void menuFilmes(){
	printf("\n\n\tSESSÃO 01 - SALA 01 - HORARIO 12:00 - Star Wars Episódio 9 - A Ascensão Skywalker\n");
	printf("\tSESSÃO 02 - SALA 01 - HORARIO 15:00 - Star Wars Episódio 9 - A Ascensão Skywalker\n\n");
	printf("\tSESSÃO 03 - SALA 02 - HORARIO 12:00 - Harry Poket - E a Ordem do Félix\n");
	printf("\tSESSÃO 04 - SALA 02 - HORARIO 15:00 - Harry Poket - E a Ordem do Félix\n");
}

int sessaoEscolhida(int escolha){

	int resposta;
	int qntdIngressos;

	switch(escolha){
		case 1:
			resposta = 1;
			limpar();
			printf("\n\n\tStar Wars Episódio 9 - A Ascensão Skywalker\n\n\tSESSÃO 01 - SALA 01 - HORARIO 12:00");
		break;
		case 2:
			resposta = 2;
			limpar();
			printf("\n\n\tStar Wars Episódio 9 - A Ascensão Skywalker\n\n\tSESSÃO 02 - SALA 01 - HORARIO 15:00");
		break;
		case 3:
			resposta = 3;
			limpar();
			printf("\n\n\tHarry Poket - E a Ordem do Félix\n\n\tSESSÃO 03 - SALA 02 - HORARIO 12:00");
		break;
		case 4:
			resposta = 4;
			limpar();
			printf("\n\n\tHarry Poket - E a Ordem do Félix\n\n\tSESSÃO 04 - SALA 02 - HORARIO 15:00");
		break;

		default:
			printOpInva();
			resposta = 0;
		break;
	}
	return resposta;
}

void menuBusca(){
	printf(	"1 - Ativos\n"
			"2 - Inativos\n"
			"3 - Todos\n"
			"\n0 - Sair\n\n");
}

void menuOpcoesEdicao(){
	printf(	"\n\nInfome o que deseja editar\n\n1 - Ativar / Desativar\n"
			"2 - Nome\n"
			"3 - CPF\n"
			"4 - Telefone\n"
			"5 - Idade\n"
			"\n0 - Sair\n\n");
}

int confirmarEdicao(){
	char confirmar;
	int resposta;

	printf("\n\nConfirmar edição? S para sim | N para cancelar\n\t");
	scanf("%c", &confirmar);
	varrer();
	confirmar = toupper(confirmar);

	if(confirmar == 'S'){
		return resposta = 1;
	}else{
		return resposta = 0;
	}
}

void menuInicio(){

	printf(	"\t\t _________________________________________________________________________________________________\n"
		  	"\t\t |                                                                                               |\n"
			"\t\t |                                           ______                                              |\n"
			"\t\t |                        |\\            /|  |   _  |   |\\            /|                          |\n"
			"\t\t |                        | \\          / |  |  |_| |   | \\          / |                          |\n"
			"\t\t |                        |  \\        /  |  |   __/_   |  \\        /  |                          |\n"
			"\t\t |                        |   \\      /   |  |   __  |  |   \\      /   |                          |\n"
			"\t\t |                        |    \\    /    |  |  |  | |  |    \\    /    |                          |\n"
			"\t\t |                        |     \\  /     |  |  |__| |  |     \\  /     |                          |\n"
			"\t\t |                        |      \\/      |  |_______|  |      \\/      |                          |\n"
			"\t\t |                                                                                               |\n"
			"\t\t |                                                                                               |\n"
			"\t\t |                                                                                               |\n"
			"\t\t |                                                                                               |\n"
			"\t\t |                                                                                               |\n"
			"\t\t |                                                                                               |\n"
			"\t\t |                                                                                               |\n"
			"\t\t |                                                                                               |\n"
			"\t\t |                                                                                               |\n"
			"\t\t |                                                                                               |\n"
			"\t\t |                                                                                               |\n"
			"\t\t |_______________________________________________________________________________________________|\n\n\n"


			"\t   _________________________      ________________________      ________________________      _________________________\n"
			"\t  |                         |    |                        |    |                        |    |                         |\n"
			"\t  |                         |    |                        |    |                        |    |                         |\n"
			"\t _____________________________  ____________________________  ____________________________  _____________________________  \n"
			"\t|                             ||                            ||                            ||                             | \n"
			"\t|                             ||                            ||                            ||                             | \n"
			"\t|                             ||                            ||                            ||                             | \n"
			"\t|                             ||                            ||                            ||                             | \n"
	"");

	pausar();
}
