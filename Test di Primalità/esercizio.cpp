#include <time.h>
#include <math.h>
#include <iostream>
#include <set>

const int N = 1105;

int modexp(int base, int exp, int n) {
    int res = 1;
    base %= n;
    while (exp > 0) {
        if(exp & 1){
            res = res * base % n;
            --exp;
        } else {
            base = base * base % n;
            exp /= 2;
        }
    }
    return res;
}

bool Congruente(int a, int b, int n){
    return (a - b) % n == 0;
}

int mcd(int a, int b){
    // Il MCD e` calcolato usando l'algoritmo Euclideo
    while (b > 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

void IsCarmichael(){
    bool is_carmichael = true;
    for(int base = 1; base < N; ++base){
        if(mcd(base, N) == 1){
            int pow = modexp(base, N-1, N);
            if(!Congruente(pow, 1, N)) is_carmichael = false;
        }
    }
    std::cout << "E' un numero di Carmichael: " << std::boolalpha << is_carmichael << std::endl;
}

// input: n composto, output: lista di tutte le basi per cui MR restisce 'probabilmente primo'
std::set<int> FindMRLiers(int n){
    std::set<int> mr_bugiardi = {};
    for(int a = 2; a <= n-2; ++a){
        int s = 0;
        int q = n - 1;
        while (q % 2 == 0) {
            ++s;
            q /= 2;
        }
        int x = modexp(a, q, n);
        if (Congruente(x, 1, n) || Congruente(x, -1, n)) {
            mr_bugiardi.insert(a);
            continue;
        };
        while(s > 0){
            x = modexp(x, 2, n);
            if (Congruente(x, -1, n)) {
                mr_bugiardi.insert(a);
                continue;
            };
            --s;
        }
    }
    return mr_bugiardi;
}

void PrintList(std::set<int> l){
    for(int e : l) std::cout << e << ",\t";
    std::cout << std::endl;
}

std::set<int> FindSubgroup(std::set<int> b){
    int size = -1;
    while(b.size() != size){
        size = b.size();
        for(int x : b){
            for(int y : b){
                int tmp = (x * y) % N;
                b.insert(tmp);
            }
        }
    }
    return b;
}

int main() {
    srand(time(NULL));

    IsCarmichael(); // Riempie z con la lista dei coprimi

    std::set<int> mr_bugiardi = FindMRLiers(N);
    std::cout << "MR-Bugiardi (#=" << mr_bugiardi.size() << "):" << std::endl;
    PrintList(mr_bugiardi);

    std::set<int> B = FindSubgroup(mr_bugiardi);
    std::cout << "B (#=" << B.size() << "):" << std::endl;
    PrintList(B);

    return 0;
}