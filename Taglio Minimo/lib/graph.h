#include <string>
#include <iostream>
#include <list>

namespace graph {

    typedef std::string Label;
    typedef std::list<Label> List;

    struct GraphStruct;
    struct VertexStruct;
    struct EdgeStruct;

    typedef GraphStruct *Graph;
    typedef VertexStruct *Vertex;
    typedef EdgeStruct *Edge;

    const Vertex emptyVertex = nullptr;
    const Edge emptyEdge = nullptr;

    const Label emptyLabel = "";

    // crea un database vuoto
    Graph createEmpty();

    // aggiunge un nodo, fallisce se un nodo con quell'etichetta è già presente
    // restituisce true se l'inserimento ha avuto successo
    bool addVertex(Graph g, const Label l);

    void deleteGraph(Graph g);

    // aggiunge un arco tra due nodi esistenti, fallisce se l'arco esiste già
    // restituisce true se l'inserimento ha avuto successo
    bool addEdge(Graph g, const Label n1, const Label n2);

    void deleteLoops(Graph g, Label l);

    // numero di vertici (non considera etichette duplicate)
    int numVertexes(const Graph g);

    // numero di archi
    int numEdges(const Graph g);

    Graph MCMinCut(Graph g, bool verbose);
}

// stampa il contenuto del database
void printGraph(const graph::Graph g);

// stampa il contenuto del database
void printMinCut(const graph::Graph g);
