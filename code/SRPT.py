# -*- coding: utf-8 -*-
"""
Created on Tue Jan 18 12:52:06 2022

@author: mjl
"""

import numpy as np
import heapq as hq
p_time_setup=[2,4,3,2]
p_time_task=[5,3,6,2,7]
pre=[[1,2],[0,1],[3],[0,2],[1,3]]
suc=[[1,3],[0,1,4],[0,3],[2,4]]
s_num,t_num=len(p_time_setup),len(p_time_task)
s_seq_set=[]#s_seq是node list，每个node有该setup的time以及后继task的index
t_seq_set=np.zeros(t_num)
class node:      
    def __init__(self, child_list, p_time):
        self.children=child_list
        self.p_time=p_time
    def add_time(self,t):
        for child in self.children:
            t_seq_set[child]+=t
class root_node:
    def __init__(self,s_num):
        self.children=np.arange(s_num).tolist()
    def add_time(self,t):
        for s in self.children:
            s_seq_set[s].add_time(t)
    def remove_child(self,index):
        self.children.remove(index)#要按值删除
    def add_child(self,index):
        self.children.append(index)
    
                
r=root_node(s_num)    
class R_P:#min heap by realeasetime release_time&pro_cesstime [[r1,p1],[r2,p2],....]
    def __init__(self, val):
        self.val = val
    def __lt__(self, other):
        # if self.val[0] == other.val[0]:#相同到达时间，选择更短处理时间的
        #     return self.val[1] < other.val[1]
        return self.val[0] < other.val[0]
    def get_val(self):
        return self.val       
        return self.val      
def SRPT(rp):
    min_r_time_heap=[]
    min_p_time_heap=[]
    for ele in rp:
        hq.heappush(min_r_time_heap,R_P(ele))
    sigma_C=0
    cur_time=min_r_time_heap[0].get_val()[0]
    while len(min_r_time_heap)!=0:
        while len(min_r_time_heap)!=0 and min_r_time_heap[0].get_val()[0]==cur_time:#当且时间点可释放的job全部加入p_t的minheap
            p_t=hq.heappop(min_r_time_heap).get_val()[1]
            hq.heappush(min_p_time_heap,p_t)
        if len(min_r_time_heap)!=0:#还有没释放的才有next_arr
            next_arr_time=min_r_time_heap[0].get_val()[0]
            # print('next arr:',min_r_time_heap[0].get_val()[0])
            # print(min_p_time_heap[0])
            while cur_time+min_p_time_heap[0]<=next_arr_time and len(min_p_time_heap)!=0:
                cur_time+=min_p_time_heap[0]
                sigma_C+=cur_time
                hq.heappop(min_p_time_heap)
            hq.heapreplace(min_p_time_heap,min_p_time_heap[0]-(next_arr_time-cur_time))
            cur_time=next_arr_time
        else:#都释放了的话就在p——timeheap里从小到大累加即可
            while len(min_p_time_heap)!=0:
                cur_time+=min_p_time_heap[0]
                sigma_C+=cur_time
                hq.heappop(min_p_time_heap)
    return sigma_C  
            
def merge_to_rp(t_seq_set):
    rp=[]
    for i in range(t_num):
        rp.append([])
        rp[i].append(t_seq_set[i])
        rp[i].append(p_time_task[i])
    print(rp)
    return rp
def ini_release_time():
    for i in range(s_num):
        n=node(suc[i],p_time_setup[i])
        s_seq_set.append(n)
        n.add_time(p_time_setup[i])
def get_rp_with_partial_fixed_s_seq(fixed_seq):
    cur_time=0
    for s in fixed_seq:
        s_seq_set[s].add_time(cur_time)
        cur_time+=p_time_setup[s]
def update_release_time(fixed_index,root):
    root.remove_child(fixed_index)
    root.add_time(p_time_setup[fixed_index])
ini_release_time()
print(t_seq_set)
update_release_time(2,r)
print(t_seq_set)
update_release_time(1,r)
print(t_seq_set)
update_release_time(3,r)
print(t_seq_set)