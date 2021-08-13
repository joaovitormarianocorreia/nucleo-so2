#include <system.h>
#include <stdio.h>

PTR_DESC pmain, ptic, ptac;

void far tic(){
 int i = 0;
 while (i < 100){
  printf  ("tic-");
  transfer(ptic,ptac);
  i++;
  }
  transfer(ptic,pmain);
 }

 void far tac(){
  while(1){
   printf("tac ");
   transfer(ptac,ptic);
   }
 }

 main(){
  pmain = cria_desc();
  ptic = cria_desc();
  ptac = cria_desc();
  newprocess(tic,ptic);
  newprocess(tac,ptac);
  transfer(pmain,ptic);
  printf("fim");
 }