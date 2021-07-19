#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
using namespace std;
class OPT{
    int s,t,n,minimum;
    vector<int> vis,topo_path,time,res;
    vector<vector<int> > ans,graph;
public:
    OPT();
    OPT(string filepath, string timepath);
    bool not_loop(int i,int cnt);
    void dfs(int cnt,int sum,int temp);
    void print(vector<int> &v);
    void opt();
    void exe();

};

OPT::OPT(){
    s=4,t=5,n=s+t,minimum=INT_MAX;
    vector<int> v(n,0);
    vis=v;
    topo_path=v;
    res=v;
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
    res=v;
    minimum=INT_MAX;
}
bool OPT::not_loop(int i,int cnt){
    for(int j=0;j<cnt;j++)
        if(graph[i][topo_path[j]])
            return false;
    return true;
}
void OPT::dfs(int cnt,int sum,int temp){
    if(cnt==n&&minimum>temp){

            minimum=temp;
            res=topo_path;
        }
    else for(int i=0;i<n;i++)if(!vis[i]&&not_loop(i,cnt)&&temp<minimum){
        vis[i]=1;
        topo_path[cnt]=i;
        sum+=time[i];
        if(i<s)
            dfs(cnt+1,sum,temp);
        else if(i>=s)
            dfs(cnt+1,sum,temp+sum);
        sum-=time[i];
        vis[i]=0;
    }
}
void OPT::print(vector<int> &v){
    int N=v.size();
    for(int i=0;i<N;i++)
        cout<<v[i]<<" ";
    cout<<endl;
}

void OPT::exe(){
    dfs(0,0,0);
    print(res);
    cout<<"min is"<<minimum<<endl;
}
int main()
{
    OPT o("1.csv", "time.csv");
    o.exe();
    return 0;
}