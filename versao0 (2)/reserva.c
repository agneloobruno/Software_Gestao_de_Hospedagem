#include "reserva.h"
#include <stdio.h>
#include <stdlib.h>
#include "apresentacao.h"
#include <string.h>

/**
 * Rotina que devolve o id a ser utilizado no próximo id de cadastro de reserva
 * @return Retorna o próximo ID a ser utilizado 
*/
unsigned int obterProximoIdReserva()
{
    char nomeArquivo[] = "idReserva.dat";
    FILE *f = fopen(nomeArquivo, "r+wb");
    unsigned  id=1;
    unsigned int v;
    int size;
    if (f != NULL)
    {
        size = fread(&v,sizeof(unsigned int),1, f);
        if (size > 0)
        {
            v++;
            id = v;
        }
        fseek(f,0,SEEK_SET);
        fwrite(&v, sizeof(unsigned int), 1, f);    
        fflush(f);
        fclose(f);
    }
    else
    {
        f = fopen(nomeArquivo,"wb");
        fwrite(&id, sizeof(unsigned int), 1, f);
        fclose(f);
    }
    return id;
}


/**
 * Inicia a reserva de um quarto 
 * @param checkin Data provável de entrada
 * @param checkout Data provável de saída
 * @param tipoQuarto Tipo de quarto desejado na reserva
 * @return Retorna as informações da reserva. Retorna com id maior que zero, 
 * caso a reserva ocorra com sucesso.  Caso não seja possível reservar
 * um quarto, retorna o id da reserva igual a zero. 
*/
RESERVA reservarQuarto(DATA checkin, DATA checkout, char *tipoQuarto )
{
    RESERVA r;
    r.id = 0;
    r.checkin = checkin;
    r.checkout = checkout;
    strcpy(r.tipoQuarto, tipoQuarto); 
    return r;
}


/**
 * Exibe uma reserva na tela do usuário
 * @param r Reserva que será exibida
*/
void exibirReserva( RESERVA r )
{
    char ci[15], co[15] ;
    DataToString(r.checkin, ci, false);
    DataToString(r.checkout, co, false);
    separador();
    printf("Código da reserva: %u\n", r.id);
    printf("Data de checkin: %s\n", ci );
    printf("Data de checkin: %s\n", co );
    printf("Tipo de quarto: %s\n", r.tipoQuarto);
    printf("Quarto reservado: %u\n", r.idQuarto);
    separador();   
}
