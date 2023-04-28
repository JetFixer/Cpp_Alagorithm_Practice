
/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description: 上机编程认证
 * Note: 缺省代码仅供参考，可自行决定使用、修改或删除
 */
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <utility>
#include <algorithm>
using namespace std;

class Solution {
public:
    // 待实现函数，在此函数中填入答题代码;
    vector<char> GetNTimesCharacter(int n, const vector<string> &strings)
    {
        vector<char> result;
        
        unordered_map<char, int> charTimes;
        for(const char &ch: strings.front()) {
            ++charTimes[ch];
        }
        
        for(auto it=strings.begin()+1; it!=strings.end(); ++it) {
            unordered_map<char, int> temp;
            for(const char &ch: *it) {
                if(charTimes.count(ch)&&charTimes[ch]>1) {
                    ++temp[ch];
                }
            }
            charTimes = temp;
        }
        
        for(char ch='0'; ch <='9'; ++ch) {
            if(charTimes.count(ch)&&charTimes[ch]>1) {
                result.push_back(ch);
            }
        }
        for(char ch='A'; ch <='Z'; ++ch) {
            if(charTimes.count(ch)&&charTimes[ch]>1) {
                result.push_back(ch);
            }
        }
        for(char ch='a'; ch <='z'; ++ch) {
            if(charTimes.count(ch)&&charTimes[ch]>1) {
                result.push_back(ch);
            }
        }
        
        return result;
    }
};

inline int ReadInt()
{
    int number;
    cin >> number;
    return number;
}

template<typename T>
inline vector<T> ReadVector(int size)
{
    vector<T> objects(size);
    for (int i = 0; i < size; ++i) {
        cin >> objects[i];
    }
    return objects;
}

template<typename T>
inline void WriteVector(const vector<T>& objects, char delimeter = ' ')
{
    auto it = objects.begin();
    if (it == objects.end()) {
        return;
    }
    cout << *it;
    for (++it; it != objects.end(); ++it) {
        cout << delimeter << *it;
    }
}

int main()
{   
    int n = ReadInt();
    int m = ReadInt();
    vector<string> strings = ReadVector<string>(m);
    
    Solution solu;
    auto result = solu.GetNTimesCharacter(n, strings);
    cout << "[";
    WriteVector(result);
    cout << "]" << endl;
    return 0;
}
