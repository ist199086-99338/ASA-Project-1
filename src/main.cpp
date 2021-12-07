#include <iostream>
#include <sstream>
#include <vector>

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

void solve_problem_1() {
    vector<int> sequence = read_sequence();
    
    // TODO: problem 1 solution
}

void solve_problem_2() {
    vector<int> sequence_1 = read_sequence(),
                sequence_2 = read_sequence();
    
    // TODO: problem 2 solution
}
