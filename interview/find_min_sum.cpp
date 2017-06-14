#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int abs(int a) {
  return a>0?a:-a;
}

class Solution {
public:
    /**
     * @param nums: A list of integers
     * @return: A list of integers includes the index of the first number 
     *          and the index of the last number
     */
    vector<int> subarraySumClosest(vector<int> nums){
        // write your code here
        vector<pair<int,int> > vi; 
        for(int i = 0; i < nums.size();++i) {
            if(i>0) nums[i] += nums[i-1];
            vi.push_back(make_pair(nums[i],i));
            printf("%d %d\n",i,nums[i]);
        }
        sort(vi.begin(),vi.end());
        vector<int> res;
        if(nums.size()<1) return res;
        //-3 -2 -1 -4 1
        //-4 -3 -2 -1 1
        int ans(abs(vi[0].first)), j(0),k(vi[0].second);
        for(int i = 1; i < vi.size();++i){
          int tmp=vi[i].second>vi[i-1].second?vi[i].first-vi[i-1].first:
                                                            vi[i-1].first-vi[i].first;
          tmp=abs(tmp);
            if(tmp< ans){
                ans=tmp;
                j=max(vi[i].second,vi[i-1].second);
                k=min(vi[i].second,vi[i-1].second)+1;
            }
            if(abs(vi[i].first) < ans){
                ans=abs(vi[i].first);
                j=0;
                k=vi[i].second;
            }
            if(i>0) {
              printf("%d %d %d %d\n",i,ans,vi[i].first,abs(vi[i].first-vi[i-1].first));
              printf("%d %d\n",vi[i].second,vi[i-1].second);
            }
        }
        //printf("%d\n",ans);
        if(j>k) swap(j,k);
        res.push_back(j);
        res.push_back(k);
        return res;
    }
};


int main()
{
  int a[] = {101,33,44,55,67,78,-101,33,-44,55,-67,78,-100,200,-1000,22,100,200,1000,22};
  vector<int> res(a,a+sizeof(a)/sizeof(int));
  Solution  s;
  s.subarraySumClosest(res);
}
/* sw=2;ts=2;sts=2;expandtab */
