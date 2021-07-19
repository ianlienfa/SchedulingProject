#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct node
{
    string val;
    node(string s)
    {
        val = s;
    }
};

vector<bool> parse(string s, int n)
{
    vector<bool> vec(n+1, false);
    for(int i = 0; i < s.size(); i++)
    {
        vec[((int)s[i])-48] = true;
    }
    return vec;
}


int main()
{
    deque<node> q;
    int n;
    cin >> n;

    // initialize queue
    for(int i = 1; i <= n; i++)
    {
        string s;
        s += char(i+48);
        q.push_back(node(s));
    }

    while(q.front().val.size() != n)
    {
        // parse, get vec<bool>
        string s = q.front().val;
        q.pop_front();
        vector<bool> history = parse(s, n);

        // from this push the other
        for(int i = 1; i < history.size(); i++)
        {
            if(history[i] == false)
            {
                q.push_back(node(s + char(i+48)));
            }
        }
    }

    cout << "length: " << q.size() << endl;
    for(auto it: q)
    {
        // print all permutation
        cout << it.val << endl;
    }
}