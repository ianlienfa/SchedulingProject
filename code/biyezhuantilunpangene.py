import numpy as np
import random
p_time_setup=[2,4,3,2]
p_time_task=[5,3,6,2,7]
pre=[[1,2],[0,1],[3],[0,2],[1,3]]
suc=[[1,3],[0,1,4],[0,3],[2,4]]
# f = open("exp_res.txt","w") 
# pre=[[2, 3, 6, 12, 14, 15, 17, 20, 21, 29], [2, 4, 6, 9, 20, 21], [1, 6, 9, 10, 17, 19, 24, 27], [10, 15, 20, 22, 29], [4, 7, 11, 15, 18, 20, 22, 28], [1, 3, 7, 23, 24, 25, 28], [3, 5, 11, 12, 14, 15, 20, 22, 24, 25, 27, 28], [5, 17, 20, 25], [20, 27], [6, 10, 13, 23, 28], [4, 11, 14, 15, 20, 27], [0, 1, 5, 12, 16, 27, 28], [3, 8, 13, 18, 19, 20, 27, 28], [4, 5, 10, 13, 17, 19, 29], [7, 11, 25, 26], [1, 3, 8, 16, 21, 29], [0, 2, 5, 11, 14, 24, 28], [8, 9, 10, 12, 16, 21], [0, 3, 5, 6, 7, 9, 10, 14, 18, 24, 28], [0, 2, 13, 16, 20, 23, 25, 27, 29], [8, 13, 14, 17, 21, 25, 26], [2, 4, 5, 8, 12, 23, 25, 29], [19, 26, 27], [1, 2, 20, 21, 22], [10, 11, 16, 20], [2, 14, 19, 20, 28], [14, 16, 22, 23, 26, 27, 28], [1, 4, 5, 11, 14, 17, 27], [5, 12, 15, 22, 26], [4, 16, 17, 20, 22, 23, 25, 26, 29]]
# suc=[[11, 16, 18, 19], [2, 5, 11, 15, 23, 27], [0, 1, 16, 19, 21, 23, 25], [0, 5, 6, 12, 15, 18], [1, 4, 10, 13, 21, 27, 29], [6, 7, 11, 13, 16, 18, 21, 27, 28], [0, 1, 2, 9, 18], [4, 5, 14, 18], [12, 15, 17, 20, 21], [1, 2, 17, 18], [2, 3, 9, 13, 17, 18, 24], [4, 6, 10, 14, 16, 24, 27], [0, 6, 11, 17, 21, 28], [9, 12, 13, 19, 20], [0, 6, 10, 16, 18, 20, 25, 26, 27], [0, 3, 4, 6, 10, 28], [11, 15, 17, 19, 24, 26, 29], [0, 2, 7, 13, 20, 27, 29], [4, 12, 18], [2, 12, 13, 22, 25], [0, 1, 3, 4, 6, 7, 8, 10, 12, 19, 23, 24, 25, 29], [0, 1, 15, 17, 20, 23], [3, 4, 6, 23, 26, 28, 29], [5, 9, 19, 21, 26, 29], [2, 5, 6, 16, 18], [5, 6, 7, 14, 19, 20, 21, 29], [14, 20, 22, 26, 28, 29], [2, 6, 8, 10, 11, 12, 19, 22, 26, 27], [4, 5, 6, 9, 11, 12, 16, 18, 25, 26], [0, 3, 13, 15, 19, 21, 29]]
# p_time_setup=[5, 3, 12, 18, 5, 28, 8, 1, 20, 27, 6, 18, 25, 24, 8, 1, 27, 20, 13, 4, 22, 27, 14, 17, 9, 5, 13, 6, 16, 18]
# p_time_task=[21, 22, 14, 5, 19, 24, 13, 10, 30, 9, 8, 18, 7, 9, 26, 7, 20, 25, 29, 13, 4, 4, 17, 20, 15, 14, 11, 18, 6, 9]
s_num,t_num=len(p_time_setup),len(p_time_task)
INT_MAX=t_num+1
class node:      
    def __init__(self, weight, process_time,job_name):
        self.w=weight
        self.p=process_time
        self.q=weight/process_time
        self.children=[]
        self.seq=[]
        self.seq.append(job_name)
        self.father=None
    def add_child(self,child):
        child.father=self
        self.children.append(child)
    def add_children(self,new_children):
        n=len(new_children)
        for i in range(n):
            self.add_child(new_children[i])
class outtree_schedule:
    def __init__(self,setup_job_seq):
        self.node_num=s_num+t_num
        self.job_node=[]
        self.remain_prejobs=[len(pre[i]) for i in range(t_num)]
        last_node=node(0,1,1)
        for i in range(s_num):
            new_node=node(0,1,1)
            setup_job_name=setup_job_seq[i]
            if(i==0):
                new_node=node(-INT_MAX,p_time_setup[setup_job_name],setup_job_name)
            else:
                new_node=node(0,p_time_setup[setup_job_name],setup_job_name)
                last_node.add_child(new_node)
            last_node=new_node
            self.job_node.append(new_node)
            m=len(suc[setup_job_name])#儿子数量
            for i in range(m):#遍历每个儿
                self.remain_prejobs[suc[setup_job_name][i]]-=1
                if(self.remain_prejobs[suc[setup_job_name][i]]==0):
                    new_child_node=node(1,p_time_task[suc[setup_job_name][i]],suc[setup_job_name][i]+s_num)
                    new_node.add_child(new_child_node)
                    self.job_node.append(new_child_node)
        self.find_opt()
    def merge_node(self,n1,n2):
        n1.w+=n2.w
        n1.p+=n2.p
        n1.q=n1.w/n1.p
        n1.seq+=n2.seq
        n1.add_children(n2.children)
        self.node_num-=1
    def find_max_q(self):
        n=len(self.job_node)
        pos=0
        temp_max=0
        for i in range(n):
            if(self.job_node[i].q>temp_max):
                temp_max=self.job_node[i].q
                pos=i
        return pos
    def find_opt(self):
        while self.node_num>1:
            pos=self.find_max_q()
            # if self.job_node[pos].father!=None:
            self.merge_node(self.job_node[pos].father,self.job_node[pos])
            del self.job_node[pos]
    def cal_C(self):
        job_seq=self.job_node[0].seq
        n=len(job_seq)
        C,total_time=0,0
        for i in range(n):
            job_name=job_seq[i];
            if job_name<s_num:
                total_time+=p_time_setup[job_name]
            else:
                total_time+=p_time_task[job_name-s_num]
                C+=total_time  
        return C
    def opt_seq(self):
        return self.job_node[0].seq
def cal_weight(x):
    return x/sum(x)
def local_sereach(seq):
    temp_opt_val=outtree_schedule(seq).cal_C()
    temp_opt_seq=seq
    for i in range(len(seq)-1):
        seq[i],seq[i+1]=seq[i+1],seq[i]
        val=outtree_schedule(seq).cal_C()
        if val<temp_opt_val:
            temp_opt_val=val
            temp_opt_seq=seq
        seq[i],seq[i+1]=seq[i+1],seq[i]       
    return temp_opt_seq,temp_opt_val   
def gene_algorithm(G,P,S,M):#generation繁衍代數，population人數，suviverate存活率,mutation突變率
    seq=np.arange(s_num)
    population=np.array([np.random.permutation(seq) for i in range(P)])
    fit=np.zeros(P)  
    survive,mutation=round(P*S),round(P*M)
    weight=cal_weight(np.arange(P))[::-1]
    for g in range(G):
        fit=np.array([outtree_schedule(population[p]).cal_C() for p in range(P)])#每个人的sigC算出来，当成fitness
        sort_index=np.argsort(fit[:])#按sigC从小到大排
        population=population[sort_index,:]
        #=================local_sereach======================
        wait_to_local_sereach=random.choices(range(P), weights=weight, k=round(P/20))
        for index in wait_to_local_sereach:
            population[index],fit[index]=local_sereach(population[index])            
        sort_index=np.argsort(fit[:])#按sigC从小到大排
        population=population[sort_index,:]
        #=====================================================
        new_population=population#留原始母體
        
        #=================结果====================================
        if (g+1)%20==0:#每过几个可以输出一下看一下结果
            print(fit[sort_index[0]])
            print(population[0,:])
        #======================================================
        for i in range(survive,P):#交配，sigC大的的覆蓋掉
            fatherindex,motherindex=random.choices(range(P), weights=weight, k=2)
            father,mother=population[fatherindex,:],population[motherindex,:]
            mask=np.random.randint(0,2,s_num)#隨即一個mask
            can_use,son=[1]*s_num,[-1]*s_num#能用的话是1
            for j in range(s_num):
                if can_use[mother[j]]==0 and can_use[father[j]]==0:#妈爸的值前面都用了
                    continue;
                elif can_use[mother[j]]==1 and can_use[father[j]]==1:#妈爸都可以用
                    if mask[j]==0:
                        son[j]=father[j]
                        can_use[father[j]]=0
                    else:
                        son[j]=mother[j]
                        can_use[mother[j]]=0
                else:
                    son[j]=can_use[father[j]]*father[j]+can_use[mother[j]]*mother[j]
                    can_use[father[j]],can_use[mother[j]]=0,0
            remain=set([k for k in range(s_num) if can_use[k]==1])#把没用到的拿出来
            new_population[i,:]=[remain.pop() if son[k]==-1 else son[k] for k in range(s_num)]#没用到的塞进儿子,且population[i,:]=son=[.....]
        population=new_population
        for i in range(mutation):#突变
            mutater=np.random.randint(P)
            m1=m2=np.random.randint(s_num)#随即一个突变位置
            while m1==m2:
                m2=np.random.randint(s_num)
            population[mutater][m1],population[mutater][m2]=population[mutater][m2],population[mutater][m1] 
    fit=[outtree_schedule(population[p]).cal_C() for p in range(P)]       
    sort_index=np.argsort(fit[:])#按sigC从小到大排
    population=population[sort_index,:]
    return population[0]
def exe():
    for i in range(1):
        l=gene_algorithm(500,200,0.3,0.002)
        print(l)
        print(outtree_schedule(l).cal_C())

if __name__ == '__main__':
    exe()