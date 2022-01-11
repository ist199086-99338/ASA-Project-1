#include <iostream>
#include <sstream>

#include <vector>
#include <unordered_set>

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
    size_t repeated = 0;
    duplo tuple_i, tuple_j;
    size_t size_x = x.size();

    for (size_t i = 0; i < size_x; i++) {
        // ler aqui
        tuple_i = p[i];
        int x_i = x[i];
        for (size_t j = 0; j < i; j++) {
            if (x_i > x[j]) { // then there's a new subvector with one more element
                tuple_j = p[j];
                if (tuple_j.v + 1 == tuple_i.v) // esta a repetir o valor
                    tuple_i.n += tuple_j.n;
                
                else if (tuple_j.v + 1 > tuple_i.v) { // esta a subir no size da sublista
                    tuple_i.v = tuple_j.v + 1; // nova lista tem tamanho +1
                    tuple_i.n = tuple_j.n;     // ha p[j].n listas de tamanho p[i].v
                }
            }
        }
        if (tuple_i.v > result) {
            result = tuple_i.v;
            repeated = tuple_i.n;
        } // result vai ser updated
        else if (tuple_i.v == result) {
            repeated += tuple_i.n;
        }
        p[i] = tuple_i;
    }

    cout << result << " " << repeated << endl;
}

void lcis(vector<int> s1, vector<int> s2) {
    int res, var;
    size_t size_i = s1.size();
    size_t size_j = s2.size();
    unordered_set <int> set_s2;
    for (size_t i = 0; i < s2.size(); i++) {
        set_s2.insert(s2[i]);
    }


    // Guarda o valor da l.cis a cada index;
    vector<int> p = vector<int> (size_j, 0);

    for (size_t i = 0; i < size_i; i++) {
        var = 0;
        if (set_s2.find(s1[i]) != set_s2.end()) {
            for (size_t j = 0; j < size_j; j++) {
                if (s1[i] == s2[j] && p[j] < var + 1) // found a common number, update the vector
                    p[j] = var + 1;
                else if (s1[i] > s2[j] && p[j] > var)
                    var = p[j];
            }
        }
    }

    res = 0;
    for (size_t j = 0; j < size_j; j++) {
        if (p[j] > res) 
            res = p[j];
    }

    cout << res << endl;
}

void solve_problem_1() {
    vector<int> sequence = read_sequence();
    
    longest_possible_subsequence(sequence);
}

void solve_problem_2() {
    vector<int> sequence_1 = read_sequence(),
                sequence_2 = read_sequence();

    lcis(sequence_1, sequence_2);
}
