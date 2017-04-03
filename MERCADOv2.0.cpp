#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>

/*
Nome: Sistema para controle de Supermercado
Autor: Carlos Eduardo T. da Silva
Data: 27/02/2017
Fun��o: Realizar compras, vendas, consultar estoque e saldo de um Supermercado
*/

typedef struct{     				//Declara��o de estrutura registro
	int cod;						//C�digo do produto
	char nome[21];					//Nome do produto armazenado em vetor de at� 30 caracteres
	int qtd;						//Quantidade do produto	
	float preco;					//Pre�o unitario do produto(compra)
}REGProduto;
REGProduto produto[99];				//Par�metro do registro definido como 'produto' com at� 99 produtos

//Prot�tipos das fun��es

//Fun��o 1: Insere produto no estoque
int insereProduto (int *contador, float *saldo);
//Fun��o 2: Realizar uma venda
int venda (int *contador, float *saldo);
//Fun��o 3: Consultar o Estoque dos produtos
void imprimeEstoque (int *contador);
//Fun��o 4: Consultar o Saldo do Caixa
void consultaSaldo(float *saldo);

//FUN��O PRINCIPAL
int main(){
	setlocale(LC_ALL,"Portuguese");						//Acentua��o
	//Declara��o das Vari�veis da fun��o principal
	int func,count=0;					//func: Fun��o Desejada; count: Contador qtd de produtos, passado como *contador para todas as fun��es
	int sair=1;   								//sair: usada no loop do switch/case
	float saldomain=3000;						//saldomain � o saldo inicial, passado como *saldo para todas as fun��es
	
	
	while(sair){
	
		//Menu do sistema
		system("clear || cls"); 						//Comando para limpar a Tela, onde "clear" use-se para SO Linux e "cls" para Windows
		printf("\t\tSUPERMERCADO JOOJ\n\t\t\tMENU\n\n");
	   	printf("[1].Inserir Produto\t[2].Realizar Venda\n[3].Consultar Estoque\t[4].Consultar Saldo\n[0].Sair\n");
		printf("C�digo: ");					
		scanf("%d",&func);								//Leitura do c�digo referente ao menu
		
		switch(func){									//Dependendo do valor de func, � executado os comandos do case
		case 1:     								 	//Caso o usuario digite 1, entra neste case
			insereProduto(&count, &saldomain);         	 //Chamada da fun��o, utilizando saldo e o contador como parametro
			printf("\n\nAperte ENTER para continuar");
			getch();    					        	//Mesma fun��o que o system("PAUSE"), por�m sem a mensagem para continuar.
			break;										//Sair do case
	
		case 2:											//Caso digite 2
			imprimeEstoque(&count);						//Chamada da fun��o imprimeEstoque
			venda(&count,&saldomain);					//Chamada da fun��o venda
			printf("\nAperte ENTER para continuar");
			getch();
			break;
	
		case 3:											//Caso digite 3
			imprimeEstoque(&count);						//Chamada da fun��o imprimeEstoque
			printf("\n\nAperte ENTER para continuar");
			getch();
			break;
	
		case 4:											//Caso digite 4
			consultaSaldo(&saldomain);					//Chamada da fun��o consultaSaldo
			printf("\nAperte ENTER para continuar");
			getch();
			break;
		
		case 0:											//Caso digite 0
			printf("\t\tSaindo...");
			sair = 0;									//Variavel do swicht/case recebe 0, saindo do loop do menu
			break;
	
		default:										//Caso digite algum outro numero
			printf("\nC�digo Inv�lido!\nAperte ENTER para continuar");
			getch();
			break;
		}
	}
	
return 0;
}

//FUN��O 1: INSERE PRODUTO NO ESTOQUE

int insereProduto (int *contador, float *saldo){  //'*contador' serve para fazer o controle do total de produtos
	
	//Declara��o das variaveis locais da fun��o
	float checa_saldo=*saldo;					//Checa saldo serve para conferir se o saldo possibilitar� a compra
												//Caso o saldo fique negativo,a compra � cancelada
												
	//Entrada de dados
	printf("\nInsira o C�digo do Produto: ");
	scanf("%d",&produto[*contador].cod);		//Leitura do codigo do produto em fun��o do contador
	
	for(int i=0;i<*contador;i++){
		while(produto[*contador].cod==produto[i].cod){			//Enquanto o c�digo digitado ja existir
			printf("\n\tC�digo '%d' em uso, favor escolher outro!\nC�digo: ",produto[i].cod);
			scanf("%d",&produto[*contador].cod);				//O Usu�rio ter� de escolher outro
			i=0;
		}
	}
		
	printf("\nNome: ");
	scanf("%s",&produto[*contador].nome);		//Leitura do nome do produto em fun��o do contador
		
	printf("\nQtd: ");
	scanf("%d",&produto[*contador].qtd);		//Leitura da quantidade do produto em fun��o do contador
	
	printf("\nPre�o Unit�rio: ");
	scanf("%f",&produto[*contador].preco);		//Leitura do pre�o do produto em fun��o do contador
	
	checa_saldo=*saldo-((produto[*contador].qtd)*(produto[*contador].preco)); //Calculo do saldo ap�s a compra dos produtos
	if(checa_saldo<0){
		printf("\n\t\tAVISO: SALDO NEGATIVO\n\t\tCOMPRA CANCELADA\n");		//Se o saldo for menor que 0, � emitido um aviso na tela
																			//o saldo permanecer� e todos os dados serao perdidos
																			//e a compra ser� cancelada
	}												
	else{
		*saldo=checa_saldo;								//Caso o saldo seja positivo ap�s a compra, saldo recebe o valor atual
		*contador=*contador+1;							//Incremento do contador,ou seja da qtd de produtos
	}
			
} 

//FUN��O 2: REALIZAR UMA VENDA

int venda (int *contador, float *saldo){
	
	setlocale(LC_ALL,"Portuguese");
	
	//Declara��o das variaveis locais da fun��o
	int codvenda,qtdvenda;		//codvenda � o c�digo do produto que o usu�rio deseja vender, e qtdvenda sua quantidade
	float precototal;			//precototal � usado para calcular o valor total da venda
	
	printf("\n\nInsira o C�digo do produto a ser vendido: ");
	scanf("%d",&codvenda);		//Leitura do c�digo do produto a ser vendido
	
	for(int i=0;i<*contador;i++){
		
		if(codvenda==produto[i].cod){	//Caso o c�digo lido exista
			printf("Insira a quantidade a ser vendida do produto : ");
			scanf("%d",&qtdvenda);		//L�-se a quantidade a ser vendida
				if(qtdvenda<=produto[i].qtd && qtdvenda>0){	//Se for possivel, ou seja, se o estoque possuir o montante para a venda
					
					precototal= qtdvenda * (produto[i].preco*1.25);	//Calcula-se o pre�o total, onde multiplica-se por 1.25para obter lucro sobre o produto
				
					printf("\nNome\t\t\t\tPre�o(Venda)\t\tTotal");
					printf("\n%s \t\t R$ %.2f \t\t R$ %.2f \n",produto[i].nome,produto[i].preco*1.25,precototal);
					printf("\n\t\tVenda Efetuada com Sucesso");
					
					produto[i].qtd=(produto[i].qtd) - (qtdvenda); //Tira-se do estoque o montante que foi vendido
					
					*saldo= (*saldo) + (precototal);			//Soma-se o valor de venda ao saldo
					return 0;
					
				}
				else{		//Se n�o for possivel a venda por causa de estoque insuficiente
					printf("\n\t\tQUANTIDADE NO ESTOQUE INSUFICIENTE !\n\t\t\t VENDA CANCELADA!\n");
					return 0;
				}
				
		}	
	}
	printf("\n\t\tC�digo Inv�lido\n");  //Caso o c�digo n�o exista no sitema,imprime-se um aviso
}

//FUN��O 3: CONSULTAR O ESTOQUE DOS PRODUTOS

void imprimeEstoque (int *contador){	
	setlocale(LC_ALL,"Portuguese");
	
	//Declara��o das variaveis locais da fun��o
	int alinhar;				//alinhar serve para padronizar as strings com o nome do produto, deixando-as de mesmo tamanho
	
	printf("\nC�digo \t Nome\t\t\tQtd \t Pre�o(Compra)\tPre�o(Venda) \n");	
	
	for(int i=0;i<*contador;i++){
		alinhar=strlen(produto[i].nome);		//alinhar recebe o tamanho da string
		
		for(int j=alinhar;j<20;j++){			//a partir desse tamanho, at� 20
			produto[i].nome[j]=' ';				//a string recebe espa�os, assim todas as strings ficam de 'tamanho 20'
		}
		
		printf("\n %d \t %s \t %d \t R$ %.2f \t R$ %.2f  ",produto[i].cod,produto[i].nome,produto[i].qtd,produto[i].preco,produto[i].preco*1.25);
	}
					
}

//FUN��O 4: CONSULTAR O SALDO DO CAIXA

void consultaSaldo(float *saldo){
	printf("\nSALDO R$%.2f\n",*saldo);				//� mostrado o Saldo na tela do Usu�rio
}