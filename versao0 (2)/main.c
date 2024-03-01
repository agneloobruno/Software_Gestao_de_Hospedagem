#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quarto.h"
#include "apresentacao.h"
#include "tempo.h"
#include "reserva.h"


int main(int argc, char const *argv[])
{
    // testando entrada de datas
    DATA data1, data2;
    StringToData("12/02/2023", &data1);
    StringToData("12/03/2023", &data2);
    int dias = DataDiff(data2, data1);
    printf("Diferença de dias é %d\n",dias);
    QUARTO q, *lista, *listaBusca=NULL;
    int opcao = MenuPrincipal();
    if (opcao == 4 )
    {
        // testando leitura, exibição e gravação de quarto no CSV e no DAT                 
        lerQuarto(&q);
        exibirQuarto(q);
        gravarQuartoCSV(q);
        gravarQuartoDAT(q);    
    }
    // testando leitura de quartos armazenados em disco
    int qtde = quantidadeQuartosCSV();
    lista = (QUARTO *) malloc(sizeof(QUARTO)*qtde);    
    lerQuartosCSV(lista);
    for (int i = 0; i < qtde; i++)
    {
       exibirQuarto(lista[i]);
    }
    // testando a busca de um tipo de quarto específico definido pelo usuário    
    listaBusca = (QUARTO *) malloc(sizeof(QUARTO)*qtde);
    char tipoQuartoBusca[10];
    printf("Entre com o tipo de quarto desejado ->");
    scanf(" %[^\n]s", tipoQuartoBusca);
    int qtdeTipo = buscarTipoQuarto(tipoQuartoBusca,lista, qtde, listaBusca);    
    getchar();
    for (int j = 0; j < qtdeTipo; j++)    
    {
        exibirQuarto(listaBusca[j]);
    }
    getchar();
    free(listaBusca);
    free(lista);
    // testando a função de reservarQuarto (função ainda incompleta)
    RESERVA res;    
    res = reservarQuarto(data1, data2, "triplo");
    exibirReserva(res);
    return 0;
}


/*************************************************************************************/

/*************************************************************************************/

