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

/*
    extracts longest possible subsequence of x in ascending order
*/
vector<int> mps(vector<int> x) {
    // recursion stop condition
    if(x.size() <= 1)
        return x;
    
    // exclude last element of x
    vector<int> clamped(x.begin(), x.end() - 1);

    // recursive step
    vector<int> recurs = mps(clamped);

    // last elements
    int x_last = x.back(),
        recurs_last = recurs.back();
    
    // checking last element should suffice
    if(x_last > recurs_last) {
        recurs.push_back(x_last);
        return recurs;
    }

    return recurs;
}

void print_solution(vector<int> solution) {
    cout << "Size: " << solution.size() << endl;
    for(size_t i = 0; i < solution.size(); i++)
        cout << "i=" << i << ": " << solution[i] << endl;
}

void solve_problem_1() {
    vector<int> sequence = read_sequence();

    vector<int> solution = mps(sequence);
    
    print_solution(solution);

    // TODO: problem 1 solution
}

void solve_problem_2() {
    vector<int> sequence_1 = read_sequence(),
                sequence_2 = read_sequence();
    
    // TODO: problem 2 solution
}
