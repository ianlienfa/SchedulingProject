#include <iostream>
#include <bitset>
#include <vector>
#include <map>
#include <queue>
#include "Uheap.h"
#include "Q_ELEMENT.h"
#include "PriorityQueue.h"
using namespace std;

typedef struct Q_ELEMENT E;
typedef vector<int> Vi;
typedef vector<Vi> VVi;
typedef bitset<100> B;
typedef vector<B> Vb;
typedef vector<double> Vd;
typedef deque<Q_ELEMENT> Qe;
#define SWAP(i, j){int tmp = i; i = j; j = tmp;}

typedef struct BFSElement{
    Vi seq; bool visited;
    BFSElement(Vi seq, bool visited = false) {this->seq = seq; this->visited = visited;}
}Eb;

/* struct SetAndTestSchedule

/ Data structure
*   Basic structure for 1|bipartite|SigmaCj
*   <2d-Boolean vector> child, prec: information of the precendence dependecies 
*   <Double vector>     s, t: the processing time of set-up and test jobs

/ Usage
*   The constructor is not well-designed(I believe this has something to do with Bitset),
    so user should initiate all the attribute in their main function

*/

// p_si, p_ti should be 1-based
struct SetAndTestSchedule
{
private:
    int Sn, Tn, Jn;
    vector<B> child, prec;
    Vd s, t;
public:
    Vd j;
    bool debug = false;
    SetAndTestSchedule(int Sn, int Tn) {
        this->Sn = Sn; this->Tn = Tn;
        this->Jn = Sn+Tn;
        child.assign(Sn+1, B(0));
        prec.assign(Tn+1, B(0));
        s.resize(Sn+1);
        t.resize(Tn+1);
    }
    SetAndTestSchedule(){}
    void inputInit();
    void init(Vb prec, Vb child, Vd s, Vd t){this->prec = prec; this->child = child; this->s = s; this->t = t;}
    inline int stoParentidx(int i){return i;}
    inline int tTojobidx(int i){return i+Sn;}
    inline int originidx(int i) { return (i > Sn) ? i-(Sn) : i; }
    inline bool isT(int i){return i > Sn;}
    Uheap toUheap(const Vi &seq, const Vb &prec, const Vb &child, const Vd& s, const Vd &t);
    void precedenceClearUp(const Vi &seq, Vb prec, Vb child, Vi &parent);
    pair<list<int>, double> solve(Vb prec, Vb child, Vd s, Vd t, bool print = false);
    pair<list<int>, double> solve(){return solve(prec, child, s, t, true);};
    double computeSeq(list<int> v);
    pair<list<int>, double> DFSsolve(Vb prec, Vb child, Vd s, Vd t, bool print = false);
    void DFS(double &min, list<int> &min_seq, B visited, Vi seq, int lv);
    pair<list<int>, double> BFSsolve(Vb prec, Vb child, Vd s, Vd t, bool print);
    pair<list<int>, double> BFSBBsolve(Vb prec, Vb child, Vd s, Vd t, bool print);
    pair<list<int>, double> BFSBBsolve(){return BFSBBsolve(prec, child, s, t, true);};
    QQjr qqjrGen(E &e, bool debug);
    pair<list<int>, double> BFSCBBsolve(Vb prec, Vb child, Vd s, Vd t, bool print);
};

void SetAndTestSchedule::inputInit()
{
    // all 1-based, init and ref
    int tmp, Sn, Tn;;
    cin >> Sn >> Tn;
    Vd s ,t;
    Vb prec;
    Vb child;
    child.assign(Sn+1, B(0));
    prec.assign(Tn+1, B(0));
    s.resize(Sn+1);
    t.resize(Tn+1);
    j.resize(Sn+Tn+1);
    copy(s.begin()+1, s.end(), j.begin()+1);
    copy(t.begin()+1, t.end(), j.begin()+1+Sn);

    // construct
    for(int i = 1; i <= Sn; i++){cin >> s[i]; }
    for(int i = 1; i <= Tn; i++){cin >> t[i]; }
    cin >> tmp;
    if(tmp != -1) cout << "input error" << endl;

    // input precedencies
    // i means set up job i is test job j's parent
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
}

void SetAndTestSchedule::precedenceClearUp(const Vi &seq, Vb prec, Vb child, Vi &parent)
{
    // seq: 存有set up job idx, 0-based
    // prec: 大小為Tn+1, prec[test job idx]為存有map到 set up job的 bitset array，兩個都是1-based
    // parent: 大小為 Tn+Sn+1, idx 要經過轉換
    // parse seq and set up the precedencies of set up jobs
    parent.resize(Jn+1);
    for(int i = seq.size() - 1; i >= 0; i--) {
        if (i == 0)
            parent[seq[i]] = seq[i];
        else
            parent[seq[i]] = seq[i - 1];

        // for all test job of set job i clean precedence if test job can be process later
        for (int j = 1; j <= Tn; j++) {
            if (child[seq[i]].test(j)) {
                parent[tTojobidx(j)] = seq[i];
                for (int p = 1; p <= Sn; p++) {
                    if (p == seq[i])
                        continue;
                    if (prec[j].test(p)) {
                        child[p].reset(j);
                        prec[j].reset(p);
                    }
                }
            }
        }
    }
}

Uheap SetAndTestSchedule::toUheap(const Vi &seq, const Vb &prec, const Vb &child, const Vd& s, const Vd &t)
{
    // info init and some checking
    vector<NodeInfo> info;
    info.resize(Tn+Sn+1); // 0 is forbidden
    info[0] = NodeInfo();
    if(child.size() != Sn+1 || prec.size() != Tn+1 || seq.size() != Sn || s.size() != Sn+1 || t.size() != Tn+1)
        printf("child or prec size error! child.size: %d, prec: %d, seq: %d\n", child.size(), prec.size(), seq.size());

    // use seq & prec & child to construct new 1-1 parent dependencies
    vector<int> parent;

    // precedence clear up
    precedenceClearUp(seq, prec, child, parent);

    // import set up job first
    for(int i = 1; i <= Sn; i++)
    {
        if(seq[0] == i)
            info[i] = (NodeInfo(-1.0e+10, s[i], parent[i]));
        else
            info[i] = (NodeInfo(0, s[i], parent[i]));
    }
    for(int j = 1; j <= Tn; j++)
    {
        info[tTojobidx(j)] = (NodeInfo(1, t[j], parent[tTojobidx(j)]));
    }

    if(info.size() != Sn + Tn + 1)
        printf("toUheap: info size error!\n");

    return Uheap(info);
}

double SetAndTestSchedule::computeSeq(list<int> seq)
{
    if(seq.size() != Sn + Tn)
        printf("ComputeSeq: seq size error!\n");
    int cum = 0;
    int ans = 0;
    if(debug) printf("whole seq: ");
    for(auto i: seq)
    {
        // if(debug) printf("%d, ", i);
        // i is the number in seq, which are job indecies
        cum += (isT(i)) ? t[originidx(i)] : s[i];
        ans += (isT(i)) ? cum : 0;
        if(debug) printf("i: %d, cum: %d, ans: %d\n", i, cum, ans);
    }
    if(debug) printf("\n");
    return ans;
}


pair<list<int>, double> SetAndTestSchedule::BFSsolve(Vb prec, Vb child, Vd s, Vd t, bool print)
{
//init
    this->s = s;
    this->t = t;
    this->child = child;
    this->prec = prec;

    deque<BFSElement> q;
    Vi v;
    for(int i = 1; i <= Sn; i++)
        v.push_back(i);
    q.push_front(Eb(v));

    double min = 0x3FFFFFFF;
    list<int> min_seq;

    int sz = 1;
    int l = 0;
    while(q.size())
    {
        int next_sz = 0;
        while(sz--)
        {
            Eb &now = q.back();
            if(!now.visited)
            {
// run outtree
// for(auto it: now.seq) printf("%d, ", it); printf("\n");
                Uheap hp = toUheap(now.seq, prec, child, s, t);
//                hp.debug = true;
                list<int> v = hp.find_seq();
                double ans = computeSeq(v);
                if(ans < min)
                {
                    if(debug) printf("ans: %.2f, min: %.2f\n", ans, min);
                    min = ans;
                    min_seq = v;
                    for(auto it: min_seq) printf("%d, ", it); printf("\n");
                    printf("now min: %.1f\n", min);
                }
            }

            for(int i = l; i < now.seq.size(); i++)
            {
                Eb e(now);
                SWAP(now.seq[l], now.seq[i]);
                if(i == l)
                    e.visited = true;
                q.push_front(e);
                next_sz++;
            }

            q.pop_back();
        }
        sz = next_sz;
        l++;
    }
    return make_pair(min_seq, min);
}


void SetAndTestSchedule::DFS(double &min, list<int> &min_seq, B visited, Vi seq, int lv)
{
    if(lv == Sn)
    {
        Uheap hp = toUheap(seq, prec, child, s, t);
        list<int> v = hp.find_seq();
        double ans = computeSeq(v);
        if(ans < min)
        {
            if(debug) printf("ans: %.2f, min: %.2f\n", ans, min);
            min = ans;
            min_seq = v;
            printf("now min: %.1f\n", min);
            printf("seq: "); for(auto it: min_seq) printf("%d, ", it); printf("\n");
        }
        return;
    }

    // for(int i = 1; i <= Sn; i++)
    // {
    //     if(!visited.test(i))
    //     {
    //         Vi v(seq);
    //         B b(visited);
    //         b.set(i);
    //         v.push_back(i);
    //         DFS(min, min_seq, b, v, lv+1);
    //     }
    // }

    for(int i = Sn; i >= 1; i--)
    {
        if(!visited.test(i))
        {
            Vi v(seq);
            B b(visited);
            b.set(i);
            v.push_back(i);
            DFS(min, min_seq, b, v, lv+1);
        }
    }
}

pair<list<int>, double> SetAndTestSchedule::DFSsolve(Vb prec, Vb child, Vd s, Vd t, bool print)
{
//init
    this->s = s;
    this->t = t;
    this->child = child;
    this->prec = prec;

    double min = 0x3FFFFFFF;
    list<int> min_seq;
    DFS(min, min_seq, B(0), Vi(0), 0);
    return make_pair(min_seq, min);
}

// BST, not halting
pair<list<int>, double> SetAndTestSchedule::solve(Vb prec, Vb child, Vd s, Vd t, bool print)
{
//init
    this->s = s;
    this->t = t;
    this->prec = prec;
    this->child = child;

// BST generate permutations, here we don't need c
    Qe q;
    q.push_front(E(B(0), Vi(), 0));
    long long sz = 1, lv = 0;
    double min = 0x3FFFFFFF;
    list<int> min_seq;

    while(q.size())
    {
        long long next_sz = 0;
        while(sz--)
        {
            E &e = q.back();

// for each permutation, solve it by Uheap
            if(lv == Sn)
            {

                if(debug) {
                    printf("\n\nnew case starts.\n");
                    printf("set job seq: "); for(auto it: e.seq) printf("%d, ", it); printf("\n");
                }
                Uheap hp = toUheap(e.seq, prec, child, s, t);
//                hp.debug = true;
                list<int> v = hp.find_seq();
                double ans = computeSeq(v);
                if(ans < min)
                {
                    if(debug) printf("ans: %.2f, min: %.2f\n", ans, min);
                    min = ans;
                    min_seq = v;
                    printf("now min: %.1f\n", min);
                }
            }

// branch
            for(int i = 1; i <= Sn; i++)
            {
                if(!e.visited.test(i))
                {
                    Vi v_in(e.seq);
                    v_in.push_back(i);
                    q.push_front(E((B(e.visited).set(i)), v_in, 0));
                    next_sz++;
                }
            }
            q.pop_back();
        }
        sz = next_sz;
        lv++;
    }

    if(print)
    {
        printf("optimal seq:");
        for(auto it: min_seq) printf("%d, ", it); printf("\n");
        printf("min obj: %.1f\n", min);
    }

    return make_pair(min_seq, min);
}


// pair<list<int>, double> SetAndTestSchedule::BFSBBsolve(Vb prec, Vb child, Vd s, Vd t, bool print)
// {
//     //init
//     this->s = s;
//     this->t = t;
//     this->prec = prec;
//     this->child = child;

//     // BFS generate permutations, here we don't need c
//     PriorityQueue<E> q([](const E &e1, const E &e2){return e1.lb < e2.lb;});
//     q.push(E(B(0), Vi(), 0));
//     long long sz = 1, lv = 0;
//     double min = 0x3FFFFFFF;
//     list<int> min_seq;
//     int srptBest = 0x3FFFFFFF;

//     while(q.size())
//     {
// //        cout << "round: " << sz++ << endl;
//     //    q.bst_print();
// // long long next_sz = 0;
//         E e = q.top();
//         q.extract();
//     //    cout << endl << endl << endl;

//         // for each permutation, solve it by Uheap
    
//         if(e.seq.size() == Sn)
//         {
//             if(debug) {
//                 printf("\n\nnew case starts.\n");
//                 printf("set job seq: "); for(auto it: e.seq) printf("%d, ", it); printf("\n");
//             }
//             Uheap hp = toUheap(e.seq, prec, child, s, t);
// //                hp.debug = true;
//             list<int> v = hp.find_seq();
//             double ans = computeSeq(v);
//             if(ans < min)
//             {
//                 if(debug) printf("ans: %.2f, min: %.2f\n", ans, min);
//                 min = ans;
//                 min_seq = v;
//                 printf("now min: %.1f\n", min);
//             }
//             continue;
//         }

//         // branch
//         double fixed = 0;
//         double sigmaCj_fixed = 0;
//         for(int i = 0; i < e.seq.size(); i++)
//         {
//             fixed += s[e.seq[i]];
//             sigmaCj_fixed += fixed;
//         }
        
//         // compute out-tree generating left sequence 
//         Vi outTreeVec(e.seq);        
//         for(int i = 1; i <= Sn; i++)
//         {
//             if(!e.visited.test(i))
//             {
//                 outTreeVec.push_back(i);                
//             }
//         }
//         cout << "outtree seq: ";
//         for(auto it: outTreeVec)
//             cout << it << " "; cout << endl;
//         Uheap hp = toUheap(outTreeVec, prec, child, s, t);
// //                hp.debug = true;
//         list<int> v = hp.find_seq();
//         double ans = computeSeq(v);
//         // cout << "ans: " << ans << endl;
//         // cout << "min: " << min << endl;              
//         if(ans < min)
//         {
//             if(debug) printf("ans: %.2f, min: %.2f\n", ans, min);
//             min = ans;
//             min_seq = v;
//             for(auto it: min_seq)
//             cout << it << ", " ; cout << endl;   
//             printf("now min: %.1f\n", min);
//         }


//         for(int i = 1; i <= Sn; i++)
//         {
//             if(!e.visited.test(i))
//             {
//                 Vi v_in(e.seq);
//                 v_in.push_back(i);
//                 // 1. tidy up the seq till this time point
//                 // 2. compute lb using SRPT
//                 QQjr job_with_rj = qqjrGen(e, fixed);  
//                 // for(auto it: job_with_rj){
//                 //     cout << "(";
//                 //     for(auto itt: it) 
//                 //         cout << itt << ", ";
//                 //     cout << ")";
//                 //     }           
//                 // cout << endl;   
//                 int srpt = SRPT(job_with_rj);
//                 int lb = sigmaCj_fixed + SRPT(job_with_rj) + s[i];
//                 E topush = E((B(e.visited).set(i)), v_in, lb);
//                 // cout << topush << " SigmaCjFixed: " << sigmaCj_fixed << " SRPT: " << srpt << endl;
//                 q.push(E((B(e.visited).set(i)), v_in, lb));
//                 // if(srpt < srptBest)
//                 // {
//                 //     srptBest = srpt;

//                 //     // // add computation
//                 //     // for(int i = 1; i <= Sn; i++)
//                 //     // {
//                 //     //     if(!e.visited.test(i))
//                 // }
//                 // cout << " best srpt: " << srptBest << endl;
// // next_sz++;   
//             }
//         }
// //        q.bst_print();
//     }

//     if(print)
//     {
//         printf("optimal seq:");
//         for(auto it: min_seq) printf("%d, ", it); printf("\n");
//         printf("min obj: %.1f\n", min);
//     }

//     return make_pair(min_seq, min);
// }


QQjr SetAndTestSchedule::qqjrGen(E &e, bool debug = false)
{
    QQjr qqjr;
    map<int, vector<int>> mp;   // this is for aggregation of jobs happening at the same time    
    if(debug) cout << e << endl;
    for(int t = 1; t <= Tn; t++)
    {
        // cout << prec[t] << endl;

        // extract the sequenced_setup_jobs from test job j's parents
        B sequenced_setup_jobs = (e.visited) & prec[t];
        // cout << "seq: " << sequenced_setup_jobs << endl;

        // extract the parents in non_sequenced_setup_jobs 
        B non_sequenced_setup_jobs = (~sequenced_setup_jobs) & prec[t];
        // cout << "non_seq: " << non_sequenced_setup_jobs << endl;

        // construct the accumulated value of sequenced jobs
        map<int, int> accu;     // <index, accumulated_process_time>
        for(int i = e.seq.size()-1; (i >= 0) && (e.seq.size()); i--)
        {
            for(map<int,int>::iterator it=accu.begin(); it!=accu.end(); ++it)
            {
                it->second += s[e.seq[i]];
            }
            accu[e.seq[i]] = s[e.seq[i]];   // accu is given the set up job processing time            
        }

        // init release time component value
        int fix = 0, non_seq_sum = 0;
        
        // two cases: 1. there exists non_seq_setup_jobs 2. there doesn't
        if(non_sequenced_setup_jobs.any())
        {
            // the sum of sequenced_setup_jobs will be the last one
            fix = accu[e.seq.back()];  

            // accumulate the sum of non_sequenced_setup_jobs
            for(int i = 0; i <= Sn; i++)
            {
                if(non_sequenced_setup_jobs.test(i))
                    non_seq_sum += s[i];
            }
        }
        else
        {
            // find the last job of the seqenced_set_up_jobs
            for(vector<int>::reverse_iterator it = e.seq.rbegin(); it != e.seq.rend(); ++it)
            {
                // int idx = *it;
                // cout << *it << endl;
                if(sequenced_setup_jobs.test(*it))
                {
                    // cout << accu[*it] << endl; 
                    fix = accu[*it];
                    break;
                }
            }
        }

        int r = fix + non_seq_sum;     
        if(debug) printf("t[%d]: %d\n", t, r);
        map<int, vector<int>>::iterator it = mp.find(r);
        if(it == mp.end())
        {
            mp.insert(make_pair(r, vector<int>({tTojobidx(t)})));
        }
        else
        {
            it->second.push_back(tTojobidx(t));
        }
    }

    // turn back to QQjr    
    /* 
        from <r, index>
        to [idx_of_r][<index, p, r>]
    */
    for(auto it: mp)
    {
        deque<Jr> qjr;
        for(int i = 0; i < it.second.size(); i++)
        {
            // 用了新的j的pi值，可能會錯
            qjr.push_back(Jr(it.second[i], j[it.second[i]], it.first));
        }
        qqjr.push_back(qjr);
    }
    return qqjr;
}


/* SetAndTestSchedule::BFSCBBsolve

/ Data strucutre

*   Every level is a contour, their lower bound is being ordered using a priority queue
    The element of queue is in type Q_ELEMENT(alias as E), with attributes -- (B visited, Vi seq, double lb)

*   'min' and 'min_seq' is used as incumbent solution

*   levelvisited來記錄每個contour是否為空

*   'mask' is to get rid of inplausible levels
    ex: Sn + Tn = 5 -> level should be only 5 level
    levelvisited :              1111...1111111
    levelvisited after masking: 0000...0011111

*   if elements on one level are all being visited, contour[level].size() should == 0,
    and levelVisited.set(level, 0) should be implemented

/ Algorithm

1.  建立contour結構，依照job數搜尋樹有Sn+Tn層，每一層(每個contour)為一個以lower bound排序的priority queue
2.  建立levelvisited bitmap，每一個bit對應到contour的一層，若bit值為1表示尚未完全訪問
3.  while(整個contour還有node未訪問):
        for(所有level):
            if(該層contour還有node未訪問):
                *   取出lower bound最小者
                *   if(set-up job sequence被完整生成(也就是訪問到最深處)):
                    計算對應該set-up job sequence的 sigmaCj            
                *   做branching -- 將還未排入sequence的set-up job排入sequence(一個深度排一個)
            else:
                *   將該層對應levelvisited bit設為0
*/


// cyclic-BFS + Branch-and-Bound
pair<list<int>, double> SetAndTestSchedule::BFSCBBsolve(Vb prec, Vb child, Vd s, Vd t, bool print)
{
    //init
    this->s = s;
    this->t = t;
    this->prec = prec;
    this->child = child;

    // BST generate permutations, here we don't need c
    vector<PriorityQueue<E>> contour;
    
    // each level has one contour(priority queue)
    contour.assign(Tn+Sn+1, PriorityQueue<E>([](const E &e1, const E &e2){return e1.lb < e2.lb;}));
    
    // PriorityQueue<E> q([](const E &e1, const E &e2){return e1.lb < e2.lb;});
    contour[0].push(E(B(0), Vi(), 0));
    
    // incumbent solution init
    long long sz = 1, lv = 0;
    double min = 0x3FFFFFFF;
    list<int> min_seq;
    B levelVisited; levelVisited.set();     // levelvisited = 1111....1111, 用levelvisited來記錄每個contour是否為空
    B mask(0); mask.flip(); mask >>= (mask.size() - (Tn + Sn+ 1));    // mask用來去掉不合理的level

    while((levelVisited & mask).any())  // if there exists node unvisited...
    {
        for(int level = 0; level <= Tn+Sn; level++)
        {
            if(contour[level].size())
            {
                E e = contour[level].top();
                contour[level].extract();  

                if(debug)
                {                    
                    printf("\nset job seq: "); for(auto it: e.seq) printf("%d, ", it); printf("\n");
                    printf("E: "); cout << e << endl;
                }

                // for each permutation, solve it by Uheap
                if(e.seq.size() == Sn)
                {
                    if(debug) 
                    {
                        printf("\n\nnew complete seq starts.\n");
                        printf("set job seq: "); for(auto it: e.seq) printf("%d, ", it); printf("\n");
                    }
                    Uheap hp = toUheap(e.seq, prec, child, s, t);
                    // hp.debug = true;
                    list<int> v = hp.find_seq();
                    double ans = computeSeq(v);
                    if(ans < min)
                    {
                        if(debug) printf("ans: %.2f, min: %.2f\n", ans, min);
                        min = ans;
                        min_seq = v;
                        printf("now min: %.1f\n", min);
                        for(auto it: min_seq)
                        cout << it << ", " ; cout << endl << endl;
                    }
                    continue;
                }

        
                // branch
                for(int i = 1; i <= Sn; i++)
                {
                    // 現在node還沒去過的地方
                    // branching: move forward one more job
                    // compute the lower bound of the sequence and then push the node into the next level contour(priority queue)
                    if(!e.visited.test(i))  // if this set up job is not yet sequenced
                    {
                        Vi v_in(e.seq);
                        v_in.push_back(i);
                        E topush = E((B(e.visited).set(i)), v_in, 0);
                        QQjr job_with_rj = qqjrGen(topush);                    
                        int srpt = SRPT(job_with_rj);
                        topush.lb = srpt;
                        if(debug) cout << "topush: " << topush << endl;
                        contour[level+1].push(topush);                        
                    }
                }
            }
            else
            levelVisited.set(level, 0);
        }
    }

    if(print)
    {
        printf("optimal seq:");
        for(auto it: min_seq) printf("%d, ", it); printf("\n");
        printf("min obj: %.1f\n", min);
    }

    return make_pair(min_seq, min);
}


int main()
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


    //  for(auto it: st.j)
    //  {
    //      cout << it << ", ";
    //  }
    //  cout << endl;

     // input precedencies
     // i means set up job i is test job j's parent
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


    // st.debug = true;
    pair<list<int>, double> pp = st.BFSCBBsolve(prec, child, s, t, true);
    for(auto it : pp.first) printf("%d, ", it); printf("\n");

}
