#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX_CLIENTES 1000
#define TAM_NOME 101
#define TAM_CPF 15
#define TAM_DATA 11
#define TAM_TEL 15
#define TAM_EMAIL 51

void exibirCliente();


struct cliente {
    char nome[TAM_NOME];
    char dataNascimento[TAM_DATA];
    char numTelefone[TAM_TEL];
    char cpf[TAM_CPF];
    char email[TAM_EMAIL];
};

const char *nomesMeses[] = {
    "", "Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho",
    "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"
};

bool validarNome(const char *nome) {
    int len = strlen(nome);
    if (len < 4 || len > 100) {
        printf("Nome inválido!\n");
        return false;
    }

    bool temEspaco = false;

    for (int i = 0; i < len; i++) {
        char c = nome[i];
        if (!((c >= 'A' && c <= 'Z') ||
               (c >= 'a' && c <= 'z') ||
              c == ' ' || c == '-' || c == '\'')) {
            printf("Nome inválido!\n");
            return false;
        }

        if (c == ' ') {
            temEspaco = true;
        }
    }

    if (!temEspaco) {
        printf("Nome inválido!\n");
        return false;
     
    }
    return true;
}

bool validarDataNascimento(const char *data) {
    if (strlen(data) != 10 || data[2] != '/' || data[5] != '/') {
        printf("Data de nascimento inválida!\n");
        return false;
    }

    int dia, mes, ano;

    dia = (data[0] - '0') * 10 + (data[1] - '0');

    mes = (data[3] - '0') * 10 + (data[4] - '0');

    ano = (data[6] - '0') * 1000 + (data[7] - '0') * 100 + (data[8] - '0') * 10 + (data[9] - '0');

    if (mes < 1 || mes > 12 || dia < 1 || dia > 31) {
        printf("Data de nascimento inválida!\n");
        return false;
    }

    if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30) {
        printf("Data de nascimento inválida!\n");
        return false;
    }
    if (mes == 2) {
        bool bissexto = (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
        if ((bissexto && dia > 29) || (!bissexto && dia > 28)) {
            printf("Data de nascimento inválida!\n");
            return false;
        }
    }

    return true;
}

bool validarCPF(char cpf[]) {
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
        return false;
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
        return true;
    } else {
        printf("CPF inválido!\n");
        return false;
    }
}

bool validarTelefone(struct cliente clientes[], int i) {
    if (strlen(clientes[i].numTelefone) != TAM_TEL - 1 ||                         
        clientes[i].numTelefone[0] != '(' ||                              
        clientes[i].numTelefone[3] != ')' ||                                
        clientes[i].numTelefone[4] != ' ' ||                   
        clientes[i].numTelefone[10] != '-' ||                         
        clientes[i].numTelefone[1] < '1' || clientes[i].numTelefone[1] > '9' || 
        clientes[i].numTelefone[2] < '0' || clientes[i].numTelefone[2] > '9') {
        printf("Número de telefone inválido!\n");
        return false;
    }
    return true;
}

void buscarCPF(struct cliente clientes[], int quantidade) {
    char cpfBuscado[TAM_CPF];
    printf("Digite o CPF a ser buscado.\n");
    scanf("%s", cpfBuscado);
    getchar();
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
    getchar();
    printf("Aniversários do mês %02d:\n", mesAniversario);
    for (int i = 0; i < quantidade; i++) {
        if ((clientes[i].dataNascimento[3] - '0') * 10 + (clientes[i].dataNascimento[4] - '0') == mesAniversario) {
            printf("%s - %s\n", clientes[i].nome, clientes[i].dataNascimento);
        }
    }
}

bool validarEmail(char email[]) {
    int tamanho = strlen(email);

    if ((email[0] == '@' && email[tamanho] == '@') &&
        (email[0] == '-' && email[tamanho] == '-') &&
        (email[0] == '.' && email[tamanho] == '.')){  // verifica se o primeiro caractere é '@'
        printf("Email inválido!\n");
        return false;
    }

    for (int i = 0; i < tamanho; i++) { // validar caracteres
        if ((email[i] >= 'a' && email[i] <= 'z') || email[i] == '@' || email[i] == '-') {
            // caractere válido, continua
            continue;
        } else {
            printf("Email inválido!\n");
            return false;
        }
    }

    // Verifica se há '@' e suas condições específicas
    for (int i = 0; i < tamanho; i++) {
        if (email[i] == '@') {
            // Verifica se caractere antes e depois do '@' NÃO são '-'
            if ((i > 0 && email[i - 1] == '-') || (i < tamanho - 1 && email[i + 1] == '-')) {
                printf("Email inválido!\n");
                return false;
            }
            // Verifica se o primeiro ou último caractere não são '-'
            if (email[0] == '-' || email[tamanho - 1] == '-') {
                printf("Email inválido!\n");
                return false;
            }
            printf("Email válido!\n");
            return true;
        }
    }

    // Se não encontrou '@', email inválido
    printf("Email inválido!\n");
    return false;
}

/*bool validardataNascimento (struct cliente clientes[], int quantidade) {
    //DD/MM/AAAA
    if() {
        
    }
    return true;
}*/

void cadastroClientes(struct cliente clientes[], int *quantidade) {
    //Nome
    bool validador = false;
    while(!validador) {
        printf("Digite o nome completo: ");
        fgets(clientes[*quantidade].nome, TAM_NOME, stdin);
        clientes[*quantidade].nome[strcspn(clientes[*quantidade].nome, "\n")] = '\0';
        validador = validarNome(clientes[*quantidade].nome);
    }
    
    //Data de Nascimento
    validador = false;
    while (!validador) {
    printf("Digite a data de nascimento (DD/MM/AAAA): ");
    scanf("%s", clientes[*quantidade].dataNascimento);
    getchar();
    validador = validarDataNascimento(clientes[*quantidade].dataNascimento);
    }
    
    //Telefone
    validador = false;
    while (!validador) {
    printf("Digite o número de telefone ( (xx) xxxxx-xxxx ): ");
    fgets(clientes[*quantidade].numTelefone, TAM_TEL, stdin);
    clientes[*quantidade].numTelefone[strcspn(clientes[*quantidade].numTelefone, "\n")] = '\0';
    validador = validarTelefone(clientes, *quantidade);
    }
    
    // CPF
    validador = false;
    while (!validador) {
    printf("Digite o CPF (xxx.xxx.xxx-yy): ");
    fgets(clientes[*quantidade].cpf, TAM_CPF, stdin);
    clientes[*quantidade].cpf[strcspn(clientes[*quantidade].cpf, "\n")] = '\0';
    validador = validarCPF(clientes[*quantidade].cpf);
    }
    
    //Email
    validador = false;
    while (!validador) {
    printf("Digite o email: \n");
    scanf("%s", clientes[*quantidade].email);
    validador = validarEmail(clientes [*quantidade].email);
    }
    
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
        getchar();

        switch (escolha) {
            case 1:
                while (quantidade < MAX_CLIENTES) {
                    printf("\n--------Cadastro de Cliente--------\n");
                    cadastroClientes(clientes, &quantidade);
                    exibirCliente(clientes[quantidade - 1]);

                    printf("\nDeseja cadastrar outro cliente? (1 - Sim / 0 - Não)\n");
                    int opcao;
                    scanf("%d", &opcao);
                    getchar(); 
                    if (opcao == 0) break;
                }
                break;
            case 2: buscarCPF(clientes, quantidade); break;
            case 3: buscarAniversariante(clientes, quantidade); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n"); break;
        }
    } while (escolha != 0);
}
