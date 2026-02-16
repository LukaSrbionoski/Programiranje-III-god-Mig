#include <bits/stdc++.h>
using namespace std;

struct Point {
    float x, y, z;
};

bool comp(Point& a, Point& b) {
    return a.x < b.x;
}

bool comp2(const Point& a, const Point& b) {
    if (a.y != b.y) return a.y < b.y;
    return a.z < b.z;
}

float dist2(Point& a, Point& b) {
    return (a.x - b.x) * (a.x - b.x)
         + (a.y - b.y) * (a.y - b.y)
         + (a.z - b.z) * (a.z - b.z);
}

float solve(vector<Point>& v) {
    int n = v.size();

    if (n <= 3) {
        float d = 1e9;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                d = min(d, dist2(v[i], v[j]));
            }
        }
        return d;
    }

    vector<Point> v1, v2;
    float l = v[n / 2].x;   // safer split line

    for (int i = 0; i <= n / 2; i++)
        v1.push_back(v[i]);

    for (int i = n / 2 + 1; i < n; i++)
        v2.push_back(v[i]);

    float d = min(solve(v1), solve(v2));

    vector<Point> strip;
    for (auto& p : v) {
        if ((p.x - l) * (p.x - l) < d)
            strip.push_back(p);
    }

    sort(strip.begin(), strip.end(), comp2);

    for (int i = 0; i < strip.size(); i++) {
        for (int j = i + 1; j < strip.size(); j++) {
            if ((strip[j].y - strip[i].y) * (strip[j].y - strip[i].y) >= d)
                break;
            d = min(d, dist2(strip[i], strip[j]));
        }
    }

    return d;
}

int main() {
    int n;
    cout << "Enter number of points: ";
    cin >> n;

    vector<Point> v(n);

    cout << "Enter coordinates (x y z):\n";
    for (int i = 0; i < n; i++) {
        cin >> v[i].x >> v[i].y >> v[i].z;
    }

    // sort by x before solving
    sort(v.begin(), v.end(), comp);

    float result = sqrt(solve(v));

    cout << "\nMinimum distance between two points: " << result << endl;
}
