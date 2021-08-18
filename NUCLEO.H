#include <stdio.h>
#include <dos.h> far
#include <setjmp.h>
#include <alloc.h>
#include <stdlib.h>
#include <system.h>

typedef struct registros {
        unsigned bx1, es1;
} regis;

typedef union k {
        regis x;
        char far *y;
} APONTA_REG_CRIT;


typedef struct desc_p {
        char nome[35];
        enum {ativo, bloq_p,terminado} estado;
        PTR_DESC contexto;
        struct desc_p *fila_sem;
        struct desc_p *prox;
} DESCRITOR_PROC;

typedef DESCRITOR_PROC *PTR_DESC_PROC;

typedef struct {
        int s;
        PTR_DESC_PROC Q;
} semaforo;

extern void far inicia_semaforo(semaforo *sem, int n);

extern void far p(semaforo *sem);

extern void far v(semaforo *sem);

extern void far cria_processo(char nome_p[], void far (*end_prc)());

extern PTR_DESC_PROC far procura_prox_ativo();

extern void far escalador();

extern void far dispara_sistema();

extern void far volta_dos();

extern void far termina_processo();

