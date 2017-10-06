#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>

/*
Nome: Sistema para controle de Supermercado
Autor: Carlos Eduardo T. da Silva
Data: 27/02/2017
Função: Realizar compras, vendas, consultar estoque e saldo de um Supermercado
*/

typedef struct{     				//Declaração de estrutura registro
	int cod;						//Código do produto
	char nome[21];					//Nome do produto armazenado em vetor de até 30 caracteres
	int qtd;						//Quantidade do produto	
	float preco;					//Preço unitario do produto(compra)
}REGProduto;
REGProduto produto[99];				//Parâmetro do registro definido como 'produto' com até 99 produtos

//Protótipos das funções

//Função 1: Insere produto no estoque
int insereProduto (int *contador, float *saldo);
//Função 2: Realizar uma venda
int venda (int *contador, float *saldo);
//Função 3: Consultar o Estoque dos produtos
void imprimeEstoque (int *contador);
//Função 4: Consultar o Saldo do Caixa
void consultaSaldo(float *saldo);

//FUNÇÃO PRINCIPAL
int main(){
	setlocale(LC_ALL,"Portuguese");						//Acentuação
	//Declaração das Variáveis da função principal
	int func,count=0;					//func: Função Desejada; count: Contador qtd de produtos, passado como *contador para todas as funções
	int sair=1;   								//sair: usada no loop do switch/case
	float saldomain=3000;						//saldomain é o saldo inicial, passado como *saldo para todas as funções
	
	
	while(sair){
	
		//Menu do sistema
		system("clear || cls"); 						//Comando para limpar a Tela, onde "clear" use-se para SO Linux e "cls" para Windows
		printf("\t\tSUPERMERCADO JOOJ\n\t\t\tMENU\n\n");
	   	printf("[1].Inserir Produto\t[2].Realizar Venda\n[3].Consultar Estoque\t[4].Consultar Saldo\n[0].Sair\n");
		printf("Código: ");					
		scanf("%d",&func);								//Leitura do código referente ao menu
		
		switch(func){									//Dependendo do valor de func, é executado os comandos do case
		case 1:     								 	//Caso o usuario digite 1, entra neste case
			insereProduto(&count, &saldomain);         	 //Chamada da função, utilizando saldo e o contador como parametro
			printf("\n\nAperte ENTER para continuar");
			getch();    					        	//Mesma função que o system("PAUSE"), porém sem a mensagem para continuar.
			break;										//Sair do case
	
		case 2:											//Caso digite 2
			imprimeEstoque(&count);						//Chamada da função imprimeEstoque
			venda(&count,&saldomain);					//Chamada da função venda
			printf("\nAperte ENTER para continuar");
			getch();
			break;
	
		case 3:											//Caso digite 3
			imprimeEstoque(&count);						//Chamada da função imprimeEstoque
			printf("\n\nAperte ENTER para continuar");
			getch();
			break;
	
		case 4:											//Caso digite 4
			consultaSaldo(&saldomain);					//Chamada da função consultaSaldo
			printf("\nAperte ENTER para continuar");
			getch();
			break;
		
		case 0:											//Caso digite 0
			printf("\t\tSaindo...");
			sair = 0;									//Variavel do swicht/case recebe 0, saindo do loop do menu
			break;
	
		default:										//Caso digite algum outro numero
			printf("\nCódigo Inválido!\nAperte ENTER para continuar");
			getch();
			break;
		}
	}
	
return 0;
}

//FUNÇÃO 1: INSERE PRODUTO NO ESTOQUE

int insereProduto (int *contador, float *saldo){  //'*contador' serve para fazer o controle do total de produtos
	
	//Declaração das variaveis locais da função
	float checa_saldo=*saldo;					//Checa saldo serve para conferir se o saldo possibilitará a compra
												//Caso o saldo fique negativo,a compra é cancelada
												
	//Entrada de dados
	printf("\nInsira o Código do Produto: ");
	scanf("%d",&produto[*contador].cod);		//Leitura do codigo do produto em função do contador
	
	for(int i=0;i<*contador;i++){
		while(produto[*contador].cod==produto[i].cod){			//Enquanto o código digitado ja existir
			printf("\n\tCódigo '%d' em uso, favor escolher outro!\nCódigo: ",produto[i].cod);
			scanf("%d",&produto[*contador].cod);				//O Usuário terá de escolher outro
			i=0;
		}
	}
		
	printf("\nNome: ");
	scanf("%s",&produto[*contador].nome);		//Leitura do nome do produto em função do contador
		
	printf("\nQtd: ");
	scanf("%d",&produto[*contador].qtd);		//Leitura da quantidade do produto em função do contador
	
	printf("\nPreço Unitário: ");
	scanf("%f",&produto[*contador].preco);		//Leitura do preço do produto em função do contador
	
	checa_saldo=*saldo-((produto[*contador].qtd)*(produto[*contador].preco)); //Calculo do saldo após a compra dos produtos
	if(checa_saldo<0){
		printf("\n\t\tAVISO: SALDO NEGATIVO\n\t\tCOMPRA CANCELADA\n");		//Se o saldo for menor que 0, é emitido um aviso na tela
																			//o saldo permanecerá e todos os dados serao perdidos
																			//e a compra será cancelada
	}												
	else{
		*saldo=checa_saldo;								//Caso o saldo seja positivo após a compra, saldo recebe o valor atual
		*contador=*contador+1;							//Incremento do contador,ou seja da qtd de produtos
	}
			
} 

//FUNÇÃO 2: REALIZAR UMA VENDA

int venda (int *contador, float *saldo){
	
	setlocale(LC_ALL,"Portuguese");
	
	//Declaração das variaveis locais da função
	int codvenda,qtdvenda;		//codvenda é o código do produto que o usuário deseja vender, e qtdvenda sua quantidade
	float precototal;			//precototal é usado para calcular o valor total da venda
	
	printf("\n\nInsira o Código do produto a ser vendido: ");
	scanf("%d",&codvenda);		//Leitura do código do produto a ser vendido
	
	for(int i=0;i<*contador;i++){
		
		if(codvenda==produto[i].cod){	//Caso o código lido exista
			printf("Insira a quantidade a ser vendida do produto : ");
			scanf("%d",&qtdvenda);		//Lê-se a quantidade a ser vendida
				if(qtdvenda<=produto[i].qtd && qtdvenda>0){	//Se for possivel, ou seja, se o estoque possuir o montante para a venda
					
					precototal= qtdvenda * (produto[i].preco*1.25);	//Calcula-se o preço total, onde multiplica-se por 1.25para obter lucro sobre o produto
				
					printf("\nNome\t\t\t\tPreço(Venda)\t\tTotal");
					printf("\n%s \t\t R$ %.2f \t\t R$ %.2f \n",produto[i].nome,produto[i].preco*1.25,precototal);
					printf("\n\t\tVenda Efetuada com Sucesso");
					
					produto[i].qtd=(produto[i].qtd) - (qtdvenda); //Tira-se do estoque o montante que foi vendido
					
					*saldo= (*saldo) + (precototal);			//Soma-se o valor de venda ao saldo
					return 0;
					
				}
				else{		//Se não for possivel a venda por causa de estoque insuficiente
					printf("\n\t\tQUANTIDADE NO ESTOQUE INSUFICIENTE !\n\t\t\t VENDA CANCELADA!\n");
					return 0;
				}
				
		}	
	}
	printf("\n\t\tCódigo Inválido\n");  //Caso o código não exista no sitema,imprime-se um aviso
}

//FUNÇÃO 3: CONSULTAR O ESTOQUE DOS PRODUTOS

void imprimeEstoque (int *contador){	
	setlocale(LC_ALL,"Portuguese");
	
	//Declaração das variaveis locais da função
	int alinhar;				//alinhar serve para padronizar as strings com o nome do produto, deixando-as de mesmo tamanho
	
	printf("\nCódigo \t Nome\t\t\tQtd \t Preço(Compra)\tPreço(Venda) \n");	
	
	for(int i=0;i<*contador;i++){
		alinhar=strlen(produto[i].nome);		//alinhar recebe o tamanho da string
		
		for(int j=alinhar;j<20;j++){			//a partir desse tamanho, até 20
			produto[i].nome[j]=' ';				//a string recebe espaços, assim todas as strings ficam de 'tamanho 20'
		}
		
		printf("\n %d \t %s \t %d \t R$ %.2f \t R$ %.2f  ",produto[i].cod,produto[i].nome,produto[i].qtd,produto[i].preco,produto[i].preco*1.25);
	}
					
}

//FUNÇÃO 4: CONSULTAR O SALDO DO CAIXA

void consultaSaldo(float *saldo){
	printf("\nSALDO R$%.2f\n",*saldo);				//É mostrado o Saldo na tela do Usuário
}
