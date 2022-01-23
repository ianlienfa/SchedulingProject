#include <iostream>
#include <vector>
using namespace std;
#define SWAP(a, b){int tmp = a; a = b; b = tmp;}

void arr_print(vector<int> &arr)
{
    for(auto it:arr)
        cout << it << " ";
    cout << endl;
}

void perm_print(int k, vector<int> arr)
{
    if(k == 1)
        arr_print(arr);
    else
    {
        vector<vector<int>> child;
        child.assign(k, vector<int>(arr));
        for(int i = 0; i < k-1; i++)
        {
            // beside the first vector, swap done on all vector
            SWAP(child[i+1][i], child[i+1][k-1]);
        }
        for(int i = 0; i < child.size(); i++)
        {
            perm_print(k-1, child[i]);
        }
    }
}



void perm_print(vector<int> arr)
{
    perm_print(arr.size(), arr);
}


int main()
{
    vector<int> arr = {1, 2, 3};
    perm_print(arr);
}