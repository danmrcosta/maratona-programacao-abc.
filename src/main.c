#include <stdio.h>
#include <string.h>
#include <ctype.h>


//struct da equipe , utilizado typedef para usar o Alias EQUIPES
typedef struct{

  char nome_equipe[51];
  char instituicao_origem[51];
  char nome_integrantes[3][101];


}EQUIPES;

void validar_nomes(EQUIPES* equipe){
  int tamanho = 0;
  int tem_Sobrenome = 0;

  for(int i = 0; i < 3; i++){ // loop percorre 3 integrantes;
    

    //utilizado do while para caso nao passe nos requisitos ficar em loop ate passar
    do{
      printf("Digite o nome do %d integrante:\n", i + 1);
      fgets(equipe->nome_integrantes[i], sizeof(equipe->nome_integrantes[i]), stdin); //fgets para ler sobrenome

      // recebe o tamanho da string(melhor para visualizar e entender o codigo)
      tamanho = strlen(equipe->nome_integrantes[i]);

      //variaveis "flags para verificar sobronome"
      int encontrou_letra = 0;
      int encontrou_espaco = 0;
      tem_Sobrenome = 0;


    //loop que percorre a string e verifica espacos e letras
    //a logica utilizada foi que o sobrenome é pelo menos 1 letra(do nome) + 1 espaco depois + 1 letra do sobrenome
    for(int j = 0; j < tamanho; j++){
      char c = equipe->nome_integrantes[i][j];

      if(!isspace(c)){
        if(encontrou_letra){
          encontrou_letra = 1;
        }
        else if(encontrou_espaco){
          tem_Sobrenome = 1;
          break;
        }
        else if(encontrou_letra){
          encontrou_espaco = 1;
        }
      }
    }


    //condicoes especificas para o loop
    if (tamanho < 5 || tamanho > 50){
      printf("Nome deve conter entre 5 a 50 caracteres!\n");
    }
    else if(!tem_Sobrenome){
      printf("Precisa conter pelo menos um nome e sobrenome\n");
    }

      //caso tudo seja verdade o loop continua
    } while(tamanho < 5 || tamanho > 50 || !tem_Sobrenome);

    printf("Nome cadastrado com sucesso!\n");
  }

}


int main(){


  EQUIPES equipe;
  validar_nomes(&equipe);


  return 0;
}
