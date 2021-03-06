#include <stdio.h>
#include <dos.h> far
#include <setjmp.h>
#include <alloc.h>
#include <stdlib.h>
#include <string.h>
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

APONTA_REG_CRIT a;

PTR_DESC_PROC prim = NULL;
PTR_DESC d_esc;

void far inicia_semaforo(semaforo *sem, int n) {
        sem->s = n;
        sem->Q = NULL;
}

PTR_DESC_PROC far procura_prox_ativo() {
        PTR_DESC_PROC tmp;
        tmp = prim->prox;
        while(tmp->prox != prim) {
                if(tmp->estado == ativo) {
                        return tmp;
                }
                else {
                        tmp = tmp->prox;
                }
        }
        return NULL;
}

void far volta_dos() {
        disable();
        setvect(8, p_est->int_anterior);
        enable();
        exit(0);
}


void far p(semaforo *sem) {
        PTR_DESC_PROC aux;
        disable();
        if (sem->s > 0) {
                sem->s--;
        }
        else {
                prim->estado = bloq_p;
                if (sem->Q == NULL) {
                        sem->Q = prim;
                        prim->fila_sem = NULL;
                }
                else {
                        aux = sem->Q;
                        while (aux->fila_sem != NULL) {
                                aux = aux->fila_sem;
                        }
                        aux->fila_sem = prim;
                        prim->fila_sem = NULL;
                }
                aux = prim;
                if((prim = procura_prox_ativo()) == NULL) {
                        volta_dos();
                }
                transfer(aux->contexto, prim->contexto);
        }
        enable();
}

void far v(semaforo *sem) {
        PTR_DESC_PROC aux;
        disable();
        if (sem->Q != NULL) {
                sem->Q->estado = ativo;
                aux = sem->Q->fila_sem;
                sem->Q = aux;
        }
        else {
                sem->s++;
        }
        enable();
}


void far cria_processo (char nome_p[], void far (*end_proc)()) {
        PTR_DESC_PROC p_aux;
        if((p_aux = (PTR_DESC_PROC)malloc(sizeof(DESCRITOR_PROC))) == NULL) {
                exit(1);
        }

        strcpy(p_aux->nome, nome_p);
        p_aux->estado = ativo;
        p_aux->contexto = cria_desc();
        newprocess(end_proc, p_aux->contexto);

        if(prim == NULL) {
                prim = p_aux; 
        }
        else {
                p_aux->prox = prim->prox;
        }
        prim->prox = p_aux;
}





void far escalador() {
        p_est->p_origem = d_esc;
        p_est->p_destino = prim->contexto;
        p_est->num_vetor = 8;
        _AH = 0x34;
        _AL = 0x00;
        geninterrupt(0x21);
        while(1) {
                iotransfer();
                disable();
 
                        if((prim = procura_prox_ativo()) == NULL) {
                                volta_dos();
                        }
                        p_est->p_destino = prim->contexto;

                enable();
        }
}

void far dispara_sistema() {
        PTR_DESC d_dispara;
        d_esc = cria_desc();
        newprocess(escalador, d_esc);
        d_dispara = cria_desc();
        transfer(d_dispara, d_esc);
}



void far termina_processo() {
        disable();
        prim->estado = terminado;
        enable();
        while(1);
}
