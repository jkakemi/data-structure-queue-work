#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 5
typedef struct
{
    int vaga[MAX];
    int inicio;
    int fim;
    int movimento[MAX];
} Fila; // FILA DO ESTACIONAMENTO

// INSERIR CARRO NA FILA --------------------------------------
int insere(Fila *f, int placa)
{
    if(f->fim == MAX)
    {
        return 0; // RETORNA FILA CHEIA
    }
    else
    {
        f->vaga[f->fim]= placa;
        f->fim++;
        return 1; // ADICIONA O ELEMENTO NA FILA
    }
}

// INSERIR CARRO NA ESPERA --------------------------------------

int FilaEspera(Fila *FAux, int placa)
{
    if(FAux->fim == MAX)
    {
        return 0; // RETORNA FILA CHEIA

    }
    else
    {
        FAux->vaga[FAux->fim]= placa;
        FAux->fim++;
        return 1; // ADICIONA O ELEMENTO NA FILA DE ESPERA
    }
}

// REMOVER CARRO NA FILA --------------------------------------

int removeCarro(Fila *F1, Fila *FAux, int placa, int *nummov)
{
    int i, j;
    int encontrado = 0;

    // Procura o carro na fila
    for(i = 0; i < F1->fim; i++)
    {
        if(F1->vaga[i] == placa) // 1 2 3 4 5, 3 POS 2, 5 POS 4
        {
            encontrado = 1;
            break;
        }
    }

    // Se o carro foi encontrado, remove o elemento e reorganiza a fila
    if(encontrado)
    {
        for(j = i; j < F1->fim-1; j++)
        {
            F1->vaga[j] = F1->vaga[j+1];
        }
        F1->fim--;
        // Verifica se há carros na fila de espera

        if(FAux->fim > 0)
        {
            // Move o primeiro carro da fila de espera para o espaço vago no estacionamento
            F1->vaga[F1->fim] = FAux->vaga[0];
            F1->fim++;

            // Reorganiza a fila de espera
            for(i = 0; i < FAux->fim-1; i++)
            {
                FAux->vaga[i] = FAux->vaga[i+1];
            }
            FAux->fim--;
        }
        (*nummov)++;
        return 1; // Retorna sucesso
    }
    else
    {
        return 0; // Retorna que a placa não foi encontrada
    }
}

// LISTA DE CARROS NA FILA --------------------------------------

void listaCarros(Fila *F1, Fila *FAux)
{
    if(F1->fim == 0)
    {
        printf("\nEstacionamento vazio!");
    }
    else
    {
        printf("\nLISTA ESTACIONAMENTO: ");
        int i;
        for(i=0; i<F1->fim; i++)
        {
            printf("%d ", F1->vaga[i]);
        }
    }
    printf("\n");
    if(FAux->fim == 0)
    {
        printf("\nFila vazia!");
    }
    else
    {
        printf("\nLISTA FILA DE ESPERA: ");
        int i;
        for(i=0; i<FAux->fim; i++)
        {
            printf("%d ", FAux->vaga[i]);
        }
    }
    printf("\n");
}

void inicia(Fila *f)
{
    f->inicio = f->fim = 0;

}

void main(void)
{
    char op;
    int placa;
    int nummov=0;

    Fila F1, FAux;
    inicia(&F1);
    inicia(&FAux);

    do
    {
        printf("\n*********************");
        printf("\n*    C - CHEGADA    *");
        printf("\n*    P - PARTIDA    *");
        printf("\n*L - LISTA DE ESPERA*");
        printf("\n*     S - SAIR      *");
        printf("\n*********************");
        printf("\nDigite uma opcao: ");
        setbuf(stdin, NULL);
        scanf("%c", &op);

        char aux = toupper(op);

        switch(aux)
        {
        case 'C':
            printf("\nDigite a placa: ");
            scanf("%d", &placa);

            //int achou=0, i;
            for(int j=0; j<1; j++)
            {
                int achou, i;
                do
                {
                    achou = 0;
                    for(i = 0; i < F1.fim; i++)
                    {
                        if(F1.vaga[i] == placa)
                        {
                            printf("Placa ja inserida!\nInforme outra placa: ");
                            scanf("%d", &placa);
                            achou = 1;
                            break;
                        }
                    }
                }
                while(achou == 1);
            }
            int retorno = insere(&F1, placa);
            if(retorno == 1)
            {
                printf("\nCarro %d inserido no estacionamento.", placa);
                /*for(int k=0; k<F1.fim; k++){
                    printf("\n%d", F1.vaga[k]);
                }*/
            }
            else
            {
                printf("\nEstacionamento cheio.");
                int espera = FilaEspera(&FAux, placa);
                if(espera == 1)
                {
                    printf("\nCarro %d adicionado na fila de espera.", placa);
                    /*for(int k=0; k<FAux.fim; k++)
                    {
                        printf("\n%d", FAux.vaga[k]);
                    }*/
                }
                else
                {
                    printf("\nNao ha mais vagas na fila de espera!");
                }
            }
            break;
        case 'P':
            printf("\nDigite a placa do carro que deseja remover: ");
            scanf("%d", &placa);

            int remocao = removeCarro(&F1, &FAux, placa, &nummov);
            if(remocao == 1)
            { // 1 2 3 4 5, tiro o 3, fila aux: 1 2, tirei o 3, fila original: 1 2 4 5.
                for(int i=0; i<F1.fim; i++){
                    F1.movimento[i] = F1.movimento[i]+1;
                    //printf("Movimento %d e carro %d\n", F1.movimento[i], F1.vaga[i]);
                }

                printf("\nCarro %d retirado com %d movimentos.", placa, nummov-1);
                /*for(int k=0; k<F1.fim; k++){
                    printf("\n%d", F1.vaga[k]);
                }*/
            }
            else
            {
                printf("\nPlaca do carro nao encontrado.");
            }

            break;
        case 'L':
            listaCarros(&F1, &FAux);
            break;
        case 'S':
            printf("\nSaindo...");
            break;
        default:
            printf("\nOpcao invalida.");
            break;
        }

    }
    while(op != 'S');
}
