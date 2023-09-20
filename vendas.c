#include <stdio.h>
#include <windows.h>

typedef struct _PECA
{
    int id;
    char sap[20];
    char data[15];
    char nome[30];
    char solicitante[30];
    int quant;
    int atividade;
} PECA;

int reservar(PECA *x, int n, int c);
void eliminar(PECA *x, int n, int *l);
int salvar(PECA *x, int n, int c);
int carregar(PECA *x, int n, int *v, int *ct);


int main()
{
    int end = 1, resultado, i = 0, j = 0, cont = 0, var = 0;
    char buff[10], opcao[20];
    PECA PECA[100];
    i = carregar(PECA, i, &var, &cont);

    while (end == 1)
    {
        system("cls");
        printf("Selecione a Opcao, var: %d", var);
        printf("\n \n1) Reservar Peca. \n2) Ver Pecas Reservadas. \n3) Cancelar Reserva de Pecas. \n4) Fechar. \n \n     >>> ");
        scanf("%s", opcao);

        if (strcmp(opcao, "1") == 0)
        {
            i = reservar(PECA, var, cont);
            var++;
            cont++;
        }
        if (strcmp(opcao, "2") == 0)
        {
            system("cls");
            if (i == 0)
            {
                printf("Nao existem pecas cadastradas em nossa base de dados!\n");
                printf("\nPressione qualquer tecla para continuar! \n   >>> ");
                scanf("%s", buff);
            }
            else
            {
                j = 0;
                while (j < i)
                {
                    if(PECA[j].atividade = 1)
                        printf("\nId: %d) Solicitante: %s  -  Peca: %s  -  Sap: %s  -  Data: %s\n\n", PECA[j].id, PECA[j].solicitante, PECA[j].nome, PECA[j].sap, PECA[j].data);
                    j++;
                }
                printf("\n\nPressione qualquer tecla para continuar! \n   >>> ");
                scanf("%s", buff);
                j = 0;
            }
        }

        if (strcmp(opcao, "3") == 0)
        {
            if (i == 0)
            {
                system("cls");
                printf("Nao existem pecas cadastradas em nossa base de dados!\n");
                printf("\nPressione qualquer tecla para continuar! \n   >>> ");
                scanf("%s", buff);
            }
            else
            {
                eliminar(PECA, i, &var);
                var--;
                i--;
                printf("\nReserva cancelada! Pressione qualquer tecla para continuar! \n   >>> ");
                scanf("%s", buff);
            }
        }

        if (strcmp(opcao, "4") == 0)
        {
            end = salvar(PECA, var, cont);
        }
        else
        {
        }
    }

    printf("\nVoce Fechou o programa");
    printf("\nPressione qualquer tecla para fechar a tela! \n   >>> ");
    scanf("%s", buff);
    return 0;
}

int reservar(PECA *x, int n, int c)
{
    FILE *fp;
    fp = fopen("basedepecas.dat", "ab");
    char buff[10];
    system("cls");
    setbuf(stdin, 0);

    printf("Digite seu nome: ");
    fgets(x[c].solicitante, 30, stdin);
    x[c].solicitante[strcspn(x[c].solicitante, "\n")] = 0;

    printf("\nDigite a peca que quer reservar, %s: ", x[c].solicitante);
    fgets(x[c].nome, 30, stdin);
    x[c].nome[strcspn(x[c].nome, "\n")] = 0;

    printf("\nDigite o SAP do varejo: ");
    scanf("%s", x[c].sap);

    printf("\nDigite a data: ");
    scanf("%s", x[c].data);
    x[c].id = c;

    printf("\n%s reservou a peca %s, do sap %s, no dia %s.\n\n", x[c].solicitante, x[c].nome, x[c].sap, x[c].data);
    printf("\nPressione qualquer tecla para continuar! \n   >>> ");
    scanf("%s", buff);

    x[c].atividade = 1;
    x[c].quant = n+1;
    fwrite(&x[c], sizeof(PECA), 1, fp);
    fclose(fp);
    n++;
    return n;
}

void eliminar(PECA *x, int n, int *l)
{
    int j = 0, k = 0, elim;
    system("cls");
    printf("Digite o Id da peca que queira cancelar a reserva:\n");
    while (j < n)
    {
        printf("\n\nId: %d) Solicitante: %s  -  Peca: %s  -  Sap: %s  -  Data: %s\n", x[j].id, x[j].solicitante, x[j].nome, x[j].sap, x[j].data);
        j++;
    }
    printf("\n \n \n   >>> ");
    scanf("%d", &elim);
    x[elim].atividade = 0;
    elim--;
    system("cls");
    // if (elim >= 0 && elim < n)
    // { // se a posição é valida
    //     int i;

    //     // andar todos um para trás a partir da posição a remover
    //     for (i = elim; i < n - 1; ++i)
    //     {
    //         x[i] = x[i + 1];
    //     }

    //     x = realloc(x, --n * sizeof(PECA)); // reduzir o tamanho do array em 1 unidade
    // }
    FILE *arq;
    FILE *temp;
    arq = fopen("basedepecas.dat", "rb");
    temp = fopen("temp.dat", "wb");

    if (arq == NULL || temp == NULL) {
        perror("Erro ao abrir arquivos");
        return;
    }

    while(fread(&x[k], sizeof(PECA), 1, arq))
    {
        if(x[k].id != elim)
        {
            fwrite(&x[k].id, sizeof(PECA), 1, temp);
            k++;
        }
    }
    fclose(arq);
    fclose(temp);
    remove("basedepecas.dat");
    rename("temp.dat", "basedepecas.dat");
}

int salvar(PECA *x, int n, int c)
{
    FILE *fp;
    fp = fopen("contador.txt", "w");
    fprintf(fp, "%d %d", n, c);
    fclose(fp);
    return 0;
}

int carregar(PECA *x, int n, int *v, int *ct)
{
    int cont = 0, t = 0;
    char c;
    FILE *fp;
    FILE *pt;
    pt = fopen("contador.txt", "r");
    fp = fopen("basedepecas.dat", "rb");
    fscanf(pt, "%d %d", &n, &cont);
    
    if(fp == NULL)
    {
        printf("erro");
        return 0;
    }
    else
    {
        while(!feof(fp))
        {
            fread(&x[t], (sizeof(PECA)), 1, fp);
            t++;        
        }
    }
    fclose(fp);
    *v = n;
    *ct = cont;
    return n;


}