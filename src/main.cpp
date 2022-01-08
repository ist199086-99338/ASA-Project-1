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
/*
void lcis(vector<int> s1, vector<int> s2) {
    // Guarda o valor da l.cis a cada index;
    
    vector<int> p = vector<int> (min(s1.size(), s2.size()), 1);
    int res = 0;

    for (size_t i = 0; i < s1.size(); i++) {
        int lis = 1;

        for (size_t j = 0; j < s2.size(); j++) {
            if (s1[i] == s2[j]) { // sao iguais, do something (incrementar a posicao de p maybe)
                p[i] = max(lis, p[j]);
                if (p[i] > res)
                    res = p[i];
            }

            if (s1[i] > s2[j]) { 
                // ???? update da lis ????
                lis = max(lis, p[j]);
            }
        }
    }

    cout << res << endl;
    
}
*/

void lcis2(vector<int> s1, vector<int> s2) {
    vector< vector<duplo> > table = vector< vector<duplo> > (s1.size() + 1, vector<duplo>(s2.size() + 1, {0, 0}));

    for(size_t i = 1; i <= s1.size(); i++) {
        for(size_t j = 1; j <= s2.size(); j++) {
            duplo left = table[i][j - 1];
            duplo top = table[i - 1][j];
            duplo *position = &table[i][j];

            // numbers at index i and j are different
            if(s1[i - 1] != s2[j - 1]) {
            
                // copy from left (j-1) if its last number (n) is lower than up's (i-1), copy from up otherwise
                if(top.v == left.v)
                    *position = top.n > left.n ? left : top;
                
                // copy from left (j-1) if its max sequence length (v) is higher than up's (i - 1), copy from up otherwise
                else
                    *position = top.v > left.v ? top : left;
            }

            // numbers at index i and j are equal
            else {
                if(left.v > top.v && (int) left.n < s1[i - 1])
                    *position = {left.v + 1, (size_t) s1[i - 1]};
                    
                else {
                    for(int k = i - 1; k >= 0; k--) {
                        if((int) table[k][j].n < s1[i - 1]) {
                            *position = {table[k][j].v + 1, (size_t) s1[i - 1]};
                            break;
                        }
                    }
                }
            }
        }
    }

    cout << table[s1.size()][s2.size()].v << endl;
}

void solve_problem_1() {
    vector<int> sequence = read_sequence();
    
    longest_possible_subsequence(sequence);
}

void solve_problem_2() {
    vector<int> sequence_1 = read_sequence(),
                sequence_2 = read_sequence();

    lcis2(sequence_1, sequence_2);
}
