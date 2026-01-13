#include <iostream>
#include <random>
#include <time.h>
#include <queue>
#include <math.h>

const int n_pr_faulty = 1;
const int n_pr_fedeli = 3;
const int n_pr_tot = n_pr_fedeli + n_pr_faulty;
const int T = n_pr_faulty * 2 + 1;

std::queue<int> messaggi[n_pr_fedeli];
bool bits[n_pr_fedeli] = {true, true, false};
bool moneta;

// Ogni processo fedele trasmette agli altri processi fedeli il proprio bit
void trasmetti(){
	for(int t = 0; t < n_pr_fedeli; ++t){
		for(int r = 0; r < n_pr_fedeli; ++r){
			if(r != t) messaggi[r].push(bits[t]);
		}
	}
}

// Segue protocollo Monte Carlo
void fedele(int id){
	std::cout << "[FEDELE " << id << "] bit: " << bits[id] << "\t ricevuti: ";
	// Conta il numero totale dei bit e numero dei bit positivi
	int count_pos = int(bits[id]);
	int count_tot = 1;
	while(!messaggi[id].empty()){
		int bit_ricevuto = messaggi[id].front();
		messaggi[id].pop();
		std::cout << bit_ricevuto;
		if(bit_ricevuto) ++count_pos;
		++count_tot;
	}
	// Valuta tally e assegna il valore del bit
	bool max = (count_pos > count_tot / 2);
	int tally = (max ? count_pos : count_tot - count_pos);
	if (tally >= T) bits[id] = max;
	else bits[id] = moneta;
	std::cout << "\t max: " << max << "\t tally: " << tally << std::endl;
}

// Invia a ogni processo fedele il contrario del bit di quel processo
void faulty(int id){
	for(int i = 0; i < n_pr_fedeli; ++i){
		messaggi[i].push(!bits[i]);
	}
	std::cout << "[FAULTY] bit inviati" << std::endl;
}

// Imposta i bit al valore di partenza (split 2 1)
void resetBits(){
	bool random = rand() % 2;
	bits[0] = bits[1] = random;
	bits[2] = !random;
}

// Controlla se tutti i bit dei processi fedeli hanno lo stesso valore
bool ConsensoRaggiunto(){
	bool first = bits[0];
	for(int i = 1; i < n_pr_fedeli; ++i)
		if(bits[i] != first) return false;
	return true;
}

// Itera fino al raggiungimento del consenso i seguenti step:
// - sorteggio della moneta
// - scambio dei bit tra processi fedeli
// - invio dei bit da parte del processo malizioso
// - calcolo dei bit dei processi fedeli
int CercaConsenso(){
	int n_round = 0;
	while(true){
		moneta = rand() % 2;

		std::cout << "************ round n° " << n_round << " ************" << std::endl;
		std::cout << "moneta: " << moneta << "\t bits:";
		for(int i = 0; i < n_pr_fedeli; ++i)
			std::cout << '\t' << bits[i];
		std::cout << std::endl;

		trasmetti();
		for(int i = n_pr_fedeli; i < n_pr_tot; ++i) faulty(i);
		for(int i = 0; i < n_pr_fedeli; ++i) fedele(i);

		++n_round;
		
		if(ConsensoRaggiunto()){
			std::cout << "consenso raggiunto in " << n_round << " round" << std::endl;
			std::cout << "valore bit: " << bits[0] << std::endl << std::endl;
			break;
		}
	}
	return n_round;
}

int main(){
	srand(time(NULL));
	// Cerca il consenso R volte e salva ogni volta il numero del round in cui è stato trovato
	const int R = 1024;
	int results[R];
	for(int i = 0; i < R; ++i){
		std::cout << "******* ITERAZIONE N° " << i << " ********" << std::endl;
		results[i] = CercaConsenso();
		resetBits();
	}

	// Salva i risultati su un file di output
	FILE * fd = fopen("out_grafico.txt", "w");
	// Prima linea con [numero processi fedeli] [numero processi faulty] [numero di esecuzioni]
    fprintf(fd, "%d %d %d\n", n_pr_fedeli, n_pr_faulty, R);
    for(int n_round = 1; n_round <= 10; ++n_round){
		int count = 0;
		for(int ndx = 0; ndx < R; ++ndx)
			if(results[ndx] == n_round) ++count;
		std::cout << "Il consenso è stato trovato in " << n_round << " round " << count << " volte" << std::endl;
		// Per ogni numero da 1 a 10, la frequenza con cui il consenso è stato trovato in quel numero di round
        fprintf(fd, "%d %.4f\n", n_round, float(count)/R);
    }
    fclose(fd);
}

