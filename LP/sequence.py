#%%
import gurobipy as gp 
from gurobipy import GRB

try:
    model = gp.Model("seq")

    # constant variable (the given conditions)
    D = [[0 for i in range(0, 60+1)] for j in range(0, 60+1)]   # Dependency table
    D[1][31:] = [0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1]
    D[2][31:] = [0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0]
    D[3][31:] = [0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0]
    D[4][31:] = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1]
    D[6][31:] = [0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0]
    D[7][31:] = [0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0]
    D[8][31:] = [0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0]
    D[9][31:] = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0]
    D[10][31:] = [0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0]
    D[11][31:] = [0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0]
    D[12][31:] = [1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0]
    D[13][31:] = [0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0]
    D[14][31:] = [0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1]
    D[15][31:] = [0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0]
    D[16][31:] = [0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1]
    D[17][31:] = [1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0]
    D[18][31:] = [0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0]
    D[19][31:] = [1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0]
    D[20][31:] = [1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1]
    D[21][31:] = [0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0]
    D[22][31:] = [0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1]
    D[23][31:] = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0]
    D[24][31:] = [0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0]
    D[25][31:] = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    D[26][31:] = [0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0]
    D[27][31:] = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0]
    D[28][31:] = [0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0]
    D[29][31:] = [0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0]
    D[30][31:] = [0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1]
    

    P = [0, 21, 22, 14, 5, 19, 24, 13, 10, 30, 9, 8, 18, 7, 9, 26, 7, 20, 25, 29, 13, 4, 4, 17, 20, 15, 14, 11, 18, 6, 9, 5, 3, 12, 18, 5, 28, 8, 1, 20, 27, 6, 18, 25, 24, 8, 1, 27, 20, 13, 4, 22, 27, 14, 17, 9, 5, 13, 6, 16, 18]    # working time of test jobs , requirement jobs
    R = 30       # number of requirement jobs
    J = 30       # number of test jobs
    N = R + J   # total number of jobs
    M = 1

    # Big Constant
    Mw = 100000
    My = 100000

    # variable preparations
    S_p = [(m, n) for m in range(1, M+1) for n in range(1, N+1)]     
    C_p = [(m, n) for m in range(1, M+1) for n in range(1, N+1)]     
    W_p = [(m, n) for m in range(1, M+1) for n in range(1, N+1)]     
    Y_p = [(i, j) for i in range (1, N+1) for j in range (1, N+1)]
    
    # variables
    S = model.addVars(S_p, vtype = GRB.INTEGER, name="S")
    C = model.addVars(C_p, vtype = GRB.INTEGER, name="C")
    W = model.addVars(W_p, vtype = GRB.BINARY, name="W")
    Y = model.addVars(Y_p, vtype = GRB.BINARY, name="Y")

    # set objective
    model.setObjective(gp.quicksum(C[m, i] for m in range(1, M+1) for i in range(1, J+1)), GRB.MINIMIZE)

    # ---------------- set constrains ---------------- #

    # j 個 test job 由 m 個 machine 共同分工完成 -- 完整性
    model.addConstr(gp.quicksum(W[m,j] for j in range(1, J+1) for m in range(1, M+1)) == J, "c1a")

    # 同一個 test job j 在整次工作中只能在一個machine上執行，且僅執行一次 -- 一次性
    for j in range(1, J+1):
        model.addConstr(gp.quicksum(W[m,j] for m in range(1, M+1)) == 1)

    # 相依性
    for m in range(1, M+1):
        for j in range(1, J+1):
            for r in range(J+1, N+1):
                if D[j][r] == 1:
                    model.addConstr((1 - W[m, j]) * Mw + (W[m, r] - 1) >= 0)
                    model.addConstr(Y[r, j] == 1)

    
    # 一定要有先後
    for m in range(1, N+1):
        for n in range(m+1, N+1):
            model.addConstr(Y[m, n] + Y[n, m] == 1)
    
    # job 兩兩之間次序不能對調
    # start time >= 0
    # Completion time 定義
    for m in range(1, M+1):
        for n in range(1, N+1):
            model.addConstr(S[m, n] >= 0)
            model.addConstr(C[m, n] - (S[m, n] + P[n]) * W[m, n] == 0)
    
    
    # # 排他性
    for m in range(1, M+1):
        for i in range(1, N+1):
            for j in range(i+1, N+1):
                model.addConstr(S[m, j] - C[m, i] + My * (1 - Y[i, j]) + Mw * (1 - W[m, i]) + Mw * (1 - W[m, j]) >= 0)
                model.addConstr(S[m, i] - C[m, j] + My * Y[i, j] + Mw * (1 - W[m, i]) + Mw * (1 - W[m, j]) >= 0)


    # optimize
    model.optimize()

except gp.GurobiError as e:
    print('Error code ' + str(e.errno) + ': ' + str(e))

# except AttributeError:
#     print('Encountered an attribute error')

%%

# %%
