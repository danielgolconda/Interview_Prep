/* 1) - Sum of the elements in the range [L,R] 
  2) - point updates
  3) range update with increment 
*/
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
int a[MAXN],seg[4*MAXN];

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

  seg[idx] = seg[2*idx + 1] + seg[2*idx + 2];
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
    return 0;
  }

  int mid = start + ((end-start)/2);

  int lans = query(start,mid,l,r,2*idx + 1);
  int rans = query(mid+1,end,l,r,2*idx + 2);

  return lans + rans;
}

void update(int start,int end,int idx,int pos,int upd)
{

  if(start == end)
  {
    seg[idx] = upd;
    return ;
  }

  int mid = start + ((end-start)/2);

  if(pos <= mid)
  {
    update(start,mid,2*idx + 1,pos,upd);
  }
  else
  {
    update(mid+1,end,2*idx + 2,pos,upd);
  }

  seg[idx] = seg[2*idx + 1] + seg[2*idx + 2];
  return ;
}

void updateRange(int start,int end,int idx,int l,int r,int upd)
{
  // sequence important
  // first - outof bounds
  if(start > r || end < l)
  {
    return ;
  }
  // Leaf element
  if(start == end)
  {
    seg[idx] = upd;
    return ;
  }

  // recursive case
  int mid = start + ((end-start)/2);

  updateRange(start,mid,2*idx + 1,l,r,upd);
  updateRange(mid+1,end,2*idx + 2,l,r,upd);

  seg[idx] = seg[2*idx + 1] + seg[2*idx + 2];
  return ;
}
int32_t main()
{
  c_p_c();
  int n;
  cin >> n;

  for(int i=0;i<n;i++)
  {
    cin >> a[i];
  }

  build(0,n-1,0);
  int q;
  cin >> q;
  while(q--)
  {
    int type;
    cin >> type;
    if(type == 1)
    {
      // sum of the elements in the range [L,R]
      int l,r;
      cin >> l >> r;
      l--,r--;
      cout<<query(0,n-1,l,r,0)<<endl;
    }
    else if(type == 2)
    {
      // point updates A[x] += y
      int x,y;
      cin >> x >> y;
      x--;
      update(0,n-1,0,x,y);
    }
    else
    {
      // Range updates A[L:R] += y;
      int l,r,y;
      cin >> l >> r >> y;
      l--,r--;
      updateRange(0,n-1,0,l,r,y);
    }
  }
  return 0;
}

