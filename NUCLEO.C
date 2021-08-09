#include<system.h>
#include<stdio.h>
#include<string.h>
#include<NUCLEO.H>

typedef struct desc_proc {
        char nome[35];
        enum {ativo, terminado} estado;
        PTR_DESC contexto;
        struct desc_proc *prox;
} DESCRITOR_PROC;

typedef DESCRITOR_PROC *PTR_DESC_PROC;

PTR_DESC_PROC prim = NULL;
PTR_DESC d_esc;

void far cria_processo (char nome_p[], void far (*end_proc)())
{
 PTR_DESC_PROC p_aux, tmp;
 if((p_aux = (PTR_DESC_PROC)malloc(sizeof(DESCRITOR_PROC))) == NULL)
 {
  exit(1);
 }
 strcpy(p_aux->nome, nome_p);
 p_aux->estado = ativo;
 p_aux->contexto = cria_des; // Inicializa o descritor de co-rotina
 newprocess(end_proc, p_aux->contexto);

 if(prim == NULL)
 {
  prim = p_aux;
  prim->prox = NULL;
 }
 else if(prim->prox == NULL)
 {
  prim->prox = p_aux;
  p_aux->prox = prim;
 }
 else
 {
  tmp = prim;
  while (tmp->prox != prim)
  {
   tmp = tmp->prox;
  }
  p_aux->prox = prim;
  tmp->prox = p_aux;
 }
}

PTR_DESC_PROC far procura_prox_ativo()
{
 PTR_DESC_PROC tmp;
 tmp = prim->prox;
 while(tmp->prox != prim)
 {
  if(trmp->estado == ativo)
  {
   return tmp;
  }
  else
  {
   tmp = tmp->prox;
  }
 }
 return NULL;
}



void far escalador()
{
 p_est->p_origem = d_esc;
 p_est->p_destino = prim->contexto;
 p_est->num_vetor = 8;
 while(1)
 {
  iotransfer();
  disable();
  if((prim = procura_prox_ativo()) == NULL)
  {
   volta_dos();
  }
  p_est->p_destino = prim->contexto;
  enable();
 }
}

void far dispara_sistema()
{
 PTR_DESC d_dispara;
 d_esc = cria_desc();
 newprocess(escalador, d_esc);
 d_dispara = cria_desc();
 transfer(d_dispara, d_esc);
}

void far volta_dos()
{
 disable();
 setvect(8, p_est->inst_anterior);
 enable();
 exit(0);
}

void far termina_processo()
{
 disable();
 prim->estado = terminado;
 enable();
 while(1);
}
