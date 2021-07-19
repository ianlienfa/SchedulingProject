#include<iostream>
#include<vector>
#include <sstream>
#include <climits> 
#include <fstream>
using namespace std;
typedef vector<vector<int> > Vii;

class OPT{
    int s,t,n;
    string filepath = "1.txt";
    vector<int> vis,topo_path,time;
    vector<vector<int> > ans,graph;
public:
    OPT();
    OPT(string filepath, string timepath);
    bool not_loop(int i,int cnt);
    void dfs(int cnt);
    void print();
    void opt();
    void exe();
    
};

OPT::OPT(){
    s=4,t=5,n=s+t;
    vector<int> v(n,0);
    vis=v;
    topo_path=v;
    time={2,4,3,2,5,3,6,2,7};
    graph = {{0,0,0,0,0,1,0,1,0},
             {0,0,0,0,1,1,0,0,1},
             {0,0,0,0,1,0,0,1,0},
             {0,0,0,0,0,0,1,0,1},
             {0,0,0,0,0,0,0,0,0},
             {0,0,0,0,0,0,0,0,0},
             {0,0,0,0,0,0,0,0,0},
             {0,0,0,0,0,0,0,0,0},
             {0,0,0,0,0,0,0,0,0}};
}

OPT::OPT(string filepath, string timepath){
    ifstream file; string inputline; int row_ct = 0;

    // initialized graph
    file.open(filepath);
    if(file.fail())
        exit(1);
    getline(file, inputline);
    while(getline(file, inputline)) 
    {
        row_ct++;
        vector<int> row;
        std::size_t found = inputline.find_first_of(",");
        while(found != string::npos)
        {
            row.push_back(stoi(inputline.substr(found+1, 1)));
            found=inputline.find_first_of(",",found+2);
        }
        graph.push_back(row);
    }
    s = graph[0].size();    // initialize s
    t = row_ct;             // initialize t
    n = s + t;
    for(size_t i = 0; i < graph.size(); i++)
    {
        graph[i].resize(graph[i].size() + row_ct);
    }
    for(int i = 0; i < row_ct; i++)
    {
        vector<int> dummyvec(graph[0].size());
        graph.push_back(dummyvec);
    }

    for(int i = 0; i < graph.size(); i++)
    {
        for(int j = 0; j < graph[i].size(); j++)
            cout << graph[i][j] << " ";
            cout << endl;
    }

    // initialize time
    file.open(timepath);
    getline(file, inputline);   //s
    getline(file, inputline);
    stringstream ss(inputline);
    string token;
    while(getline(ss, token, ','))
    {
        if(int(token[0]) > 57 || int(token[0]) < 48)
            continue;
        time.push_back(stoi(token));    
    }
    getline(file, inputline);   //t
    getline(file, inputline);   
    ss.str(inputline);
    while(getline(ss, token, ','))
    {
        if(int(token[0]) > 57 || int(token[0]) < 48)
            continue;
        time.push_back(stoi(token));    
    }
    
    // initialized other elements
    vector<int> v(n,0);
    vis=v;
    topo_path=v;
}


bool OPT::not_loop(int i,int cnt){
    for(int j=0;j<cnt;j++)
        if(graph[i][topo_path[j]])
            return false;
    return true;
}
void OPT::dfs(int cnt){
    if(cnt==n)
        ans.push_back(topo_path);
    else for(int i=0;i<n;i++)if(!vis[i]&&not_loop(i,cnt)){
        vis[i]=1;
        topo_path[cnt]=i;
        dfs(cnt+1);
        vis[i]=0;
    }
}
void OPT::print(){
    int N=ans.size();
    cout<<N<<endl;
    for(int i=0;i<N;i++){
        for(int j=0;j<n;j++){
            cout<<ans[i][j];
        }
        cout<<endl;
    }
}
void OPT::opt(){
    int N=ans.size(),res=INT_MAX,per_total_time,temp;
    for(int i=0;i<N;i++){
        per_total_time=0,temp=0;
        for(int j=0;j<n;j++){
            per_total_time+=time[ans[i][j]];
            if(ans[i][j]>=s)
                temp+=per_total_time;
            if(temp>=res)
                continue;
        }
        res=temp;
    }
    cout<<"the minnimum end time sum is "<<res<<endl;
}
void OPT::exe(){
    dfs(0);
    opt();
}


// int main()
// {
//     OPT o;
//     o.exe();
//     return 0;
// }

int main()
{
    OPT o("1.csv", "time.csv");
    cout << "safe" << endl;
    o.exe();
}