#include<nucleo.h>
#include<stdio.h>

FILE *arq;

int buffer[6], mensagem = 0, pont_prod = 0, pont_consum = 0, max = 6;

semaforo mutex, cheio, vazio;

void far deposita(int msg, int prod){
	if((&vazio)->s < 0){
		fprintf(arq, "Produtor %d nao conseguiu inserir mensagem %d.\n", prod, msg);
		printf("Produtor %d nao conseguiu inserir mensagem %d.\n", prod, msg);
	} else {
		fprintf(arq, "Produtor %d conseguiu inserir mensagem %d.\n", prod, msg);
		printf("Produtor %d conseguiu inserir mensagem %d.\n", prod, msg);
		mensagem++;
		buffer[pont_prod++] = msg;
		if(pont_prod > max)
			pont_prod = 0;
	}
}
void far retira(int prod){
	if((&cheio)->s > max){
		fprintf(arq, "Produtor %d conseguiu retirar mensagem .\n", prod);
		printf("Produtor %d conseguiu retirar mensagem .\n", prod);
	} else {
		fprintf(arq, "Produtor %d conseguiu retirar mensagem %d.\n", prod, buffer[pont_consum]);
		printf("Produtor %d conseguiu retirar mensagem %d.\n", prod, buffer[pont_consum]);
		pont_consum++;
		if(pont_consum > max)
			pont_consum = 0;
	}
}
void far produtor1(){
	int i = 0;
	while(i < 10){
		p(&vazio);
		p(&mutex);
		deposita(mensagem, 1);
		v(&mutex);
		v(&cheio);
		i++;
	}
	termina_processo();
}
void far produtor2(){
	int i = 0;
	while(i < 10){
		p(&vazio);
		p(&mutex);
		deposita(mensagem, 2);
		v(&mutex);
		v(&cheio);
		i++;
	}
	termina_processo();
}
void far consumidor1(){
	int i = 0;
	while(i < 10){
		p(&cheio);
		p(&mutex);
		retira(1);
		v(&mutex);
		v(&vazio);
		i++;
	}
	termina_processo();
}
void far consumidor2(){
	int i = 0;
	while(i < 10){
		p(&cheio);
		p(&mutex);
		retira(2);
		v(&mutex);
		v(&vazio);
		i++;
	}
	termina_processo();
}
main(){
	arq = fopen("RESUL.txt","w");
	cria_processo("p1", produtor1);
	cria_processo("p2", produtor2);
	cria_processo("c1", consumidor1);
	cria_processo("c2", consumidor2);
	inicia_semaforo(&cheio, 0);
	inicia_semaforo(&vazio, max);
	inicia_semaforo(&mutex, 1);
	dispara_sistema();
	fclose(arq);
}