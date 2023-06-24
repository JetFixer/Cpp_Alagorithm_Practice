#include <vector>
using namespace std;

vector<int> singleNumbers(vector<int>& nums) {
    int num = 0;
    for(const int& i : nums) { num ^= i;}

    for(int o = 1; o <= num; o <<= 1)  {
        if((num ^ o) < num) {
            num = o;
            break;
        }
    }

    vector<int> result{0, 0};
    for(const int& i : nums) {
        if((i & num) == 0) { result[0] ^= i;}
        else { result[1] ^= i;}
    }

    return result;
}

int main() {
    vector<int> nums{1,2,10,4,1,4,3,3};
    singleNumbers(nums);
    return 0;
}