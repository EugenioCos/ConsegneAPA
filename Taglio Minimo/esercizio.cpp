#include <iostream>
#include <random>
#include <time.h>
#include "lib/graph.h"

using namespace std;

const int R = 100000;
const int NUM_ARCHI = 21;
const int NUM_NODI = 9;
const char FRITSCH_NODI[NUM_NODI] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
const string FRITSCH_ARCHI[NUM_ARCHI] = {"AH","AB","AC","AD","AI","BH","BE","BC","CE","CF","CD","DF","DI","EH","EG","EF","FG","FI","GH","GI","HI"};
bool risultato[R];

graph::Graph createFritshGraph(){
    graph::Graph g = graph::createEmpty();
    for(int i = 0; i < NUM_NODI; ++i){
        string l(1, FRITSCH_NODI[i]);
        if (!graph::addVertex(g, l))
            throw runtime_error("nodo " + l + " già presente");
    }
    for(int i = 0; i < NUM_ARCHI; ++i){
        string arco_str = FRITSCH_ARCHI[i];
        string n1(1, arco_str.at(0));
        string n2(1, arco_str.at(1));
        if (!graph::addEdge(g, n1, n2))
            throw runtime_error("arco tra " + n1 + " e " + n2 + " già presente");
    }
    return g;
}

void iteraMCMinCut(){
    cout << std::boolalpha;
    for(int i = 0; i < R; ++i){
        // Creazione grafo di Fritsch
        graph::Graph fritsch = createFritshGraph();
        graph::Graph minCut = graph::MCMinCut(fritsch, false);
        risultato[i] = graph::numEdges(minCut) == 4;
        cout << "Iterazione n°" << i << ", trovato: " << risultato[i] << endl;
        graph::deleteGraph(fritsch);
    }
}

int numSucess(){
    int count = 0;
    for(int i = 0; i < R; ++i){
        if(risultato[i]) ++count;
    }
    return count;
}

int main(int argv, char * argc[]) {
    srand(time(NULL));
    if(argv > 1) {
        // Iterazione di MCMinCut che mostra a console i passaggi
        graph::Graph fritsch = createFritshGraph();
        graph::Graph minCut = graph::MCMinCut(fritsch, true);
    } else {
        srand(time(NULL));
        iteraMCMinCut();
        cout << "R: " << R << ", numero di successi: " << numSucess() << endl;
    }
}