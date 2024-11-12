#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define FILE_NAME "usuarios.txt"
#define CHAVE_CESAR 3

typedef struct {
    char nome[50];
    char senha[200];
} Usuario;

void criptografarSenha(char* senha) {
    for (int i = 0; senha[i] != '\0'; i++) {
        senha[i] = senha[i] + CHAVE_CESAR;
    }
}


void converterParaASCII(char* senha, char* senhaASCII) {
    senhaASCII[0] = '\0'; 
    char buffer[10];
    for (int i = 0; senha[i] != '\0'; i++) {
        sprintf(buffer, "%d ", (int)senha[i]); 
        strcat(senhaASCII, buffer);            
    }
}

void inserirUsuario() {
    Usuario u;
    char senha[50];
    FILE *file = fopen(FILE_NAME, "a");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("Nome do usu�rio: ");
    scanf("%s", u.nome);
    printf("Senha do usu�rio: ");
    scanf("%s", senha);

    criptografarSenha(senha);      
    converterParaASCII(senha, u.senha); 

    fprintf(file, "%s %s\n", u.nome, u.senha);
    fclose(file);
    printf("Usu�rio inserido com sucesso!\n");
}

void listarUsuarios() {
    Usuario u;
    FILE *file = fopen(FILE_NAME, "r");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("\nLista de Usu�rios:\n");
    printf("Nome\n");

    while (fscanf(file, "%49s %199[^\n]", u.nome, u.senha) == 2) {
        printf("%s\n", u.nome); 
    }

    fclose(file);
}

void alterarUsuario() {
    char nome[50], senha[50];
    int encontrado = 0;
    Usuario u;
    FILE *file = fopen(FILE_NAME, "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("Nome do usu�rio a ser alterado: ");
    scanf("%s", nome);

    while (fscanf(file, "%49s %199[^\n]", u.nome, u.senha) == 2) {
        if (strcmp(u.nome, nome) == 0) {
            encontrado = 1;
            printf("Novo nome: ");
            scanf("%s", u.nome);
            printf("Nova senha: ");
            scanf("%s", senha);

            criptografarSenha(senha);      
            converterParaASCII(senha, u.senha); 
        }
        fprintf(tempFile, "%s %s\n", u.nome, u.senha);
    }

    fclose(file);
    fclose(tempFile);

    if (encontrado) {
        remove(FILE_NAME);
        rename("temp.txt", FILE_NAME);
        printf("Usu�rio alterado com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("Usu�rio n�o encontrado.\n");
    }
}

void excluirUsuario() {
    char nome[50];
    int encontrado = 0;
    Usuario u;
    FILE *file = fopen(FILE_NAME, "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("Nome do usu�rio a ser exclu�do: ");
    scanf("%s", nome);

    while (fscanf(file, "%49s %199[^\n]", u.nome, u.senha) == 2) {
        if (strcmp(u.nome, nome) == 0) {
            encontrado = 1;
            continue;
        }
        fprintf(tempFile, "%s %s\n", u.nome, u.senha);
    }

    fclose(file);
    fclose(tempFile);

    if (encontrado) {
        remove(FILE_NAME);
        rename("temp.txt", FILE_NAME);
        printf("Usu�rio exclu�do com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("Usu�rio n�o encontrado.\n");
    }
}

void menu() {
    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1. Inserir Usu�rio\n");
        printf("2. Alterar Usu�rio\n");
        printf("3. Excluir Usu�rio\n");
        printf("4. Listar Usu�rios\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                inserirUsuario();
                break;
            case 2:
                alterarUsuario();
                break;
            case 3:
                excluirUsuario();
                break;
            case 4:
                listarUsuarios();
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 5);
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    menu();
    return 0;
}

