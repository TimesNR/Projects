#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generarDigitosAleatorios(int *arr, int N);
void actualizarEstadoAnillo(int *celular, int *regla, int N);
void evolucionarAutomata(int *celular, int *regla, int N, int *pasos);
void imprimirEstado(int *celular, int N);

int main(int argc, char *argv[])
{
	int N= 60;
	int pasos= 1000;
	/// int autocelular[N];			// estatica
	int *autocelular= (int *) malloc(N*sizeof(int));	 // dinamica
	
	int regla[8];
	// regla 110: 01110110
	
	regla[0]= 0; regla[1]= 1; regla[2]= 1; regla[3]= 0;
	regla[4]= 1; regla[5]= 1; regla[6]= 1; regla[7]= 0;
	
	generarDigitosAleatorios(autocelular, N);
	evolucionarAutomata(autocelular, regla, N, pasos);
	
	free(autocelular);
	
	return 0;
} 

void generarDigitosAleatorios(int *arr, int N)
{
	int k=0;
	
	srand(time(NULL));	// inicializar el generador aleatorio
	
	for (k=0; k<N; k++)
	   arr[k]= rand()%2;
}

void actualizarEstado(int *celular, int *regla, int N)
{
	int k=0;
	int *siguiente= (int *) malloc(N*sizeof(int));
	
	for (k=0; k<N; k++)
	   {
	   	 if (celular[k-1]==0 && celular[k]==0 && celular[k+1]==0)
	   	   siguiente[k]= regla[0];
	   	   
	   	 if (celular[k-1]==0 && celular[k]==0 && celular[k+1]==1)
	   	   siguiente[k]= regla[1];
	   	   
	   	 if (celular[k-1]==0 && celular[k]==1 && celular[k+1]==0)
	   	   siguiente[k]= regla[2];
	   	   
	   	 if (celular[k-1]==0 && celular[k]==1 && celular[k+1]==1)
	   	   siguiente[k]= regla[3];
	   	   
	   	 if (celular[k-1]==1 && celular[k]==0 && celular[k+1]==0)
	   	   siguiente[k]= regla[4];
	   	   
	   	 if (celular[k-1]==1 && celular[k]==0 && celular[k+1]==1)
	   	   siguiente[k]= regla[5];
	   	   
	   	 if (celular[k-1]==1 && celular[k]==1 && celular[k+1]==0)
	   	   siguiente[k]= regla[6];
	   	   
	   	 if (celular[k-1]==1 && celular[k]==1 && celular[k+1]==1)
	   	   siguiente[k]= regla[7];
	   }
	   
	for (k=0; k<N; k++)
	   celular[k]= siguiente[k];
	   
	free(siguiente);
}

void actualizarEstadoAnillo(int *celular, int *regla, int N)
{
	int k=0;
	int izq=0, der=0;
	int *siguiente= (int *) malloc(N*sizeof(int));
	
	for (k=0; k<N; k++)
	   {
	   	 izq= k-1;
	   	 if (izq<0)
	   	   izq= N-1;
	   	
	   	 der= (k+1)%N;
	   	 
	   	 if (celular[izq]==0 && celular[k]==0 && celular[der]==0)
	   	   siguiente[k]= regla[0];
	   	   
	   	 if (celular[izq]==0 && celular[k]==0 && celular[der]==1)
	   	   siguiente[k]= regla[1];
	   	   
	   	 if (celular[izq]==0 && celular[k]==1 && celular[der]==0)
	   	   siguiente[k]= regla[2];
	   	   
	   	 if (celular[izq]==0 && celular[k]==1 && celular[der]==1)
	   	   siguiente[k]= regla[3];
	   	   
	   	 if (celular[izq]==1 && celular[k]==0 && celular[der]==0)
	   	   siguiente[k]= regla[4];
	   	   
	   	 if (celular[izq]==1 && celular[k]==0 && celular[der]==1)
	   	   siguiente[k]= regla[5];
	   	   
	   	 if (celular[izq]==1 && celular[k]==1 && celular[der]==0)
	   	   siguiente[k]= regla[6];
	   	   
	   	 if (celular[izq]==1 && celular[k]==1 && celular[der]==1)
	   	   siguiente[k]= regla[7];
	   }
	   
	for (k=0; k<N; k++)
	   celular[k]= siguiente[k];
	   
	free(siguiente);
}

void evolucionarAutomata(int *celular, int *regla, int N, int *pasos)
{
	int k=0;
	
	for (k=0; k<pasos; k++)
	   {
	   	 actualizarEstadoAnillo(celular, regla, N);
	   	 imprimirEstado(celular, N);
	   }
}

void imprimirEstado(int *celular, int N)
{
	int k=0;
	
	for (k=0; k<N; k++)
	   printf("%d", celular[k]);
	printf("\n");
}

void crossover(int *nuevoC, int *nuevoD, int *genA, int *genB, int N)
{
	int mitad= N/2;
	
	for (k=0; k<mitad; k++)
	   {
	   		nuevoC[k]= genA[k];
	   		nuevoD[k]= genB[k];
	   }
	   
	for (k= mitad+1; k<N; k++)
	   {
	   		nuevoC[k]= genB[k];
	   		nuevoD[k]= genA[k];
	   }
}

void mutacion(int *gen, int N)
{
	int k=0;
	
	srand(time(NULL));	// inicializar el generador aleatorio
	
	for (k=0; k<N; k++)
	   if (rand()%2==0)
	     gen[k]= rand()%2;
}

int fitness(int *solucion, int *ponderacion, int N)
{
	int k= 0;
	int opt= 0;
	
	for (k=0; k<N; k++)
	   opt+= solucion[k]*ponderacion[k];
	   
	return(opt);
}

void generarPonderacionesAleatorias(int *arr, int N)
{
	int k=0;
	
	srand(time(NULL));	// inicializar el generador aleatorio
	
	for (k=0; k<N; k++)
	   arr[k]= rand()%100;
}

void generarSolucion(int *original, int generaciones)
{
	
	for (k=0; k<generaciones; k++)
}












