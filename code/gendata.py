# -*- coding: utf-8 -*-
"""
Created on Thu Jan 20 11:50:41 2022

@author: mjl
"""
import numpy as np
import random
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
def tran_to_graph(suc):
    g=np.zeros((s_num,t_num))
    for i in range(s_num):
        for j in suc[i]:
            g[i][j]=1
    # print(g)
    for i in range(len(g)):
        for j in range(len(g[0])):
            print(int(g[i][j]),end=' ')
        print()
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
pre,suc,p_time_setup,p_time_task=generate_data(10,10,1,10,1,10)
s_num,t_num=len(p_time_setup),len(p_time_task)
# tran_to_graph(suc)
pre,suc,p_time_setup,p_time_task=inp()
print(pre)
print(suc)
print(p_time_setup)
print(p_time_task)