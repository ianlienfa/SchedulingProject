#%%
import gurobipy as gp 
from gurobipy import GRB

try:
    m = gp.Model("2p")

    # constant variable (the given conditions)
    D = [[0 for i in range(0, 9+1)] for j in range(0, 9+1)]   # Dependency table
    D[1][6:] = [0, 1, 1, 0]
    D[2][6:] = [1, 1, 0, 0]
    D[3][6:] = [0, 0, 0, 1]
    D[4][6:] = [1, 0, 1, 0]
    D[5][6:] = [0, 1, 0, 1]
    
    P = [0, 5, 3, 6, 2, 7, 2, 4, 3, 2]    # working time of test jobs , requirement jobs
    R = 4       # number of requirement jobs
    J = 5       # number of test jobs
    N = R + J   # total number of jobs
    M = 2

    # variable preparations
    S_p = [(m, n) for m in range(1, M+1) for n in range(1, N+1)]     
    C_p = [(m, n) for m in range(1, M+1) for n in range(1, N+1)]     
    W_p = [(m, n) for m in range(1, M+1) for n in range(1, N+1)]     
    
    # variables
    S = m.addVars(S_p, vtype = GRB.INTEGER, name="S")
    C = m.addVars(C_p, vtype = GRB.INTEGER, name="C")
    W = m.addVars(W_p, vtype = GRB.BINARY, name="W")
    
    TotalCost = m.addVar(vtype = GRB.INTEGER, name="TotalCost")

    # set objective
    m.setObjective(TotalCost, GRB.MINIMIZE)

    # set constraints

    # every test job have to be finished
    m.addConstr(gp.quicksum(W[m,j] for j in range(1, J+1) for m in range(1, M+1)) == J, "c1a")
    
    # every test job should only be done at one machine
    for j in range(1, J+1):
        m.addConstr(gp.quicksum(W[m,j] for m in range(1, M+1)) == 1)                     
    
    # r with dependency should be done before j & ordering
    for m in range(1, M+1):
        for j in range(1, J+1):
            for r in range(J+1, N+1):                
                # if(D[j][r] == 1):
                #     m.addConstr(W[m, r] == 1 if W[m, j] == 1)                     
                # if(D[j][r] == 1):
                #     m.addConstr(C[m, r] - S[m, j] <= 0)                     

    # # avoid collision
    # for ni in (1, N+1):
    #     for nj in (1, N+1):
    #         if(W[ni, nj] == 1):
    #             m.addConstr(S[ni, nj] >= 0)

    # # define completion time
    # for m in range(1, M+1):
    #     for n in range(1, N+1):
    #         m.addConstr(C[m, n] == S[m, n] + P[n])

    # 排他
    for m in range(1, M+1):
        for i in range(1, N+1):
            for j in range(1, N+1):
                if(S[m, i] < S[m, j]):
                    m.addConstr(C[m, i] <= S[m, j])

    # Total cost
    m.addConstr(TotalCost == gp.quicksum(C[m, n] for m in range(1, M+1) for n in range(1, N+1) if W[m, n] == 1))

    

    # # optimize
    # m.optimize()

    # for v in m.getVars():
    #     print('%s %g' % (v.varName, v.x))

    #     print('Obj: %g' % m.objVal)


except gp.GurobiError as e:
    print('Error code ' + str(e.errno) + ': ' + str(e))

except AttributeError:
    print('Encountered an attribute error')


# %%
