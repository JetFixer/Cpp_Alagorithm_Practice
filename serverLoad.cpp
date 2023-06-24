#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Message {
    int start;
    int load;
};

bool cmp(const Message& a, const Message& b) {
    return a.start < b.start;
}

struct SvrWork {
    int index;
    int timeNode;
};

auto SvrOrder = [](const SvrWork& a, const SvrWork& b) {
    if(a.timeNode != b.timeNode) return a.timeNode > b.timeNode;
    return a.index > b.index;
};

class Solution {
public:
    vector<int> FindHighestLoadServers(int serverNum, const vector<Message> &messages)
    {
        vector<int> result(serverNum + 1, 0);
        int maxLoad = 0;
        vector<Message> messageSorted(messages);
        sort(messageSorted.begin(), messageSorted.end(), cmp);
        
        priority_queue<SvrWork, vector<SvrWork>, decltype(SvrOrder)> serverQue(SvrOrder);
        for(int i=1; i<=serverNum; ++i) {
            SvrWork sw;
            sw.index = i;
            sw.timeNode = 0;
            serverQue.push(sw);
        }
        for(const Message& msg:messageSorted) {
            if(msg.start < serverQue.top().timeNode) { continue;}
            SvrWork tmp = serverQue.top();
            serverQue.pop();
            result[tmp.index] += msg.load;
            maxLoad = maxLoad > result[tmp.index]?maxLoad : result[tmp.index];
            tmp.timeNode = msg.start + msg.load;
            serverQue.push(tmp);
        }
        
        vector<int> svrList;
        for(int i=1; i<=serverNum; ++i) {
            if(result[i] == maxLoad) { svrList.push_back(i);}
        }
        return svrList;
    }
};

inline int ReadInt()
{
    int number;
    cin >> number;
    return number;
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
    cout << endl;
}

int main()
{
    int serverNum = ReadInt();
    int n = ReadInt();
    vector<Message> msgs;
    for (int i = 0; i < n; ++i) {
        Message obj;
        cin >> obj.start >> obj.load;
        msgs.push_back(obj);
    }

    Solution solu;
    vector<int> result = solu.FindHighestLoadServers(serverNum, msgs);
    WriteVector(result, ' ');

    return 0;
}

