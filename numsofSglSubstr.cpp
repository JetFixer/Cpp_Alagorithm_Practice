#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int GetCountOfSubString(const string &input)
    {        
        int total = 0;
        int l=0, r=1;
        unordered_set<char> subs{input[0]};
        
        while(l < input.size()) {
            while(r < input.size()&&subs.count(input[r]) == 0) {
                subs.insert(input[r++]);
            }
            total += r-l;
            subs.erase(input[l++]);
        }
        
        return total;
    }
};

int main()
{
    string input;
    cin >> input;

    Solution solu;
    cout << solu.GetCountOfSubString(input) << endl;

    return 0;
}

