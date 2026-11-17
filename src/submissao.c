

#include <stdio.h>
#include <string.h>

#include "submissao.h"
#include "equipes.h"
#include "validacao.h"

void realizar_submissao(EQUIPES equipes[], int quantidade) {

    char nome[51]; // armazenar o nome;
    int indice; //variavel usada para a condicao
    char problema; //guardar o caractere do problema
    int tempo; // guardar o tempo de cada problema
    char veredito[5]; // guardar os conceitos e +1 para o caractere nulo(pois sao 4)

    // Procura equipe
    do {
        printf("Digite o nome da equipe:\n");
        fgets(nome, sizeof(nome), stdin);

        limpar_nova_linha(nome);

        indice = buscar_equipe(equipes, quantidade, nome);

        if (indice == -1) {
            printf("Equipe nao encontrada! Tente novamente.\n");
        }

    } while (indice == -1);

    printf("Equipe encontrada!\n");

    // Ler problema
    printf("Digite o problema (A ate N):\n");
    scanf(" %c", &problema);

    // Ler tempo
    printf("Digite o tempo:\n");
    scanf("%d", &tempo);

    // Consumir/limpar o enter  deixado pelo scanf
    getchar();

    // Ler veredito
    printf("Digite o veredito (AC, PE, MLE, TLE ou WA):\n");
    fgets(veredito, sizeof(veredito), stdin);

    limpar_nova_linha(veredito);

    // Registrar submissao
    registrar_submissao(&equipes[indice], problema, tempo, veredito);
}

void registrar_submissao(EQUIPES *equipe, char problema, int tempo, char veredito[]) {

    // Você implementará a lógica de atualização aqui.
    //


}
