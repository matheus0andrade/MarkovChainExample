#include <bits/stdc++.h>
using namespace std;

int cnt = 1;
vector<int> sum;
vector<vector<int>> adj;
unordered_map<string, int> mp;
vector<string> rev;

vector<string> fix(string s) {
    vector<string> ans;
    string cur = "";
    for(int i = 0; i < s.size(); i++) {
        if(s[i] >= 'A' && s[i] <= 'Z') {
            cur += (s[i] - 'A' + 'a');
            continue;
        }
        if(s[i] >= 'a' && s[i] <= 'z') {
            cur += s[i];
            continue;
        }
        if(s[i] == '.' or s[i] == '!' or s[i] == '?') {
            if(cur != "")
                ans.push_back(cur);
            ans.push_back(".");
            cur.clear();
            continue;
        }
        if(s[i] == ',') {
            if(cur != "")
                ans.push_back(cur);
            ans.push_back(",");
            cur.clear();
            continue;
        }
        if(s[i] == ' ') {
            if(cur != "")
                ans.push_back(cur);
            cur = "";
            continue;
        }
        cur += s[i];
    }
    if(cur != "")
        ans.push_back(cur);

    return ans;
}

void read(ifstream &file) {
    string s = "", last = ".", tot = "";
    bool start = true;
    while(file >> s) {
        vector<string> v = fix(s);
        for(int i = 0; i < v.size(); i++) {
            if(!mp[v[i]]) {
                mp[v[i]] = ++cnt;
                sum.push_back(0);
                adj.push_back(vector<int>());
                rev.push_back(v[i]);
            }
            if(v[i] == ".") {
                start = true;
                sum[mp[last]]++;
                adj[mp[last]].push_back(1);
                last = v[i];
                continue;
            }
            adj[mp[last]].push_back(mp[v[i]]);
            sum[mp[last]]++;
            last = v[i];
        }
    }
    if(last != ".") {
        adj[mp[last]].push_back(1);
        sum[mp[last]]++;
    }
}

int main() {
    rev.resize(2);
    adj.resize(2);
    sum.resize(2);
    srand(time(NULL));
    rev[1] = ".";
    mp["."] = 1;
    ifstream in("input.txt");
    ofstream out("output.txt");
    read(in);
    for(int j = 0; j < 10; j++) {
        int cur = 1;
        for(int i = 0; i < 30; i++) {
            int x = rand() % sum[cur];
            if(adj[cur][x] == 1 && i < 10) {
                continue;
            }
            cur = adj[cur][x];
            out << (cur != 1 && i && rev[cur] != "," ? " " : "") << rev[cur];
            if(cur == 1)
                break;
        }
        out << "\n";
    }
    in.close();
    out.close();
    return 0;
}