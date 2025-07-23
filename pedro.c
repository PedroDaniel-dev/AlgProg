#include <stdio.h>
#include <string.h>
// Constantes para tamanhos máximos e valores padrão
#define MAX_CLIENTES 1000
#define TAM_NOME 101
#define TAM_CPF 15
#define TAM_DATA 11
#define TAM_TEL 16
#define TAM_EMAIL 51
#define DDD_DEFAULT "(21)"

struct cliente {
    char nome[TAM_NOME];
    char dataNascimento[TAM_DATA]; // 22032005
    char numTelefone[TAM_TEL];    // 21965759433
    char cpf[TAM_CPF];            //21411681711
};

const char *nomesMeses[] = {"","Janeiro","Fevereiro","Março","Abril","Maio",
    "Junho","Julho","Agosto","Setembro","Outubro","Novembro","Dezembro"};

void cadastroClientes(struct cliente clientes[], int *quantidade) {
    printf("Digite o nome: \n");
    getchar(); // Limpar buffer
    fgets(clientes[*quantidade].nome, TAM_NOME, stdin);
    printf("Digite a data de nascimento (DD/MM/AAAA): \n");
    scanf("%s", clientes[*quantidade].dataNascimento);
    printf("Digite o número de telefone: \n");
    scanf("%s", clientes[*quantidade].numTelefone);
    printf("Digite o CPF (com ou sem pontos): \n");
    scanf("%s", clientes[*quantidade].cpf);
    (*quantidade)++;
}

void exibirCliente(struct cliente c) {
    //Saida de informaçoes
    printf("Nome:%s\n", c.nome);
    printf("Nascimento:%s\n", c.dataNascimento);
    printf("Telefone:%s\n", c.numTelefone);
    printf("CPF:%s\n", c.cpf);
}

void validarCPF(int array[]) {
    int soma = 0;
    int j = 10;

    // Primeiro dígito verificador
    for (int i = 0; i <14; i++) {
        soma += array[i] * j;
        j--;
    }

    int resto = soma % 11;
    int primeiroDigito = (resto < 2) ? 0 : 11 - resto;

    soma = 0;
    j = 11;

    // Segundo dígito verificador
    for (int i = 0; i < 10; i++) {
        soma += array[i] * j;
        j--;
    }

    resto = soma % 11;
    int segundoDigito = (resto < 2) ? 0 : 11 - resto;

    // Verificação final
    if (array[9] == primeiroDigito && array[10] == segundoDigito) {
        printf("CPF válido!\n");
    } else {
        printf("CPF inválido!\n");
    }
}

void validarEmail()  {
    
}

void buscarCPF(struct cliente clientes[], int quantidade) {
    char cpfBuscado[TAM_CPF];
    printf("Digite o CPF a ser buscado.\n");
    scanf("%s", cpfBuscado);
    for (int i = 0; i < quantidade; i++) {
        if (strcmp(clientes[i].cpf, cpfBuscado) == 0) {
            exibirCliente(clientes[i]);
        }
    }
}

/*void buscarCPF(struct cliente clientes[], int quantidade) {
    printf("Digite o CPF a ser buscado.\n");
    int cpfBuscado;
    scanf("%d", &cpfBuscado);
    for (int i = 0; i < MAX_CLIENTES; i++) {
        if(cliente[i].cpf = cpfBuscado){
            exibirCliente(i)
        }
}*/

void buscarAniversariante(struct cliente clientes[], int quantidade, int mes){
    printf("Digite o mês para buscar aniversariantes:\n");
    int mesAniversario;
    scanf("%d", &mesAniversario);
    printf("Aniversários do mês %02d:\n", mes);
    for (int i = 0; i < MAX_CLIENTES; i++) {
        // Comparar com os dígitos do mês na string "DD/MM/AAAA"
        if ((clientes[i].dataNascimento[3] - '0') * 10 + (clientes[i].dataNascimento[4] - '0') == mes) {
            printf("%s - %s\n", clientes[i].nome, clientes[i].dataNascimento);
        }
    }
}

int main(){
    struct cliente clientes[MAX_CLIENTES];
    int mesAniversario;
    int escolha;
    int quantidaClientes = 0;
      printf("--------Bem-vindo!!!--------\n");
    /*do {
    printf("Bem-vindo!\nO que voce gostaria de fazer?\nSe quiser de fazer o cadastro digite (1)\nSe quiser Buscar por usuarios digite (2)\nSe quiser ver os aniversariantes do mes digite (3)\n");
    scanf("%d", &escolha);
    }
    switch(escolha) {
        case 1:
            printf("--------Bem-vindo faça o cadastro!!!!--------\n");
            while(quantidaClientes <= MAX_CLIENTES) {
                printf("--------Faça o cadastro!!!!--------\n");
                
                cadastroClientes(clientes, &quantidaClientes);
                exibirCliente(clientes[quantidaClientes - 1]);;
                
                quantidaClientes++;
                break;
                
                
        case 3:
                printf("Em qual mes voce gostaria de consultar os aniversariantes?\n");
                int mesAniversario;
                scanf("%d", &mesAniversario);
                buscarAniversariante(clientes, quantidaClientes, mesAniversario);
    }*/
    do {
    printf("\nO que você deseja fazer?\n");
    printf("1 - Cadastrar cliente\n");
    printf("2 - Buscar cliente por CPF\n");
    printf("3 - Buscar aniversariantes do mês\n");
    printf("0 - Sair\n");
    scanf("%d", &escolha);

    switch (escolha) {
        case 1:
            while (quantidaClientes < MAX_CLIENTES) {
                printf("\n--------Cadastro de Cliente--------\n");
                cadastroClientes(clientes, &quantidaClientes);
                exibirCliente(clientes[quantidaClientes - 1]);

                /* printf("\nDeseja cadastrar outro cliente? (1 - Sim / 0 - Não)\n");
                int opcao;
                scanf("%d", &opcao);
                if (opcao == 0) {
                    break;
                } Perguntar se pode!!! */
            }
            break;
            
        case 2: buscarCPF(clientes, quantidaClientes); break;
        case 3: buscarAniversariante(clientes, quantidaClientes, mesAniversario); break;
        case 0: printf("Saindo...\n"); break;
        default: printf("Opção inválida!\n"); break;
    }

} while (escolha != 0);
    
}