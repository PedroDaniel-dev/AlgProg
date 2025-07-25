#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX_CLIENTES 1000
#define TAM_NOME 101
#define TAM_CPF 15
#define TAM_DATA 11
#define TAM_TEL 16
#define TAM_EMAIL 51

void exibirCliente();


struct cliente {
    char nome[TAM_NOME];
    char dataNascimento[TAM_DATA];
    char numTelefone[TAM_TEL];
    char cpf[TAM_CPF];
    char email[TAM_EMAIL];
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

bool validarCPF(char cpf[], struct cliente clientes[], int quantidade) {
    int array[11];
    int j = 0;
    
    // Transforma os caracteres em dígitos, ignorando pontos/hífens
    for (int i = 0; cpf[i] != '\0' && j < 11; i++) {
        if (cpf[i] >= '0' && cpf[i] <= '9') {
            array[j++] = cpf[i] - '0';
        }
    }
    
    for (int i = 0; i < quantidade; i++) {
        if (strcmp(clientes[i].cpf, clientes[quantidade].cpf) == 0) {
            printf("Esse CPF já está cadastrado!\n");
            return false;
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
    int segundoDigito;
    if (resto < 2) {
        segundoDigito = 0;
    } else {
        segundoDigito = 11 - resto;
    }

    if (array[9] == primeiroDigito && array[10] == segundoDigito) {
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


void selectionSort(struct cliente aniversariantes[], int qtdAniversariantes) {
    for (int i = 0; i < qtdAniversariantes - 1; i++) {    // selection sort por dia do aniversário
        int menor_dia = i;
        for (int j = i + 1; j < qtdAniversariantes; j++) {  //
            int dia_j = (aniversariantes[j].dataNascimento[0] - '0') * 10 + (aniversariantes[j].dataNascimento[1] - '0');   //armazena o dia do aniversário do cliente no for j
            int dia_minimo = (aniversariantes[menor_dia].dataNascimento[0] - '0') * 10 + (aniversariantes[menor_dia].dataNascimento[1] - '0');  //armazena o dia do aniversário do cliente menor_dia
            if (dia_j < dia_minimo) {   //compara os dois
                menor_dia = j;
            }
        }
        if (menor_dia != i) {   // se encontrar um menor dia, troca os clientes
                               // e depois troca os aniversariantes
            struct cliente temp = aniversariantes[i];
            aniversariantes[i] = aniversariantes[menor_dia];
            aniversariantes[menor_dia] = temp;
        }
    }
}

void buscarAniversariante(struct cliente clientes[], int quantidade){
    char *nomeMeses[] = {
        "", "Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho",
        "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"
    };

    printf("Digite o nome do mês para buscar aniversariantes: (ex.: Março)\n");
    
    int mesAniversario = 0;
    char mes[10];
    
    scanf("%s", mes);
    getchar();
    
    struct cliente aniversariantes[MAX_CLIENTES];   //array temporário para armazenar aniversariantes
    int qtdAniversariantes = 0;
    

    // Descobre o número do mês
    for(int i = 1; i <= 12; i++) {
        if(strcasecmp(mes, nomeMeses[i]) == 0) {
            mesAniversario = i;
            break;
        }
    }

    if (mesAniversario == 0) {
        printf("Mês inválido!\n");
        return;
    }

    printf("Aniversários do mês de %s:\n", nomeMeses[mesAniversario]);

    for (int i = 0; i < quantidade; i++) {
        if ((clientes[i].dataNascimento[3] - '0') * 10 + (clientes[i].dataNascimento[4] - '0') == mesAniversario) {
            aniversariantes[qtdAniversariantes++] = clientes[i];
        }
    }
    
    selectionSort(aniversariantes, qtdAniversariantes);
    
    for (int i = 0; i < qtdAniversariantes; i++) {
        printf("%s - %s\n", aniversariantes[i].nome, aniversariantes[i].dataNascimento);
    }
}

bool validarEmail(char email[]) {
    int tamanho = strlen(email);

    if ((email[0] == '@' && email[tamanho - 1] == '@') &&
        (email[0] == '-' && email[tamanho - 1] == '-') &&
        (email[0] == '.' && email[tamanho - 1] == '.')){  // verifica se o primeiro caractere é '@'
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
            return true;
        }
    }

    // Se não encontrou '@', email inválido
    printf("Email inválido!\n");
    return false;
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


void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // descarta o restante da linha
    }
}

void cadastroClientes(struct cliente clientes[], int *quantidade) {
    bool validador = false;

    // CPF
    while (!validador) {
        printf("Digite o CPF (xxx.xxx.xxx-yy): ");
        fgets(clientes[*quantidade].cpf, TAM_CPF, stdin);
        if (clientes[*quantidade].cpf[strlen(clientes[*quantidade].cpf) - 1] != '\n') {
            limparBuffer();
        }
        clientes[*quantidade].cpf[strcspn(clientes[*quantidade].cpf, "\n")] = '\0';
        validador = validarCPF(clientes[*quantidade].cpf, clientes, *quantidade);
        }
        
    }

    // Nome
    validador = false;
    while (!validador) {
        printf("Digite o nome completo: ");
        fgets(clientes[*quantidade].nome, TAM_NOME, stdin);

        // Se não tiver o '\n', limpar buffer
        if (clientes[*quantidade].nome[strlen(clientes[*quantidade].nome) - 1] != '\n') {
            limparBuffer();
        }
        clientes[*quantidade].nome[strcspn(clientes[*quantidade].nome, "\n")] = '\0';
        validador = validarNome(clientes[*quantidade].nome);
    }

    // Data de nascimento
    validador = false;
    while (!validador) {
        printf("Digite a data de nascimento (DD/MM/AAAA): ");
        fgets(clientes[*quantidade].dataNascimento, TAM_DATA, stdin);
        if (clientes[*quantidade].dataNascimento[strlen(clientes[*quantidade].dataNascimento) - 1] != '\n') {
            limparBuffer();
        }
        clientes[*quantidade].dataNascimento[strcspn(clientes[*quantidade].dataNascimento, "\n")] = '\0';
        validador = validarDataNascimento(clientes[*quantidade].dataNascimento);
    }

/*    // Telefone
    validador = false;
    while (!validador) {
        printf("Digite o número de telefone ( (xx) xxxxx-xxxx ): ");
        fgets(clientes[*quantidade].numTelefone, TAM_TEL, stdin);
        if (clientes[*quantidade].numTelefone[strlen(clientes[*quantidade].numTelefone) - 1] != '\n') {
            limparBuffer();
        }
        clientes[*quantidade].numTelefone[strcspn(clientes[*quantidade].numTelefone, "\n")] = '\0';
        validador = validarTelefone(clientes, *quantidade);
    }

    // Email
    validador = false;
    while (!validador) {
        printf("Digite o email: ");
        fgets(clientes[*quantidade].email, TAM_EMAIL, stdin);
        if (clientes[*quantidade].email[strlen(clientes[*quantidade].email) - 1] != '\n') {
            limparBuffer();
        }
        clientes[*quantidade].email[strcspn(clientes[*quantidade].email, "\n")] = '\0';
        validador = validarEmail(clientes[*quantidade].email);
    } */

    // Incrementa quantidade de clientes cadastrados
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

    printf("----- Bem-vindo ao Sistema Maison du Chocolat -----\n");

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
