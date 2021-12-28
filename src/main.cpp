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
vector<int> longest_possible_subsequence(vector<int> x) {
    vector< vector<int> > p = vector< vector<int> >(x.size(), vector<int>());

    p[0].push_back(x[0]);

    for(size_t i = 1; i < x.size(); i++) {
        
        // skip repeats
        if(x[i] == x[i - 1])
            continue;

        for(size_t j = 1; j < x.size(); j++) {
            if(p[j - 1].empty())
                break;

            if((p[j].empty() && p[j - 1].back() < x[i]) || (!p[j].empty() && p[j - 1].back() < p[j].front())) {
                p[j] = p[j - 1];
                p[j].push_back(x[i]);
                break;
            }

            if(p[j - 1].back() > x[i]) {
                if(j == 1 || p[j - 1][p[j - 1].size() - 2] < x[i]) {
                    p[j - 1].pop_back();
                    p[j - 1].push_back(x[i]);
                }
            }
        }
    }

    for(size_t i = 0; i < x.size(); i++)
        if(i + 1 == p.size() || p[i + 1].empty())
            return p[i];

    return vector<int> ();
}

void print_solution(vector<int> solution) {
    cout << "Size: " << solution.size() << endl;
    for(size_t i = 0; i < solution.size(); i++)
        cout << "i=" << i << ": " << solution[i] << endl;
}

void solve_problem_1() {
    vector<int> sequence = read_sequence();

    vector<int> solution = longest_possible_subsequence(sequence);
    
    print_solution(solution);
}

void solve_problem_2() {
    vector<int> sequence_1 = read_sequence(),
                sequence_2 = read_sequence();
    
    // TODO: problem 2 solution
}
