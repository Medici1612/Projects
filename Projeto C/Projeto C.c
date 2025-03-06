#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <Windows.h>

int i;

typedef struct {
    char nome[100];
    char cpf[20];
    char telefone[20];
    char status[20];
    int classe;
    int forca, resistencia, agilidade, inteligencia, fe;
} Cliente;

void salvar_classe(Cliente cliente);
void preencher_dados_pessoais(Cliente *cliente);
void exibir_personagem();
int validar_cpf(const char *cpf);
int cpf_existente(const char *cpf);
void buscar_cliente_por_cpf(const char *cpf);
void ordenar_clientes_por_cpf();
int comparar_clientes(const void *a, const void *b);
void editar_ou_excluir_personagem(const char *cpf);

void telaBoasVindas() {
    printf("=======================================================\n");
    printf("                   Bem-vindo ao jogo                  \n");
    printf("                                                     \n");
    printf("=======================================================\n");
    printf("                                                     \n");
    printf("    LLL        III     GGGG     HHH  HHH    TTTTTT  \n");
    printf("    LLL        III    G         HHH  HHH      TT    \n");
    printf("    LLL        III    G  GG     HHHHHHHH      TT    \n");
    printf("    LLL        III    G    G    HHH  HHH      TT    \n");
    printf("    LLLLLLL    III      GGG     HHH  HHH      TT    \n");
    printf("                                                     \n");
    printf("   SSS         OOOO       UU    UU    LLL       SSS  \n");
    printf("  SSS         OO  OO      UU    UU    LLL     SSS    \n");
    printf(" SSS         OO    OO     UU    UU    LLL     SSS    \n");
    printf("   SSS       OO    OO     UU    UU    LLL       SSS  \n");
    printf("     SSS     OO    OO     UU    UU    LLL         SSS\n");
    printf("     SSS      OO  OO      UU    UU    LLL         SSS\n");
    printf("   SSS         OOOO         UUUU      LLLLLLL   SSS  \n");
    printf("=======================================================\n");
    printf("Pressione Enter para continuar...\n");
    getchar();
    system("cls");
}


int main() {
    setlocale(LC_ALL, "");
    int opcao;
	telaBoasVindas();
    while (1) {
        printf("\t----- Light Souls -----\n");
        printf("1. Criar personagem\n");
        printf("2. Exibir personagens\n");
        printf("3. Buscar cliente por CPF\n");
        printf("4. Ordenar clientes por CPF\n");
        printf("5. Editar/Excluir personagem\n");
        printf("6. Sair\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &opcao);
	system("cls");
        switch (opcao) {
            case 1: {
                Cliente cliente;
                preencher_dados_pessoais(&cliente);

                if (cpf_existente(cliente.cpf)) {
                    printf("CPF j� cadastrado. Opera��o cancelada.\n");
                } else {
                    salvar_classe(cliente);
                }
                break;
            }
            case 2:
                exibir_personagem();
                break;
            case 3: {
                char cpf[20];
                printf("Digite o CPF para busca: ");
                scanf("%s", cpf);
                buscar_cliente_por_cpf(cpf);
                break;
            }
            case 4:
                ordenar_clientes_por_cpf();
                break;
            case 5: {
                char cpf[20];
                printf("Digite o CPF para editar ou excluir: ");
                scanf("%s", cpf);
                editar_ou_excluir_personagem(cpf);
                break;
            }
            case 6:
                printf("Saindo...\n");
                return 0;
            default:
                printf("Op��o inv�lida. Tente novamente.\n");
        }
    }
    return 0;
}


void salvar_classe(Cliente cliente) {
    FILE *arquivo = fopen("clientes.txt", "a");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo para salvar.\n");
        exit(1);  
    }
    fprintf(arquivo, "%s;%s;%s;%s;%d;%d;%d;%d;%d;%d\n", 
            cliente.nome, cliente.cpf, cliente.telefone, cliente.status,
            cliente.classe, cliente.forca, cliente.resistencia, cliente.agilidade, 
            cliente.inteligencia, cliente.fe);
    fclose(arquivo);
    printf("Personagem salvo com sucesso.\n");
    	system("cls");
}


void preencher_dados_pessoais(Cliente *cliente) {
    getchar(); 
    printf("Digite o nome: ");
    fgets(cliente->nome, 100, stdin);
    cliente->nome[strcspn(cliente->nome, "\n")] = '\0';

    while (1) {
        do {
            printf("Digite o CPF (11 d�gitos): ");
            scanf("%s", cliente->cpf);
        } while (!validar_cpf(cliente->cpf));

        if (cpf_existente(cliente->cpf)) {
            printf("CPF j� cadastrado. Digite outro CPF.\n");
        } else {
            break; 
        }
    }

    printf("Digite o telefone: ");
    getchar(); 
    fgets(cliente->telefone, 20, stdin);
    cliente->telefone[strcspn(cliente->telefone, "\n")] = '\0';

    printf("Digite o status: ");
    fgets(cliente->status, 20, stdin);
    cliente->status[strcspn(cliente->status, "\n")] = '\0';

    printf("Escolha a classe: \n1-B�rbaro\n2-Assassino\n3-Cl�rigo\n4-Mago\n ");
    scanf("%d", &cliente->classe);
	system("cls");
    printf("Defina os atributos:\n");
    printf("For�a: ");
    scanf("%d", &cliente->forca);
    printf("Resist�ncia: ");
    scanf("%d", &cliente->resistencia);
    printf("Agilidade: ");
    scanf("%d", &cliente->agilidade);
    printf("Intelig�ncia: ");
    scanf("%d", &cliente->inteligencia);
    printf("F�: ");
    scanf("%d", &cliente->fe);
}
void exibir_personagem() {
    FILE *arquivo = fopen("clientes.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    Cliente cliente;
    int encontrado = 0;
    printf("\n---- Personagens Cadastrados ----\n");
    while (fscanf(arquivo, "%99[^;];%19[^;];%19[^;];%19[^;];%d;%d;%d;%d;%d;%d\n", 
            cliente.nome, cliente.cpf, cliente.telefone, cliente.status,
            &cliente.classe, &cliente.forca, &cliente.resistencia, &cliente.agilidade,
            &cliente.inteligencia, &cliente.fe) != EOF) {
        
        printf("Nome: %s\n", cliente.nome);
        printf("CPF: %s\n", cliente.cpf);
        printf("Telefone: %s\n", cliente.telefone);
        printf("Status: %s\n", cliente.status);
        printf("Classe: %d\n", cliente.classe);
        printf("For�a: %d\n", cliente.forca);
        printf("Resist�ncia: %d\n", cliente.resistencia);
        printf("Agilidade: %d\n", cliente.agilidade);
        printf("Intelig�ncia: %d\n", cliente.inteligencia);
        printf("F�: %d\n", cliente.fe);
        printf("---------------------------------\n");

        encontrado = 1;
    }

    if (!encontrado) {
        printf("Nenhum personagem encontrado.\n");
    }

    fclose(arquivo);
}


int validar_cpf(const char *cpf) {
    if (strlen(cpf) != 11) {
        printf("CPF inv�lido! O CPF deve ter 11 d�gitos.\n");
        return 0;
    }

    for (i = 0; i < 11; i++) {
        if (!isdigit(cpf[i])) {
            printf("CPF inv�lido! O CPF deve conter apenas n�meros.\n");
            return 0;
        }
    }
    return 1;
}


int cpf_existente(const char *cpf) {
    FILE *arquivo = fopen("clientes.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return 0;
    }

    Cliente cliente;
    while (fscanf(arquivo, "%99[^;];%19[^;];%19[^;];%19[^;];%d;%d;%d;%d;%d;%d\n", 
            cliente.nome, cliente.cpf, cliente.telefone, cliente.status,
            &cliente.classe, &cliente.forca, &cliente.resistencia, &cliente.agilidade,
            &cliente.inteligencia, &cliente.fe) != EOF) {
        if (strcmp(cpf, cliente.cpf) == 0) {
            fclose(arquivo);
            return 1; // CPF encontrado
        }
    }

    fclose(arquivo);
    return 0; // CPF n�o encontrado
}


void buscar_cliente_por_cpf(const char *cpf) {
    FILE *arquivo = fopen("clientes.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    Cliente cliente;
    while (fscanf(arquivo, "%99[^;];%19[^;];%19[^;];%19[^;];%d;%d;%d;%d;%d;%d\n", 
            cliente.nome, cliente.cpf, cliente.telefone, cliente.status,
            &cliente.classe, &cliente.forca, &cliente.resistencia, &cliente.agilidade,
            &cliente.inteligencia, &cliente.fe) != EOF) {
        if (strcmp(cpf, cliente.cpf) == 0) {
            printf("\n---- Personagem Encontrado ----\n");
            printf("Nome: %s\n", cliente.nome);
            printf("CPF: %s\n", cliente.cpf);
            printf("Telefone: %s\n", cliente.telefone);
            printf("Status: %s\n", cliente.status);
            printf("Classe: %d\n", cliente.classe);
            printf("For�a: %d\n", cliente.forca);
            printf("Resist�ncia: %d\n", cliente.resistencia);
            printf("Agilidade: %d\n", cliente.agilidade);
            printf("Intelig�ncia: %d\n", cliente.inteligencia);
            printf("F�: %d\n", cliente.fe);
            fclose(arquivo);
            Sleep(5000);
            	system("cls");
            return;
        }
    }

    printf("Cliente com o CPF %s n�o encontrado.\n", cpf);
    fclose(arquivo);
}


void ordenar_clientes_por_cpf() {
    FILE *arquivo = fopen("clientes.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    Cliente clientes[100];
    int count = 0;

    while (fscanf(arquivo, "%99[^;];%19[^;];%19[^;];%19[^;];%d;%d;%d;%d;%d;%d\n", 
            clientes[count].nome, clientes[count].cpf, clientes[count].telefone, 
            clientes[count].status, &clientes[count].classe, &clientes[count].forca, 
            &clientes[count].resistencia, &clientes[count].agilidade, 
            &clientes[count].inteligencia, &clientes[count].fe) != EOF) {
        count++;
    }

    fclose(arquivo);

    qsort(clientes, count, sizeof(Cliente), comparar_clientes);

    printf("\nClientes ordenados por CPF:\n");
    for (i = 0; i < count; i++) {
        printf("Nome: %s, CPF: %s, Status: %s, Classe: %d\n", 
               clientes[i].nome, clientes[i].cpf, clientes[i].status, clientes[i].classe);
    }
}


int comparar_clientes(const void *a, const void *b) {
    return strcmp(((Cliente *)a)->cpf, ((Cliente *)b)->cpf);
}


void editar_ou_excluir_personagem(const char *cpf) {
    FILE *arquivo = fopen("clientes.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    Cliente clientes[100];
    int count = 0;

    while (fscanf(arquivo, "%99[^;];%19[^;];%19[^;];%19[^;];%d;%d;%d;%d;%d;%d\n", 
            clientes[count].nome, clientes[count].cpf, clientes[count].telefone, 
            clientes[count].status, &clientes[count].classe, &clientes[count].forca, 
            &clientes[count].resistencia, &clientes[count].agilidade, 
            &clientes[count].inteligencia, &clientes[count].fe) != EOF) {
        count++;
    }

    fclose(arquivo);

    int index = -1;
    for (i = 0; i < count; i++) {
        if (strcmp(cpf, clientes[i].cpf) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Personagem n�o encontrado para edi��o.\n");
        return;
    }

    printf("Personagem encontrado. Escolha a opera��o:\n");
    printf("1. Editar\n");
    printf("2. Excluir\n");
    int operacao;
    scanf("%d", &operacao);

    if (operacao == 1) {
        printf("Digite o novo nome (atual: %s): ", clientes[index].nome);
        getchar(); 
        fgets(clientes[index].nome, 100, stdin);
        clientes[index].nome[strcspn(clientes[index].nome, "\n")] = '\0';

        printf("Digite o novo telefone (atual: %s): ", clientes[index].telefone);
        fgets(clientes[index].telefone, 20, stdin);
        clientes[index].telefone[strcspn(clientes[index].telefone, "\n")] = '\0';

        printf("Digite o novo status (atual: %s): ", clientes[index].status);
        fgets(clientes[index].status, 20, stdin);
        clientes[index].status[strcspn(clientes[index].status, "\n")] = '\0';

        printf("Defina novos atributos:\n");
        printf("For�a (atual: %d): ", clientes[index].forca);
        scanf("%d", &clientes[index].forca);
        printf("Resist�ncia (atual: %d): ", clientes[index].resistencia);
        scanf("%d", &clientes[index].resistencia);
        printf("Agilidade (atual: %d): ", clientes[index].agilidade);
        scanf("%d", &clientes[index].agilidade);
        printf("Intelig�ncia (atual: %d): ", clientes[index].inteligencia);
        scanf("%d", &clientes[index].inteligencia);
        printf("F� (atual: %d): ", clientes[index].fe);
        scanf("%d", &clientes[index].fe);

        arquivo = fopen("clientes.txt", "w");
        if (!arquivo) {
            printf("Erro ao abrir o arquivo para regravar.\n");
            return;
        }

        for ( i = 0; i < count; i++) {
            fprintf(arquivo, "%s;%s;%s;%s;%d;%d;%d;%d;%d;%d\n", 
                    clientes[i].nome, clientes[i].cpf, clientes[i].telefone, 
                    clientes[i].status, clientes[i].classe, clientes[i].forca, 
                    clientes[i].resistencia, clientes[i].agilidade, 
                    clientes[i].inteligencia, clientes[i].fe);
        }

        fclose(arquivo);
        printf("Personagem editado com sucesso.\n");

    } else if (operacao == 2) {
        for ( i = index; i < count - 1; i++) {
            clientes[i] = clientes[i + 1];
        }
        count--; 

        arquivo = fopen("clientes.txt", "w");
        if (!arquivo) {
            printf("Erro ao abrir o arquivo para regravar.\n");
            return;
        }

        for ( i = 0; i < count; i++) {
            fprintf(arquivo, "%s;%s;%s;%s;%d;%d;%d;%d;%d;%d\n", 
                    clientes[i].nome, clientes[i].cpf, clientes[i].telefone, 
                    clientes[i].status, clientes[i].classe, clientes[i].forca, 
                    clientes[i].resistencia, clientes[i].agilidade, 
                    clientes[i].inteligencia, clientes[i].fe);
        }

        fclose(arquivo);
        printf("Personagem exclu�do com sucesso.\n");

    } else {
     printf("Opera��o inv�lida.\n");
    }
}

