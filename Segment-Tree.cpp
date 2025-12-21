#include <iostream>
#include <vector>
using namespace std;

void segment_tree(vector<int>& v, vector<int>& a, int pos, int L, int R) {
    if (L == R) {
        v[pos] = a[L];
        return;
    }
    int mid = (L + R) / 2;
    segment_tree(v, a, pos*2, L, mid);
    segment_tree(v, a, pos*2 + 1, mid + 1, R);
    v[pos] = v[pos*2] + v[pos*2 + 1];
}

int sum(const vector<int>& tree, int l, int r, int L, int R, int pos) {
    if (l<=L && R<=r){
        return tree[pos];
    }
    if (R<l || r<L){
        return 0;
    }
    int mid = (L + R) / 2;
    return sum(tree, l, r, L, mid, pos*2) + sum(tree, l, r, mid + 1, R, pos*2 + 1);
}
int main() {
    vector<int> a = {3, 2, 4, 1, 8, 16, 11};
    int n = a.size();
    vector<int> tree(4 * n, 0);
    segment_tree(tree, a, 1, 0, n - 1);
    cout << sum(tree, 2, 5, 0, n - 1, 1) << endl;
}
