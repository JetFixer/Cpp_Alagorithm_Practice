#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <iomanip>
using namespace std;

class Solution {
public:
    // 待实现函数，在此函数中填入答题代码;
    float PhoneSellManage(float demand, const vector<float> &inventory, const vector<float> &price)
    {
        float salesSam = 0;
        vector<pair<float,int>> orders;
        for(int i=0; i<inventory.size(); ++i) {
            orders.push_back(make_pair(price[i]/inventory[i], i));
        }
        sort(orders.begin(), orders.end());
        
        for(int i=orders.size()-1; i>=0&&demand>0.01; --i) {
            int idx = orders[i].second;
            if(demand - inventory[idx] > -0.01) { 
                salesSam += price[idx];
                demand -= inventory[idx];
            }
            else {
                salesSam += demand * (price[idx] / inventory[idx]);
                break;
            }
        }
        
        return salesSam;
    }
};

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
    int num;
    float demand;
    cin >> num >> demand;
    vector<float> inventory = ReadVector<float>(num);
    vector<float> price = ReadVector<float>(num);
    
    Solution solu;
    float result = solu.PhoneSellManage(demand, inventory, price);
    cout.setf(ios::fixed);
    cout << setprecision(2) << result;
    return 0;
}
