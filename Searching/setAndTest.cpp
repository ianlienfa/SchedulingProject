#include <iostream>
#include <bitset>
#include <vector>
#include <queue>
#include "Uheap.h"
using namespace std;

typedef struct Q_ELEMENT E;
typedef vector<int> Vi;
typedef vector<Vi> VVi;
typedef bitset<100> B;
typedef vector<B> Vb;
typedef deque<Q_ELEMENT> Qe;

struct Q_ELEMENT
{
    B visited;
    Vi seq;
    int c;
    Q_ELEMENT(){}
    Q_ELEMENT(B visited, Vi seq, int c){this->visited = visited; this->seq = seq; this->c = c;}
};

struct SetAndTest
{
    // data members
    int Sn, Tn, Jn;
    vector<B> parent;
    Vi s, t, j;

    // inline functions
    inline int tTojobidx(int i){return i + Sn;}
    inline int originidx(int i) { return (i >= Sn) ? i - Sn : i; }
    inline bool isT(int i){return i >= Sn;}

    SetAndTest(int Sn, int Tn) {
        this->Sn = Sn; this->Tn = Tn; this->Jn = Sn + Tn;
        parent.assign(Sn+Tn, B(0));
        j.resize(Sn+Tn);
        s.resize(Sn);
        t.resize(Tn);
    }
    int calSigmaCj(const Vi &seq, const Vi &j);
    void BSTsolve(Vi &ans, const Vi &j, const Vb &parent);
    void printAns(const Vi &ans, const Vi &j);
    void solve(const Vi &j, const Vb &parent);
    bool isRunnable(const B &visited, const B &parent);
    B toUnvisited(const B &visited);
    B retrieveParentMask(const B visited, const Vb &parent);
};

int SetAndTest::calSigmaCj(const Vi &seq, const Vi &j)
{
    int cum = 0;
    int ans = 0;
    for(int i = 0; i < seq.size(); i++)
    {
        cum += j[i];
        if(isT(seq[i])) ans += cum;
    }
    return ans;
}

void SetAndTest::printAns(const Vi &ans, const Vi &j)
{
    // print ans seq
    for(int i = 0; i < ans.size(); i++)
    {
        (isT(i)) ? printf("t") : printf("s");
        printf("%d", originidx(ans[i]));
        if(i != ans.size()-1) printf(" ,");
    }
    printf("\n");

    // print ans
    printf("Sigma Cj: %d\n", calSigmaCj(ans, j));
}

void SetAndTest::solve(const Vi &j, const Vb &parent)
{
    // ans seq
    Vi ans;

    // BST solve ans
    BSTsolve(ans, j, parent);

    // printAns
    printAns(ans, j);
}

B SetAndTest::toUnvisited(const B &visited)
{
    B mask; mask.set();
    mask >>= (mask.size() - (Sn+Tn));
    B unvisited(visited);
    unvisited.flip();
    unvisited &= mask;
    return unvisited;
}

bool SetAndTest::isRunnable(const B &visited, const B &parent)
{
    B unvisited;
    unvisited = toUnvisited(visited);
    unvisited &= parent;
    return !unvisited.any();
}

void SetAndTest::BSTsolve(Vi &ans, const Vi &j, const Vb &parent)
{
    ans.resize(Jn);

    // init state and q
    Qe q;
    q.push_front(E(B(0), Vi(), 0));
    int sz = 1, lv = 0;
    while(q.size())
    {
        // traverse every node on one level
        int next_sz = 0;
        while(sz--)
        {
            // get the state
            E &e = q.back();

            // calculate at the last lv
            if(lv == Jn)
            {
                // 接上
            }

            // retrieve its unvisited state
            B unvisited;
            unvisited = toUnvisited(e.visited);

            // start branching
            for(int i = 0; i < Jn; i++)
            {
                // prune if its parent is not yet visited
                if(unvisited.test(i) && isRunnable(e.visited, parent[i]))
                {
                    Vi v_in(e.seq);
                    v_in.push_back(j[i]);
                    q.push_front(E((B(e.visited).set(i)), v_in, e.c + j[i]));
                    next_sz++;
                }
            }

            // pop from queue
            q.pop_back();
        }
        sz = next_sz;
        lv++;
    }
}



//
//int main()
//{
//    // all 0-based, init and ref
//    int tmp, Sn, Tn;;
//    cin >> Sn >> Tn;
//    SetAndTest st(Sn, Tn);
//    Vi &s = st.s, &t = st.t, &j = st.j;
//    Vb &parent = st.parent;
//
//    // construct
//    for(int i = 0; i < Sn; i++){cin >> s[i]; j[i] = s[i];}
//    for(int i = 0; i < Tn; i++){cin >> t[i]; j[i+Sn] = t[i];}
//    cin >> tmp;
//    if(tmp != -1) cout << "input error" << endl;
//
//    // input precedencies
//    // i means set up job i is test job j's parent
//    for(int i = 0; i < Sn; i++)
//    {
//        int b;
//        for(int j = 0; j < Tn; j++)
//        {
//            cin >> b;
//            if(b) {
//                parent[st.tTojobidx(j)].set(i);
//            }
//        }
//    }
//
//    // test job, set up job in j
//    // parent 0 ~ Sn+Tn-1 存每個工作的parent bitset
//    // job    0 ~ Sn+Tn-1 存每個工作的processing time
//    st.solve(j, parent);
//}



