#include <iostream>
#include <string>
#include <utility>
#include <algorithm>
using namespace std;

class Solution {
public:
    // 待实现函数，在此函数中填入答题代码;
    string GetHexString(long long input)
    {
        string result;
        
        if(input/0xFFFFFFFF!=0) {
            result = "overflow";
            return result;
        }
        
        string strInteger;
        while(strInteger.size()<8&&input!=0) {
            int last = input & 0xF;
            switch(last) {
                case 10: strInteger.push_back('A'); break;
                case 11: strInteger.push_back('B'); break;
                case 12: strInteger.push_back('C'); break;
                case 13: strInteger.push_back('D'); break;
                case 14: strInteger.push_back('E'); break;
                case 15: strInteger.push_back('F'); break;
                default: strInteger.push_back(last+'0'); break;
            }
            input = input >> 4;
        }
        
        while(strInteger.size()<8) {
            strInteger.push_back('0');
        }
        
        reverse(strInteger.begin(),strInteger.end());
        string minusInteger = strInteger.substr(6,2)+strInteger.substr(4,2)+strInteger.substr(2,2)+strInteger.substr(0,2);
        
        strInteger.insert(6," ");
        strInteger.insert(4," ");
        strInteger.insert(2," ");
        minusInteger.insert(6," ");
        minusInteger.insert(4," ");
        minusInteger.insert(2," ");
        
        result = strInteger + "\n" + minusInteger;
        return result;
    }
};

int main()
{   
    long long input;
    cin >> input;
    
    Solution solu;
    string result = solu.GetHexString(input);
    cout << result;
    return 0;
}

