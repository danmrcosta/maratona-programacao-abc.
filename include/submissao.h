#ifndef SUBMISSAO_H
#define SUBMISSAO_H

#include "equipes.h"

void registrar_submissao(EQUIPES *equipe, char problema, int tempo, char veredito[]); //registra submissoes

void realizar_submissao(EQUIPES *equipe, int quantidade); //realiza as submissoes

#endif
