#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <utility>
#include <algorithm>
using namespace std;

//9,3,5,-,2,*,+
//3,-3,-,2,/,10,-

class Solution {
public:
    int CalcExpression(const string &expression)
    {
        int result = 0;

        if(expression.back()>='0'&&expression.back()<='9') return str2int(expression, 0, expression.size()-1);
        
        stack<char> calc;
        stack<int> nums;
        int index = expression.size()-1;
        while(1) {
            int last = index;
            while(index>0&&expression[index-1]!=',') --index;
            
            if(expression[last]>='0'&&expression[last]<='9') {
                int l = str2int(expression, index, last);
                while(calc.size()&&calc.top()=='0') {
                    int r = nums.top();
                    nums.pop();
                    calc.pop();
                    int ans;
                    switch(calc.top()) {
                        case '+': ans = l+r; break;
                        case '-': ans = l-r; break;
                        case '/': ans = l/r; break;
                        case '*': ans = l*r; break;
                        default: break;
                    }
                    calc.pop();
                    l = ans;
                }
                if(calc.empty()) {
                    result = l;
                    break;
                }
                else {
                    nums.push(l);
                    calc.push('0');
                }
            }
            else {
                calc.push(expression[last]);
            }
            index -= 2;            
        }

        return result;
    }
    
    int str2int(const string &expression, int i, int j) {
        return atoi(expression.substr(i, j-i+1).c_str());
    }
};

inline string ReadLine()
{
    string line;
    getline(cin, line);
    return line;
}

int main()
{
    string expression = ReadLine();
    Solution solu;
    int result = solu.CalcExpression(expression);
    cout << result << endl;
    
    return 0;
}
