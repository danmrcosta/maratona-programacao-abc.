#include <stdio.h>
#include <string.h>
#include <ctype.h>


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
