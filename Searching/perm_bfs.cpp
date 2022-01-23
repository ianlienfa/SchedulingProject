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
    friend bool operator<(const node& n1, const node &n2)
    {
        if(n1.val.size() < n2.val.size())
            return true;
        if(n1.val.size() == n2.val.size()) {
            int size = n1.val.size();
            for (int i = 0; i < size; i++) {
                if ((int) (n1.val[i]) < (int) (n2.val[i]))
                    return true;
                if ((int) (n1.val[i]) == (int) (n2.val[i]))
                    continue;
                else
                    return false;
            }
        }
        return false;
    }
    friend bool operator>(const node& n1, const node &n2)
    {
        if(n1.val.size() > n2.val.size())
            return true;
        if(n1.val.size() == n2.val.size()) {
            int size = n1.val.size();
            for (int i = 0; i < size; i++) {
                if ((int) (n1.val[i]) > (int) (n2.val[i]))
                    return true;
                if ((int) (n1.val[i]) == (int) (n2.val[i]))
                    continue;
                else
                    return false;
            }
        }
        return false;
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

void perm_bfs(int n)
{
    priority_queue<node, vector<node>, greater<node>> q;
    // initialize queue
    for(int i = 1; i <= n; i++)
    {
        string s;
        s += char(i+48);
        q.push(node(s));
    }

    while(q.top().val.size() != n)
    {
        // parse, get vec<bool>
        string s = q.top().val;
        q.pop();
        vector<bool> history = parse(s, n);

        // from this push the other
        for(int i = 1; i < history.size(); i++)
        {
            if(history[i] == false)
            {
                q.push(node(s + char(i+48)));
            }
        }
    }

    cout << "length: " << q.size() << endl;
    while(!q.empty())
    {
        // print all permutation
        cout << q.top().val << endl;
        q.pop();
    }
}



int main()
{
    perm_bfs(8);
}