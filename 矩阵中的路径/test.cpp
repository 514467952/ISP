#include<iostream>
#include<vector>
using namespace std;


class person 
{
  public:
    bool hasPath(vector<vector<char>>& matrix, string &str) 
    {
      for(int i = 0 ;i< matrix.size();++i)
        for(int j =0;j< matrix[i].size();++j)
          if(dfs(matrix,str,0,i,j)) return true;
      return false;
    }
    bool dfs(vector<vector<char>>&v,string&s,int u,int x,int y)
    {
      if(v[x][y] != s[u]) return false;
      if(u == s.size()-1) return true;
      char t = v[x][y];
      v[x][y] = '*';
      int dx[4] = {-1,0,1,0};
      int dy[4] = {0,1,0,-1};
      for(int i=0;i<4;++i)
      {
        int a = x+dx[i],b = y+dy[i];
        if(a>=0&&a<v.size() && b>=0&&b<v[a].size())
        {
          if(dfs(v,s,u+1,a,b)) return true;
        }
      }

      v[x][y] =t;
      return false;
    }
};

int main()
{
  return 0;
}
