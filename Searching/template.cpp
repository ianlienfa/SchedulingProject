#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

template<class T>
class pq
{
    vector<T> vt;
    bool (*cmpr)(const T& t1, const T &t2);
public:
    pq(vector<T> vt, bool (*cmpr)(const T& t1, const T &t2))
    {
        this->vt = vt;
        this->cmpr = cmpr;
    }
    void mysort()
    {
        sort(vt.begin(), vt.end(), cmpr);
        for(auto it: vt)
        {
            cout << it << endl;
        }
    }
};


int main() {
    vector<int> v = {2, 5, 3, 7};
    pq<int> q(v, [](const int &i1, const int &i2){return i1 < i2;});
    q.mysort();
}
