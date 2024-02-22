#ifndef __RESERVA_H__
#define __RESERVA_H__

#include "tempo.h"

typedef struct RESERVA
{
    /* Identificação da reserva do cliente */
    unsigned int id;
    /* CPF do cliente que fez a reserva */
    char CPF[14];
    /* Data de provavel entrada do cliente */
    DATA checkin;
    /* Data de provavel saída do cliente */
    DATA checkout;
    /* Tipo de quarto reservado */
    char tipoQuarto[7]; // "Single", "Duplo", "Tripo"
    /* Identificação do quarto */
    unsigned int idQuarto;
} RESERVA;



/**
 * Rotina que devolve o id a ser utilizado no próximo id de cadastro de reserva
 * @return Retorna o próximo ID a ser utilizado 
*/
unsigned int obterProximoIdReserva();


/**
 * Inicia a reserva de um quarto 
 * @param checkin Data provável de entrada
 * @param checkout Data provável de saída
 * @param tipoQuarto Tipo de quarto desejado na reserva
 * @return Retorna as informações da reserva. Retorna com id maior que zero, 
 * caso a reserva ocorra com sucesso.  Caso não seja possível reservar
 * um quarto, retorna o id da reserva igual a zero. 
*/
RESERVA reservarQuarto(DATA checkin, DATA checkout, char *tipoQuarto );


/**
 * Exibe uma reserva na tela do usuário
 * @param r Reserva que será exibida
*/
void exibirReserva( RESERVA r );


#endif
