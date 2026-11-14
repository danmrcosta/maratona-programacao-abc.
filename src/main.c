
#include <stdio.h>

#include "equipes.h"

int main(){
  EQUIPES equipe;
  validar_nomes(&equipe);

    printf("Equipe %s\n",equipe.nome_equipe);
    printf("Instituicao origem %s\n",equipe.instituicao_origem);
  for(int i = 0; i < 3; i++){
    printf("Integrante %d: %s\n", i,equipe.nome_integrantes[i]);
  }
  return 0;
}

