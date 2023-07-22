#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void MergeSort(vector<int>& nums, int i, int j)
    {
        if(i >= j) { return;}
        int mid = (i + j) / 2;
        MergeSort(nums, i, mid);
        MergeSort(nums, mid + 1, j);

        vector<int> left(nums.begin() + i, nums.begin() + mid + 1);
        vector<int> right(nums.begin() + mid + 1, nums.begin() + j + 1);

        int l = 0, r = 0, pos = i;
        while(pos <= j && l < mid - i + 1 && r < j - mid) {
            int lastl = l, lastr = r;

            while(r < j - mid && left[l] <= right[r]) { ++r;}
            copy(right.begin() + lastr, right.begin() + r, nums.begin() + pos);
            pos += r - lastr;
            
            if(r >= j - mid) { break;}
            while(l < mid - i + 1 && left[l] > right[r]) { ++l;}
            copy(left.begin() + lastl, left.begin() + l, nums.begin() + pos);
            pos += l - lastl;

            cnt += (j - mid - r) * (l - lastl);
        }

        copy(left.begin() + l, left.end(), nums.begin() + pos);
        copy(right.begin() + r, right.end(), nums.begin() + pos);

        return;
    }

    int reversePairs(vector<int>& nums)
    {
        MergeSort(nums, 0, nums.size() - 1);
        return cnt;
    }

private:
    int cnt = 0;
};

int main()
{
    Solution s;
    vector<int> ans{4, 5, 6, 7};
    int res = s.reversePairs(ans);
    return 0;
}
