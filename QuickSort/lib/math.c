#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <fcntl.h>

int ValoreAtteso(int confronti[], int R){
    //Calcola valore atteso
    long long int tmp = 0;
    for(int i = 0; i < R; i++)
        tmp += confronti[i];
    tmp /= R;
    return (int)tmp;
}

int DeviazioneStandard(int confronti[], int valoreAtteso, int R){
    // Calcolo deviazione standard
    long long int deviazione = 0;
    for(int i = 0; i < R; ++i){
        int diff = confronti[i] - valoreAtteso;
        deviazione += pow(diff, 2);
    }
    deviazione /= (R-1);
    return sqrt(deviazione);
}
