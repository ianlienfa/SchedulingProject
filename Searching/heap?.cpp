#include <iostream>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

struct node
{
    string val;
    int score;
    node(string s)
    {
        val = s;
    }
};

template<class T>
class Heap
{
    class Cmp {
        bool operator() (const T& x, const T& y) const {return x<y;}
        typedef T first_argument_type;
        typedef T second_argument_type;
        typedef bool result_type;
    };
    vector<T> vec;
    Cmp cmp;
    Heap(Cmp cmp = less<T>()) {
        cout << "yes" << endl;
        this->cmp = cmp;
    }
};




int main()
{
    Heap<int> h;
}