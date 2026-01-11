#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib/utility.h"

const int R = 100000;
const int N = 10000;
int confronti[R];
int intervalli_grafico = 50;
const char * output_file = "out_grafico.txt";
int S[N];

int main(){
    /*
    - Creazione della sequenza
    - Iterazioni di quicksort con salvataggio del numero di confronti
    - Calcolo di valore atteso e deviazione standard
    */
    srand(time(NULL));
    CreaSequenza(S, N, 100000);
    printf("Sequenza creata\n");
    IteraQuickSort(S, confronti, N, R); 
    int atteso = ValoreAtteso(confronti, R);
    int deviazione = DeviazioneStandard(confronti, atteso, R);
    printf("Media empirica: %d\n", atteso);
    printf("Deviazione standard: %d\n", deviazione);
    
    /*
    Calcolo del numero di confronti minimo, massimo
    */
    int min = 1000000000;
    int max = 0;
    for(int i = 0; i < R; i++){
        if(confronti[i] < min) min = confronti[i];
        if(confronti[i] > max) max = confronti[i];
    }
    printf("Numero confronti minimo: %d\n", min);
    printf("Numero confronti massimo: %d\n", max);
    
    /*
    Apertura del file di output
    */
    FILE * out_fd = fopen(output_file, "w");
    if(out_fd == NULL){
        printf("Impossibile aprire il file output");
        exit(0);
    };
    
    /*
    Scrittura sul file, output:
    - Viene scritta la prima riga con i parametri (R, N, min, etc.)
    - Viene scritta una riga per ogni valore da mostrare nel grafico nella forma [x] [y]
    - Viene prodotto un file con 50 valori per un grafico bin 50
    Procedimento:
    - L'array dei confronti è in ordine crescente in modo da scorrere solo una volta
    - Per oniuno dei 50 intervalli si sale finchè si trovano valori appartenenti all'intervallo
    - Al termine dell'itervallo si calcolano e scrivono i valori x e y medi (oppure y=0)
    */
    fprintf(out_fd, "%d %d %d %d %d\n", atteso, N, R, min, max);
    LVQuickSort(confronti, 0, R);
    double intervallo_left_limit = min;
    double delta = (max - min)/intervalli_grafico;
    int iterazioni = 0;
    long long int n_medio = 0;
    int index = 0;
    while(index < R){
        if(confronti[index] <= intervallo_left_limit + delta){
            n_medio += confronti[index];
            ++iterazioni;
            ++index;
            continue;
        }
        if(n_medio > 0) n_medio /= iterazioni;
        else n_medio = intervallo_left_limit + delta/2;
        fprintf(out_fd, "%lld %d\n", n_medio, iterazioni);
        iterazioni = n_medio = 0;
        intervallo_left_limit += delta;
    }
    fclose(out_fd);
    printf( "Esecuzione terminata\n");
}
