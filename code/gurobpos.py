# -*- coding: utf-8 -*-
"""
Created on Thu Jan 20 17:05:17 2022

@author: mjl
"""

from gurobipy import *
import numpy as np
import random
# p_time_setup=[2,4,3,2]
# p_time_task=[5,3,6,2,7]
# pre=[[1,2],[0,1],[3],[0,2],[1,3]]
# suc=[[1,3],[0,1,4],[0,3],[2,4]]
# pre=[[2, 3, 6, 12, 14, 15, 17, 20, 21, 29], [2, 4, 6, 9, 20, 21], [1, 6, 9, 10, 17, 19, 24, 27], [10, 15, 20, 22, 29], [4, 7, 11, 15, 18, 20, 22, 28], [1, 3, 7, 23, 24, 25, 28], [3, 5, 11, 12, 14, 15, 20, 22, 24, 25, 27, 28], [5, 17, 20, 25], [20, 27], [6, 10, 13, 23, 28], [4, 11, 14, 15, 20, 27], [0, 1, 5, 12, 16, 27, 28], [3, 8, 13, 18, 19, 20, 27, 28], [4, 5, 10, 13, 17, 19, 29], [7, 11, 25, 26], [1, 3, 8, 16, 21, 29], [0, 2, 5, 11, 14, 24, 28], [8, 9, 10, 12, 16, 21], [0, 3, 5, 6, 7, 9, 10, 14, 18, 24, 28], [0, 2, 13, 16, 20, 23, 25, 27, 29], [8, 13, 14, 17, 21, 25, 26], [2, 4, 5, 8, 12, 23, 25, 29], [19, 26, 27], [1, 2, 20, 21, 22], [10, 11, 16, 20], [2, 14, 19, 20, 28], [14, 16, 22, 23, 26, 27, 28], [1, 4, 5, 11, 14, 17, 27], [5, 12, 15, 22, 26], [4, 16, 17, 20, 22, 23, 25, 26, 29]]
# suc=[[11, 16, 18, 19], [2, 5, 11, 15, 23, 27], [0, 1, 16, 19, 21, 23, 25], [0, 5, 6, 12, 15, 18], [1, 4, 10, 13, 21, 27, 29], [6, 7, 11, 13, 16, 18, 21, 27, 28], [0, 1, 2, 9, 18], [4, 5, 14, 18], [12, 15, 17, 20, 21], [1, 2, 17, 18], [2, 3, 9, 13, 17, 18, 24], [4, 6, 10, 14, 16, 24, 27], [0, 6, 11, 17, 21, 28], [9, 12, 13, 19, 20], [0, 6, 10, 16, 18, 20, 25, 26, 27], [0, 3, 4, 6, 10, 28], [11, 15, 17, 19, 24, 26, 29], [0, 2, 7, 13, 20, 27, 29], [4, 12, 18], [2, 12, 13, 22, 25], [0, 1, 3, 4, 6, 7, 8, 10, 12, 19, 23, 24, 25, 29], [0, 1, 15, 17, 20, 23], [3, 4, 6, 23, 26, 28, 29], [5, 9, 19, 21, 26, 29], [2, 5, 6, 16, 18], [5, 6, 7, 14, 19, 20, 21, 29], [14, 20, 22, 26, 28, 29], [2, 6, 8, 10, 11, 12, 19, 22, 26, 27], [4, 5, 6, 9, 11, 12, 16, 18, 25, 26], [0, 3, 13, 15, 19, 21, 29]]
# p_time_setup=[5, 3, 12, 18, 5, 28, 8, 1, 20, 27, 6, 18, 25, 24, 8, 1, 27, 20, 13, 4, 22, 27, 14, 17, 9, 5, 13, 6, 16, 18]
# p_time_task=[21, 22, 14, 5, 19, 24, 13, 10, 30, 9, 8, 18, 7, 9, 26, 7, 20, 25, 29, 13, 4, 4, 17, 20, 15, 14, 11, 18, 6, 9]
def generate_suc_by_pre(pre,s_num,t_num):
    suc=[[] for i in range(s_num)]
    for i in range(t_num):
        for s in pre[i]:
            suc[s].append(i)
    return suc
def generate_data(s_num,t_num,pt_lb,pt_ub,pre_lb,pre_ub):#processing time上下界，前置job上下界
    p_time_setup=[random.randrange(pt_lb,pt_ub) for i in range(s_num)]
    p_time_task=[random.randrange(pt_lb,pt_ub) for i in range(t_num)]
    pre=[random.sample(range(s_num), random.randrange(pre_lb,pre_ub)) for i in range(t_num)]
    suc=generate_suc_by_pre(pre,s_num,t_num)
    for s in range(s_num):
        if suc[s]==[]:
            t=random.randrange(t_num)
            suc[s].append(t)
            pre[t].append(s)
    return pre,suc,p_time_setup,p_time_task
def inp():
    s=input()
    l=[i for i in s.split("\n")]
    s_num,t_num=l[0].split(" ")
    s_num=int(s_num)
    t_num=int(t_num)
    p_time_setup=[i for i in l[1].split(" ")][:-1]
    p_time_task=[i for i in l[2].split(" ")][:-1]
    N=[[j for j in l[i].split(" ")]for i in range(4,4+s_num)]
    for i in range(s_num-1):
        N[i]=N[i][:-1]
    p_time_setup=[int(i) for i in p_time_setup]
    p_time_task=[int(i) for i in p_time_task]
    N=[[int(j) for j in N[i]]for i in range(s_num)]
    g=np.zeros((s_num,t_num))
    print(N)
    suc=[[] for i in range(s_num)]
    pre=[[] for i in range(t_num)]
    for i in range(s_num):
        for j in range(len(N[0])):
            if N[i][j]==1:
                suc[i].append(j)
    for j in range(t_num):
        for i in range(s_num):
            if N[i][j]==1:
                pre[j].append(i)
    return pre,suc,p_time_setup,p_time_task
pre,suc,p_time_setup,p_time_task=inp()
# j_n=10
# pre,suc,p_time_setup,p_time_task=generate_data(j_n,j_n,1,10,1,j_n)
s_num,t_num=len(p_time_setup),len(p_time_task)
p_num=s_num+t_num
time=p_time_setup
time.extend(p_time_task)

def sovle_by_gurobi_pos():
    m = Model("mip1")
    # Create variables
    x = m.addVars(s_num+t_num,p_num,vtype=GRB.BINARY, name="x")
    m.update()
    m.setObjective(quicksum(x[i,j]* (time[i]+ quicksum(x[i_p,j_p]*time[i_p] for i_p in range(s_num+t_num) for j_p in range(j) ) )  for i in range(s_num,s_num+t_num) for j in range(p_num)), GRB.MINIMIZE)
    # ==============================|完成時間=========|歷史時間和..............................................................|.|.......
    # Add constraint:每一個位置上都要正好run一個job 
    for j in range(p_num):
        m.addConstr(quicksum(x[i,j] for i in range(s_num+t_num))==1)
    # Add constraint:每一個job都要正好run一個job
    for i in range(s_num+t_num):
        m.addConstr(quicksum(x[i,j] for j in range(p_num))==1)
    # Add constraint: task job run之前,屬於他的setup都要跑完
    for i in range(s_num,s_num+t_num):
        for j in range(p_num):
            m.addConstr(quicksum(x[i_p,j_p] for i_p in pre[i-s_num] for j_p in range(j))>=x[i,j]*len(pre[i-s_num]))
    m.optimize()
    print('Obj:', m.objVal)
sovle_by_gurobi_pos()   
# sovle_by_gurobi_seq()  
    # for v in m.getVars():
    #     print(v.varName, v.x)
    
    # print('Obj:', m.objVal)
    