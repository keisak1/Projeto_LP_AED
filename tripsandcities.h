//
// Created by Nuno on 23/12/2021.
//

#ifndef PROJETO_LP_AED_TRIPSANDCITIES_H
#define PROJETO_LP_AED_TRIPSANDCITIES_H
#include "creation_resizing.h"
#include "csvData.h"

/**
 * Função para editar uma viagem e atualizar no CSV.
 * @param user
 */
void editTrips(LIST_QUEUE_NODE *user);
/**
 *
 * @param head
 */
void searchCityByName(LIST_QUEUE_NODE *head);
/**
 * Função para introduzir uma nova viagem ao cliente e atualizar no CSV.
 * @param head
 */
void insertTrips(LIST_QUEUE_NODE *head);
/**
 * Remove viagem do cliente e atualiza no CSV.
 * @param head
 */
void removeTrips(LIST_QUEUE_NODE *head);
/**
 * Cria ficheiro binário com cidades, descrição, pontos de interesse e as suas coordenadas.
 */
void citiesToBin();
/**
 * Guarda cidades na lista ligada.
 * @return
 */
CITYNODE *storeCity();
/**
 * Do ficheiro binário guarda a informação numa lista ligada.
 * @param token
 * @param row
 * @return
 */
CITYNODE *binToNode(char *token, char *row);
/**
 * Escreve a lista ligada no ficheiro binário.
 * @param head
 * @return
 */
CITYNODE *updateToBin(CITYNODE *head);
/**
 * Procura cidade pelo ID.
 * @param head
 */
void searchCityByID(CITYNODE *head);
/**
 * Procura pontos de interesse de uma cidade, usando o ID da cidade para pesquisar.
 * @param head
 */
void searchPoI(CITYNODE *head);
/**
 * Remove pontos de interesse a uma cidade e atualiza no ficheiro binário.
 * @param head
 */
void removePoI(CITYNODE *head);
/**
 * Insere pontos de interesse a uma cidade e atualiza no ficheiro binário.
 * @param head
 */
void insertPoI(CITYNODE *head);
/**
 * Edita informação da cidade e atualiza no ficheiro binário.
 * @param user
 */
void editCityInfo(CITYNODE *user);
/**
 * Procura a viagem do cliente a partir do NIF.
 * @param head
 * @param user
 * @param NIF
 */
void searchUserTrip(LIST_QUEUE_NODE *head,CITYNODE *user, int NIF);
/**
 * Gera um relatório com clientes e as respetivas viagens.
 * @param head
 * @param user
 */
void generateReport(LIST_QUEUE_NODE *head, CITYNODE *user);


#endif //PROJETO_LP_AED_TRIPSANDCITIES_H
