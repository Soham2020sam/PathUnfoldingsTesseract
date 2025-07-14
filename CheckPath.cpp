#include<bits/stdc++.h>
using namespace std;
int n, m;
string verticesTesseract[] = {"ABCD", "ABba", "BCcb", "DCcd", "abcd", "ADda", "EFGH", "EFfe", "FGgf", "HGgh", "efgh", "EHhe", "BCGF", "BbfF", "ABFE", "EHDA", "AEea", "abfe", "adhe", "DHhd", "cdhg", "gfbc", "CGgc", "CDHG"};
map<string, vector<string> > edges;
vector<vector<char> > grid;
vector<vector<char> > grid2;
vector<set<pair<int, string> > > adj;
void read(){
    ifstream cin("unfoldings.in");
    string s;
    cin >> s;
    int idx1 = 0;
    int idx2 = 0;
    for(int i = 0; i < (int)s.size(); i++){
        if(s[i] == '['){
            idx1 = i;
            break;
        }
    }
    for(int i = (int)s.size() - 1; i >= 0; i--){
        if(s[i] == ']'){
            idx2 = i;
            break;
        }
    }
    vector<vector<char> > v2;
    string k = "";
    for(int i = idx1 + 2; i < idx2; i++){
        if(s[i] == ']'){
            vector<char> x;
            for(int j = 0; j < (int)k.size(); j++){
                if(k[j] == '"' || k[j] == ','){
                    continue;
                }
                else{
                    if(k[j] == '?'){
                        x.push_back('?');
                    }
                    else{
                        x.push_back('g');
                        j++;
                    }
                }
            }
            v2.push_back(x);
            i += 2;
            k = "";
        }
        else{
            k += s[i];
        }
    }
    grid2.resize((int)v2[0].size(), vector<char>((int)v2.size()));
    for(int i = 0; i < (int)v2.size(); i++){
        for(int j = 0; j < (int)v2[i].size(); j++){
            grid2[j][i] = v2[i][j];
        }
    }
}
void doubleGrid(){
    grid.resize(4 * (int)grid2.size(), vector<char>(4 * (int)grid2[0].size()));
    n = grid.size();
    m = grid[0].size();
    for(int i = 0; i < grid2.size(); i++){
        for(int j = 0; j < grid2[0].size(); j++){
            if(grid2[i][j] == '?'){
                for(int k = 0; k <= 3; k++){
                    for(int l = 0; l <= 3; l++){
                        grid[4 * i + k][4 * j + l] = 'x';
                    }
                }
            }
            else{
                grid[4 * i][4 * j] = '+';
                grid[4 * i + 3][4 * j] = '+';
                grid[4 * i][4 * j + 3] = '+';
                grid[4 * i + 3][4 * j + 3] = '+';
                grid[4 * i][4 * j + 1] = '-';
                grid[4 * i][4 * j + 2] = '-';
                grid[4 * i + 3][4 * j + 1] = '-';
                grid[4 * i + 3][4 * j + 2] = '-';
                grid[4 * i + 1][4 * j] = '|';
                grid[4 * i + 2][4 * j] = '|';
                grid[4 * i + 1][4 * j + 3] = '|';
                grid[4 * i + 2][4 * j + 3] = '|';
                for(int k = 1; k <= 2; k++){
                    for(int l = 1; l <= 2; l++){
                        grid[4 * i + k][4 * j + l] = 'x';
                    }
                }
            }
        }
    }
    for(int i = 0; i < (int)grid.size(); i++){
        for(int j = 0; j < (int)grid[0].size(); j++){
            cout << grid[i][j];
        }
        cout << "\n";
    }
}
vector<vector<string> > recurse(string cur, vector<bool> visited, map<string, bool> visited2, int idx){
    visited[idx] = true;
    string c = cur;
    sort(c.begin(), c.end());
    visited2[c] = true;
    vector<vector<string> > curPath;
    for(pair<int, string> v : adj[idx]){
        if(visited[v.first]){
            continue;
        }
        assert(v.first != idx);
        if(v.second == "N"){
            string edge;
            edge += cur[0];
            edge += cur[1];
            for(string a : edges[edge]){
                string b = a;
                sort(b.begin(), b.end());
                if(visited2[b]){
                    continue;
                }
                string thing = a;
                string res = "";
                for(int k = 0; k < 4; k++){
                    if(thing[2] == cur[1] && thing[3] == cur[0]){
                        res = thing;
                        vector<vector<string> > y = recurse(res, visited, visited2, v.first);
                        for(vector<string> y2 : y) curPath.push_back(y2);
                        break;
                    }
                    rotate(thing.begin(), thing.begin() + 1, thing.end());
                }
                reverse(thing.begin(), thing.end());
                for(int k = 0; k < 4; k++){
                    if(thing[2] == cur[1] && thing[3] == cur[0]){
                        res = thing;
                        vector<vector<string> > y = recurse(res, visited, visited2, v.first);
                        for(vector<string> y2 : y) curPath.push_back(y2);
                        break;
                    }
                    rotate(thing.begin(), thing.begin() + 1, thing.end());
                }
            }
        }
        if(v.second == "E"){
            string edge;
            edge += cur[1];
            edge += cur[2];
            for(string a : edges[edge]){
                string b = a;
                sort(b.begin(), b.end());
                if(visited2[b]){
                    continue;
                }
                string thing = a;
                string res = "";
                for(int k = 0; k < 4; k++){
                    if(thing[0] == cur[1] && thing[3] == cur[2]){
                        res = thing;
                        vector<vector<string> > y = recurse(res, visited, visited2, v.first);
                        for(vector<string> y2 : y) curPath.push_back(y2);
                        break;
                    }
                    rotate(thing.begin(), thing.begin() + 1, thing.end());
                }
                reverse(thing.begin(), thing.end());
                for(int k = 0; k < 4; k++){
                    if(thing[0] == cur[1] && thing[3] == cur[2]){
                        res = thing;
                        vector<vector<string> > y = recurse(res, visited, visited2, v.first);
                        for(vector<string> y2 : y) curPath.push_back(y2);
                        break;
                    }
                    rotate(thing.begin(), thing.begin() + 1, thing.end());
                }
            }
        }
        if(v.second == "S"){
            string edge;
            edge += cur[2];
            edge += cur[3];
            for(string a : edges[edge]){
                string b = a;
                sort(b.begin(), b.end());
                if(visited2[b]){
                    continue;
                }
                string thing = a;
                string res = "";
                for(int k = 0; k < 4; k++){
                    if(thing[1] == cur[2] && thing[0] == cur[3]){
                        res = thing;
                        vector<vector<string> > y = recurse(res, visited, visited2, v.first);
                        for(vector<string> y2 : y) curPath.push_back(y2);
                        break;
                    }
                    rotate(thing.begin(), thing.begin() + 1, thing.end());
                }
                reverse(thing.begin(), thing.end());
                for(int k = 0; k < 4; k++){
                    if(thing[1] == cur[2] && thing[0] == cur[3]){
                        res = thing;
                        vector<vector<string> > y = recurse(res, visited, visited2, v.first);
                        for(vector<string> y2 : y) curPath.push_back(y2);
                        break;
                    }
                    rotate(thing.begin(), thing.begin() + 1, thing.end());
                }
            }
        }
        if(v.second == "W"){
            string edge;
            edge += cur[3];
            edge += cur[0];
            for(string a : edges[edge]){
                string b = a;
                sort(b.begin(), b.end());
                if(visited2[b]){
                    continue;
                }
                string thing = a;
                string res = "";
                for(int k = 0; k < 4; k++){
                    if(thing[2] == cur[3] && thing[1] == cur[0]){
                        res = thing;
                        vector<vector<string> > y = recurse(res, visited, visited2, v.first);
                        for(vector<string> y2 : y) curPath.push_back(y2);
                        break;
                    }
                    rotate(thing.begin(), thing.begin() + 1, thing.end());
                }
                reverse(thing.begin(), thing.end());
                for(int k = 0; k < 4; k++){
                    if(thing[2] == cur[3] && thing[1] == cur[0]){
                        res = thing;
                        vector<vector<string> > y = recurse(res, visited, visited2, v.first);
                        for(vector<string> y2 : y) curPath.push_back(y2);
                        break;
                    }
                    rotate(thing.begin(), thing.begin() + 1, thing.end());
                }

            }
        }
    }
    if(curPath.empty()){
        vector<string> y2(24);
        y2[idx] = cur;
        curPath.push_back(y2);
        return curPath;
    }
    else{
        vector<vector<string> > thingy;
        for(vector<string>& y2 : curPath){
            y2[idx] = cur;
            set<string> s;
            int val = 0;
            for(int j = 0; j < 24; j++){
                if(!y2[j].empty()){
                    s.insert(y2[j]);
                    val++;
                }
            }
            if((int)s.size() == val){
                thingy.push_back(y2);
            }
        }
        return thingy;
    }
}
int main(){
    read();
    doubleGrid();
    cout << n << " " << m << "\n";
    for(int i = 0; i < 24; i++){
        for(int j = 0; j < 4; j++){
            string s = "";
            s += verticesTesseract[i][j];
            s += verticesTesseract[i][(j + 1) % 4];
            edges[s].push_back(verticesTesseract[i]);
            reverse(s.begin(), s.end());
            edges[s].push_back(verticesTesseract[i]);
        }
    }
    vector<pair<int, int> > squares;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(grid[i][j] == '+'){
                if(grid[i][j + 1] == '-'
                && grid[i][j + 2] == '-'
                && grid[i][j + 3] == '+'
                && grid[i + 1][j] == '|'
                && grid[i + 2][j] == '|'
                && grid[i + 3][j] == '+'
                && grid[i + 3][j + 1] == '-'
                && grid[i + 3][j + 2] == '-'
                && grid[i + 1][j + 3] == '|'
                && grid[i + 2][j + 3] == '|'
                && grid[i + 3][j + 3] == '+'){
                    squares.push_back(make_pair(i, j));
                }
            }
        }
    }
    assert((int)squares.size() == 24);
    adj.resize((int)squares.size());
    vector<vector<string> > dir((int)squares.size(), vector<string>((int)squares.size(), ""));
    for(int i = 0; i < (int)squares.size(); i++){
        for(int j = 0; j < (int)squares.size(); j++){
            if(squares[i].first - squares[j].first == 4 && squares[i].second == squares[j].second){
                adj[i].insert(make_pair(j, "N"));
                dir[i][j] = "N";
            }
            if(squares[j].first - squares[i].first == 4  && squares[i].second == squares[j].second){
                adj[i].insert(make_pair(j, "S"));
                dir[i][j] = "S";
            }
            if(squares[i].second - squares[j].second == 4  && squares[i].first == squares[j].first){
                adj[i].insert(make_pair(j, "W"));
                dir[i][j] = "W";
            }
            if(squares[j].second - squares[i].second == 4  && squares[i].first == squares[j].first){
                adj[i].insert(make_pair(j, "E"));
                dir[i][j] = "E";
            }
        }
    }
    int idx = -1;
    for(int i = 0; i < (int)squares.size(); i++){
        if(adj[i].size() == 1){
            idx = i;
            break;
        }
    }
    if(idx != -1){
        vector<bool> visited(24, false);
        map<string, bool> visited2;
        vector<vector<string> > a = recurse("ABCD", visited, visited2, idx);
        bool works = false;
        int soFar = 0;
        vector<string> maximal;
        if(!a.empty()){
            for(vector<string> v : a){
                int values = 24;
                bool cool = true;
                for(int r = 0; r < 24; r++){
                    if(v[r].empty()){
                        values--;
                        cool = false;
                        // break;
                    }
                }
                if(values > soFar){
                    maximal = v;
                    soFar = values;
                }
                if(cool){
                    works = true;
                    break;
                }
            }
        }
        for(string c : maximal){
            cout << c << "\n";
        }
        if(works){
            cout << "Unfolding works!\n";
        }
        else{
            cout << "Does not fold\n";
        }
    }
    else{
        bool works = false;
        int soFar = 0;
        vector<string> maximal;
        for(int i = 0; i < (int)squares.size(); i++){
            for(int j = i + 1; j < (int)squares.size(); j++){
                if((int)dir[i][j].size() != 0){
                    adj[i].erase(make_pair(j, dir[i][j]));
                    adj[j].erase(make_pair(i, dir[j][i]));
                    vector<bool> visited(24, false);
                    map<string, bool> visited2;
                    vector<vector<string> > a = recurse("ABCD", visited, visited2, i);
                    int idxVal = -1;
                    if(!a.empty()){
                        for(int k = 0; k < (int)a.size(); k++){
                            vector<string> v = a[k];
                            bool cool = true;
                            int values = 24;
                            for(int r = 0; r < 24; r++){
                                if(v[r].empty()){
                                    cool = false;
                                    values--;
                                }
                            }
                            if(values > soFar){
                                maximal = v;
                                soFar = values;
                            }
                            if(cool){
                                idxVal = k;
                                works = true;
                                break;
                            }
                        }
                    }
                    adj[i].insert(make_pair(j, dir[i][j]));
                    adj[j].insert(make_pair(i, dir[j][i]));
                    if(works){
                        cout << i << " " << j << "\n";
                        cout << "Unfolding works!\n";
                        for(string val : a[idxVal]){
                            cout << val << "\n";
                        }
                        break;
                    }
                }
            }
            if(works){
                break;
            }
        }
        if(!works){
            for(string c : maximal){
                cout << c << "\n";
            }
            cout << "Does not fold\n";
        }
    }
}