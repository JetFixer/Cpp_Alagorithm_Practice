#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>
#include <set>
using namespace std;

class Solution {
public:
    // 待实现函数，在此函数中填入答题代码
    int GetMaxSendNum(int cap, const vector<int> &bill, const vector<int> &pri)
    {
        map<int, multiset<int>> list;
        
        for(int i=0; i<bill.size(); ++i) {
            list[pri[i]].insert(bill[i]);
        }
        
        int count = 0;
        for(int i=0; i<=30; ++i) {
            if(!list.count(i)) continue;
            for(auto it=list[i].begin(); it!=list[i].end(); ++it) {
                if(*it<cap) {
                    ++count;
                    cap -= *it;
                }
                else return count;
            }
        }
        
        return -1;
    }
};

// 以下为考题输入输出框架，此部分代码不建议改动
inline int ReadInt()
{
    int number;
    std::cin >> number;
    return number;
}

template<typename T>
inline std::vector<T> ReadVector(int size)
{
    std::vector<T> objects(size);
    for (int i = 0; i < size; ++i) {
        std::cin >> objects[i];
    }
    return objects;
}

int main()
{
    int cap = ReadInt();
    int n = ReadInt();
    vector<int> bill = ReadVector<int>(n);
    vector<int> pri = ReadVector<int>(n);
    Solution solu;
    int res = solu.GetMaxSendNum(cap, bill, pri);
    cout << res;
    return 0;
}
