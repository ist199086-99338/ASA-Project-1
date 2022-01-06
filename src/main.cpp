#include <iostream>
#include <sstream>

#include <vector>
#include <algorithm>

using namespace std;

void solve_problem_1();
void solve_problem_2();

int main() {

    int problem;
    
    string line;
    getline(cin, line);

    problem = stoi(line);

    if (problem == 1) solve_problem_1();
    else if (problem == 2) solve_problem_2();

    return 0;
}

/*
    reads in a whitespace separated sequence of integers from cin
*/
vector<int> read_sequence() {
    vector<int> seq;
    string raw, n;
    
    getline(cin, raw);
    stringstream ss(raw);
    while(getline(ss, n, ' '))
        seq.push_back(stoi(n));
    
    return seq;
}

typedef struct {
    size_t v, n;
} duplo;

/*
    extracts longest possible subsequence of x in ascending order
*/
void longest_possible_subsequence(vector<int> x) {
    vector<duplo> p = vector<duplo> (x.size(), {1, 1});

    size_t result = 1;
    size_t repeated = x.size();

    for (size_t i = 0; i < x.size(); i++) {
        for (size_t j = 0; j < i; j++) {
            if (x[i] > x[j]) { // then there's a new subvector with one more element
                if (p[j].v + 1 == p[i].v) // esta a repetir o valor
                    p[i].n += p[j].n;
                
                else if (p[j].v + 1 > p[i].v) { // esta a subir no size da sublista
                    p[i].v = p[j].v + 1; // nova lista tem tamanho +1
                    p[i].n = p[j].n;     // ha p[j].n listas de tamanho p[i].v
                }

                if(p[i].v > result) // result vai ser updated
                    result = p[i].v;
            }
        }
    }

    repeated = 0;
    for (size_t i = 0; i < p.size(); i++) {
        if (p[i].v == result)
            repeated += p[i].n;
    }
    cout << result << " " << repeated << endl;
}

void solve_problem_1() {
    vector<int> sequence = read_sequence();
    
    longest_possible_subsequence(sequence);
}

void solve_problem_2() {
    vector<int> sequence_1 = read_sequence(),
                sequence_2 = read_sequence();
    
    // TODO: problem 2 solution
}
