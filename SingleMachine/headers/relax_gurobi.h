//
// Created by 林恩衍 on 2021/10/6.
//

#ifndef RELAX_GUROBI_H
#define RELAX_GUROBI_H

#include <iostream>
#include <queue>
#include <fstream>
#include <vector>
#include <bitset>
#include <unistd.h>
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


struct Relax_Gurobi
{
    const static int M = 1;

    // Big Constant
    const static int Mw = 20;
    const static int My = 100000;

    // hyper param
    // 解放的constraint不連續，難relax
    const static int lambda = 10;

    static int relax_lb(const Vb &_child, const Vd &_s, const Vd &_t, const Vi &setup_done);
};

#define relax_gurobi_DEBUG  0
#define relax_lb_SIMPLE_SEQ 0
#define relax_lb_RELAX_PREC 1

#if relax_lb_SIMPLE_SEQ == 1
int Relax_Gurobi::relax_lb(const Vb &_child, const Vd &_s, const Vd &_t, const Vi &setup_done)
{    
    /*  == Variables decalration == */
    Vb child(_child);
    Vd s(_s);
    Vd t(_t);    

    GRBVar **X;
    GRBVar *C;

    int J = t.size()-1;
    int R = s.size()-1;
    int N = J + R;

    Vd P(N+1);
    copy(s.begin()+1, s.end(), P.begin()+1);
    copy(t.begin()+1, t.end(), P.begin()+R+1);
    
    #if relax_gurobi_DEBUG== 1
        cout << "N = " << N << endl;
        cout << "J = " << J << endl;
        cout << "R = " << R << endl;        
        for(auto it = s.begin(); it != s.end(); it++)
        {
            cout << *it << " ";
        }
        cout << endl;
        for(auto it = t.begin(); it != t.end(); it++)
        {
            cout << *it << " ";
        }
        cout << endl;
        for(auto it = P.begin(); it != P.end(); it++)
        {
            cout << *it << " ";
        }
        cout << endl;
        for(auto it = child.begin(); it != child.end(); it++)
        {
            cout << *it << " " << endl;
        }
        cout << endl;
    #endif

    try {

    // Create an environment
    GRBEnv env = GRBEnv(true);
    env.set("LogFile", "gurobi/mip1.log");
    env.set(GRB_IntParam_OutputFlag, 1);
    env.start();
    
    // Create an empty model
    GRBModel model = GRBModel(env);
    // model.set("SolutionLimit", "1");
    

    /*  ================ Variable Population =============
        // C: completion time
        // X: if X[i][j] = 1, job i completes before j
        ==================================================    
    */

    C = new GRBVar[N+1];
    for(int i = 1; i <= N; i++)
    {
        string c_idx = "C" + to_string(i);
        C[i] = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_INTEGER, c_idx);
    }

    X = new GRBVar*[N+1];
    for(int i = 1; i <= N; i++)
    {
        X[i] = new GRBVar[N+1];
        for(int j = 1; j <= N; j++)
        {
            string x_constr = "X" + to_string(i) + "_" + to_string(j);
            X[i][j] = model.addVar(0.0, 1.0, 0.0, GRB_BINARY, x_constr);
        }
    }               

    /*  ================ Set objective =================
    ================================================  */    
    GRBLinExpr objExpr = 0;
    for(int j = R+1; j <= N; j++)
    {
        // Add up all the completion time of test-jobs
        objExpr += C[j];
    }
    
    model.setObjective(objExpr, GRB_MINIMIZE);


    /*  ================ Set Constraints =================
    ================================================  */ 
    // 必須要有先後次序
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= N; j++)
        {
            if(i == j) continue;
            string exclsvty_constr = "Exclusivity_" + to_string(i) + "_" + to_string(j);
            model.addConstr(X[i][j] + X[j][i] == 1, exclsvty_constr);
        }
    }    
    
    // 先後次序不可有迴圈
    for(int i = 1; i <= N; i++)
    {
        for(int j = i+1; j <= N; j++)
        {
            if(i == j) continue;
            for(int k = j+1; k <= N; k++)
            {
                if(i == k || j == k) continue;
                string loopfree = to_string(i) + "_" + to_string(j) + "_" + to_string(k) + "_loopfree";
                string loopfree2 = to_string(j) + "_" + to_string(i) + "_" + to_string(k) + "_loopfree";
                model.addConstr(X[i][j] + X[j][k] + X[k][i] <= 2, loopfree);
                model.addConstr(X[j][i] + X[i][k] + X[k][j] <= 2, loopfree2);
            }
        }
    }    
    
    // set-up -- test dependencies
    for(int i = 1; i <= R; i++)
    {
        for(int j = R+1; j <= N; j++)
        {
            int test_idx = j - R;            
            if(child[i].test(j-R))
            {
                string order_constr = "s"+ to_string(i) + "_t" + to_string(test_idx)+ "_s_than_j";
                #if relax_gurobi_DEBUG
                    cout << order_constr << endl;
                #endif
                model.addConstr(X[i][j] +  == 1, order_constr);
            }
        }
    }
    
    // set-up -- set-up dependencies
    for(int i = 0; i < setup_done.size(); i++)
    {
        for(int j = i+1; j < setup_done.size(); j++)
        {
            string order_constr = "s"+ to_string(setup_done[i]) + "_s" + to_string(setup_done[j])+ "_s_than_s";
            #if relax_gurobi_DEBUG
                cout << order_constr << endl;
            #endif
            model.addConstr(X[setup_done[i]][setup_done[j]] == 1, order_constr);            
        }
    }
    
    // Cj definitions
    for(int i = 1; i <= N; i++)
    {
        string C_constr = "C_" + to_string(i);
        GRBLinExpr CjExpr = 0;
        for(int j = 1; j <= N; j++)
        {            
            if(i == j) continue;
            CjExpr += P[j] * X[j][i];
        }
        CjExpr += P[i];
        model.addConstr(C[i] - CjExpr >= 0, C_constr);    
    }

    // Optimize model
    model.write("model.lp");
    model.optimize();    
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
#endif

#if relax_lb_RELAX_PREC == 1
int Relax_Gurobi::relax_lb(const Vb &_child, const Vd &_s, const Vd &_t, const Vi &setup_done)
{    
    /*  == Variables decalration == */
    Vb child(_child);
    Vd s(_s);
    Vd t(_t);    

    GRBVar **X;
    GRBVar **y_ij;
    GRBVar *C;

    int J = t.size()-1;
    int R = s.size()-1;
    int N = J + R;

    Vd P(N+1);
    copy(s.begin()+1, s.end(), P.begin()+1);
    copy(t.begin()+1, t.end(), P.begin()+R+1);
    
    #if relax_gurobi_DEBUG== 1
        cout << "N = " << N << endl;
        cout << "J = " << J << endl;
        cout << "R = " << R << endl;        
        for(auto it = s.begin(); it != s.end(); it++)
        {
            cout << *it << " ";
        }
        cout << endl;
        for(auto it = t.begin(); it != t.end(); it++)
        {
            cout << *it << " ";
        }
        cout << endl;
        for(auto it = P.begin(); it != P.end(); it++)
        {
            cout << *it << " ";
        }
        cout << endl;
        for(auto it = child.begin(); it != child.end(); it++)
        {
            cout << *it << " " << endl;
        }
        cout << endl;
    #endif

    try {

    // Create an environment
    GRBEnv env = GRBEnv(true);
    env.set("LogFile", "gurobi/mip1.log");
    env.set(GRB_IntParam_OutputFlag, 0);
    env.start();
    
    // Create an empty model
    GRBModel model = GRBModel(env);
    model.set("SolutionLimit", "1");
    

    /*  ================ Variable Population =============
        // C: completion time
        // X: if X[i][j] = 1, job i completes before j
        ==================================================    
    */

    C = new GRBVar[N+1];
    for(int i = 1; i <= N; i++)
    {
        string c_idx = "C" + to_string(i);
        C[i] = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_INTEGER, c_idx);
    }

    X = new GRBVar*[N+1];
    for(int i = 1; i <= N; i++)
    {
        X[i] = new GRBVar[N+1];
        for(int j = 1; j <= N; j++)
        {
            string x_constr = "X" + to_string(i) + "_" + to_string(j);
            X[i][j] = model.addVar(0.0, 1.0, 0.0, GRB_BINARY, x_constr);
        }
    }           

    y_ij = new GRBVar*[N+1];    
    // Kx = new GRBVar*[N+1];
    for(int i = 1; i <= N; i++)
    {            
        y_ij[i] = new GRBVar[N+1];      
        // Kx[i] = new GRBVar[N+1];     
    }
    for(int i = 1; i <= N; i++)
    {                       
        for(int j = i+1; j <= N; j++)
        {
            // add auxiliary bool variables
            string aux_ij = to_string(i) + "_" + to_string(j);
            string aux_ji = to_string(j) + "_" + to_string(i);
            y_ij[i][j] = model.addVar(0.0, 1.0, 0.0, GRB_BINARY, aux_ij+"y_ij");
            y_ij[j][i] = model.addVar(0.0, 1.0, 0.0, GRB_BINARY, aux_ji+"y_ij");
            // Kx[i][j] = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_INTEGER, aux_ij+"_Kx");
            // Kx[j][i] = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_INTEGER, aux_ij+"_Kx");
        }
    }    

    /*  ================ Set objective =================
    ================================================  */    
    GRBLinExpr objExpr = 0;
    for(int j = R+1; j <= N; j++)
    {
        // Add up all the completion time of test-jobs
        objExpr += C[j];
    }
    for(int i = 1; i <= N; i++)
    {
        // relaxation penalty
        for(int j = i+1; j <= N; j++)
        {
            objExpr += (1 - y_ij[i][j]) * lambda;
            objExpr += (1 - y_ij[j][i]) * lambda;
        }
    }
    model.setObjective(objExpr, GRB_MINIMIZE);


    /*  ================ Set Constraints =================
    ================================================  */ 
    // 必須要有先後次序
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= N; j++)
        {
            if(i == j) continue;
            string exclsvty_constr = "Exclusivity_" + to_string(i) + "_" + to_string(j);
            model.addConstr(X[i][j] + X[j][i] == 1, exclsvty_constr);
        }
    }    
    
    // 先後次序不可有迴圈
    for(int i = 1; i <= N; i++)
    {
        for(int j = i+1; j <= N; j++)
        {
            if(i == j) continue;
            for(int k = j+1; k <= N; k++)
            {
                if(i == k || j == k) continue;
                string loopfree = to_string(i) + "_" + to_string(j) + "_" + to_string(k) + "_loopfree";
                string loopfree2 = to_string(j) + "_" + to_string(i) + "_" + to_string(k) + "_loopfree";
                model.addConstr(X[i][j] + X[j][k] + X[k][i] <= 2, loopfree);
                model.addConstr(X[j][i] + X[i][k] + X[k][j] <= 2, loopfree2);
            }
        }
    }    
    
    // set-up -- test dependencies
    for(int i = 1; i <= R; i++)
    {
        for(int j = R+1; j <= N; j++)
        {
            int test_idx = j - R;            
            if(child[i].test(j-R))
            {
                string order_constr = "s"+ to_string(i) + "_t" + to_string(test_idx)+ "_s_than_j";
                #if relax_gurobi_DEBUG
                    cout << order_constr << endl;
                #endif
                model.addConstr(X[i][j] + (1 - y_ij[i][j]) == 1, order_constr);
            }
        }
    }
    
    // set-up -- set-up dependencies
    for(int i = 0; i < setup_done.size(); i++)
    {
        for(int j = i+1; j < setup_done.size(); j++)
        {
            string order_constr = "s"+ to_string(setup_done[i]) + "_s" + to_string(setup_done[j])+ "_s_than_s";
            #if relax_gurobi_DEBUG
                cout << order_constr << endl;
            #endif
            model.addConstr(X[setup_done[i]][setup_done[j]] == 1, order_constr);            
        }
    }
    
    // Cj definitions
    for(int i = 1; i <= N; i++)
    {
        string C_constr = "C_" + to_string(i);
        GRBLinExpr CjExpr = 0;
        for(int j = 1; j <= N; j++)
        {            
            if(i == j) continue;
            CjExpr += P[j] * X[j][i];
        }
        CjExpr += P[i];
        model.addConstr(C[i] - CjExpr >= 0, C_constr);    
    }

    // Optimize model
    model.write("model.lp");
    model.optimize();    
    // return model.get(GRB_DoubleAttr_ObjBound);
    return model.getObjective().getValue();

    } catch(GRBException e) {
        cout << "Error code = " << e.getErrorCode() << endl;
        cout << e.getMessage() << endl;
    } catch(...) {
        cout << "Exception during optimization" << endl;
    }

    // return lower bound
    return 0;
}
#endif


#endif