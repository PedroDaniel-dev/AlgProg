#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_CLIENTES 1000
#define TAM_NOME 101
#define TAM_CPF 15
#define TAM_DATA 11
#define TAM_TEL 16
#define TAM_EMAIL 51
#define DDD_PADRAO "(21)"

typedef struct {
    char nome[TAM_NOME];
    char cpf[TAM_CPF];
    char nascimento[TAM_DATA];
    char telefone[TAM_TEL];
    char email[TAM_EMAIL];
} Cliente;

// Funções de validação
int validar_nome(const char *nome) {
    int len = strlen(nome);
    int tem_espaco = 0;
    if (len < 4 || len >= TAM_NOME) return 0;
    for (int i = 0; i < len; i++) {
        char c = nome[i];
        if (!isalpha(c) && c != ' ' && c != '-' && c != '\'') return 0;
        if (c == ' ') tem_espaco = 1;
    }
    return tem_espaco;
}

int validar_cpf(const char *cpf) {
    if (strlen(cpf) != 14) return 0;
    if (cpf[3] != '.' || cpf[7] != '.' || cpf[11] != '-') return 0;
    for (int i = 0; i < 14; i++) {
        if (i == 3 || i == 7 || i == 11) continue;
        if (!isdigit(cpf[i])) return 0;
    }
    // Validação dos dígitos verificadores omitida por brevidade
    return 1;
}

int validar_data(const char *data) {
    if (strlen(data) != 10 || data[2] != '/' || data[5] != '/') return 0;
    int d, m, a;
    if (sscanf(data, "%d/%d/%d", &d, &m, &a) != 3) return 0;
    if (a < 1900 || a > 2100 || m < 1 || m > 12 || d < 1 || d > 31) return 0;
    int maxDias[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if (d > maxDias[m]) {
        if (m == 2 && d == 29 && ((a % 4 == 0 && a % 100 != 0) || a % 400 == 0)) return 1;
        return 0;
    }
    return 1;
}

int validar_email(const char *email) {
    int len = strlen(email);
    if (len < 5 || len >= TAM_EMAIL) return 0;
    char *at = strchr(email, '@');
    if (!at || at == email || at == email + len - 1) return 0;
    char *dominio = at + 1;
    if (!strchr(dominio, '.')) return 0;
    for (int i = 0; i < len; i++) {
        char c = email[i];
        if (c == '@') continue;
        if (!islower(c) && !isdigit(c) && c != '-' && c != '.') return 0;
    }
    if (email[0] == '-' || email[len-1] == '-') return 0;
    return 1;
}

int validar_ddd(const char *ddd) {
    int d1 = ddd[1] - '0', d2 = ddd[2] - '0';
    int ddd_num = d1 * 10 + d2;
    int ddds_validos[] = {11, 12, 13, 14, 15, 16, 17, 18, 19, 21, 22, 24, 27, 28, 31, 32, 33, 34, 35, 37, 38,
    41, 42, 43, 44, 45, 46, 47, 48, 49, 51, 53, 54, 55, 61, 62, 63, 64, 65, 66, 67, 68,
    69, 71, 73, 74, 75, 77, 79, 81, 87, 82, 83, 84, 85, 88, 86, 89, 91, 92, 93, 94, 95,
    96, 97,98, 99};
    for (int i = 0; i < 9; i++) if (ddd_num == ddds_validos[i]) return 1;
    return 0;
}

int formatar_telefone(const char *orig, char *saida) {
    int len = strlen(orig);
    char clean[TAM_TEL];
    int j = 0;
    for (int i = 0; i < len; i++) if (isdigit(orig[i])) clean[j++] = orig[i];
    clean[j] = '\0';

    if (orig[0] == '(' && orig[3] == ')' && orig[4] == ' ') {
        if (!validar_ddd(orig)) return 0;
        if (len < 14 || len > 15 || orig[len-5] != '-') return 0;
        strncpy(saida, orig, TAM_TEL-1);
        saida[TAM_TEL-1] = '\0';
        return 1;
    } else {
        if (j == 8) {
            snprintf(saida, TAM_TEL, "%s %c%c%c%c-%c%c%c%c", DDD_PADRAO,
                clean[0], clean[1], clean[2], clean[3], clean[4], clean[5], clean[6], clean[7]);
            return 1;
        } else if (j == 9 && clean[0] == '9') {
            snprintf(saida, TAM_TEL, "%s %c%c%c%c%c-%c%c%c%c", DDD_PADRAO,
                clean[0], clean[1], clean[2], clean[3], clean[4], clean[5], clean[6], clean[7], clean[8]);
            return 1;
        }
    }
    return 0;
}

// Função para limpar buffer
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Busca cliente por CPF
int buscar_cliente(Cliente *clientes, int total, const char *cpf) {
    for (int i = 0; i < total; i++)
        if (strcmp(clientes[i].cpf, cpf) == 0) return i;
    return -1;
}

// Cadastro de cliente
void cadastrar_cliente(Cliente *clientes, int *total) {
    if (*total >= MAX_CLIENTES) {
        printf("Limite de clientes atingido.\n");
        return;
    }
    char cpf[TAM_CPF];
    do {
        printf("CPF (xxx.xxx.xxx-yy): ");
        fgets(cpf, TAM_CPF, stdin);
        cpf[strcspn(cpf, "\n")] = '\0';
        if (!validar_cpf(cpf)) printf("CPF inválido. Tente novamente.\n");
    } while (!validar_cpf(cpf));

    int idx = buscar_cliente(clientes, *total, cpf);
    if (idx >= 0) {
        char resp[4];
        printf("CPF já cadastrado. Atualizar dados? (s/n): ");
        fgets(resp, sizeof(resp), stdin);
        if (tolower(resp[0]) != 's') {
            printf("Operação cancelada.\n");
            return;
        }
    }

    Cliente novo;
    strcpy(novo.cpf, cpf);

    do {
        printf("Nome completo: ");
        fgets(novo.nome, TAM_NOME, stdin);
        novo.nome[strcspn(novo.nome, "\n")] = '\0';
        if (!validar_nome(novo.nome)) printf("Nome inválido. Tente novamente.\n");
    } while (!validar_nome(novo.nome));

    do {
        printf("Data de nascimento (DD/MM/AAAA): ");
        fgets(novo.nascimento, TAM_DATA, stdin);
        novo.nascimento[strcspn(novo.nascimento, "\n")] = '\0';
        if (!validar_data(novo.nascimento)) printf("Data inválida. Tente novamente.\n");
    } while (!validar_data(novo.nascimento));

    char tel[TAM_TEL];
    do {
        printf("Telefone ((DDD) prefixo-sufixo ou prefixo-sufixo): ");
        fgets(tel, TAM_TEL, stdin);
        tel[strcspn(tel, "\n")] = '\0';
        if (!formatar_telefone(tel, novo.telefone)) printf("Telefone inválido. Tente novamente.\n");
    } while (!formatar_telefone(tel, novo.telefone));

    do {
        printf("Email: ");
        fgets(novo.email, TAM_EMAIL, stdin);
        novo.email[strcspn(novo.email, "\n")] = '\0';
        if (!validar_email(novo.email)) printf("Email inválido. Tente novamente.\n");
    } while (!validar_email(novo.email));

    if (idx >= 0) clientes[idx] = novo;
    else clientes[(*total)++] = novo;

    printf("Cliente cadastrado/atualizado com sucesso!\n");
}

// Busca e cadastro via CPF
void buscar_ou_cadastrar(Cliente *clientes, int *total) {
    char cpf[TAM_CPF];
    do {
        printf("CPF para busca (xxx.xxx.xxx-yy): ");
        fgets(cpf, TAM_CPF, stdin);
        cpf[strcspn(cpf, "\n")] = '\0';
        if (!validar_cpf(cpf)) printf("CPF inválido. Tente novamente.\n");
    } while (!validar_cpf(cpf));

    int idx = buscar_cliente(clientes, *total, cpf);
    if (idx < 0) {
        char resp[4];
        printf("Cliente não encontrado. Deseja cadastrar? (s/n): ");
        fgets(resp, sizeof(resp), stdin);
        if (tolower(resp[0]) == 's') cadastrar_cliente(clientes, total);
        else printf("Busca cancelada.\n");
    } else {
        Cliente *c = &clientes[idx];
        printf("\n--- Dados do Cliente ---\n");
        printf("Nome: %s\nCPF: %s\nNascimento: %s\nTelefone: %s\nEmail: %s\n",
            c->nome, c->cpf, c->nascimento, c->telefone, c->email);
    }
}

// Ordenação Bubble Sort por data de aniversário
void ordenar_aniversariantes(Cliente *clientes, int idxs[], int total) {
    for (int i = 0; i < total-1; i++) {
        for (int j = 0; j < total-i-1; j++) {
            int d1, m1, d2, m2;
            sscanf(clientes[idxs[j]].nascimento, "%d/%d", &d1, &m1);
            sscanf(clientes[idxs[j+1]].nascimento, "%d/%d", &d2, &m2);
            if (m1 > m2 || (m1 == m2 && d1 > d2)) {
                int tmp = idxs[j];
                idxs[j] = idxs[j+1];
                idxs[j+1] = tmp;
            }
        }
    }
}

// Listar aniversariantes do mês
void listar_aniversariantes(Cliente *clientes, int total) {
    int mes;
    printf("Digite o mês para listar aniversariantes (1-12): ");
    if (scanf("%d", &mes) != 1 || mes < 1 || mes > 12) {
        printf("Mês inválido.\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();

    int idxs[MAX_CLIENTES], cnt = 0;
    for (int i = 0; i < total; i++) {
        int d, m, a;
        if (sscanf(clientes[i].nascimento, "%d/%d/%d", &d, &m, &a) == 3 && m == mes) {
            idxs[cnt++] = i;
        }
    }
    ordenar_aniversariantes(clientes, idxs, cnt);

    printf("\n--- Aniversariantes do mês %d ---\n", mes);
    if (cnt == 0) printf("Nenhum aniversariante encontrado.\n");
    else {
        for (int i = 0; i < cnt; i++) {
            Cliente *c = &clientes[idxs[i]];
            printf("Nome: %s | Data: %s | Telefone: %s | Email: %s\n",
                c->nome, c->nascimento, c->telefone, c->email);
        }
    }
}

// Menu principal
void menu() {
    Cliente clientes[MAX_CLIENTES];
    int total = 0, opc;
    do {
        printf("\n--- Sistema de Cadastro de Clientes ---\n");
        printf("1 - Cadastrar Cliente\n");
        printf("2 - Buscar Cliente por CPF\n");
        printf("3 - Listar Aniversariantes por Mês\n");
        printf("0 - Sair\nOpção: ");
        if (scanf("%d", &opc) != 1) {
            printf("Entrada inválida.\n");
            limpar_buffer();
            continue;
        }
        limpar_buffer();
        switch (opc) {
            case 1: cadastrar_cliente(clientes, &total); break;
            case 2: buscar_ou_cadastrar(clientes, &total); break;
            case 3: listar_aniversariantes(clientes, total); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida.\n");
        }
    } while (opc != 0);
}

int main() {
    menu();
    return 0;
}