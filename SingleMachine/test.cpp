#include <iostream>
#include <bitset>
#include <vector>
using namespace std;

typedef bitset<30> B;

int main()
{
    vector<int> s = {1, 5, 6, 7, 8};
    for(vector<int>::reverse_iterator it = s.rbegin(); it != s.rend(); ++it)
    {
        cout << *it << endl;
    }
    
}