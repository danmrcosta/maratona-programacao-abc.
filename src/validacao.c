
#include <string.h>
#include <ctype.h>

#include "validacao.h"

// Limpa o \n do fgets
void limpar_nova_linha(char *s){
  for(int k = 0; s[k] != '\0'; k++){
    if(s[k] == '\n'){ s[k] = '\0'; break; }
  }
}

// Validacao: só letra, espaço, hífen, apóstrofo
int nome_pessoa_valido(char *nome){
  int tamanho = strlen(nome);
  if(tamanho < 5 || tamanho > 100) return 0; // max = 100 e nao 50

  int tem_espaco = 0;
  int tem_letra_antes = 0;
  int tem_letra_depois = 0;

  for(int i = 0; i < tamanho; i++){
    char c = nome[i];
    // Só valido isso aqui
    if(!(isalpha(c) || c == ' ' || c == '-' || c == '\'')){
      return 0;
    }
    if(c == ' ') tem_espaco = 1;
    else if(isalpha(c)){
        if(!tem_espaco) tem_letra_antes = 1;
        else tem_letra_depois = 1;
    }
  }

  // Precisa ter nome e sobrenome = letra + espaço + letra
  // ta com um bug aqui
  return (tem_espaco && tem_letra_antes && tem_letra_depois);
}

// Validacao - parte equipe / instituicao: max 50
int nome_equipe_instituicao_valido(char *nome){
  int tamanho = strlen(nome);
  return (tamanho >= 1 && tamanho <= 50);
}

