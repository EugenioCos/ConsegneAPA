#include "graph.h"

using namespace graph;

struct graph::GraphStruct {
  Vertex first;
  unsigned int n_nodes;
};

struct graph::VertexStruct {
  Label name;
  Label original_name;
  Vertex next;
  Edge adjacent;
  unsigned int n_adjacents;
};

struct graph::EdgeStruct {
  Vertex from; //uguale per tutti i vertici di una stessa lista di adiacenza
  Vertex to; //2° vertice a cui si riferisce la relazione
  Edge next;
};

// crea un grafo vuoto
Graph graph::createEmpty(){
  Graph main = new GraphStruct{emptyVertex, 0};
  return main;
}

// verifica se la struttura dati è vuota
bool isEmpty(const Graph g){
  return g->first == emptyVertex;
}

// ricerca di un vertice a partire da un vertice dato
Vertex getVertex(const Vertex start, const Label l){
  if(start == emptyVertex) return emptyVertex;
  Vertex cur = start;
  while(cur != emptyVertex){ //scorro in cerca del vertice richiesto
    if(cur->name == l) return cur;
    cur = cur->next;
  }
  return emptyVertex;
}

// funzione ausiliaria aggiunge semi arco a lista di adiacenza del vertice from
bool addAlphaEdge(Vertex from, Vertex to) {
  //scorrimento per controllare se l'arco è già presente
  Edge cur = from->adjacent;
  while(cur != emptyEdge && cur->next != emptyEdge){ //scorro fino all'ultimo elemento della lista di adiacenze
    if(cur->to->name == to->name) return false; //semi arco già presente
    cur = cur->next;
  }
  //aggiunta del nuovo semi arco
  Edge new_half_edge = new EdgeStruct{from, to, emptyEdge};
  if(from->adjacent == emptyEdge) from->adjacent = new_half_edge;
  else cur->next = new_half_edge;
  ++(from->n_adjacents);
  return true;
}

// aggiunge un arco tra due nodi
// fallisce se un arco identico esiste già
bool graph::addEdge(Graph g, const Label l1, const Label l2){
  //Verifico casi iniziali
  Vertex v1 = getVertex(g->first, l1);
  Vertex v2 = getVertex(g->first, l2);
  if(v1 == emptyVertex || v2 == emptyVertex || v1 == v2) return false;
  //aggiungo le due parti dell'arco
  if (!addAlphaEdge(v1, v2)) return false; // arco già presente
  //arco non presente, aggiungo l'altra metà
  v2->adjacent = new EdgeStruct{v2, v1, v2->adjacent};
  ++(v2->n_adjacents);
  return true;
}

// funzione ausiliaria, dato un vertice v e una label l, 
// elimina tutti i semi-archi che partono da v e arrivano a vertici di etichetta l
void deleteAlphaEdges(Vertex v, Label l){
  // casi iniziali
  if(v == emptyVertex || v->adjacent == emptyEdge) return;
  // scorro su tutta la lista di adiacenza e elimino gli archi richiesti
  Edge prev = emptyEdge, cur = v->adjacent;
  while(cur != emptyEdge){
    if(cur->to->name == l){
      // aggiusto puntatori
      if(prev == emptyEdge) v->adjacent = cur->next;
      else prev->next = cur->next;
      // cancello, aggiorno contatore
      free(cur);
      --(v->n_adjacents);
      // aggiorno cur
      if(prev == emptyEdge) cur = v->adjacent;
      else cur = prev->next;
    } else {
      prev = cur;
      cur = cur->next;
    }
  }
}

// data un'etichetta, elimina tutti gli archi tra vertici con la stessa etichetta
void graph::deleteLoops(Graph g, Label l){
  Vertex vertex = getVertex(g->first, l);
  while(vertex != emptyVertex){
    deleteAlphaEdges(vertex, l);
    vertex = getVertex(vertex->next, l);
  }
}

// aggiunge un vertice con nome l, fallisce se un vertice con quell'etichetta è già presente
// restituisce true se l'inserimento ha avuto successo
bool graph::addVertex(Graph g, const Label l){
  if(getVertex(g->first, l) != emptyVertex || l == emptyLabel) return false;
  g->first = new VertexStruct{l, l, g->first, emptyEdge, 0};
  ++(g->n_nodes);
  return true;
}

// funzione ausiliaria, cancella un semiarco dato e i suoi successivi
void deleteGraphAuxE(Edge e){
  if(e->next != emptyEdge) deleteGraphAuxE(e->next);
  free(e);
}

// funzione ausiliaria, cancella un vertice e i suoi successivi
void deleteGraphAuxV(Vertex v){
  if(v->next != emptyVertex) deleteGraphAuxV(v->next);
  if(v->adjacent != emptyEdge) deleteGraphAuxE(v->adjacent); 
  free(v);
}

// cancella un grafo
void graph::deleteGraph(Graph g){
  // caso iniziale
  if(!isEmpty(g)) deleteGraphAuxV(g->first);
  free(g);
}

// numero di vertici (non considera etichette)
int graph::numVertexes(const Graph g){
  return g->n_nodes;
}

// funzione ausiliaria, conta archi di un vertice dato e dei suoi successivi
int numEdgesAux(const Vertex v){
  if(v == emptyVertex) return 0;
  return v->n_adjacents + numEdgesAux(v->next);
}

// conta archi
int graph::numEdges(const Graph g){
  return numEdgesAux(g->first)/2; // numero archi = numero semi-archi / 2
}

Edge pickEdge(Vertex v, int n){
  if(v == emptyVertex) return emptyEdge;
  if(v->adjacent != emptyEdge) {
    Edge cur = v->adjacent;
    while(cur != emptyEdge){
      if(n == 0) return cur;
      --n;
      cur = cur->next;
    }
  }
  return pickEdge(v->next, n);
}

void renameVertex(Graph g, Label l_old, Label l_new){
  Vertex cur = getVertex(g->first, l_old);
  while(cur != emptyVertex){
    cur->name = l_new;
    cur = getVertex(cur->next, l_old);
  }
}

Label mergeLabels(Label l1, Label l2){
  Label merged_l = "";
  int ndx1 = 0, ndx2 = 0;
  while(ndx1 < l1.length() || ndx2 < l2.length()){
    if(ndx1 >= l1.length() || (l2[ndx2] < l1[ndx1] && ndx2 < l2.length())){
      merged_l += l2[ndx2];
      ++ndx2;
    } else if(ndx2 >= l2.length() || (l1[ndx1] < l2[ndx2] && ndx1 < l1.length())){
      merged_l += l1[ndx1];
      ++ndx1;
    } else if(l1[ndx1] == l2[ndx2]){
      merged_l += l1[ndx1];
      ++ndx1;
      ++ndx2;
    }
  }
  return merged_l;
}

Label mergeNodes(Graph g, Edge e){
  Label l1 = e->from->name;
  Label l2 = e->to->name;
  Label merged_l = mergeLabels(l1, l2);
  renameVertex(g, l1, merged_l);
  renameVertex(g, l2, merged_l);
  return merged_l;
}

Graph graph::MCMinCut(Graph g, bool verbose){
  int n = g->n_nodes;
  for (int i = n; i > 2; --i){
    // 1. campiona un arco G con probabilità uniforme
    if(verbose) std::cout << "--- Iterazione " << n-i << std::endl;
    if(numEdges(g) == 0) break;
    int r = rand() % (numEdges(g)*2);
    Edge e = pickEdge(g->first, r);
    if(verbose) std::cout << "- Arco scelto: " << e->from->name << " <-> " << e->to->name << std::endl;
    // e identifica i suoi vertici, u e v, in un nuovo vertice uv
    Label new_name = mergeNodes(g, e);
    // 2. rimuovi tutti gli archi che univano i vertici u e v, incluso quello campionato, e mantieni tutti
    // gli archi che incidono sul nuovo vertice uv
    deleteLoops(g, new_name);
    if(verbose) {
      printGraph(g);
      std::cout << std::endl;
    }
  }
  if(verbose) printMinCut(g);
  // C` e costituito dagli archi che uniscono gli ultimi due vertici rimasti di G
  return g;
}

// stampa i vertici
void printVertexes(const Vertex v){
  if(v == emptyVertex) return;
  std::cout << "nome: " << v->name << std::endl;
  printVertexes(v->next);
}

// stampa gli archi
void printEdges(const Graph g){
  Vertex vertex = g->first;
  std::cout << "- SEMI-ARCHI: ( " << graph::numEdges(g) << " ARCHI )" << std::endl;
  while(vertex != emptyVertex){
    Edge edge = vertex->adjacent;
    while(edge != emptyEdge){
      Label from = vertex->name  + " ( " + vertex->original_name + " )";
      Label to = edge->to->name  + " ( " + edge->to->original_name + " )";
      std::cout << from << "  ->  " << to << std::endl;
      edge = edge->next;
    }
    vertex = vertex->next;
  }
}

// stampa archi e nodi del grafo
void printGraph(const Graph g){
  std::cout << "- NODI:" << std::endl;
  printVertexes(g->first);
  printEdges(g);
}

// stampa gli archi del taglio minimo
void printMinCut(const Graph g){
  std::cout << "- TAGLIO MINIMO (presunto): " << std::endl;
  printEdges(g);
}