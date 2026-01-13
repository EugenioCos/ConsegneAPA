# Compito 6.1. Implementazione di MCMinCut

Autore: Eugenio Costagliola, s5583414

## Lista comandi (da eseguire dalla root):

- Per compilare il programma

  > make

- Per eseguire il programma:

  > ./exec

- Per eseguire MCMicCut una sola volta e vedere i passaggi svolti:

  > ./exec [un qualsiasi argomento]

## Svolgimento

Di seguito riportata la consegna suddivisa in parti accompagnate dalla
spiegazione del lavoro svolto.

1. _Genera il grafo di Fritsch in Figura 11_

    Ho deciso di implementare il grafo riciclando l'ultimo laboratorio del corso Algoritmi e Strutture Dati del primo anno. <br>
    Il grafo è implementato tramite una lista di nodi (vertici) ciascuno con lista di adiacenza che rappresenta gli archi dal lato di tale vertice e ogni arco è nella lista di adiacenza di entrambi i nodi.
    
2. _e calcola la frequenza empirica ˆp con la quale ottieni un taglio minimo applicando MCMinCut 10^5 volte._

    Implementato in esercizio.cpp.
    Il taglio minimo è ottenuto quando
    - all'ultima iterazione del ciclo all'interno di MCMinCut tutti i nodi sono identificati in esattamente 2 nomi distinti e quindi si ha il grafo iniziale diviso in 2 componenti.
    - gli unici archi rimasti alla fine di MCMinCut solo quelli tra le due componenti perchè a ogni raggruppamento vengono cancellati tutti gli archi cappio, dunque questi sono gli archi che dividono i grafo originale nelle due componenti trovate. 
    - le due componenti trovate sono connesse perchè ogni raggruppamento di nodi viene svolto sulla base di un arco esistente, dunque l'algoritmo non può unire due nodi non connessi.
    - l'insieme degli archi ha cardinalità 4.
    
3. _Utilizza ˆp per calcolare il numero di run R necessari per
ottenere il taglio minimo con una probabilità del 99.9%._

    - numero di volte in cui il taglio minimo è stato trovato: 32666
    - frequenza di successo: 32666/R = 3.27 * 10^-1
    - numero di run richiesti per P(successo)=99.9%
    Avere successo in r round con probabilità p significa che la probabilità che tutti e r round faliscano è 1 - p
    (1 - 0.327) ^ r = 10^-3
    r = 17
    P(successo) = 0.327 * (1 - 0.327) ^ 17 ~= 0.999

    Pertanto, sulla base della frequenza osservata, il numero di run necessari per trovare un taglio minimo con probabilità del 99.9% è 17

## Esempio di output

Di seguito riportato un output di esecuzione.

### Esecuzione esercizio
Iterazione n°0, trovato: true
Iterazione n°1, trovato: false
[...]
Iterazione n°99998, trovato: false
Iterazione n°99999, trovato: false
R: 100000, numero di successi: 32666

### Esecuzione MCMinCut con passaggi
```
--- Iterazione 0
- Arco scelto: B <-> E
- NODI:
nome: I
nome: H
nome: G
nome: F
nome: BE
nome: D
nome: C
nome: BE
nome: A
- SEMI-ARCHI: ( 20 ARCHI )
I ( I )  ->  H ( H )
I ( I )  ->  G ( G )
I ( I )  ->  F ( F )
I ( I )  ->  D ( D )
I ( I )  ->  A ( A )
H ( H )  ->  G ( G )
H ( H )  ->  BE ( E )
H ( H )  ->  BE ( B )
H ( H )  ->  A ( A )
H ( H )  ->  I ( I )
G ( G )  ->  F ( F )
G ( G )  ->  BE ( E )
G ( G )  ->  H ( H )
G ( G )  ->  I ( I )
F ( F )  ->  BE ( E )
F ( F )  ->  D ( D )
F ( F )  ->  C ( C )
F ( F )  ->  G ( G )
F ( F )  ->  I ( I )
BE ( E )  ->  C ( C )
BE ( E )  ->  H ( H )
BE ( E )  ->  G ( G )
BE ( E )  ->  F ( F )
D ( D )  ->  C ( C )
D ( D )  ->  A ( A )
D ( D )  ->  F ( F )
D ( D )  ->  I ( I )
C ( C )  ->  BE ( B )
C ( C )  ->  A ( A )
C ( C )  ->  BE ( E )
C ( C )  ->  F ( F )
C ( C )  ->  D ( D )
BE ( B )  ->  A ( A )
BE ( B )  ->  H ( H )
BE ( B )  ->  C ( C )
A ( A )  ->  H ( H )
A ( A )  ->  BE ( B )
A ( A )  ->  C ( C )
A ( A )  ->  D ( D )
A ( A )  ->  I ( I )

--- Iterazione 1
- Arco scelto: H <-> BE
- NODI:
nome: I
nome: BEH
nome: G
nome: F
nome: BEH
nome: D
nome: C
nome: BEH
nome: A
- SEMI-ARCHI: ( 18 ARCHI )
I ( I )  ->  BEH ( H )
I ( I )  ->  G ( G )
I ( I )  ->  F ( F )
I ( I )  ->  D ( D )
I ( I )  ->  A ( A )
BEH ( H )  ->  G ( G )
BEH ( H )  ->  A ( A )
BEH ( H )  ->  I ( I )
G ( G )  ->  F ( F )
G ( G )  ->  BEH ( E )
G ( G )  ->  BEH ( H )
G ( G )  ->  I ( I )
F ( F )  ->  BEH ( E )
F ( F )  ->  D ( D )
F ( F )  ->  C ( C )
F ( F )  ->  G ( G )
F ( F )  ->  I ( I )
BEH ( E )  ->  C ( C )
BEH ( E )  ->  G ( G )
BEH ( E )  ->  F ( F )
D ( D )  ->  C ( C )
D ( D )  ->  A ( A )
D ( D )  ->  F ( F )
D ( D )  ->  I ( I )
C ( C )  ->  BEH ( B )
C ( C )  ->  A ( A )
C ( C )  ->  BEH ( E )
C ( C )  ->  F ( F )
C ( C )  ->  D ( D )
BEH ( B )  ->  A ( A )
BEH ( B )  ->  C ( C )
A ( A )  ->  BEH ( H )
A ( A )  ->  BEH ( B )
A ( A )  ->  C ( C )
A ( A )  ->  D ( D )
A ( A )  ->  I ( I )

--- Iterazione 2
- Arco scelto: G <-> BEH
- NODI:
nome: I
nome: BEGH
nome: BEGH
nome: F
nome: BEGH
nome: D
nome: C
nome: BEGH
nome: A
- SEMI-ARCHI: ( 16 ARCHI )
I ( I )  ->  BEGH ( H )
I ( I )  ->  BEGH ( G )
I ( I )  ->  F ( F )
I ( I )  ->  D ( D )
I ( I )  ->  A ( A )
BEGH ( H )  ->  A ( A )
BEGH ( H )  ->  I ( I )
BEGH ( G )  ->  F ( F )
BEGH ( G )  ->  I ( I )
F ( F )  ->  BEGH ( E )
F ( F )  ->  D ( D )
F ( F )  ->  C ( C )
F ( F )  ->  BEGH ( G )
F ( F )  ->  I ( I )
BEGH ( E )  ->  C ( C )
BEGH ( E )  ->  F ( F )
D ( D )  ->  C ( C )
D ( D )  ->  A ( A )
D ( D )  ->  F ( F )
D ( D )  ->  I ( I )
C ( C )  ->  BEGH ( B )
C ( C )  ->  A ( A )
C ( C )  ->  BEGH ( E )
C ( C )  ->  F ( F )
C ( C )  ->  D ( D )
BEGH ( B )  ->  A ( A )
BEGH ( B )  ->  C ( C )
A ( A )  ->  BEGH ( H )
A ( A )  ->  BEGH ( B )
A ( A )  ->  C ( C )
A ( A )  ->  D ( D )
A ( A )  ->  I ( I )

--- Iterazione 3
- Arco scelto: I <-> BEGH
- NODI:
nome: BEGHI
nome: BEGHI
nome: BEGHI
nome: F
nome: BEGHI
nome: D
nome: C
nome: BEGHI
nome: A
- SEMI-ARCHI: ( 14 ARCHI )
BEGHI ( I )  ->  F ( F )
BEGHI ( I )  ->  D ( D )
BEGHI ( I )  ->  A ( A )
BEGHI ( H )  ->  A ( A )
BEGHI ( G )  ->  F ( F )
F ( F )  ->  BEGHI ( E )
F ( F )  ->  D ( D )
F ( F )  ->  C ( C )
F ( F )  ->  BEGHI ( G )
F ( F )  ->  BEGHI ( I )
BEGHI ( E )  ->  C ( C )
BEGHI ( E )  ->  F ( F )
D ( D )  ->  C ( C )
D ( D )  ->  A ( A )
D ( D )  ->  F ( F )
D ( D )  ->  BEGHI ( I )
C ( C )  ->  BEGHI ( B )
C ( C )  ->  A ( A )
C ( C )  ->  BEGHI ( E )
C ( C )  ->  F ( F )
C ( C )  ->  D ( D )
BEGHI ( B )  ->  A ( A )
BEGHI ( B )  ->  C ( C )
A ( A )  ->  BEGHI ( H )
A ( A )  ->  BEGHI ( B )
A ( A )  ->  C ( C )
A ( A )  ->  D ( D )
A ( A )  ->  BEGHI ( I )

--- Iterazione 4
- Arco scelto: C <-> A
- NODI:
nome: BEGHI
nome: BEGHI
nome: BEGHI
nome: F
nome: BEGHI
nome: D
nome: AC
nome: BEGHI
nome: AC
- SEMI-ARCHI: ( 13 ARCHI )
BEGHI ( I )  ->  F ( F )
BEGHI ( I )  ->  D ( D )
BEGHI ( I )  ->  AC ( A )
BEGHI ( H )  ->  AC ( A )
BEGHI ( G )  ->  F ( F )
F ( F )  ->  BEGHI ( E )
F ( F )  ->  D ( D )
F ( F )  ->  AC ( C )
F ( F )  ->  BEGHI ( G )
F ( F )  ->  BEGHI ( I )
BEGHI ( E )  ->  AC ( C )
BEGHI ( E )  ->  F ( F )
D ( D )  ->  AC ( C )
D ( D )  ->  AC ( A )
D ( D )  ->  F ( F )
D ( D )  ->  BEGHI ( I )
AC ( C )  ->  BEGHI ( B )
AC ( C )  ->  BEGHI ( E )
AC ( C )  ->  F ( F )
AC ( C )  ->  D ( D )
BEGHI ( B )  ->  AC ( A )
BEGHI ( B )  ->  AC ( C )
AC ( A )  ->  BEGHI ( H )
AC ( A )  ->  BEGHI ( B )
AC ( A )  ->  D ( D )
AC ( A )  ->  BEGHI ( I )

--- Iterazione 5
- Arco scelto: BEGHI <-> F
- NODI:
nome: BEFGHI
nome: BEFGHI
nome: BEFGHI
nome: BEFGHI
nome: BEFGHI
nome: D
nome: AC
nome: BEFGHI
nome: AC
- SEMI-ARCHI: ( 10 ARCHI )
BEFGHI ( I )  ->  D ( D )
BEFGHI ( I )  ->  AC ( A )
BEFGHI ( H )  ->  AC ( A )
BEFGHI ( F )  ->  D ( D )
BEFGHI ( F )  ->  AC ( C )
BEFGHI ( E )  ->  AC ( C )
D ( D )  ->  AC ( C )
D ( D )  ->  AC ( A )
D ( D )  ->  BEFGHI ( F )
D ( D )  ->  BEFGHI ( I )
AC ( C )  ->  BEFGHI ( B )
AC ( C )  ->  BEFGHI ( E )
AC ( C )  ->  BEFGHI ( F )
AC ( C )  ->  D ( D )
BEFGHI ( B )  ->  AC ( A )
BEFGHI ( B )  ->  AC ( C )
AC ( A )  ->  BEFGHI ( H )
AC ( A )  ->  BEFGHI ( B )
AC ( A )  ->  D ( D )
AC ( A )  ->  BEFGHI ( I )

--- Iterazione 6
- Arco scelto: BEFGHI <-> AC
- NODI:
nome: ABCEFGHI
nome: ABCEFGHI
nome: ABCEFGHI
nome: ABCEFGHI
nome: ABCEFGHI
nome: D
nome: ABCEFGHI
nome: ABCEFGHI
nome: ABCEFGHI
- SEMI-ARCHI: ( 4 ARCHI )
ABCEFGHI ( I )  ->  D ( D )
ABCEFGHI ( F )  ->  D ( D )
D ( D )  ->  ABCEFGHI ( C )
D ( D )  ->  ABCEFGHI ( A )
D ( D )  ->  ABCEFGHI ( F )
D ( D )  ->  ABCEFGHI ( I )
ABCEFGHI ( C )  ->  D ( D )
ABCEFGHI ( A )  ->  D ( D )

- TAGLIO MINIMO (presunto): 
- SEMI-ARCHI: ( 4 ARCHI )
ABCEFGHI ( I )  ->  D ( D )
ABCEFGHI ( F )  ->  D ( D )
D ( D )  ->  ABCEFGHI ( C )
D ( D )  ->  ABCEFGHI ( A )
D ( D )  ->  ABCEFGHI ( F )
D ( D )  ->  ABCEFGHI ( I )
ABCEFGHI ( C )  ->  D ( D )
ABCEFGHI ( A )  ->  D ( D )
```