#include<iostream>
using namespace std;

const int N =100;
int tmp[N];
void merge_sort(int a[],int l,int r)
{
  if(l>=r) return;
  int mid = (l+r)>>1;
  merge_sort(a,l,mid);
  merge_sort(a,mid+1,r);

  int k =0;
  int i = l;
  int j = mid+1;
  while(i<=mid&&j<=r)
  {
    if(a[i] < a[j]) tmp[k++] = a[i++];
    else tmp[k++] = a[j++];
  }
  while(i<=mid) tmp[k++] =a[i++];
  while(j<=r)  tmp[k++] = a[j++];

  for(i=l,j=0;i<=r;++i,++j) a[i] =tmp[j];
}

int main()
{
  int a[] ={3,2,5,8,4,7,6,9};
  merge_sort(a,0,7);
  for(int i=0;i<8;++i) 
      cout<<a[i]<<" ";
  cout<<endl;
  return 0;
}
