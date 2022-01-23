#%%
from gurobipy import *
s_num=30
t_num=30
j_num=s_num+t_num
m_num=3
time_slot=500
time=[5,3,12,8,5,28,8,1,20,27,6,18,25,24,8,1,27,20,13,4,22,27,14,17,9,5,13,4,16,18,21,22,14,5,19,24,13,10,30,9,8,18,7,9,26,7,20,25,29,13,4,4,17,20,15,14,11,18,6,9]
ready_list=[[2,3,6,12,14,15,17,20,21,29],
            [2,4,6,9,20,21],
            [1,6,9,10,17,19,24,27],
            [10,15,20,22,29],
            [4,7,11,15,18,20,22,28],
            [1,3,7,23,24,25,28],
            [3,5,11,12,14,15,20,22,24,25,27,28],
            [5,17,20,25],
            [20,27],
            [6,10,13,23,28],
            [4,11,14,15,20,27],
            [0,1,5,12,16,27,28],
            [3,8,13,18,19,20,27,28],
            [4,5,10,13,17,19,29],
            [7,11,25,26],
            [1,3,8,16,21,29],
            [0,2,5,11,14,24,28],
            [8,9,10,12,16,21],
            [0,3,5,6,7,9,10,14,18,24,28],
            [0,2,13,16,20,23,25,27,29],
            [8,13,14,17,21,25,26],
            [2,4,5,8,12,23,25,29],
            [19,26,27],
            [1,2,20,21,22],
            [10,11,16,20],
            [2,14,19,20,28],
            [14,16,22,23,26,27,28],
            [1,4,5,11,14,17,27],
            [5,12,15,22,26],
            [4,16,17,20,22,23,25,26,29]]
ready_num=[10,6,8,5,8,7,12,4,2,5,6,7,8,7,4,6,7,6,11,9,7,8,3,5,4,5,7,7,5,9]

# optimal solution 101  0 2 7 1 5 4 3 6 8
try:
    m = Model("mip1")
    x = m.addVars(j_num, m_num, time_slot,vtype=GRB.BINARY, name="x")
    # Xijk, whether job i works on machine j start from time slot k

    # Integrate new variables
    m.update()

    # Set objective
    m.setObjective(quicksum(x[i,j,k]*k for i in range (s_num,j_num)  for j in range(m_num) for k in range (time_slot) ),GRB.MINIMIZE)
    
    #C1:某mac在某一個時間點，最多run 一個 job
    for j in range(m_num):
        for k in range(time_slot):
                m.addConstr(quicksum(x[i,j,k] for i in range(j_num))<=1)
                
    #C2:任意一個task job，都要run一次
    for i in range(s_num,j_num):
        m.addConstr(quicksum(x[i,j,k] for j in range(m_num) for k in range(time_slot))==1)#第二種
        #m.addConstr(quicksum(quicksum(quicksum(x[i,j,k,l] for l in range(k+1,time_slot)) for k in range(time_slot))  for j in range(m))==1)#第一種寫法
    #C3:sup job 在某mac最多run一次
    for j in range(m_num):
        for i in range(s_num):
            m.addConstr(quicksum(x[i,j,k] for k in range(time_slot))<=1)
    #C4:task job run 之前，sup要都run完
    for i in range(s_num,j_num):
        for j in range(m_num):
            for k in range(time_slot):
                m.addConstr(quicksum(x[i_p,j,k_p] for i_p in ready_list[i-s_num] for k_p in range(k))>=ready_num[i-s_num]*x[i,j,k])
    #C5:某mac在run某job時，time[i]後不可run其他的
    for j in range(m_num):
        for i in range(j_num):
            for k in range(time_slot):
                m.addConstr(quicksum(x[i_p,j,k_p] for i_p in range(j_num) for k_p in range(k+1,min(time_slot,k+time[i])))*x[i,j,k]<=0)
            
            
    m.optimize()
    m.write('mip1.lp')   

    for v in m.getVars():
        if v.x==1:
            print('%s %g' % (v.varName, v.x))


    print("min_time_sum is ",m.ObjVal)
except GurobiError:
    print('Encountered a Gurobi error')
# %%
