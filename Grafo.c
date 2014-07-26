/* Autor: Lucas Gabriel de Araújo Assis
 * Implementação dos métodos declarados no arquivo de cabeçalho Grafo.h
 */
#include "Grafo.h"


//Disponibilliza memória necessária para a criação de um grafo e inicializa as arestas
int cria_grafo(grafo *g)
{
	int indice_linha, indice_coluna;

	if(!(*g = (grafo)malloc(sizeof(struct tipo_grafo))))
		 return 0;
	(*g)->num_vertices = 0;

	for(indice_linha = 0; indice_linha < MAX; indice_linha++)
		  for (indice_coluna = 0; indice_coluna < MAX; indice_coluna++)
		  {
		  	(*g)->arestas[indice_linha][indice_coluna].conexao = 0;
		  	(*g)->arestas[indice_linha][indice_coluna].peso = 0;
		  	(*g)->arestas[indice_linha][indice_coluna].status = pronto;
		  }
	return 1;
}

//Realiza a busca de um vértice a partir de um vértice qualquer.
int busca_vertice(grafo g, char cidade[])
{
	int indice;

	for(indice = 0; indice < MAX && indice < g->num_vertices; indice++)
    if(strcmp(g->vertices[indice].cidade, cidade)==0)
    	 return indice;

 return -1;
}


//Insere uma cidade em um vértice do grafo.
int insere_vertice(grafo g, char cidade[], int *codigo)
{
 int busca;

 if(g->num_vertices < MAX)
 {
 	busca = busca_vertice(g,cidade);

 	if(busca == -1)
 	{
   strcpy(g->vertices[g->num_vertices].cidade, cidade);
   g->vertices[g->num_vertices].chave = g->num_vertices;
   *codigo = g->num_vertices;
   g->num_vertices++;
   return 1;
 	}
 	else
 	{
 		*codigo = g->vertices[busca].chave;
 		return 1;
 	}
 }
 return 0;
}

//Insere uma aresta no grafo, arestas serão as ligações entre um par de cidades.
int insere_aresta(grafo g, tipo_chave primeira, tipo_chave segunda, tipo_peso peso)
{
	//Realiza a ligação entre as cidades com as posições passadas como parâmetro.
	g->arestas[primeira][segunda].conexao = 1;
	g->arestas[primeira][segunda].peso = peso;
	g->arestas[primeira][segunda].status = espera;

	g->arestas[segunda][primeira].conexao = 1;
	g->arestas[segunda][primeira].peso = peso;
	g->arestas[segunda][primeira].status = espera;	

	return 1;
}

//Libera a memória alocada pelo grafo.
int termina_grafo(grafo *g)
{
	//Realiza a liberação de memória utilizada pelo grafo.
	free(*g);

	return 1;
}

/*Implementação do algoritmo do Dijkstra, que será utilizado para realizar o cálculo
 * das distâncias entre as cidades.
 */
 int dijkstra(grafo g, tipo_chave origem)
 {
 	int distancia[MAX], permancencia[MAX], caminho[MAX],
 	    posicao_corrente, indice, corrente , distancia_corrente, verificados = 0, auxiliar = 0,
 	    menor_distancia, nova_distancia;

 	for (indice = 0; indice < g->num_vertices; indice++)
 	{
 		permancencia[indice] = NAO_MEMBRO;
 		distancia[indice] = INFINITO;
 	}

 	permancencia[origem] = MEMBRO;
 	distancia[origem] = 0;

 	posicao_corrente = origem;
 	corrente = posicao_corrente;

 	while(verificados != (g->num_vertices-1))
 	{
 		menor_distancia = INFINITO;
 		distancia_corrente = distancia[posicao_corrente];

 		for(indice = 0; indice < g->num_vertices; indice++)
 		{
 			if(permancencia[indice]==NAO_MEMBRO)
 			{
 				if(g->arestas[posicao_corrente][indice].conexao)
 				{
 					nova_distancia = distancia_corrente + g->arestas[posicao_corrente][indice].peso;

 					if(nova_distancia < distancia[indice])
 					{
 						distancia[indice] = nova_distancia;
 						caminho[indice] = posicao_corrente;
 					}
 				}
 				if(distancia[indice] < menor_distancia)
 				{
 					menor_distancia = distancia[indice];
 					corrente = indice;
 				}
 			}
 		}
 		posicao_corrente = corrente;
 		permancencia[posicao_corrente] = MEMBRO;
 		auxiliar += distancia[posicao_corrente];
 		verificados++;
 	}
 	return auxiliar;
 }
