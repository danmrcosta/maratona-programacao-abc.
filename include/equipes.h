
#ifndef EQUIPES_H
#define EQUIPES_H

typedef struct {
  int resolvidos; // quantidade de problemas resolvdos
  int minutos; // tempo total de submissao em minutos
  int qnt_submissoes; // quantidade total de submissões
} DESEMPENHO;


typedef struct{
  char nome_equipe[51]; //sempre com 1 a mais por causa do caractere nulo
  char instituicao_origem[51]; //sempre com 1 a mais por causa do caractere nulo
  char nome_integrantes[3][101]; // linha 0 pessoa 1, linha 1 pessoa2 , linha 2 pessoa 3...
  DESEMPENHO problemas[14]; // A a N, 14 problemas
} EQUIPES;

void validar_nomes(EQUIPES *equipe);

int buscar_equipe(EQUIPES equipes[], int quantidade, char nome[]); // realiza a busca da equipe, e retorna o indice

#endif

