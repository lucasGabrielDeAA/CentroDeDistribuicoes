/* Autor: Lucas Gabriel de Araújo Assis
 * Declaração das estruturasde dados e métodos para se implementar o cálculo do Dijkstra.
 */
#ifndef GRAFO_H
#define GRAFO_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 100 //Número máximo de vértices.
#define NAO_MEMBRO 0
#define MEMBRO 1
#define INFINITO 1000000

typedef int tipo_chave;
typedef int tipo_peso;

//Enumeração para definir o estado de cada aresta do grafo de cidades.
enum tipo_status
{
 espera, pronto, processado
};

typedef struct
{
 tipo_chave chave;
 char cidade[MAX];
 enum tipo_status status;
 
}tipo_elemento;

typedef struct
{
 int conexao;
 tipo_peso peso;
 enum tipo_status status;
}tipo_aresta;

struct tipo_grafo
{
 tipo_elemento vertices[MAX];
 tipo_aresta arestas[MAX][MAX];
 int num_vertices;
};

typedef struct tipo_grafo *grafo;

//Disponibilliza memória necessária para a criação de um grafo e inicializa as arestas
int cria_grafo(grafo *g);

//Realiza a busca de um vértice a partir de um vértice qualquer.
int busca_vertice(grafo g, char cidade[]);

//Insere uma cidade em um vértice do grafo.
int insere_vertice(grafo g, char cidade[], int *codigo);

//Insere uma aresta no grafo, arestas serão as ligações entre um par de cidades.
int insere_aresta(grafo g, tipo_chave primeira, tipo_chave segunda, tipo_peso peso);

//Libera a memória alocada pelo grafo.
int termina_grafo(grafo *g);

/*Implementação do algoritmo do Dijkstra, que será utilizado para realizar o cálculo
 * das distâncias entre as cidades.
 */
 int dijkstra(grafo g, tipo_chave origem);

#endif