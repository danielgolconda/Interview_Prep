
#include<bits/stdc++.h>
using namespace std;

#define ff              first
#define ss              second
#define int             long long
#define pb              push_back
#define mp              make_pair
#define pii             pair<int,int>
#define vi              vector<int>
#define mii             map<int,int>
#define pqb             priority_queue<int>
#define pqs             priority_queue<int,vi,greater<int> >
#define setbits(x)      __builtin_popcountll(x)
#define zrobits(x)      __builtin_ctzll(x)
#define mod             1000000007
#define inf             1e18
#define ps(x,y)         fixed<<setprecision(y)<<x
mt19937                 rng(chrono::steady_clock::now().time_since_epoch().count());


void c_p_c()
{
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
}
const int MAXN = 1e5 + 1;
int a[MAXN],seg[4*MAXN + 1];

void build(int start,int end,int idx)
{
  if(start == end)
  {
    seg[idx] = a[start];
    return ;
  }
  int mid = start + ((end-start)/2);

  build(start,mid,2*idx + 1);
  build(mid+1,end,2*idx + 2);

  seg[idx] = min(seg[2*idx + 1], seg[2*idx + 2]);
  return ;
}

int query(int start,int end,int l,int r,int idx)
{
  if(l <= start && r >= end)
  {
    return seg[idx];
  }
  if(start > r || end < l)
  {
    return INT_MAX;
  }

  int mid = start + ((end-start)/2);

  int lans = query(start,mid,l,r,2*idx + 1);
  int rans = query(mid+1,end,l,r,2*idx + 2);

  return min(lans,rans);
}

void update(int start,int end,int idx,int upd,int el)
{
  if(start == end)
  {
    seg[idx] = el;
    return ;
  }

  int mid = start + ((end-start)/2);

  if(upd <= mid) // important line 
  {
    update(start,mid,2*idx + 1,upd,el);
  }
  else
  {
    update(mid+1,end,2*idx + 2,upd,el);  
  }
  
  seg[idx] = min(seg[2*idx + 1],seg[2*idx + 2]);
  return ;
}
int32_t main()
{
  c_p_c();

  int n,q;
  cin >> n >> q;

  for(int i=0;i<n;i++)
  {
    cin >> a[i];
  }

  build(0,n-1,0);

  
  while(q--)
  {
    char x;
    int l,r;
    cin >> x >> l >> r;

    if(x == 'q')
    {
      l--,r--;
      cout<<query(0,n-1,l,r,0)<<endl;
    }
    else
    {
      l--;
      update(0,n-1,0,l,r); 
    }
  }
  return 0;
}

