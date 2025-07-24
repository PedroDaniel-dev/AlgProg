#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


#define MAX_CLIENTES 1000
#define TAM_NOME 101
#define TAM_CPF 15
#define TAM_DATA 11
#define TAM_TEL 15
#define TAM_EMAIL 51

struct cliente {
    char nome[TAM_NOME];
    char dataNascimento[TAM_DATA];
    char numTelefone[TAM_TEL];
    char cpf[TAM_CPF];
    char email[TAM_EMAIL];
};

void exibirCliente();

const char *nomesMeses[] = {
    "", "Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho",
    "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"
};

void validarCPF(char cpf[]) {
    int array[11];
    int j = 0;

    // Transforma os caracteres em dígitos, ignorando pontos/hífens
    for (int i = 0; cpf[i] != '\0' && j < 11; i++) {
        if (cpf[i] >= '0' && cpf[i] <= '9') {
            array[j++] = cpf[i] - '0';
        }
    }

    if (j != 11) {
        printf("CPF inválido!\n");
        return;
    }

    int soma = 0;
    int peso = 10;

    for (int i = 0; i < 9; i++) {
        soma += array[i] * peso--;
    }

    int resto = soma % 11;
    int primeiroDigito = (resto < 2) ? 0 : 11 - resto;

    soma = 0;
    peso = 11;
    for (int i = 0; i < 10; i++) {
        soma += array[i] * peso--;
    }

    resto = soma % 11;
    int segundoDigito = (resto < 2) ? 0 : 11 - resto;

    if (array[9] == primeiroDigito && array[10] == segundoDigito) {
        printf("CPF válido!\n");
    } else {
        printf("CPF inválido!\n");
    }
}

void validarTelefone(struct cliente clientes[], int i) {
    if (strlen(clientes[i].numTelefone) != TAM_TEL - 1 ||                         
        clientes[i].numTelefone[0] != '(' ||                              
        clientes[i].numTelefone[3] != ')' ||                                
        clientes[i].numTelefone[4] != ' ' ||                   
        clientes[i].numTelefone[10] != '-' ||                         
        clientes[i].numTelefone[1] < '1' || clientes[i].numTelefone[1] > '9' || 
        clientes[i].numTelefone[2] < '0' || clientes[i].numTelefone[2] > '9') {
        printf("Número de telefone inválido!\n");
    }
}

void buscarCPF(struct cliente clientes[], int quantidade) {
    char cpfBuscado[TAM_CPF];
    printf("Digite o CPF a ser buscado.\n");
    scanf("%s", cpfBuscado);
    for (int i = 0; i < quantidade; i++) {
        if (strcmp(clientes[i].cpf, cpfBuscado) == 0) {
            exibirCliente(clientes[i]);
            return;
        }
    }
    printf("Usuário não encontrado.\n");
}

void buscarAniversariante(struct cliente clientes[], int quantidade){
    printf("Digite o mês para buscar aniversariantes:\n");
    int mesAniversario;
    scanf("%d", &mesAniversario);
    printf("Aniversários do mês %02d:\n", mesAniversario);
    for (int i = 0; i < quantidade; i++) {
        if ((clientes[i].dataNascimento[3]) * 10 + (clientes[i].dataNascimento[4]) == mesAniversario) {
            printf("%s - %s\n", clientes[i].nome, clientes[i].dataNascimento);
        }
    }
}

bool validarEmail(char email[]) {
    int tamanho = strlen(email);
    int posArroba = -1;

    //Verificação de Comprimento
    if (tamanho == 0 || tamanho > TAM_EMAIL || tamanho < 3) {
        printf("Email inválido: Tamanho incorreto (mín. 3, máx. %d caracteres).\n", TAM_EMAIL);
        return false;
    }

    //Passagem Única: Validar caracteres e encontrar a posição do '@'
    for (int i = 0; i < tamanho; i++) {
        char currentChar = email[i];

        //Verifica se o caractere atual é um '@'
        if (currentChar == '@') {
            if (posArroba != -1) {
                printf("Email inválido: Contém mais de um '@'.\n");
                return false;
            }
            posArroba = i;
        }
        else if (!(islower(currentChar) || isdigit(currentChar) || currentChar == '-')) {
            // Se o caractere NÃO for nenhum dos permitidos, então é inválido.
            printf("Email inválido: Caractere '%c' não permitido (apenas minúsculas, dígitos e hífens).\n", currentChar);
            return false;
        }
    }

    //Verificações do '@' após a passagem completa do loop
    if (posArroba == -1) {
        printf("Email inválido: Não contém '@'.\n");
        return false;
    }
    // verificar se o '@' não está no início ou no fim do email
    if (posArroba == 0 || posArroba == tamanho - 1) {
        printf("Email inválido: '@' não pode estar no início ou no fim.\n");
        return false;
    }
    //Validar o <username>
    if (email[0] == '-' || email[posArroba - 1] == '-') {
        printf("Email inválido: Nome de usuário não pode começar ou terminar com hífen.\n");
        return false;
    }
    //Validar o <dominio>
    if (email[posArroba + 1] == '-' || email[tamanho - 1] == '-') {
        printf("Email inválido: Domínio não pode começar ou terminar com hífen.\n");
        return false;
    }
    // Se todas as verificações passarem, o email é válido
    return true;
}

void cadastroClientes(struct cliente clientes[], int *quantidade) {
    bool emailValido;
    //Nome
    printf("Digite o nome: \n");
    getchar();
    fgets(clientes[*quantidade].nome, TAM_NOME, stdin);
    clientes[*quantidade].nome[strcspn(clientes[*quantidade].nome, "\n")] = '\0'; 
    //Data de Nascimento
    printf("Digite a data de nascimento (DD/MM/AAAA): \n");
    scanf("%s", clientes[*quantidade].dataNascimento);
    //Telefone
    printf("Digite o número de telefone ( (xx) xxxxx-xxxx ):\n");
    fgets(clientes[*quantidade].numTelefone, TAM_NOME, stdin);
    clientes[*quantidade].numTelefone[strcspn(clientes[*quantidade].numTelefone, "\n")] = '\0'; 
    validarTelefone(clientes, *quantidade);
    // CPF
    printf("Digite o CPF (xxx.xxx.xxx-yy):\n");
    scanf("%s", clientes[*quantidade].cpf);

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    validarCPF(clientes[*quantidade].cpf);

    //Email
    do {
    printf("Email: ");
    fgets(clientes[*quantidade].email, TAM_EMAIL, stdin);
    clientes[*quantidade].email[strcspn(clientes[*quantidade].email, "\n")] = 0;

    bool emailValido = validarEmail(clientes[*quantidade].email);

    if (!emailValido) {
        printf("Email inválido! Por favor, siga o formato <username>@<dominio>!\n");
        printf("Apenas letras minúsculas, números e hífens (não pode começar/terminar com hífen).\n");
    }
} while (!validarEmail(clientes[*quantidade].email));

    //Proxima posição da Array
    (*quantidade)++;
    printf("\n---------------------------------\n");
    printf("--------Dados Fornecidos:--------\n");
    printf("---------------------------------\n");
}


void exibirCliente(struct cliente c) {
    printf("Nome: %s\n", c.nome);
    printf("Nascimento: %s\n", c.dataNascimento);
    printf("Telefone: %s\n", c.numTelefone);
    printf("CPF: %s\n", c.cpf);
    printf("Email: %s\n", c.email);
}

int main() {
    struct cliente clientes[MAX_CLIENTES];
    int escolha;
    int quantidade = 0;

    printf("--------Bem-vindo!!!--------\n");

    do {
        printf("\nO que você deseja fazer?\n");
        printf("1 - Cadastrar cliente\n");
        printf("2 - Buscar cliente por CPF\n");
        printf("3 - Buscar aniversariantes do mês\n");
        printf("0 - Sair\n");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                while (quantidade < MAX_CLIENTES) {
                    printf("\n--------Cadastro de Cliente--------\n");
                    cadastroClientes(clientes, &quantidade);
                    exibirCliente(clientes[quantidade - 1]);

                    printf("\nDeseja cadastrar outro cliente? (1 - Sim / 0 - Não)\n");
                    int opcao;
                    scanf("%d", &opcao);
                    if (opcao == 0) break;
                }
                break;
            case 2:
                buscarCPF(clientes, quantidade);
                break;
            case 3:
                buscarAniversariante(clientes, quantidade);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (escolha != 0);
}
