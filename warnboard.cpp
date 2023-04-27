
/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description: 上机编程认证
 * Note: 缺省代码仅供参考，可自行决定使用、修改或删除
 */
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue>
using namespace std;

class Solution {
public:
    // 待实现函数，在此函数中填入答题代码;
    vector<string> GetAllFault(const vector<string> &arrayA, const vector<string> &arrayB)
    {
        vector<string> result;
        
        priority_queue<string, vector<string>, greater<string>> temp;
        
        for(const string& str: arrayA) {
            temp.push(str);
        }
        for(const string& str: arrayB) {
            temp.push(str);
        }
        
        while(temp.size()) {
            string tmp = temp.top();
            temp.pop();
            if(result.size()&&tmp==result.back()) {
                continue;
            }
            result.push_back(tmp);
        }
        
        return result;
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

template<typename T>
inline void WriteVector(const std::vector<T>& objects, char delimeter = ' ')
{
    auto it = objects.begin();
    if (it == objects.end()) {
        return;
    }
    std::cout << *it;
    for (++it; it != objects.end(); ++it) {
        std::cout << delimeter << *it;
    }
}

int main()
{
    int arrayANum = ReadInt();
    vector<string> arrayA = ReadVector<string>(arrayANum);
    int arrayBNum = ReadInt();
    vector<string> arrayB = ReadVector<string>(arrayBNum);

    Solution solu;
    auto result = solu.GetAllFault(arrayA, arrayB);
    cout << "[";
    WriteVector(result, ' ');
    cout << "]" << endl;
    return 0;
}
