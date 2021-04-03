//
// Created by luoxiYun on 2021/3/28.
//
#include "common.h"

typedef long long ll;
using vi = vector<int>;using vvi = vector<vector<int>>;
#define EPS (1e-7)
#define PI (acos(-1))
#define MOD 1000000007LL
#define REP(i, n) for (ll i = 0; i < n; i++)
#define REPR(i, n) for (ll i = n; i >= 0; i--)
#define FOR(i, m, n) for (ll i = m; i < n; i++)
#define FORR(i, m, n) for (ll i = m; i >= n; i--)
#ifdef LOCAL_DEBUG
#define DBGVV(a) cout << #a << " : \n";for(ll i=0;i<a.size();i++){DBG(i)DBGV(a[i])};
#define DBGV(a) cout << #a << " : ";for(auto b:a)cout << b << ' ';cout << endl;
#define DBG(a) cout << #a << " : " << a << endl;
#define DBGL(a) cout << #a;for(auto b=a;b;b=b->next)cout<<' '<<b->val;cout<<endl;
#define DBGT(a) cout << #a << " : \n" << a << endl;
#define DBGN(a) cout << #a << " : \n" << a << endl;
#else
#define DBGVV(a)
#define DBGV(a)
#define DBG(a)
#define DBGL(a)
#define DBGT(a)
#define DBGN(a)
#endif
#define ALL(v) v.begin(), v.end()
#define ALLR(v) v.rbegin(), v.rend()
#define VALID (ii>=0&&ii<m&&jj>=0&&jj<n)
#define pb push_back
template <class T>
bool chmax(T& a, const T& b){if (a < b){a = b;return 1;}return 0;}
template <class T>
bool chmin(T& a, const T& b){if (b < a){a = b;return 1;}return 0;}
const int di[] = { 0,-1,0,1 };const int dj[] = { 1,0,-1,0 };
string i2s(ll x){if(!x)return "0";if(x<0)return "-"+i2s(-x);char c[20]={0};int idx=0;while(x){c[idx++]='0'+x%10;x/=10;}reverse(c,c+idx);return c;}
string i2s(ll x,int radix){if(!x)return "0";if(x<0)return "-"+i2s(-x,radix);char c[64]={0};int idx=0;while(x){c[idx++]='0'+x%radix;x/=radix;}reverse(c,c+idx);return c;}
ll s2i(const string&s){int signal=1,idx=0;ll val=0;if(s[0]=='-'){signal=-1;idx++;}while(idx<s.size())val=val*10+s[idx++]-'0';return signal*val;}
ll s2i(const string&s,int radix){int signal=1,idx=0;ll val=0;if(s[0]=='-'){signal=-1;idx++;}while(idx<s.size())val=val*radix+s[idx++]-'0';return signal*val;}
ll gcd(ll a, ll b){a = abs(a);b = abs(b);if (a < b)swap(a, b);while (b){ll temp = a % b;a = b;b = temp;}return a;}
ll lcm(ll a, ll b){return a / gcd(a, b) * b;}
ll factorial(ll a){return a?factorial(a-1)*a:1;}
ll fastPower(ll a,ll n,ll mod=1000000007){ll res=1;while(n){if(n&1)res=res*a%mod;a=a*a%mod;n>>=1;}return res;}
void extgcd(ll a,ll b,ll& x,ll& y){if(!a){x=0,y=1;}else{extgcd(b%a,a,y,x);x-=(b/a)*y;}}
ll inv(ll a,ll mod=1000000007){ll x,y;extgcd(a,mod,x,y);return (x+mod)%mod;}
vi invTable(ll m, ll mod=1000000007){vi table(m+1,1);for(int i=2;i<=m;i++){table[i]=(mod-mod/i)*table[mod%i]%mod;}return table;}
ll combination(ll m, ll n, ll mod=1000000007){if(m<=20){auto getf=[](){vector<ll>f(21);for(int i=0;i<=20;i++)f[i]=i?f[i-1]*i:1;return f;};static vector<ll>f=getf();return f[m]/f[n]/f[m-n];}
    else{auto getf=[&](){vector<ll>f(21,0);for(int i=1;i<=20;i++)f[i]=inv(i,mod);return f;};static vector<ll>f=getf();if(n>m/2)n=m-n;ll res=1;for(int i=0;i<n;i++)res=res*(m-i)%mod;for(int i=1;i<=n;i++)res=res*f[i]%mod;return res;}}
vvi combinationTable(int m,int n,int mod){vvi table(m,vi(n,0));for(int j=1;j<n;j++)for(int i=1;i<m;i++){if(j==1)table[i][j]=i;else table[i][j]=(table[i-1][j]+table[i-1][j-1])%mod;}return table;}
bool isprime(ll n){if(n<2)return false;if(n==2)return true;if(n%2==0)return false;for(int i=3;i<=sqrt(n);i+=2)if(n%i==0)return false;return true;}
vi getprime(int range){vi primes{2};bitset<200000>b;for(int i=3;i<=range;i+=2){if(!b[i]){primes.push_back(i);for(int j=i*3;j<=range;j+=i*2)b.set(j);}}return primes;}
vi getFactor(ll n,ll range=10000){static vector<int>primes=getprime(range);vector<int>ans;for(int a:primes){if(a*a>n)break;while(n%a==0){n/=a;ans.push_back(a);}}if(n>1)ans.push_back(n);return ans;}
vector<ll> presum(vi&a){vector<ll> v(a.size() + 1,0);REP(i, a.size())v[i + 1] = v[i] + a[i];return v;}
vector<ll> postsum(vi&a){vector<ll> v(a.size() + 1,0);REPR(i, a.size()-1)v[i] = v[i+1] + a[i];return v;}
vector<int> premax(vi&a){vector<int> v(a.size(),0);REP(i, a.size())v[i] =i? max(v[i-1],a[i]):a[i];return v;}
vector<int> premin(vi&a){vector<int> v(a.size(),0);REP(i, a.size())v[i] =i? min(v[i-1],a[i]):a[i];return v;}
vector<int> postmax(vi&a){vector<int> v(a.size(),0);REPR(i, a.size()-1)v[i] =i+1<a.size()? max(v[i+1],a[i]):a[i];return v;}
vector<int> postmin(vi&a){vector<int> v(a.size(),0);REPR(i, a.size()-1)v[i] =i+1<a.size()? min(v[i+1],a[i]):a[i];return v;}
template<class T>
vi next_different(vector<T>&a){vi v(a.size());for(int i=0,j;i<a.size();){for(j=i+1;j<a.size()&&a[j]==a[i];j++);while(i<j)v[i++]=j;}return v;}
vi next_different(const string&a){vi v(a.size());for(int i=0,j;i<a.size();){for(j=i+1;j<a.size()&&a[j]==a[i];j++);while(i<j)v[i++]=j;}return v;}
template<class T>
vi prev_different(vector<T>&a){vi v(a.size());for(int i=int(a.size())-1,j;i>=0;){for(j=i-1;j>=0&&a[j]==a[i];j--);while(i>j)v[i--]=j;}return v;}
vi prev_different(const string&a){vi v(a.size());for(int i=int(a.size())-1,j;i>=0;){for(j=i-1;j>=0&&a[j]==a[i];j--);while(i>j)v[i--]=j;}return v;}
vi getSubsequenceSum(vi&nums){int nonzero=0;for(int a:nums)if(a)nonzero++;vector<int>v(1<<nonzero,0);int size=1;
    for(int a:nums){if(!a)continue;int duplicate=0;for(int i=0,j=0;i<size&&j<size;){if(v[i]+a==v[j]){duplicate++,i++,j++;}else if(v[i]+a<v[j])i++;else j++;}
        int i=size-1,j=size-1;size=size*2-duplicate;int k=size-1;while(i>=0&&j>=0){if(v[i]==v[j]+a){v[k--]=v[i--];j--;}else if(v[i]>v[j]+a)v[k--]=v[i--];
            else v[k--]=v[j--]+a;}while(j>=0)v[k--]=v[j--]+a;}v.resize(size);return v;}
template<class T>
vi getrank(vector<T>&a){int idx[a.size()];iota(idx,idx+a.size(),0);sort(idx,idx+a.size(),[&](int x,int y)->bool{return a[x]<a[y];});vi rnk(a.size());REP(i,a.size())rnk[idx[i]]=i;return rnk;}
template<class T>
vi getrank2(vector<T>&a){
    int idx[a.size()];iota(idx,idx+a.size(),0);sort(idx,idx+a.size(),[&](int x,int y)->bool{return a[x]<a[y];});vi rnk(a.size());
    for(int i=0,j,k=0;i<a.size();k++){for(j=i+1;j<a.size()&&a[idx[j]]==a[idx[i]];j++);while(i<j)rnk[idx[i++]]=k;}return rnk;}
ListNode* makelistnode(const vi&v) {if (v.empty())return nullptr;ListNode* p = new ListNode(-1);ListNode* q = p;for (int b : v) {q->next = new ListNode(b);q = q->next;}return p->next;}
vector<ListNode*> listtoarr(ListNode* p) {vector<ListNode*>v;while (p) {v.pb(p);p = p->next;}return v;}
ListNode* arrtolist(vector<ListNode*>&arr){if(arr.empty())return nullptr;REP(i,arr.size())arr[i]->next=i+1<arr.size()?arr[i+1]:nullptr;return arr[0];}
vi getnext(const string&needle){vi next(needle.size());for(int i=0,j=-1;i<needle.size();i++){if(!i)next[i]=j;else{while(j>=0&&needle[i-1]!=needle[j])j=next[j];next[i]=++j>=0&&needle[i]==needle[j]?next[j]:j;}}return next;}
vi getarm(const string&s){
    string s2="^#";for(char c:s){s2+=c;s2+="#";}s2+='$';int middle,maxright=0;vi arm(s2.size(),0);
    FOR(i,1,s2.size()-1){if(i<=maxright){int opp=middle*2-i;if(opp-arm[opp]==middle*2-maxright){
                int l=i-arm[opp],r=i+arm[opp];while(l>0&&r<s2.size()&&s2[l-1]==s2[r+1]){l--,r++;}arm[i]=r-i;if(chmax(maxright,r))middle=i;
            }else arm[i]=min(arm[opp],maxright-int(i));}
        else{int l=i,r=i;while(l>0&&r<s2.size()&&s2[l-1]==s2[r+1]){l--,r++;}arm[i]=r-i;if(chmax(maxright,r))middle=i;}}return arm;}
bool query_polindromic(vi&arm,int l,int r){return arm[l+r+2]>=r-l;}
template<class iterator>
bool isPolindromic(iterator begin,iterator end){while(begin<end)if(*begin++!=*--end)return false;return true;}
template<class T>
int getDirection(T*cur,T*next,T*query){T x1=*next-*cur;T y1=*(next+1)-*(cur+1);T x2=*query-*next;T y2=*(query+1)-*(next+1);
    T res=x1*y2-x2*y1;if(res>0)return 2;else if(res<0)return 4;res=x1*x2+y1*y2;if(res>0)return 1;else if(abs(x2)<abs(x1)||abs(y2)<abs(y1))return -1;else return 3;}
class Union{
#define UNIONSIZE 100000
public:int find[UNIONSIZE],size[UNIONSIZE],n,group;
    Union(int _n):n(_n),group(_n){iota(find,find+n,0);fill(size,size+n,1);}
    Union(const Union&other):n(other.n),group(other.group){memcpy(find,other.find,n*sizeof(int));memcpy(size,other.size,n*sizeof(int));}
    void reset(){iota(find,find+n,0);fill(size,size+n,1);group=n;}
    int Find(int i){if(find[i]==i)return i;else return find[i]=Find(find[i]);}
    bool unite(int i,int j){if((i=Find(i))==(j=Find(j)))return false;if(i<j){find[j]=i;size[i]+=size[j];}else{find[i]=j;size[j]+=size[i];}group--;return true;}
    bool same(int i,int j){return Find(i)==Find(j);}};
template<class T=int,int type=0>
struct Heap{
#define HEAPSIZE 100000
    typedef function<bool(const T&,const T&)> Operation;int Data[HEAPSIZE+1],Pos[HEAPSIZE+1]={0};unordered_map<T,int>M;vector<T>v;bitset<HEAPSIZE+1>pool;Operation cmp;
    Heap(Operation _cmp):cmp(_cmp){v.resize(HEAPSIZE+1);pool.set();pool.reset(0);}
    void push(const T&val){int idx,cur,parent;if(!M.count(val)){idx=pool._Find_first();pool.reset(idx);M[val]=idx;v[idx]=val;Pos[idx]=M.size();}else idx=M[val];
        for(cur=Pos[idx];parent=cur>>1;cur=parent){if(cmp(v[Data[parent]],val))Pos[Data[cur]=Data[parent]]=cur;else break;}Pos[Data[cur]=idx]=cur;}
    void sink(const T&val){if(!M.count(val))return;int idx=M[val],cur,son;for(cur=Pos[idx];(son=cur<<1)<=M.size();cur=son){if(son+1<=M.size()&&cmp(v[Data[son]],v[Data[son+1]]))son++;
            if(cmp(val,v[Data[son]]))Pos[Data[cur]=Data[son]]=cur;else break;}Pos[Data[cur]=idx]=cur;}
    void pop(){if(M.empty())return;pool.set(Data[1]);M.erase(v[Data[1]]);if(M.empty())return;T&val=v[Data[M.size()+1]];int idx=M[val],cur,son;for(cur=1;(son=cur<<1)<=M.size();cur=son){
            if(son+1<=M.size()&&cmp(v[Data[son]],v[Data[son+1]]))son++;if(cmp(val,v[Data[son]]))Pos[Data[cur]=Data[son]]=cur;else break;}Pos[Data[cur]=idx]=cur;}
    const T&top(){return v[Data[1]];}
    const size_t size(){return M.size();}};
template<class T>
struct Heap<T,0>{
#define HEAPSIZE 100000
    typedef function<bool(int&,int&)> Operation;int Data[HEAPSIZE+1],Pos[HEAPSIZE+1]={0},Size;Operation cmp;Heap(Operation _cmp):cmp(_cmp),Size(0){}
    void push(int val){int cur,parent;if(!Pos[val])Pos[val]=++Size;for(cur=Pos[val];parent=cur>>1;cur=parent){if(cmp(Data[parent],val))Pos[Data[cur]=Data[parent]]=cur;else break;}Pos[Data[cur]=val]=cur;}
    void sink(int val){if(!Pos[val])return;int cur,son;for(cur=Pos[val];(son=cur<<1)<=Size;cur=son){if(son+1<=Size&&cmp(Data[son],Data[son+1]))son++;
            if(cmp(val,Data[son]))Pos[Data[cur]=Data[son]]=cur;else break;}Pos[Data[cur]=val]=cur;}
    void pop(){if(!Size)return;Pos[Data[1]]=0;if(!--Size)return;int val=Data[Size+1],cur,son;for(cur=1;(son=cur<<1)<=Size;cur=son){
            if(son+1<=Size&&cmp(Data[son],Data[son+1]))son++;if(cmp(val,Data[son]))Pos[Data[cur]=Data[son]]=cur;else break;}Pos[Data[cur]=val]=cur;}
    const int top(){return Data[1];}
    const size_t size(){return Size;}};
class StaticTrie {
#define TRIESIZE 100000
#define TRIEN 30
public:int data[TRIESIZE+1][TRIEN]={0};bitset<TRIESIZE+1>pool;
    StaticTrie(){data[0][26]=-1;data[0][27]=0;pool.set();pool.reset(0);}void clear(){memset(data,0,sizeof(data));data[0][26]=-1;pool.set();pool.reset(0);}
    int* operator[](int i){return data[i];}
    void Malloc(int&idx){idx=pool._Find_first();memset(data[idx],0,TRIEN*sizeof(int));data[idx][26]=-1;pool.reset(idx);}
    void Free(int&idx){pool.set(idx);idx=0;}
    int insert(int cur,const string&word,int i,int _signal) {int res=0;if(i==word.size()){if(data[cur][26]<0){data[cur][26]=_signal;res=1;}}else{
            if(!data[cur][word[i]-'a']){Malloc(data[cur][word[i]-'a']);}res=insert(data[cur][word[i]-'a'],word,i+1,_signal);}data[cur][27]+=res;return res;}
    void insert(const string&word,int _signal=1) {insert(0,word,0,_signal);}
    int search(const string&word) {int cur=0;for(int i=0;i<word.size();i++){if(!data[cur][word[i]-'a']){return -1;}cur=data[cur][word[i]-'a'];}return data[cur][26];}
    bool startsWith(const string&prefix) {int cur=0;for(int i=0;i<prefix.size();i++){if(!data[cur][prefix[i]-'a']){return false;}cur=data[cur][prefix[i]-'a'];}return true;}};
class BiTrie {
#define TRIESIZE 1000000
#define TRIEN 4
public:
    i nt data[TRIESIZE+1][TRIEN]={0},used;BiTrie():used(1){}void clear(){memset(data,0,sizeof(data));used=1;}
    void insert(int num){int cur=0;for(int i=31;i>=0;i--){int&next=data[cur][num>>i&1];if(!next)next=used++;cur=next;}}
    int searchMax(int num) {if(used==1)return 0;int cur=0,maxSame=0;for(int i=31;i>=0;i--){maxSame<<=1;int next=data[cur][num>>i&1];
            if(next){cur=next;maxSame++;}else cur=data[cur][!((num>>i)&1)];}return maxSame;}};
template<class T>
class SegTree{typedef function<T(T&,T&)> Operation;
#define SEGTREEDEPTH 17
public:T data[1<<(SEGTREEDEPTH+1)]={0};int X;T default_val;Operation op;SegTree(int n,T _default_val,Operation _op):default_val(_default_val),op(_op){
        for(X=4;X<n;X<<=1);if(memcmp(data,&default_val,sizeof(default_val))){fill(data+X,data+X*2,default_val);}for(int i=X-1;i;i--){data[i]=op(data[i*2],data[i*2+1]);}}
    template<class Tlike>
    SegTree(vector<Tlike>&nums,T _default_val,Operation _op):default_val(_default_val),op(_op){for(X=4;X<nums.size();X<<=1);
        for(int i=0;i<nums.size();i++){data[X+i]=nums[i];}if(memcmp(data,&default_val,sizeof(default_val))){fill(data+X+nums.size(),data+X*2,default_val);}for(int i=X-1;i;i--){data[i]=op(data[i*2],data[i*2+1]);}}
    void set(int i,T val){data[i+=X]=val;while(i>>=1){data[i]=op(data[i*2],data[i*2+1]);}}T& operator[](int i){return data[i+X];}
    T operator()(int l,int r){l=max(l,0);r=min(r,X-1);if(l>r)return default_val;if(l==r)return data[l+X];T res=op(data[l+=X],data[r+=X]);
        while(l/2!=r/2){if(l%2==0)res=op(res,data[l+1]);if(r%2)res=op(res,data[r-1]);l>>=1;r>>=1;}return res;}
    void step(int i,T inc){for(i+=X;i;i>>=1)data[i]=op(data[i],inc);}void step_forward(T i){if(is_same<T,int>::value||is_same<T,long>::value){for(i+=X;i;i>>=1)data[i]++;}}
    void step_back(T i){if(is_same<T,int>::value||is_same<T,long>::value){for(i+=X;i;i>>=1)data[i]--;}}
    int find_nth(T n){if((is_same<T,int>::value||is_same<T,long>::value)&&n<data[1]){int i=1;while(i<X){if(data[i*2]>=n+1){i<<=1;}else{n-=data[i*2];i=(i<<1)+1;}}return i-X;}else return -1;}};
template<class T>
class LazyTree{typedef function<T(T&,T&)> Operation;struct elem{T val;T inc;bool b;elem():val(),inc(),b(false){}elem(T _val):val(_val),inc(),b(false){}elem(T _val,T _inc):val(_val),inc(_inc),b(false){}elem(T _val,T _inc,bool _b):val(_val),inc(_inc),b(_b){}};
#define LAZYTREEDEPTH 17
    inline int size(int i){return __builtin_clz(i)+Y-31;}void inherite(int i,T inc){data[i].val+=inc;data[i].inc+=inc;data[i].b=true;}
public:elem data[1<<(LAZYTREEDEPTH+1)];int X,Y;T default_val;Operation op;
    LazyTree(int n,T _default_val,Operation _op):default_val(_default_val),op(_op){for(X=4;X<n;X<<=1);Y=__builtin_ctz(X);if(memcmp(data,&default_val,sizeof(default_val))){
            fill(data+X,data+X*2,elem(default_val));}for(int i=X-1;i;i--){data[i].val=op(data[i*2].val,data[i*2+1].val);}}
    template<class Tlike>
    LazyTree(vector<Tlike>&nums,T _default_val,Operation _op):default_val(_default_val),op(_op){for(X=4;X<nums.size();X<<=1);Y=__builtin_ctz(X);
        for(int i=0;i<nums.size();i++){data[X+i]=nums[i];}if(memcmp(data,&default_val,sizeof(default_val))){fill(data+X+nums.size(),data+X*2,default_val);}for(int i=X-1;i;i--){data[i]=elem(op(data[i*2].val,data[i*2+1].val));}}
    void set(int i,T inc){push_down(i);data[i+=X].val=inc;while(i>>=1){data[i].val=op(data[i*2].val,data[i*2+1].val);}}
    void step(int i,T inc){push_down(i);inherite(i+=X,inc);while(i>>=1){data[i].val=op(data[i*2].val,data[i*2+1].val);}}
    void step(int l,int r,T inc){if(l==r)step(l,inc);else{push_down(l);push_down(r);inherite(l+=X,inc);inherite(r+=X,inc);while((l>>1)!=(r>>1)){if(l%2==0)inherite(l+1,inc);if(r%2)inherite(r-1,inc);
                data[l>>1].val=op(data[l].val,data[l^1].val);data[r>>1].val=op(data[r].val,data[r^1].val);l>>=1;r>>=1;}while(l>>=1){data[l].val=op(data[l*2].val,data[l*2+1].val);}}}
    void push_down(int i){for(int j=Y,k=1;j;k=(i&(1<<--j))?(k<<1)+1:k<<1){if(data[k].b){inherite(k*2,data[k].inc);inherite(k*2+1,data[k].inc);data[k]=elem(data[k].val);}}}
    T& operator[](int i){push_down(i);return data[i+X].val;}
    T operator()(int l,int r){l=max(l,0);r=min(r,X-1);if(l>r)return default_val;if(l==r)return (*this)[l];push_down(l);push_down(r);T res=op(data[l+=X].val,data[r+=X].val);
        while(l/2!=r/2){if(l%2==0)res=op(res,data[l+1].val);if(r%2)res=op(res,data[r-1].val);l>>=1;r>>=1;}return res;}
    int find_nth(T n){if(n<data[1]){int i=1;while(i<X){if(data[i].b){data[i*2].inherite(data[i].inc/2);data[i*2+1].inherite(data[i].inc/2);data[i]=elem(data[i].val);}
                if(data[i*2].val>=n+1){i<<=1;}else{n-=data[i*2].val;i=(i<<1)+1;}}return i-X;}else return -1;}};
struct Fraction{
    long signal,numerator,denominator;
    void normalize(){if(denominator){if(!numerator){signal=denominator=1;}else{
                if(numerator<0){signal=-1;numerator*=-1;}if(denominator<0){signal*=-1;denominator*=-1;}
                long _gcd=__detail::__gcd(numerator,denominator);if(_gcd>1){numerator/=_gcd;denominator/=_gcd;}}}}
    Fraction():signal(1),numerator(0),denominator(1){}
    Fraction(long val):signal(val>=0?1:-1),numerator(abs(val)),denominator(1){}
    Fraction(long _numerator,long _denominator):signal(1),numerator(_numerator),denominator(_denominator){normalize();}
    Fraction(string&&str1,string&&str2):signal(1),numerator(0),denominator(0){
        int idx=0;if(!isdigit(str1[idx])&&str1[idx++]=='-')signal=-1;while(isdigit(str1[idx]))numerator=numerator*10+str1[idx++]-'0';idx=0;
        if(!isdigit(str2[idx])&&str2[idx++]=='-')signal*=-1;while(isdigit(str2[idx]))denominator=denominator*10+str2[idx++]-'0';normalize();
    }
    Fraction(string&&str):Fraction(str.substr(0,str.find('/')),str.substr(str.find('/')+1,str.size()-str.find('/')-1)){}
    Fraction operator+(const Fraction&other){return Fraction(signal*numerator*other.denominator+other.signal*other.numerator*denominator,denominator*other.denominator);}
    Fraction&operator+=(const Fraction&other){numerator=signal*numerator*other.denominator+other.signal*other.numerator*denominator;
        denominator*=other.denominator;signal=1;normalize();return *this;}
};
class tarjanBridge{
    typedef vector<vector<int>>::iterator vvii;vvii begin;vvii end;bool*isBridge;unordered_map<int,int>idmap;vector<int>DFN;vector<int>LOW;
    vector<int>*adj_point;vector<int>*adj_edge;int timestamp;
    int getid(int oldid){if(idmap.count(oldid))return idmap[oldid];else return idmap[oldid]=idmap.size();}
    int dfs(int cur,int from){DFN[cur]=LOW[cur]=timestamp++;
        for(int i=0;i<adj_edge[cur].size();i++){int point=adj_point[cur][i],edge=adj_edge[cur][i];if(edge!=from){
                if(DFN[point]>=0)LOW[cur]=min(LOW[cur],DFN[point]);else{int res=dfs(point,edge);
                    if(res>DFN[cur])isBridge[edge]=true;LOW[cur]=min(LOW[cur],res);}}}return LOW[cur];}
public:
    tarjanBridge(vvii _begin,vvii _end,bool*_isBridge):begin(_begin),end(_end),isBridge(_isBridge){
        for(auto it=begin;it<end;++it){getid((*it)[0]);getid((*it)[1]);}DFN.resize(idmap.size(),-1);LOW.resize(idmap.size(),-1);
        adj_point=new vector<int>[idmap.size()];adj_edge=new vector<int>[idmap.size()];
        for(auto it=begin;it<end;++it){int i=getid((*it)[0]),j=getid((*it)[1]);if(i!=j){adj_point[i].emplace_back(j);
                adj_edge[i].emplace_back(it-begin);adj_point[j].emplace_back(i);adj_edge[j].emplace_back(it-begin);}}}
    void findBridge(){timestamp=0;for(int i=0;i<idmap.size();i++)if(DFN[i]<0)dfs(i,-1);}
};
class tarjanCut{
    typedef vector<vector<int>>::iterator vvii;vvii begin;vvii end;bool*isCut;unordered_map<int,int>idmap;vector<int>iddict;
    vector<int>DFN;vector<int>LOW;vector<int>*adj_point;vector<int>*adj_edge;int timestamp;int size;
    int getid(int oldid){if(idmap.count(oldid))return idmap[oldid];else{int newid=idmap[oldid]=idmap.size();iddict.emplace_back(oldid);return newid;}}
    int findoldid(int newid){return iddict[newid];}
    int dfs(int cur,int from){DFN[cur]=LOW[cur]=timestamp++;
        for(int i=0;i<adj_edge[cur].size();i++){int point=adj_point[cur][i],edge=adj_edge[cur][i];
            if(edge!=from){if(DFN[point]>=0)LOW[cur]=min(LOW[cur],DFN[point]);else{int res=dfs(point,edge);
                    if(res>=DFN[cur]){if(from==-1)from--;else isCut[findoldid(cur)]=true;}LOW[cur]=min(LOW[cur],res);}}}return LOW[cur];}
public:
    tarjanCut(vvii _begin,vvii _end,bool _isCut[]):begin(_begin),end(_end),isCut(_isCut){
        for(auto it=begin;it<end;++it){getid((*it)[0]);getid((*it)[1]);}size=idmap.size();DFN.resize(size,-1);LOW.resize(size,-1);
        adj_point=new vector<int>[size];adj_edge=new vector<int>[size];for(auto it=begin;it<end;++it){
            int i=getid((*it)[0]),j=getid((*it)[1]);if(i!=j){adj_point[i].emplace_back(j);adj_edge[i].emplace_back(it-begin);
                adj_point[j].emplace_back(i);adj_edge[j].emplace_back(it-begin);}}}
    void findCut(){timestamp=0;for(int i=0;i<size;i++)if(DFN[i]<0)dfs(i,-1);}
};
class tarjanSCC{
    typedef vector<vector<int>>::iterator vvii;vvii begin;vvii end;int*color;unordered_map<int,int>idmap;vector<int>iddict;
    vector<int>DFN;vector<int>LOW;vector<int>*adj_point;vector<int>*adj_edge;int timestamp;stack<int>S;int curcolor;
    int getid(int oldid){if(idmap.count(oldid))return idmap[oldid];else{int newid=idmap[oldid]=idmap.size();
            iddict.emplace_back(oldid);return newid;}}int findoldid(int newid){return iddict[newid];}
    int dfs(int cur){DFN[cur]=LOW[cur]=timestamp++;S.push(cur);for(int i=0;i<adj_edge[cur].size();i++){
            int point=adj_point[cur][i],edge=adj_edge[cur][i];if(DFN[point]>=0){if(color[findoldid(point)]<0)LOW[cur]=min(LOW[cur],DFN[point]);}else{
                LOW[cur]=min(LOW[cur],dfs(point));}}if(LOW[cur]==DFN[cur]){while(color[findoldid(cur)]<0){color[findoldid(S.top())]=curcolor;S.pop();}curcolor++;
        }return LOW[cur];}
public:
    tarjanSCC(vvii _begin,vvii _end,int _color[]):begin(_begin),end(_end),color(_color){for(auto it=begin;it<end;++it){
            getid((*it)[0]);getid((*it)[1]);}DFN.resize(idmap.size(),-1);LOW.resize(idmap.size(),-1);adj_point=new vector<int>[idmap.size()];
        adj_edge=new vector<int>[idmap.size()];for(auto it=begin;it<end;++it){int i=getid((*it)[0]),j=getid((*it)[1]);
            if(i!=j){adj_point[i].emplace_back(j);adj_edge[i].emplace_back(it-begin);}}}void findSCC(){timestamp=0;
        curcolor=0;for(int i=0;i<idmap.size();i++){if(DFN[i]<0)dfs(i);}}};
struct SuffixArray{
#define MAXN 100010
    string s;int n,bucketRange;int sa[MAXN],second[MAXN],bucket[MAXN],mem[MAXN],rk_mem[MAXN],rk2_mem[MAXN],height[MAXN];int *rk,*rk2;
    SuffixArray(const string&_s):s(_s),n(s.size()),bucketRange(127){cout<<"attention MAXN,string length<="<<MAXN-1<<'\n';rk=rk_mem;rk2=rk2_mem;rk[n]=rk2[n]=-1;memset(bucket,0,sizeof(bucket));
        for(int i=0;i<n;i++)bucket[rk[i]=s[i]]++;for(int i=1;i<=bucketRange;i++)bucket[i]+=bucket[i-1];for(int i=0;i<n;i++)sa[--bucket[rk[i]]]=i;
        for(int w=1;;w<<=1){int j=0;for(int i=n-w;i<n;i++)second[j++]=i;for(int i=0;i<n;i++)if(sa[i]>=w)second[j++]=sa[i]-w;memset(bucket,0,sizeof(bucket));
            for(int i=0;i<n;i++)bucket[mem[i]=rk[second[i]]]++;for(int i=1;i<=bucketRange;i++)bucket[i]+=bucket[i-1];for(int i=n-1;i>=0;i--)sa[--bucket[mem[i]]]=second[i];
            bucketRange=rk2[sa[0]]=0;for(int i=1;i<n;i++)rk2[sa[i]]=rk[sa[i]]==rk[sa[i-1]]&&rk[sa[i]+w]==rk[sa[i-1]+w]?bucketRange:++bucketRange;
            swap(rk,rk2);if(bucketRange==n-1)break;}}
    void getHeight(){memset(height,0xff,sizeof(height));for(int i=0,h=0;i<n;i++){if(h)h--;if(rk[i])while(s[i+h]==s[sa[rk[i]-1]+h])h++;height[rk[i]]=h;}}
#undef MAXN
};