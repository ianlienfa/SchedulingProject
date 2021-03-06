/*  ================== seq_relax_c++ =======================
   
    - This code relax on the precedence constraints
    - The order of set-up and testjob in general 
      when mixed is different with that of in permSet_outtree
    - the permSet_outtree it's (set_up, test_job)
    - while here it's (test_job, set_up)
    - so in this code, test_job has smaller index 
      when using the mixed version index
    - 這裡使用了兩種indexing方式
      跟permSet_outtree裡面的indexing剛好相反

    Indecies:
    There are two kinds of indexing in this code
    1. unmixed
        - In this version, set_up and test jobs has their 
        own indecies, starting from 1 respectively

    2. mixed
        - In this version, set_up and test jobs are being 
        seen as one kind and test jobs have smaller indecies 
        starting from 1
        - range: 
            - test job:     1 ~ J
            - set_up job: J+1 ~ N 

    ==================================================    */

#include <iostream>
#include <queue>
#include <fstream>
#include <vector>
#include <bitset>
#include <string>
#include <sstream>
#include "gurobi_c++.h"
#include "SetAndTestSchedule.h"
#include "Uheap.h"
#include "Q_ELEMENT.h"
#include "PriorityQueue.h"
#include "lb_compute_param.h"
using namespace std;

// type
typedef struct Q_ELEMENT E;
typedef deque<Q_ELEMENT> Qe;
typedef vector<int> Vi;
typedef vector<double> Vd;
typedef vector<Vi> VVi;
typedef bitset<100> B;
typedef vector<B> Vb;

const int M = 1;

// Big Constant
const int Mw = 10;
const int My = 100000;

// hyper param
// 解放的constraint不連續，難relax
const int lambda = 50;


// 用child在改的時候比較有效率，因為我們固定的是set-up jobs
int relax_lb(const Vb &_child, const Vd &_s, const Vd &_t, const Vi &setup_done)
{    
    /*  == Variables decalration == */
    Vb child(_child);
    Vd s(_s);
    Vd t(_t);    

    GRBVar **S;
    GRBVar **C;
    GRBVar **W;
    GRBVar **Y;    

    int N = s.size() + t.size();
    int J = t.size();
    int R = s.size();
    Vd P(N+1);
    copy(t.begin()+1, t.end(), P.begin()+1);
    copy(s.begin()+1, s.end(), P.begin()+J+1);


    try {

    // Create an environment
    GRBEnv env = GRBEnv(true);
    // env.set(GRB_IntParam_OutputFlag, 0);
    env.set("LogFile", "mip1.log");
    env.start();
    
    // Create an empty model
    GRBModel model = GRBModel(env);
    // model.set("SolutionLimit", "1");

    /*  ================ Variable Population =============
        // S: start time, C_p: completion time
        // W: work on machine(or not)
        // Y: if Y_p[i][j] = 1, job i completes before j
        ==================================================    
    */
    S = new GRBVar*[M+1];
    for(int i = 1; i <= M; i++)
    {
        S[i] = new GRBVar[N+1];
        for(int j = 1; j <= N; j++)
            S[i][j] = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_INTEGER, "S");
    }

    C = new GRBVar*[M+1];
    for(int i = 1; i <= M; i++)
    {
        C[i] = new GRBVar[N+1];
        for(int j = 1; j <= N; j++)
            C[i][j] = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_INTEGER, "C");

    }

    W = new GRBVar*[M+1];
    for(int i = 1; i <= M; i++)
    {
        W[i] = new GRBVar[N+1];
        for(int j = 1; j <= N; j++)
            W[i][j] = model.addVar(0.0, 1.0, 0.0, GRB_BINARY, "W");
    }

    Y = new GRBVar*[N+1];
    for(int i = 1; i <= N; i++)
    {
        Y[i] = new GRBVar[N+1];
        for(int j = 1; j <= N; j++)
            Y[i][j] = model.addVar(0.0, 1.0, 0.0, GRB_BINARY, "Y");
    }
       

    /*  ================ Set objective =================
    ================================================  */    
    GRBLinExpr objExpr = 0;
    for(int m = 1; m <= M; m++)
    {
        for(int j = 1; j <= J; j++)
        {
            // Add up all the completion time of test-jobs
            objExpr += C[m][j];
        }
    }
    // 用先後順序來列relaxation，不用一定照先後順序 -> 淘汰 -> 太離散
    for(int m = 1; m <= M; m++)
    {
        for(int j = 1; j <= J; j++)
        {
            for(int r = J+1; r <= N; r++)
            {
                if(child[r-J].test(j))
                {                                                         
                    objExpr += (1 - Y[r][j]) * lambda;                    
                }
            }
        }
    }


    model.setObjective(objExpr, GRB_MINIMIZE);


    /*  ================ Set Constraints =================
    ================================================  */ 

    // j 個 test job 由 m 個 machine 共同分工完成 -- 完整性, (cmpltExpr = completion expression)

    GRBLinExpr cmpltExpr = 0;
    for(int j = 1; j <= J; j++)
    {
        for(int m = 1; m <= M; m++)
        {
            cmpltExpr += W[m][j];
        }
    }
    model.addConstr(cmpltExpr == J, "c1a");


    // 同一個 test job j 在整次工作中只能在一個machine上執行，且僅執行一次 -- 一次性
    for(int j = 1; j <= J; j++)
    {
        GRBLinExpr onceExpr = 0;
        for(int m = 1; m <= M; m++)
        {
            onceExpr += W[m][j];
        }
        string name = "onceExpr";
        name += to_string(j);
        model.addConstr(onceExpr == 1, name);
    }
    
    // 相依性
    for(int m = 1; m <= M; m++)
    {
        for(int j = 1; j <= J; j++)
        {
            for(int r = J+1; r <= N; r++)
            {
                if(child[r-J].test(j))
                {
                    string rt_constr = "t"+ to_string(j) + "_r" + to_string(r-J)+ "_dep";
                    string order_constr = "t"+ to_string(j) + "_r" + to_string(r-J)+ "_r_than_j";
                    model.addConstr(( 1 - W[m][j] ) * Mw + ( W[m][r] - 1 ) >= 0, rt_constr);

                    // If Relax
                    // model.addConstr(Y[r][j] == 1, order_constr);
                }
            }
        }
    }

    // set-up job間 相依性    
    if(setup_done.size())
    {

        cout << "here!" << endl << endl;
        // last set up job 比餘下任一set up job早做
        vector<bool> not_done_setup(R+1, true);
        for(int i = 0; i < setup_done.size(); i++)  // 這裡0是對的
        {
            not_done_setup[setup_done[i]] = false;
        }
        for(int i = 1; i <= R; i++) // 這裡要1
        {
            if(not_done_setup[i])
            {
                string order_constr = "r"+ to_string(setup_done.back()) + "_r" + to_string(i)+ "_r_than_r";
                cout << order_constr << endl;
                model.addConstr(Y[setup_done.back() + J][i + J] == 1, order_constr);
            }
        }

        // set-up job間相依性，會連續影響
        if(setup_done.size() >= 2)
        {    for(int i = 0; i < setup_done.size()-1; i++)
            {
                // r_idx = setup_done[i] + J;
                string order_constr = "r"+ to_string(setup_done[i]) + "_r" + to_string(setup_done[i+1])+ "_r_than_r";
                // cout << order_constr << endl;
                model.addConstr(Y[setup_done[i] + J][setup_done[i+1] + J] == 1, order_constr);
            }
        }
    }

    // 一定要有先後, order_clarity
    for(int i = 1; i <= N; i++)
    {
        for(int j = i+1; j <= N; j++)
        {
            string order_clar_constr = "job" + to_string(i) + "_job" + to_string(j) + "_order_clarity";
            model.addConstr(Y[i][j] + Y[j][i] == 1, order_clar_constr);
        }
    }

    // start time >= 0
    // completion time definitions
    for(int m = 1; m <= M; m++)
    {
        for(int n = 1; n <= N; n++)
        {
            string start_constr = "job" + to_string(n) + "_on_m" + to_string(m) + "_startTime";
            string completion_constr = "job" + to_string(n) + "_on_m" + to_string(m) + "_CompletionTime";
            model.addConstr(S[m][n] >= 0, start_constr);
            model.addQConstr(C[m][n] - ( S[m][n] + P[n] ) * W[m][n] == 0, completion_constr);
        }
    }

    // 排他性, Exclusivity
    // 不是你先就是我先
    for(int m = 1; m <= M; m++)
    {
        for(int i = 1; i <= N; i++)
        {
            for(int j = i+1; j <= N; j++)
            {
                string ij_constr = "job" + to_string(i) + "_finishes_bf" + "_job" + to_string(j) + "_on_" + to_string(m);
                string ji_constr = "job" + to_string(j) + "_finishes_bf" + "_job" + to_string(i) + "_on_" + to_string(m);
                // cout << ji_constr << endl;
                model.addConstr(S[m][j] - C[m][i] + My * ( 1 - Y[i][j] ) + My * ( 1 - W[m][i] ) + My * ( 1 - W[m][j] ) >= 0, ij_constr);
                model.addConstr(S[m][i] - C[m][j] + My * Y[i][j] + My * ( 1 - W[m][i] ) + My * ( 1 - W[m][j] ) >= 0);
            }
        }
    } 

    // Optimize model
    model.optimize();    
    
    auto it = model.getVars();
    for(int i = 0; i < model.get(GRB_IntAttr_NumVars); i++)
    {
        cout << it[i].get(GRB_StringAttr_VarName) << ":" << it[i].get(GRB_DoubleAttr_X) << endl;
    }


    return model.get(GRB_DoubleAttr_ObjBound);

    } catch(GRBException e) {
        cout << "Error code = " << e.getErrorCode() << endl;
        cout << e.getMessage() << endl;
    } catch(...) {
        cout << "Exception during optimization" << endl;
    }

    // return lower bound
    return 0;
}

Lb_Compute_Param lbComputeParamSetUp(const Vb &_child, const Vd &_s, const Vd &_t, const Vi &setup_done)
{
    Vb child(_child);
    Vd s(_s);
    Vd t(_t);
    for(int i = 0; i < setup_done.size(); ++i)
    {        
        child[setup_done[i]].reset();
        s[setup_done[i]] = 0;
    }
    return Lb_Compute_Param(child, s, t);
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

    // done test
    // Vi setup_done = {12, 21, 15, 28, 5, 16, 27, 11, 20, 23, 30, 17, 29, 3, 24, 14, 7, 26, 1, 18, 6, 2, 13, 9, 22, 4, 19, 8, 25, 10};    
    Vi setup_done = {};

    cout << "optimal: " << relax_lb(child, s, t, setup_done) << endl;
}