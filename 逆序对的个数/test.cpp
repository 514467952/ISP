#include<iostream>
using namespace std;

const int N =1000010;
int n;
int q[N] ,tmp[N];
int merge_sort(int l,int r)
{
  if(l>=r) return 0;
  int mid = (l+r) >>1;
  int res = merge_sort(l,mid) + merge_sort(mid+1,r);
  
  int k = 0;
  int i = l;
  int j = mid+1;
  while(i<=mid && j<=r)
  {
    if(q[i]<=q[j]) tmp[k++] =q[i++];
    else
    {
      tmp[k++] =q[j++];
      res += mid-i+1;
    }
  }
  while(i<=mid) tmp[k++] =q[i++];
  while(j<=r) tmp[k++] =q[j++];

  for(i=l,j=0;i<=r;++i,++j) q[i] =tmp[j];

  return res;
}
int main()
{
  cin>>n;
  for(int i=0;i<n;++i) cin>>q[i];
  cout << merge_sort(0,n-1);
  return 0;
}
