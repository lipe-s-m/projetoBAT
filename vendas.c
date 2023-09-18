#include <stdio.h>
#include <windows.h>

void reservar(char *nome, int *varejo, char *date);
void ver(char nome, int varejo, int date);

int main()
{
    int end = 1, opcao, sap = 5, resultado;
    char data[20], peca[30], buff[10];
    
    while(end == 1)
    {
        system("cls");
        printf("Selecione a Opcao");
        printf("\n \n1) Reservar Peca. \n2) Ver Pecas Reservadas. \n3) Fechar \n \n     >>> ");
        scanf("%d", &opcao);
        
        if(opcao == 1)
            reservar(peca, &sap, data);
        
        if(opcao == 2)
        {
            printf("\nnome: %s  -  sap: %d", peca, sap);
            printf("\nPressione qualquer tecla para continuar! \n   >>> ");
            scanf("%s", buff);
        }
        if(opcao == 3)
            end = 0;
    }
    printf("Voce Fechou o programa");
    return 0;
}

void reservar(char *nome, int *varejo, char *date)
{
    int end = 1, opcao, sap, resultado;
    char buff[10];
    system("cls");
    setbuf(stdin, 0);

    printf("Digite a peca que vc quer reservar: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = 0;

    printf("\nDigite o SAP do varejo: ");
    scanf("%d", &sap);
    *varejo = sap;
    printf("\nDigite a data: ");
    scanf("%s", date);
    printf("\nVoce reservou a peca %s, do sap %d, no dia %s.\n\n", nome, *varejo, date);
    printf("\nPressione qualquer tecla para continuar! \n   >>> ");
    scanf("%s", buff);
}