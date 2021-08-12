 #include <system.h>
 #include <stdio.h>

 PTR_DESC pmain, p_esc, pa, pb;

 void far corotinaA(){
  while(1){
   printf("corotinaA ");
   }
 }

 void far corotinaB(){
  while(1){
   printf("corotinaB ");
   }
 }

 void far escalador(){
  p_est->p_origem = p_esc;
  p_est->p_destino = pa;
  p_est->num_vetor = 8;
  while(1){
   iotransfer();
   disable();
   if(p_est->p_destino == pa)
    p_est->p_destino = pb;
   else
    p_est->p_destino = pa;
   enable();
   }
 }

 main(){
  pmain = cria_desc();
  pa = cria_desc();
  pb = cria_desc();
  p_esc = cria_desc();
  newprocess(corotinaA, pa);
  newprocess(corotinaB, pb);
  newprocess(escalador, p_esc);
  transfer(pmain,p_esc);
 }