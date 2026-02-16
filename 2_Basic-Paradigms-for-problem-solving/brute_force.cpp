#include <iostream>
#include <vector>

using namespace std;

void inc_coin (int &coin, vector<pair<int, int>> &s) {
    for (auto &p : s) {
        if (p.first == coin) {
            p.second++;
        }
    }
}

bool isEqual(vector<int> &v1, vector<int> &v2) {
    if (v1.size() != v2.size()) return false;
    // Checking all elements of vector equal or not
    for (int i = 0; i < v1.size(); i++) {
        if (v1[i] != v2[i]) return false;
    }
    return true;
}

vector<vector<pair<int, int>>>
coins_change (int change, vector<int> &coins)
{
    vector<vector<pair<int, int>>> sol;
    vector<pair<int, int>> zero;
    for (int c : coins) {
        zero.push_back ({c, 0});
    }
    if (change == 0)
    {
        sol.push_back (zero);
    }
    else
    {
        for (int c : coins) {
            if ((change - c) >= 0) {
                auto s = coins_change (change - c, coins);
                for (auto ss : s) {
                    inc_coin (c, ss);
                    sol.push_back(ss);
                }
            }
        }
    }
    return sol;

}

bool same_solution(const vector<pair<int,int>>& a,const vector<pair<int,int>>& b){
    if (a.size() != b.size()) return false;

    for (int i = 0; i < a.size(); i++) {
        if (a[i].second != b[i].second)
            return false;
    }
    return true;
}

void filter_duplicates(vector<vector<pair<int, int>>>& solutions){
    vector<vector<pair<int,int>>> uniqe;

    for (auto &sol : solutions) {
        bool found= false;
        for (auto &u :uniqe) {
            if (same_solution(sol,u)) {
                found=true;
                break;
            }
        }
        if (!found) {
            uniqe.push_back(sol);
        }
    }
    solutions=uniqe;
}
void print_solutions(const vector<vector<pair<int,int>>>& solutions)
{
    int idx = 1;

    for (const auto& sol : solutions) {
        cout << idx++ << ". ";

        for (const auto& p : sol) {
            if (p.second > 0) {
                cout << "<" << p.first << "," << p.second << "> ";
            }
        }
        cout << '\n';
    }
}


// 1,2,5,10,50
// change = 455
// 1. <1,0>, <2,0>, <5,1>, <10, 0>, <50,9>

int main (){
    int n;
    abs (1);
    vector<int> coins;
    int change;
    cout << "Enter change sum: ";
    cin >> change;

    cout<<"\nEnter coins:\n";

    while(cin>>n){
        coins.push_back(n);
    }

    auto solutions = coins_change (change, coins);
    filter_duplicates(solutions);

    print_solutions(solutions);

}