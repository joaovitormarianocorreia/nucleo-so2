#include <system.h>
#include <stdio.h>
#include <string.h>

typedef struct desc_proc {
        char nome[35];
        enum {ativo, terminado} estado;
        PTR_DESC contexto;
        struct desc_proc *prox;
} DESCRITOR_PROC;

typedef DESCRITOR_PROC *PTR_DESC_PROC;

extern void far cria_processo(char nome_p[], void far (*end_prc)());

extern PTR_DESC_PROC far procura_prox_ativo();

extern void far escalador();

extern void far dispara_sistema();

extern void far termina_processo();