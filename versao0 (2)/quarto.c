#include "quarto.h"
#include "apresentacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const char separadorCSV = ';';
const char nomeArquivoCSV[] = "Quartos.csv";
const char nomeArquivoDAT[] = "Quartos.dat";
// char SETOR[6][] = {"Higiene", "Limpeza", "Bebidas", "Frios", "Padaria", "Açougue"};

/**
 * Rotina que lê os dados de um quarto através do teclado
 * @param p Ponteiro para um registro do tipo QUARTO, 
 * onde os dados lidos serão armazenados 
*/
void lerQuarto( QUARTO *p )
{
    separador();
    printf("Lendo um quarto \n");
    printf("Id do quarto :  ");
    scanf(" %d", &p->id);
    printf("Camas de solteiro: ");
    scanf(" %d", &p->camasSolteiro);
    printf("Camas de casal: ");
    scanf(" %d", &p->camasCasal);
    printf("Selecione o tipo de quarto (single ou duplo ou triplo)\n");
    printf("-> ");
    scanf(" %[^\n]", p->tipoQuarto);
    printf("Preço da diária: ");
    scanf(" %f", &p->valorDiaria);
    p->status = true; // assumindo sempre disponivel quando cadastrado
}

/**
 * Exibe os campos contidos em um registro do tipo QUARTO
 * @param p Registro que será exibido
 */
void exibirQuarto(QUARTO p)
{
    separador();
    printf("Exibindo um quarto \n");
    printf("Idenficador do quarto: ");
    printf(" %u\n", p.id);
    printf("Camas de solteiro :  ");
    printf(" %u\n", p.camasSolteiro);
    printf("Camas de casal: ");
    printf(" %u\n", p.camasCasal);
    printf("Tipo de quarto: ");
    printf(" %s\n", p.tipoQuarto);    
    printf("Preço da diária: %.2f\n", p.valorDiaria);
    printf("Status: ");
    if (p.status)
        printf("Disponível\n");
    else
        printf("Indisponível\n");
    separador();
}


/**
 * Gravando os dados de um quarto no final do arquivo. Caso o arquivo
 * não exista, gera um novo arquivo com as colunas que são o cabeçalho
 * @param p Quarto que será salvo no arquivo
 */
int gravarQuartoCSV(QUARTO p)
{
    FILE *csv;
    csv = fopen(nomeArquivoCSV, "r+w");

    if (csv == NULL)
    {
        // arquivo não existe, será criado
        printf("Criando arquivo %s\n", nomeArquivoCSV);
        csv = fopen(nomeArquivoCSV, "a");
        fprintf(csv, "id;solteiro;casal;tipo;preço;status\n");
        fflush(csv);
    }
    else
        fseek(csv, 0, SEEK_END);
    // arquivo ja existe, insere apenas o dado no final do arquivo
    fprintf(csv, "%d;%d;%d;%s;%.2f;%d\n",
            p.id, p.camasSolteiro, p.camasCasal, p.tipoQuarto,
            p.valorDiaria, p.status);
    fflush(csv);
    fclose(csv);
    // salvando o cabeçalho do arquivo
    return 0;
}

int quantidadeQuartosCSV()
{
    FILE *csv;
    char linha[1000];
    csv = fopen(nomeArquivoCSV, "r");
    if (csv != NULL)
    {
        // lendo o cabeçalho do arquivo
        fscanf(csv, " %[^\n]s", linha);
        int contadorLinha = 0;
        while (fscanf(csv, " %[^\n]s", linha) != EOF)
        {
            contadorLinha++;
        }
        fclose(csv);
        return contadorLinha;
    }
    else
    {
        // arquivo não existe
        return 0;
    }
}


/**
 * Leitura de dados do CSV para registros
 * @param lista Ponteiro para um vetor de registros
 * com os dados que estão no arquivo
 * @return Retorna a quantidade de quartos cadastrados
 */
int lerQuartosCSV(QUARTO *lista)
{
    
    FILE *csv;
    char linha[1000];
    char *campos;
    const char s[2] = ";";
    int contadorLinha = 0;
   
    csv = fopen(nomeArquivoCSV, "r");
    if (csv != NULL)
    {
        // fim dos registros, reabrindo para ler os dados
        fseek(csv, 0, SEEK_SET);
        // lendo o cabeçalho do arquivo
        fscanf(csv, " %[^\n]s", linha);
        // alocando memoria para os registros lidos

        int i = 0;
        while (fscanf(csv, " %[^\n]s", linha) != EOF)
        {
            // separando os dados de uma linha
            campos = strtok(linha, s);
            int campoAtual = 0;
            while (campos != NULL)
            {
                //printf(" %s\n", campos);
                switch (campoAtual)
                {
                case 0:
                    lista[i].id = atoi(campos);
                    break;
                case 1:
                    lista[i].camasSolteiro = atoi(campos);
                    break;
                case 2:
                    lista[i].camasCasal = atoi(campos);
                    break;
                case 3:
                    strcpy(lista[i].tipoQuarto, campos);                    
                    break;
                case 4:
                    lista[i].valorDiaria = atof(campos);
                    break;
                case 5:
                    lista[i].status = atoi(campos);
                    break;
                default:
                    break;
                }
                campos = strtok(NULL, s);

                campoAtual++;
            }

            i++;
            // dados do setor;
        }
        contadorLinha = i;
        return contadorLinha;
    }
    else
    {
        printf("Erro - Arquivo %s não encontrado\n", nomeArquivoCSV);
        return -1;
    }
}

/**
 * Grava um registro de QUARTO em um arquivo binário
 * @param p Quarto que será salvo no arquivo
 */
int gravarQuartoDAT( QUARTO p)
{
    FILE *dat;
    dat = fopen(nomeArquivoDAT, "a+b");
    if (dat == NULL)
    {
        // arquivo não existe, será criado
        printf("Criando arquivo %s\n", nomeArquivoDAT);
        dat = fopen(nomeArquivoDAT, "ab");
    }
    fwrite(&p, sizeof(QUARTO), 1, dat);
    fflush(dat);
    fclose(dat);
    return 0;
}

/**
 * Retorna a quantidade de quartos que estão salvos no arquivo DAT
 * @return Quantidade de quartos salvos
*/
int quantidadeQuartosDAT( )
{
    int qtde = 0;
    QUARTO dummy;
    FILE *dat;
    dat = fopen(nomeArquivoDAT, "rb");
    if (dat != NULL)
    {
        while (fread(&dummy, sizeof(QUARTO), 1, dat) > 0)
            qtde++;

        return qtde;
    }
    else
    {
        return 0;
    }
}

/**
 * Leitura de dados do arquivo binário para registros
 * @param lista Ponteiro para um vetor de registros
 * com os dados que estão no arquivo
 * @return Retorna a quantidade de quartos cadastrados
 */
int lerQuartosDAT(QUARTO *lista)
{
    int qtde = 0;
    FILE *dat;
    dat = fopen(nomeArquivoDAT, "rb");
    if (dat != NULL)
    {
        while (fread(&lista[qtde], sizeof(QUARTO), 1, dat) > 0)
        {
            // exibirProduto(lista[qtde]);
            qtde++;
        }
        return qtde;
    }
    else
    {
        printf("Erro - Arquivo %s não encontrado\n", nomeArquivoDAT);
        return -1;
    }
}



/**
 * Busca os quartos existente de um determinado tipo
 * @param tipoQuarto Tipo de quarto desejado
 * @param listaEntrada Lista com todos os tipos de quartos existente;
 * @param qtdeQuartos Quantidade de quartos cadastrados
 * @param listaSaida Lista quartos de tipo QUARTO com informções encontrada 
 * com o quarto desejado. Retorna NULL caso não existam quartos do tipo desejado.
 * @return Retorna a quantidade de quartos encontrados
*/
int buscarTipoQuarto(char *tipoQuarto, QUARTO *listaEntrada, int qtdeQuartos, QUARTO *listaSaida )
{
    int qtdeQuartosDoTipo=0;
    //*listaSaida = NULL;
    for (int i = 0 ; i < qtdeQuartos;i++)
    {
        if ( strcmp(listaEntrada[i].tipoQuarto, tipoQuarto) == 0 )
        {
            
            listaSaida[qtdeQuartosDoTipo] = listaEntrada[i];
            printf("###### Exibindo durante a busca #######\n");
            exibirQuarto( listaSaida[qtdeQuartosDoTipo]);
            printf("###### ------------------------ #######\n");
            qtdeQuartosDoTipo++;
        }
    }   
    return qtdeQuartosDoTipo;
}
