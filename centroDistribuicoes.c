/* Autor: Lucas Gabriel de Araújo Assis
 * Programa para determinação da menor distância entre as cidades.
 */

#include "Grafo.h"

int main()
{
 //Cria e inicia o grafo.
 grafo g;
 
 //Arquivo para realização das comparações.
 FILE *arq_cidades;

 char origem[MAX], destino[MAX], auxiliar[MAX], palavra[MAX],
      ch;

 int indice = 0, distancia = 0, codigo_origem, codigo_destino,
     menor = 0;

 cria_grafo(&g);

 //Abre o arquivo para leitura dos dados.
 arq_cidades = fopen("cidades.txt", "r");

 printf("\n\n----------Centro de Distribuições----------\n\n");

 printf("Abrindo o arquivo 'cidades.txt'...\n\n");

 if(!arq_cidades)
   printf("Não foi possível abrir o arquivo 'cidades.txt'\7\n\n");

 else
 {
  palavra[indice] = getc(arq_cidades);

  while(palavra[indice]!= EOF)
  {
   //Lê o arquivo o primeiro token, no caso a cidade de origem.
   while(palavra[indice]!= '#' && palavra[indice]!=EOF)
   {
   	indice++;
   	palavra[indice] = getc(arq_cidades);
   }

   palavra[indice] = '\0';
   strcpy(origem,palavra);

   indice = 0;

   //Insere a cidade em um vértice do grafo.
   if(insere_vertice(g, origem, &codigo_origem)==1)
   	 printf("Inserindo '%s'.\n", origem);
   	 
   palavra[indice] = getc(arq_cidades);

   //Lê o arquivo o primeiro token, no caso a cidade de destino.
   while(palavra[indice]!= '#' && palavra[indice]!=EOF)
   {
    indice++;
    palavra[indice] = getc(arq_cidades);
   }

   palavra[indice] = '\0';
   strcpy(destino, palavra);

   indice = 0;

   if(insere_vertice(g, destino, &codigo_destino))
   	 printf("Inserindo '%s'.\n", destino);
   
   auxiliar[indice] = getc(arq_cidades);

   //Lê o arquivo o primeiro token, no caso a distância entre as cidades.
   while(auxiliar[indice]!='\n' && auxiliar[indice]!=EOF)
   {
    indice++;
    auxiliar[indice] = getc(arq_cidades);
   }

   auxiliar[indice] = '\0';
   indice = 0;
   palavra[indice] = getc(arq_cidades);
   distancia = atoi(auxiliar);
   insere_aresta(g, codigo_origem, codigo_destino, distancia);
  }

  //Calculando a distância média entre as cidades.
  int distancia_media[g->num_vertices];

  //Procura a cidade com menor distância entre todas.
  for(indice = 0; indice<g->num_vertices; indice++)
  {
   distancia_media[indice] = dijkstra(g,indice);

   if(distancia_media[indice]<menor || menor==0)
  	 menor = distancia_media[indice];
  }

  for(indice = 0; indice<g->num_vertices; indice++)
 	 //Verifica se a distância atual é a menor.
 	 if(distancia_media[indice]==menor)
 	   printf("\n\nMenor distância média: %s\n\n", g->vertices[indice].cidade);

  termina_grafo(&g);

  return 1;
 }
}