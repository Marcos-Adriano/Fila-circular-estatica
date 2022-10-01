#include <stdio.h>
#include <locale.h>
#define TAM_FILA 10


// Marcos Adriano de Vasconcelos Gonçalves ;
// Fila circular estatica

typedef struct Fila Fila;

struct Fila {
	int vetor[TAM_FILA];	//vetor de armazenamento de dados.
	int quantidade;			//quantidade de valores que estão na fila.
	int inicio, final;		//apontadores de inicio e final da fila.
	int contador;           //quantidade de vezes que foi adicionada uma senha a fila.
	int cont;
};

void inicia_fila(Fila *a) {   //inicializando a fila.
	a->quantidade = 0;
	a->inicio = 0;
	a->final = -1;
	a->contador = 0;
}

int mostrarFilaCompleta(Fila *a){ 
	int i, fim;
	
	if (a->final > -1) {
		fim = a->final; 
	}
	else {
		fim = TAM_FILA - 1;
	}
	i = a->inicio;
	
	if(a->quantidade != 0){
		printf(" Fila de espera: ");
		while (i != fim) { 
			printf("[%d]  ", a->vetor[i]);
			if (i == TAM_FILA - 1) { 
				i = 0;
			}
			else {
				i++;
			}
		}
		printf("[%d]", a->vetor[i]);
		printf("\n");	
	}
	else if(a->quantidade == 0){
		printf(" A fila está vazia!\n");
	}
}

void insere_fila(Fila *a, int num) { 
	
	if (a->quantidade < TAM_FILA) {
		a->vetor[a->final + 1] = num;
		if (a->final + 1< TAM_FILA-1) {
			a->final++;
		}
		else {
			a->final = -1;
		}
		a->quantidade++;
	}
	else {
		printf(" A fila está cheia!\n");
	}
} 

void remove_fila(Fila *a) {
	
	if (a->quantidade > 0) {
		printf(" Senha [%d], comparecer ao atendimento! \n", a->vetor[a->inicio]);
		if (a->inicio < TAM_FILA - 1) {
			a->inicio++;
		}
		else {
			a->inicio = 0;
		}
		a->quantidade = a->quantidade - 1;
		a->vetor[a->inicio - 1] = 0;
	}
	else {
		printf(" A fila está vazia!\n");
	}
}

int pegarNumero(Fila *a){
	int i, num, aux;
	printf(" Digite a senha: ");
	scanf("%d", &num);
	printf("\n");
	
	for (i=0; i < TAM_FILA; i++){
		if(num == a->vetor[i]){
			aux = i;
		}
 	}
	return aux;
}

int contarNaFrente(Fila *a){
	int i, fim, num;
	num = pegarNumero(a);
	i = a->inicio;
	
	if (num == a->inicio){
		printf(" Esta é a próxima senha da vez! \n");
	}
	else{
		while (i != num) {  
			a->contador++;
			if (i == TAM_FILA - 1) {  
				i = 0;
			}
			else {
				i++; 
			}
		}
		printf(" Quantidade de senhas na frente: %d\n", a->contador);
		a->contador = 0;
	}
}

void gerarSenha(Fila *a){
	srand((unsigned)time(NULL));
	int aux = 0;
	int i;
	int senha;
	
	if (a->quantidade < TAM_FILA){
		while (aux != -1){
			senha =(rand() % 899) + 100;
			for(i = 0; i <= TAM_FILA - 1; i++){ 
				if(a->vetor[i] != senha){
					aux++;
				}
			}
			if (aux == TAM_FILA){
				insere_fila(a, senha);
				printf(" Nova senha --> %d\n",senha);
				aux = -1;
			}	
		}
	}
	else {
		printf(" A fila está cheia! \n");
	}
}

int main(){
	setlocale(LC_ALL, "Portuguese");
	Fila f;
	inicia_fila(&f);
	int escolha;
    int a = -1;
    while (a != 0){
    	printf("\n*****************************************\n");
        printf(" Escolha uma opção: \n 1 - Gerar nova senha\n 2 - Mostrar fila de espera\n 3 - Chamar proxima senha\n 4 - Quantidade de senhas na frente\n 5 - Sair ");
        printf("\n*****************************************\n\n");
        printf(" Opção: ");
		scanf("%d", &escolha);
		printf("\n*****************************************\n\n");	
        switch(escolha){
        	case 1:
        		gerarSenha(&f);
        		break;
        	case 2:
        		mostrarFilaCompleta(&f);
				break;
        	case 3:
        		remove_fila(&f);
        		break;
        	case 4:
				contarNaFrente(&f);
        		break;
        	case 5:
				a = 0;
        		break;
        	default:
        		printf("Escolha inválida!\n");
        		break;
		}
    }
}
