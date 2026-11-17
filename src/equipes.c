
#include <stdio.h>
#include <string.h>

#include "equipes.h"
#include "validacao.h"

void validar_nomes(EQUIPES *equipe){
  // 1. Valida EQUIPE
  do{
    printf("Digite o nome da equipe (max 50 caracteres):\n");
    fgets(equipe->nome_equipe, sizeof(equipe->nome_equipe), stdin);
    limpar_nova_linha(equipe->nome_equipe);
    if(!nome_equipe_instituicao_valido(equipe->nome_equipe))
      printf("Nome da equipe deve ter 1 a 50 caracteres!\n");
  } while(!nome_equipe_instituicao_valido(equipe->nome_equipe));

  printf("Equipe %s cadastrada com sucesso!\n", equipe->nome_equipe);

  // 2. Valida INSTITUICAO
  do{
    printf("Digite a instituicao de origem (max 50 caracteres):\n");
    fgets(equipe->instituicao_origem, sizeof(equipe->instituicao_origem), stdin);
    limpar_nova_linha(equipe->instituicao_origem);
    if(!nome_equipe_instituicao_valido(equipe->instituicao_origem))
      printf("Instituicao deve ter 1 a 50 caracteres!\n");
  } while(!nome_equipe_instituicao_valido(equipe->instituicao_origem));

  printf("Instituicao %s cadastrada com sucesso!\n", equipe->instituicao_origem);

  // 3. Valida os 3 INTEGRANTES
  for(int i = 0; i < 3; i++){
    do{
      printf("Digite o nome do %d integrante:\n", i + 1);
      fgets(equipe->nome_integrantes[i], sizeof(equipe->nome_integrantes[i]), stdin);
      limpar_nova_linha(equipe->nome_integrantes[i]);

      if(!nome_pessoa_valido(equipe->nome_integrantes[i]))
        printf("Nome invalido! Use somente letras, espaco, hifen e apostrofo, 5 a 100 caracteres, com nome e sobrenome.\n");

    } while(!nome_pessoa_valido(equipe->nome_integrantes[i]));

    printf("Integrante %d cadastrado com sucesso!\n", i + 1);
  }
}

int buscar_equipe(EQUIPES equipes[], int quantidade, char nome[]){

  for(int i = 0; i < quantidade; i++){

    if(strcmp(equipes[i].nome_equipe, nome) == 0){
      return i;
    }

  }

  return -1;

}

