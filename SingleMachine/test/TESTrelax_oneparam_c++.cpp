#include <iostream>
#include <vector>
#include <map>
#include <climits>
#include <queue>
#include "Uheap.h"
#include "SetAndTestSchedule.h"
#include "Q_ELEMENT.h"
#include "relax_gurobi.h"
#include "PriorityQueue.h"
using namespace std;
typedef struct Q_ELEMENT E;
typedef deque<Q_ELEMENT> Qe;
typedef vector<int> Vi;
typedef vector<Vi> VVi;
typedef bitset<100> B;
typedef vector<B> Vb;
#define SWAP(i, j){int tmp = i; i = j; j = tmp;}

int main(int argc, char* argv[])
{
    // all 1-based, init and ref
    int tmp, Sn, Tn;;
    cin >> Sn >> Tn;
    Vd s ,t;
    Vb prec;
    Vb child;
    SetAndTestSchedule st(Sn, Tn);
    child.assign(Sn+1, B(0));
    prec.assign(Tn+1, B(0));
    s.resize(Sn+1);
    t.resize(Tn+1);
    st.j.resize(Sn+Tn+1);
    

    // construct
    for(int i = 1; i <= Sn; i++){cin >> s[i]; } 
    for(int i = 1; i <= Tn; i++){cin >> t[i]; } 
    cin >> tmp;
    if(tmp != -1) cout << "input error" << endl;
    copy(s.begin()+1, s.end(), st.j.begin()+1);
    copy(t.begin()+1, t.end(), st.j.begin()+1+Sn);     



    for(int i = 1; i <= Sn; i++)
    {
        int b;
        for(int j = 1; j <= Tn; j++)
        {
            cin >> b;
            if(b) {
                prec[j].set(i);
                child[i].set(j);
            }
        }
    }


    Vi setup_done = {};
    cout << Relax_Gurobi::relax_lb(child, s, t, setup_done) << endl;

}