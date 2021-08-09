#include <system.h>
#include <stdio.h>

PTR_DESC c1, c2, prin;
void far tic()
{
  while (1)
  {
    printf("Tic ");
    transfer(c1, c2);
  }
}

void far tac()
{
  while (1)
  {
    printf("Tac\n");
    transfer(c2, c1);
  }
}

int main()
{
  clrscr();
  c1 = cria_desc();
  c2 = cria_desc();
  prin = cria_desc();
  newprocess(tic, c1);
  newprocess(tac, c2);
  transfer(prin, c1);
}