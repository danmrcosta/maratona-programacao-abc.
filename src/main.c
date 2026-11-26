
#include <stdio.h>   // printf, scanf, fgets, getchar
#include <string.h>  // strlen, strcmp
#include <ctype.h>   // isalpha (verifica se o caractere e uma letra)

// ---------- Estruturas de dados (antes em equipes.h) ----------

// Guarda o desempenho de uma equipe em UM problema
typedef struct {
  int resolvidos;      // quantidade de problemas resolvidos
  int minutos;         // tempo total de submissao em minutos
  int qnt_submissoes;  // quantidade total de submissoes
} DESEMPENHO;

// Guarda todos os dados de uma equipe
typedef struct{
  char nome_equipe[51];          // nome da equipe: 50 caracteres + 1 do caractere nulo '\0'
  char instituicao_origem[51];   // instituicao: 50 caracteres + 1 do caractere nulo '\0'
  char nome_integrantes[3][101]; // 3 integrantes (linha 0 = pessoa 1, linha 1 = pessoa 2, linha 2 = pessoa 3), 100 caracteres + '\0'
  DESEMPENHO problemas[14];      // um desempenho para cada problema, de A ate N (14 problemas)
} EQUIPES;

// ---------- Prototipos das funcoes (antes nos .h) ----------
// Avisam o compilador que as funcoes existem, para poderem ser usadas antes de definidas

void limpar_nova_linha(char *s);                        // remove o '\n' que o fgets deixa na string
int nome_pessoa_valido(char *nome);                     // valida o nome de um integrante
int nome_equipe_instituicao_valido(char *nome);         // valida nome da equipe ou da instituicao

void validar_nomes(EQUIPES *equipe);                    // le e valida todos os dados de cadastro da equipe
int buscar_equipe(EQUIPES equipes[], int quantidade, char nome[]); // procura a equipe pelo nome e devolve o indice
void inicializar_equipe(EQUIPES *equipe);  // zera o desempenho da equipe nos 14 problemas

int veredito_valido(char *veredito); // valida os vereditos (as siglas)
void registrar_submissao(EQUIPES *equipe, char problema, int tempo, char veredito[]); // registra uma submissao
void realizar_submissao(EQUIPES *equipe, int quantidade);                             // le os dados de uma submissao

// ============================================================
// validacao.c
// ============================================================

// Remove o '\n' que o fgets guarda no final da string lida
void limpar_nova_linha(char *s){
  for(int k = 0; s[k] != '\0'; k++){          // percorre a string ate chegar no fim ('\0')
    if(s[k] == '\n'){ s[k] = '\0'; break; }   // ao achar o '\n', troca por '\0' (encerra a string ali) e para o laco
  }
}

// Validacao do nome de pessoa: so letra, espaco, hifen e apostrofo
int nome_pessoa_valido(char *nome){
  int tamanho = strlen(nome);                  // calcula quantos caracteres o nome tem
  if(tamanho < 5 || tamanho > 100) return 0;   // fora do limite de 5 a 100 caracteres: invalido (max = 100 e nao 50)

  int tem_espaco = 0;         // vira 1 quando encontra o primeiro espaco
  int tem_letra_antes = 0;    // vira 1 se houver letra antes do espaco (nome)
  int tem_letra_depois = 0;   // vira 1 se houver letra depois do espaco (sobrenome)

  for(int i = 0; i < tamanho; i++){            // examina o nome caractere por caractere
    char c = nome[i];                          // guarda o caractere atual para facilitar a leitura
    // So valido isso aqui
    if(!(isalpha(c) || c == ' ' || c == '-' || c == '\'')){  // se nao for letra, espaco, hifen ou apostrofo...
      return 0;                                // ...o nome e invalido
    }
    if(c == ' ') tem_espaco = 1;               // marca que ja passou por um espaco
    else if(isalpha(c)){                       // se o caractere for uma letra...
        if(!tem_espaco) tem_letra_antes = 1;   // ...e ainda nao houve espaco, e parte do nome
        else tem_letra_depois = 1;             // ...e ja houve espaco, e parte do sobrenome
    }
  }

  // Precisa ter nome e sobrenome = letra + espaço + letra
  // ta com um bug aqui
  return (tem_espaco && tem_letra_antes && tem_letra_depois);  // so e valido se tiver espaco, letra antes e letra depois
}

// Validacao da parte de equipe / instituicao: de 1 a 50 caracteres
int nome_equipe_instituicao_valido(char *nome){
  int tamanho = strlen(nome);                  // quantidade de caracteres da string
  return (tamanho >= 1 && tamanho <= 50);      // valido se tiver entre 1 e 50 caracteres
}

// ============================================================
// equipes.c
// ============================================================

// Le e valida nome da equipe, instituicao e os 3 integrantes
void cadastro(EQUIPES *equipe){
  // 1. Valida EQUIPE
  do{                                          // repete ate o usuario digitar um nome valido
    printf("Digite o nome da equipe (max 50 caracteres):\n");                         // pede o nome da equipe
    fgets(equipe->nome_equipe, sizeof(equipe->nome_equipe), stdin);                   // le a linha digitada (limitada ao tamanho do campo)
    limpar_nova_linha(equipe->nome_equipe);                                           // tira o '\n' do final
    if(!nome_equipe_instituicao_valido(equipe->nome_equipe))                          // se o nome nao for valido...
      printf("Nome da equipe deve ter 1 a 50 caracteres!\n");                         // ...avisa o usuario do erro
  } while(!nome_equipe_instituicao_valido(equipe->nome_equipe));                      // volta a pedir enquanto estiver invalido


  // 2. Valida INSTITUICAO
  do{                                          // repete ate a instituicao ser valida
    printf("Digite a instituicao de origem (max 50 caracteres):\n");                  // pede a instituicao
    fgets(equipe->instituicao_origem, sizeof(equipe->instituicao_origem), stdin);     // le a linha digitada
    limpar_nova_linha(equipe->instituicao_origem);                                    // tira o '\n' do final
    if(!nome_equipe_instituicao_valido(equipe->instituicao_origem))                   // se for invalida...
      printf("Instituicao deve ter 1 a 50 caracteres!\n");                            // ...mostra a mensagem de erro
  } while(!nome_equipe_instituicao_valido(equipe->instituicao_origem));               // repete enquanto estiver invalida


  // 3. Valida os 3 INTEGRANTES
  for(int i = 0; i < 3; i++){                  // repete o processo para cada um dos 3 integrantes
    do{                                        // repete ate o nome do integrante ser valido
      printf("Digite o nome do %d integrante:\n", i + 1);                             // pede o nome (i + 1 para mostrar 1, 2 e 3)
      fgets(equipe->nome_integrantes[i], sizeof(equipe->nome_integrantes[i]), stdin); // le o nome do integrante i
      limpar_nova_linha(equipe->nome_integrantes[i]);                                 // tira o '\n' do final

      if(!nome_pessoa_valido(equipe->nome_integrantes[i]))                            // se o nome for invalido...
        printf("Nome invalido! Use somente letras, espaco, hifen e apostrofo, 5 a 100 caracteres, com nome e sobrenome.\n"); // ...explica as regras

    } while(!nome_pessoa_valido(equipe->nome_integrantes[i]));                        // repete enquanto estiver invalido

  }

  printf("Equipe %s cadastrada com sucesso!\n", equipe->nome_equipe);                 // confirma o cadastro da equipe

}

// Procura uma equipe pelo nome e devolve a posicao dela no vetor (ou -1 se nao existir)
int buscar_equipe(EQUIPES equipes[], int quantidade, char nome[]){

  for(int i = 0; i < quantidade; i++){         // percorre todas as equipes cadastradas

    if(strcmp(equipes[i].nome_equipe, nome) == 0){  // compara os nomes (strcmp devolve 0 quando sao iguais)
      return i;                                // achou: devolve o indice da equipe
    }

  }

  return -1;                                   // percorreu tudo e nao achou: devolve -1

}

// Coloca zero em todos os campos de desempenho da equipe
void inicializar_equipe(EQUIPES *equipe){

  for(int i = 0; i < 14; i++){                 // percorre os 14 problemas (posicao 0 = A ate posicao 13 = N)
    equipe->problemas[i].resolvidos = 0;       // 0 = sem problema ainda 
    equipe->problemas[i].minutos = 0;          // nenhum tempo ainda
    equipe->problemas[i].qnt_submissoes = 0;   // nenhuma submissao ainda
  }

}


// ============================================================
// submissao.c
// ============================================================

// Le da entrada os dados de uma submissao e chama o registro
//

// devolve 1 se o veredito for uma das 5 siglas permitidas, e 0 caso contrario
int veredito_valido(char *veredito){
  return (strcmp(veredito, "AC") == 0 || strcmp(veredito, "PE") == 0 ||
          strcmp(veredito, "MLE") == 0 || strcmp(veredito, "TLE") == 0 ||
          strcmp(veredito, "WA") == 0);
}

//
void realizar_submissao(EQUIPES equipes[], int quantidade) {

    char nome[51];     // armazenar o nome da equipe digitado
    int indice;        // posicao da equipe no vetor
    char problema;     // guardar a letra do problema
    int tempo;         // guardar o tempo da submissao
    char veredito[100]; // guardar o veredito (tamanho folgado para uma digitacao errada nao sobrar no teclado)

    // Procura equipe
    do {                                                   // repete ate encontrar uma equipe existente
        printf("Digite o nome da equipe:\n");              // pede o nome da equipe
        fgets(nome, sizeof(nome), stdin);                  // le a linha digitada

        limpar_nova_linha(nome);                           // tira o '\n' do final

        indice = buscar_equipe(equipes, quantidade, nome); // procura a equipe e guarda a posicao (ou -1)

        if (indice == -1) {                                // se nao encontrou...
            printf("Equipe nao encontrada! Tente novamente.\n"); // ...avisa e vai pedir de novo
        }

    } while (indice == -1);                                // continua pedindo enquanto nao achar

    printf("Equipe encontrada!\n");                        // confirma que a equipe existe

    // ta lendo o  problema (so aceita de A ate N)
    do {
        printf("Digite o problema (A ate N):\n");          // pede a letra do problema
        scanf(" %c", &problema);                           // le um caractere (o espaco antes do %c ignora espacos e quebras de linha)
        if (problema < 'A' || problema > 'N') {            // se estiver fora do intervalo...
            printf("Problema invalido!\n");                // ...avisa e pede de novo
        }
    } while (problema < 'A' || problema > 'N');            // repete enquanto for invalido

    // Ler tempo (nao pode ser negativo)
    do {
        printf("Digite o tempo:\n");                       // pede o tempo da submissao
        scanf("%d", &tempo);                               // le o tempo como numero inteiro
        if (tempo < 0) {                                   // tempo negativo nao entra
            printf("Tempo invalido!\n");                   // ...avisa e pede de novo
        }
    } while (tempo < 0);                                   // repete enquanto for invalido

    // Consumir/limpar o enter deixado pelo scanf
    getchar();                                             // descarta o '\n' que sobrou, para nao atrapalhar o proximo fgets

    // Ler veredito (AC, PE, MLE, TLE ou WA)
    do {
        printf("Digite o veredito (AC, PE, MLE, TLE ou WA):\n"); // pede o resultado da submissao
        fgets(veredito, sizeof(veredito), stdin);          // le a linha digitada
        limpar_nova_linha(veredito);                       // tira o '\n' do final
        if (!veredito_valido(veredito)) {                  // se nao for uma das 5 siglas...
            printf("Veredito invalido!\n");                // ...avisa e pede de novo
        }
    } while (!veredito_valido(veredito));                  // repete enquanto for invalido

    // Registrar submissao
    registrar_submissao(&equipes[indice], problema, tempo, veredito); // envia os dados para a equipe encontrada
}

// Registra a submissao no desempenho da equipe
void registrar_submissao(EQUIPES *equipe, char problema, int tempo, char veredito[]) {

    int posicao = problema - 'A'; // A vira 0, B vira 1, n vira 13

    if(equipe->problemas[posicao].resolvidos == 1) return; // se ja foi resolvido, ignora a submissao

    equipe->problemas[posicao].qnt_submissoes++; // como chegou aqui o problema nao foi resolvido: conta +1

    if(strcmp(veredito, "AC") == 0 || strcmp(veredito, "PE") == 0){ // AC e PE sao os aceitos
      equipe->problemas[posicao].resolvidos = 1;  // marca o problema como resolvido (1 = sim)
      equipe->problemas[posicao].minutos = tempo; // guarda o tempo em que foi resolvido
    }

}

// ============================================================
// main.c
// ============================================================

int main(){
    EQUIPES equipes[5000];  // vetor com ate 5000 equipes
    int quantidade = 0;     // quantas equipes ja foram cadastradas
    int x;                  // opcao escolhida no menu

    do{
        printf("Escolha uma opção:\n");
        printf("1. Cadastro de Equipe.\n");
        printf("2. Busca por Instituição.\n");
        printf("3. Registro de Submissão.\n");
        printf("4. Apresentação do Placar Atual.\n");
        printf("0. Sair.\n");
        scanf("%d", &x);
        getchar();  // descarta o '\n' que o scanf deixou, para nao atrapalhar os fgets das outras funcoes

        switch (x){
            case 1:
                if(quantidade < 5000){
                    inicializar_equipe(&equipes[quantidade]);  // zera o desempenho da nova equipe
                    cadastro(&equipes[quantidade]);            // le e valida os dados dela
                    quantidade++;                              // agora ha uma equipe a mais
                } else {
                    printf("Limite de 5000 equipes atingido.\n");
                }
                break;
            case 2:
                printf("Opção: 2\n");
                break;
            case 3:
                if(quantidade == 0){
                    printf("Nenhuma equipe cadastrada ainda!\n");  // sem equipes, a busca pelo nome nunca terminaria
                } else {
                    realizar_submissao(equipes, quantidade);
                }
                break;
            case 4:
                printf("Opção: 4\n");
                break;
            case 0:
                printf("Encerrando.\n");
                break;
            default:
                printf("Opção inválida, escolha uma das opções do menu.\n \n");
                continue;
        }
    } while(x != 0);

    return 0;
}
