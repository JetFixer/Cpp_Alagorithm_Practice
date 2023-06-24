#include <iostream>
#include <string>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;

class MiniDhcpServer {
public:
    unordered_map<string, int> mactab;
    vector<string> isvalid;
    string preip = "192.168.0.";
    int idx = 0, isfull = 0;

    MiniDhcpServer()
    {
        isvalid.resize(256, "0");
    }
    
    string Request(const string &mac)
    {      
        if(mactab.count(mac)) {
            int nip = mactab[mac];
            if(isvalid[nip] == mac) { return preip + to_string(nip);}
            if(isvalid[nip] == "0") {
                isvalid[nip] = mac;
                ++isfull;
                return preip + to_string(nip);
            }
        }
        
        if(isfull == 256) return "NA";
        if(idx < 256) {
            mactab[mac] = idx;
            isvalid[idx] = mac;
            ++isfull;
            ++idx;
            return preip + to_string(idx-1);
        }
        
        for(int i=0; i<256; ++i) {
            if(isvalid[i] == "0") {
                isvalid[i] = mac;
                mactab[mac] = i;
                ++isfull;
                return preip + to_string(i);
            }
        }
        
        return "";
    }

    void Release(const string &mac)
    {
        if(mactab.count(mac)) {
            isvalid[mactab[mac]] = "0";
            --isfull;
        }
    }
};

int main()
{
    int line;
    cin >> line;

    MiniDhcpServer dhcp;
    for (int loop = 0; loop < line; loop++) {
        string str;
        cin >> str;
        string opration = str.substr(0, str.find_first_of("="));
        string mac = str.substr(str.find_first_of("=") + 1);

        if (opration == "REQUEST") {
            cout << dhcp.Request(mac) << endl;
        } else if (opration == "RELEASE") {
            dhcp.Release(mac);
        }
    }

    return 0;
}
