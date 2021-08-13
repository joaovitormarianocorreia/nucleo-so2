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

void far inicia_semaforo(semaforo *sem, int n);

void far p(semaforo *sem);

void far v(semaforo *sem);

void far cria_processo(char nome_p[], void far (*end_prc)());

PTR_DESC_PROC far procura_prox_ativo();

void far escalador();

void far dispara_sistema();

void far volta_dos();

void far termina_processo();

