#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;
int GetLongestFlawedVowelSubstrLen(const size_t flaw, const string& input)
{
    const unordered_set<char> metaChar{'a','e','i','o','u','A','E','I','O','U'};
    int lenMax = 0, crtFlaw = 0;
    int idxl = 0, idxr = 0;
    while(idxl < input.size()&&metaChar.count(input[idxl])==0) {
        ++idxl;
    }
    idxr = idxl;
    
    while(idxr < input.size()) {
        while(idxr < input.size()&&crtFlaw <= flaw) {
            if(crtFlaw == flaw&&metaChar.count(input[idxr])) {
                lenMax = lenMax > idxr - idxl + 1? lenMax : idxr - idxl + 1;
            }

            ++idxr;
            if(idxr < input.size()&&metaChar.count(input[idxr])==0) {
                ++crtFlaw;
            }
        }
        
        if(idxr < input.size()) {
            while(idxl < input.size()&&metaChar.count(input[idxl])) {
                ++idxl;
            }
            while(idxl < input.size()&&metaChar.count(input[idxl])==0) {
                if(idxl <= idxr) {
                    --crtFlaw;
                }
                ++idxl;
            }
            idxr = idxl > idxr ? idxl : idxr;
        }
    }
    
    return lenMax;
}

int main()
{
    size_t flaw;
    cin >> flaw;
  
    string input;
    cin >> input;

    cout << GetLongestFlawedVowelSubstrLen(flaw, input) << endl;
    return 0;
}
