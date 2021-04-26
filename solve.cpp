#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define endl '\n'
#define all(x) (x).begin(),(x).end()

int n,m;
vector<int> a,b,k;
vector<vector<vector<int>>> v;

// template<typename T> 
// struct vector{
//     int n;
//     T a[];
//     vector(){
//         this->n=0;
//         a=new T[0];
//     }
// };

struct customer{
    int id;
    vector<int> x;
    customer(int id,vector<int> x){
        x.resize(n);
        this->id=id;
        this->x=x;
    }
    void print(ofstream& fo){
        fo<<endl;
        fo<<"customer ["<<this->id<<"] : "<<endl;
        for(int i=0;i<x.size();++i){
            fo<<x[i]<<" ";
        }
        fo<<endl; // error in here
    }
};

// map<vector<int>,int> dp;

int sumVec(vector<int>& vec){
    int sum=0;
    for(int i=0;i<n;++i) sum+=a[i]*vec[i];
    return sum;
}

vector<int> add_vec(const vector<int>& a,const vector<int>& b){
    vector<int> c(a);
    for(int i=0;i<n;++i){
        c[i]+=b[i];
    }
    return c;
}

void solve(int id,vector<vector<int>>& vec,int sum,int val,vector<int> cur){
    if(sum==val){
        vec.push_back(cur);
        return;
    }
    // cout<<"sum : "<<sum<<endl;
     cout<<" cur : ";
    for(int i=0;i<cur.size();++i) cout<<cur[i]<<" ";
    cout<<endl;
    if(id==n||sum>val) return;
    for(int times=0;times<=b[id];++times){
        int add=times*a[id];
        cur[id]=times;
        solve(id+1,vec,sum+add,val,cur);
    }
    cur[id]=0;
}

void putVec(vector<vector<int>>& vec,int val){
    vector<int> cur(n,0);
    cout<<"vec : ";
    int nVec=vec.size();
    for(int i=0;i<nVec;++i){
		for(int j=0;j<vec[i].size();++j){
			cout<<vec[i][j]<<" ";
		}
		cout<<endl;
	} 
    cout<<endl;
    solve(0,vec,0,val,cur);
}

bool good(vector<int> cur){
    for(int i=0;i<n;++i){
        if(cur[i]>b[i]) return 0;
    }
    return 1;
}

void get_ans(int id,pair<int,vector<int>>& ans,vector<int> cur,int cnt,vector<customer>& list,vector<customer> tmp){
    if(!good(cur)) return;
    cout<<"you know what"<<endl;
     for(int i=0;i<tmp.size();++i){
			for(int j=0;j<tmp[i].x.size();++j) cout<<tmp[i].x[j]<<" ";
			cout<<endl;
		}
    // if(dp.find(cur)==dp.end()) dp[cur]=-1;
    // int& res=dp[cur];
    // if(res>=cnt) return;
    int res=cnt; 
    if(ans.first<cnt){
        ans.first=cnt;
        ans.second=cur;
        list=tmp;
    }
    if(id==m) return;
    // dont choose him
    get_ans(id+1,ans,cur,cnt,list,tmp);

    //choose him 
    for(vector<int> x:v[id]){
        tmp.emplace_back(id+1,x);
        get_ans(id+1,ans,add_vec(cur,x),cnt+1,list,tmp);
        tmp.pop_back();
    }
}

bool vecGreater(const vector<int>& a,const vector<int>& b){
    for(int i=0;i<(int)a.size();++i){
        if(a[i]<b[i]) return 0;
    }
    return 1;
}

// map<vector<int>,int> mask;

int sum,maxSum;

void dfs(int id,vector<int> vec,vector<customer>& list,vector<customer> tmp){
    if(id==m){
        if(!good(vec)) return;
        int sumNow=sumVec(vec);
        // cout<<"id now now : "<<id<<endl;
        // cout<<"temp : ";
        // for(customer x:tmp) cout<<x.id<<" ";
        // cout<<endl;
        // cout<<"sumNow : "<<sumNow<<endl;
        // cout<<"debug1 : "<<sumNow<<endl;
        if(maxSum<sumNow){
            maxSum=sumNow;
            list=tmp;
        }
        return;
    }
    // cout<<"id pass : "<<id<<endl;
    // if(!vecGreater(b,vec)) return;
    if(!good(vec)) return;
    int sumNow=sumVec(vec);
    // cout<<"id now now : "<<id<<endl;
    // cout<<"temp : ";
    // for(customer x:tmp) cout<<x.id<<" ";
    // cout<<endl;
    // cout<<"sumNow : "<<sumNow<<endl;
    // cout<<"debug1 : "<<sumNow<<endl;
    if(maxSum<sumNow){
        maxSum=sumNow;
        list=tmp;
    }
    // cout<<"id : "<<id<<"  mask : "<<mask[vec]<<endl;
    // cout<<"mask vec : passed"<<endl;
    // cout<<"sum : "<<sum<<"    -    sumNow : "<<sumNow<<"   <   k id : "<<k[id]<<endl;
    // cout<<"let pas"<<endl;
    dfs(id+1,vec,list,tmp);
    for(vector<int> vvv:v[id]){
        // if(id==0) cout<<"TRUETRUE"<<endl;
        customer now(id,vvv);
        tmp.push_back(now);
        dfs(id+1,add_vec(vec,vvv),list,tmp);
        tmp.pop_back();
    }
}

int main(){
    ios::sync_with_stdio(0);
	cin.tie(0);
    ifstream fi("F:/DA/input.txt");
    ofstream fo("F:/Da/output2.txt");
    ofstream fo2("F:/Da/output3.txt");
    if(fi.fail()){
        return cout<<"ifstream failed "<<endl,0;
    }
    if(fo.fail()){
        return cout<<"ofstream failed "<<endl,0;
    }
    if(fo2.fail()){
        return cout<<"ofstream2 failed "<<endl,0;
    }
    sum=0;
    fi>>n>>m;
    a.resize(n);
    for(int& x:a) fi>>x;
    b.resize(n);
    for(int& x:b) fi>>x;
    k.resize(m);
    for(int& x:k) fi>>x;
    v.resize(m);
    // print out screen content of data
    cout<<"--------------------------------------------------"<<endl;
    cout<<"CONTENT OF DATA : "<<endl;
    cout<<"n : "<<n<<"  m : "<<m<<endl;
    for(int i=0;i<n;++i){
        cout<<"a["<<i+1<<"] = "<<a[i]<<", b["<<i+1<<"] = "<<b[i]<<endl;
    }
    cout<<"~~~~~~~~~~~~~~"<<endl;
    for(int i=0;i<m;++i){
        cout<<"k["<<i+1<<"] = "<<k[i]<<endl;
    }
    cout<<"--------------------------------------------------"<<endl;
    // simplized
    int g=0;
    for(int x:a) g=__gcd(g,x);
    for(int x:k) g=__gcd(g,x);
    for(int& x:a) x/=g;
    for(int& x:k) x/=g;


    for(int i=0;i<m;++i){
        putVec(v[i],k[i]);
    }
    cout<<"v[0] : "<<endl;
    for(int i=0;i<v[0].size();++i){
		for(int j=0;j<v[0][i].size();++j){
			cout<<v[0][i][j]<<" ";
		}
		cout<<endl;
	}
    // for(int i=0;i<m;++i){
    //     cout<<"user "<<i<<" : "<<endl;
    //     for(vector<int> x:v[i]){
    //         for(int xx:x) cout<<xx<<" ";
    //         cout<<endl;
    //     }
    // }
    vector<customer> mainList;
    vector<customer> tmp;
    vector<int> cur(n,0);
    pair<int,vector<int>> ans;
    get_ans(0,ans,cur,0,mainList,tmp);
    cout<<"ansansansansansansansans : "<<ans.first<<endl;
    for(int x:ans.second) cout<<x<<" ";
    cout<<endl;
    // output in file output2
    fo<<"/////////////////////////////////////"<<endl;
    fo<<"CUSTOMER LIST"<<endl;
    // fo<<"num : "<<(int)mainList.size()<<endl;
    for(int i=0;i<(int)mainList.size();++i){
        mainList[i].print(fo);
    }
    cout<<endl<<"mainList"<<endl;
    for(int i=0;i<(int)mainList.size();++i){
        //~ mainList[i];
        for(int j=0;j<mainList[i].x.size();++j){
			cout<<mainList[i].x[j]<<" ";
		}
		cout<<endl;
    }
    fo<<"/////////////////////////////////////"<<endl;
    fo<<endl;
    fo.close();
    //////////////////////////////////////////////////
    maxSum=0;
    // output3
    sort(all(k));
    for(int i=0;i<n;++i) sum+=a[i]*b[i];
    // cout<<endl;
    // cout<<"init sum : "<<sum<<endl;
    // cout<<"helo "<<endl;
    // while(!Q.empty()){
    //     customer now=Q.front();
    //     Q.pop();
    //     if(now.id==m) continue;
    //     if(!vecGreater(b,now.x)) continue;
    //     int sumNow=sumVec(now.x);
    //     maxSum=max(maxSum,sumNow);
    //     if(mask[now.x]) continue;
    //     mask[now.x]=1;
    //     if(sum-sumNow<k[now.id]) continue;
    //     customer cus_now(now.id+1,now.x);
    //     Q.push(cus_now); // dont choose
    //     for(vector<int> vec:v[now.id]){
    //         customer cus_now1(now.id+1,add_vec(now.x,vec));
    //         Q.push(cus_now1); // choose
    //     }
    // }
    vector<int> tmp2(n,0);
    vector<customer> mainList2;
    vector<customer> temp;
    // cout<<"m : "<<m<<endl;
    dfs(0,tmp2,mainList2,temp);
    maxSum*=g;
    fo2<<"max sum : "<<maxSum<<endl;
    cout<<"max sum : "<<maxSum<<endl;
    for(customer x:mainList2){
        fo2<<"khach thu ["<<x.id<<"] : ";
        for(int xx:x.x) fo2<<xx<<" ";
        fo2<<endl;
    }
    // cout<<"v5 : ";
    // for(vector<int> x:v[4]){
    //     for(int xx:x) cout<<xx<<" ";
    // }
    // cout<<endl;
    // cout<<"v0 : ";
    // for(vector<int> x:v[0]){
    //     for(int xx:x) cout<<xx<<" ";
    // }
    // cout<<endl;
    fo2.close();
    fi.close();
    return 0;
}