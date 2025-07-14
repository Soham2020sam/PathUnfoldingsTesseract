#include<bits/stdc++.h>
using namespace std;
vector<vector<pair<int, int> > > allPosPaths;
vector<vector<string> > stringPath;
int dx[] = {1, 0, 1};
int dy[] = {0, 1, 1};
string verticesTesseract[] = {"ABCD", "ABba", "BCcb", "DCcd", "abcd", "ADda", "EFGH", "EFfe", "FGgf", "HGgh", "efgh", "EHhe", "BCGF", "BbfF", "ABFE", "EHDA", "AEea", "abfe", "adhe", "DHhd", "cdhg", "gfbc", "CGgc", "CDHG"};
map<string, int> vertices;
bool face(string x){
    for(int i = 0; i < 4; i++){
        if(vertices[x.substr(i) + x.substr(0, i)] != 0){
            return true;
        }
    }
    reverse(x.begin(), x.end());
    for(int i = 0; i < 4; i++){
        if(vertices[x.substr(i) + x.substr(0, i)] != 0){
            return true;
        }
    }
    return false;
}
vector<string> possible(string s){
    vector<string> ans;
    for(int i = 0; i < 4; i++){
        ans.push_back(s.substr(i) + s.substr(0, i));
    }
    reverse(s.begin(), s.end());
    for(int i = 0; i < 4; i++){
        ans.push_back(s.substr(i) + s.substr(0, i));
    }
    return ans;
}
void formPaths(){
    vector<int> adj[6];
    adj[0].push_back(1);
    adj[0].push_back(2);
    adj[0].push_back(3);
    adj[0].push_back(4);
    adj[5].push_back(1);
    adj[5].push_back(2);
    adj[5].push_back(3);
    adj[5].push_back(4);
    adj[1].push_back(0);
    adj[1].push_back(2);
    adj[1].push_back(4);
    adj[1].push_back(5);
    adj[2].push_back(0);
    adj[2].push_back(1);
    adj[2].push_back(3);
    adj[2].push_back(5);
    adj[3].push_back(0);
    adj[3].push_back(2);
    adj[3].push_back(4);
    adj[3].push_back(5);
    adj[4].push_back(0);
    adj[4].push_back(1);
    adj[4].push_back(3);
    adj[4].push_back(5);
    pair<int, int> val[] = {make_pair(0, 1), make_pair(0, 2), make_pair(0, 3), make_pair(1, 2), make_pair(1, 3), make_pair(2, 3)};
    pair<int, int> val2[] = {make_pair(2, 3), make_pair(1, 3), make_pair(1, 2), make_pair(0, 3), make_pair(0, 2), make_pair(0, 1)};
    for(int n1 = 0; n1 < 6; n1++){
        for(int n2 = 0; n2 < 6; n2++){
            for(int n3 = 0; n3 < 6; n3++){
                for(int n4 = 0; n4 < 6; n4++){
                    for(int n5 = 0; n5 < 6; n5++){
                        for(int n6 = 0; n6 < 6; n6++){
                            int nodes[] = {n1, n2, n3, n4, n5, n6};
                            int prevnode = 0;
                            int curnode = 0;
                            vector<pair<int, int> > path;
                            path.push_back(make_pair(0, 0));
                            map<pair<int, int>, int> val3;
                            int curColor = 0;
                            val3[make_pair(curnode, curColor)]++;
                            curnode = adj[curnode][val[n1].first];
                            curColor++;
                            curColor %= 2;
                            bool works = true;
                            while(val3[make_pair(curnode, curColor)] != 1){
                                path.push_back(make_pair(curnode, curColor));
                                val3[make_pair(curnode, curColor)]++;
                                int thing = curnode;
                                if(curColor == 0){
                                    if(adj[curnode][val[nodes[curnode]].first] == prevnode){
                                        curColor += 1;
                                        curColor %= 2;
                                        curnode = adj[curnode][val[nodes[curnode]].second];
                                    }
                                    else if(adj[curnode][val[nodes[curnode]].second] == prevnode){
                                        curColor += 1;
                                        curColor %= 2;
                                        curnode = adj[curnode][val[nodes[curnode]].first];
                                    }
                                    else{
                                        works = false;
                                        break;
                                    }
                                }
                                else{
                                    if(adj[curnode][val2[nodes[curnode]].second] == prevnode){
                                        curColor += 1;
                                        curColor %= 2;
                                        curnode = adj[curnode][val2[nodes[curnode]].first];
                                    }
                                    else if(adj[curnode][val2[nodes[curnode]].first] == prevnode){
                                        curColor += 1;
                                        curColor %= 2;
                                        curnode = adj[curnode][val2[nodes[curnode]].second];
                                    }
                                    else{
                                        works = false;
                                        break;
                                    }
                                }
                                prevnode = thing;
                            }
                            if(!works){
                                continue;
                            }
                            for(int x = 0; x < 6; x++){
                                for(int y = 0;y < 2; y++){
                                    if(val3[make_pair(x, y)] != 1){
                                        works = false;
                                        break;
                                    }
                                }
                            }
                            if(!works){
                                continue;
                            }
                            if(works){
                                allPosPaths.push_back(path);
                                cout << "HERE\n";
                            }
                        }
                    }
                }
            }
        }
    }
}
void PathToString(){
    for(vector<pair<int, int> > x : allPosPaths){
        string first[6];
        first[0] = "ABCD";
        first[1] = "ADda";
        first[2] = "ABba";
        first[3] = "BCcb";
        first[4] = "DCcd";
        first[5] = "abcd";
        string second[6];
        second[0] = "EFGH";
        second[1] = "EHhe";
        second[2] = "EFfe";
        second[3] = "FGgf";
        second[4] = "HGgh";
        second[5] = "efgh";
        string inbetween[6][6];
        inbetween[0][1] = "ADHE";
        inbetween[0][2] = "ABFE";
        inbetween[0][3] = "BCGF";
        inbetween[0][4] = "CDHG";
        inbetween[1][2] = "AEea";
        inbetween[1][4] = "DHhd";
        inbetween[1][5] = "adhe";
        inbetween[2][3] = "BbfF";
        inbetween[2][5] = "abfe";
        inbetween[3][4] = "CcgG";
        inbetween[3][5] = "bcgf";
        inbetween[4][5] = "dcgh";
        vector<string> currents;
        for(int i = 0; i < 12; i++){
            if(x[i].second == 0){
                currents.push_back(first[x[i].first]);
            }
            else{
                currents.push_back(second[x[i].first]);
            }
            currents.push_back(inbetween[min(x[i].first, x[(i + 1) % 12].first)][max(x[i].first, x[(i + 1) % 12].first)]);
        }
        stringPath.push_back(currents);
    }
}
void stringToConfig(){
    for(vector<string> path : stringPath){
        for(int g = 0; g < 24; g++){
            map<pair<int, char>, int> mp;
            for(string x : verticesTesseract){
                vertices[x]++;
            }
            bool works = true;
            for(int i = 0; i < 24; i++){
                if(!face(path[i])){
                    works = false;
                    break;
                }
                for(int j = 0; j < 4; j++){
                    mp[make_pair(i, path[i][j])]++;
                }
            }
            map<pair<int, int>, int> coordinatesVal;
            set<pair<pair<int, int>, char> > coordinates;
            int curx = 0;
            int cury = 0;
            coordinates.insert(make_pair(make_pair(curx, cury), ' '));
            coordinatesVal[make_pair(curx + 1, cury + 1)]++;
            coordinates.insert(make_pair(make_pair(curx + 1, cury + 1), path[0][3]));
            coordinatesVal[make_pair(curx + 1, cury + 2)]++;
            coordinates.insert(make_pair(make_pair(curx + 1, cury + 2), path[0][0]));
            coordinatesVal[make_pair(curx + 2, cury + 1)]++;
            coordinates.insert(make_pair(make_pair(curx + 2, cury + 1), path[0][2]));
            coordinatesVal[make_pair(curx + 2, cury + 2)]++;
            coordinates.insert(make_pair(make_pair(curx + 2, cury + 2), path[0][1]));
            coordinates.insert(make_pair(make_pair(curx + 1, cury), '-'));
            coordinates.insert(make_pair(make_pair(curx + 2, cury), '-'));
            coordinates.insert(make_pair(make_pair(curx + 3, cury), ' '));
            coordinates.insert(make_pair(make_pair(curx, cury + 1), '|'));
            coordinates.insert(make_pair(make_pair(curx, cury + 2), '|'));
            coordinates.insert(make_pair(make_pair(curx, cury + 3), ' '));
            coordinates.insert(make_pair(make_pair(curx + 3, cury + 1), '|'));
            coordinates.insert(make_pair(make_pair(curx + 3, cury + 2), '|'));
            coordinates.insert(make_pair(make_pair(curx + 3, cury + 3), ' '));
            coordinates.insert(make_pair(make_pair(curx + 1, cury + 3), '-'));
            coordinates.insert(make_pair(make_pair(curx + 2, cury + 3), '-'));
            for(int i = 1; i < 24; i++){
                int idx = -1;
                for(int j = 0; j < 4; j++){
                    if(mp[make_pair(i, path[i - 1][j])] == 1 && mp[make_pair(i, path[i - 1][(j + 1) % 4])] == 1){
                        idx = j;
                        break;
                    }
                }
                if(idx == 0){
                    vector<string> x = possible(path[i]);
                    for(string y : x){
                        if(y[3] == path[i - 1][idx] && y[2] == path[i - 1][(idx + 1) % 4]){
                            path[i] = y;
                        }
                    }
                    cury += 4;
                    coordinates.insert(make_pair(make_pair(curx, cury), ' '));
                    if(coordinatesVal[make_pair(curx + 1, cury + 1)]){
                        works = false;
                        break;
                    }
                    coordinatesVal[make_pair(curx + 1, cury + 1)]++;
                    coordinates.insert(make_pair(make_pair(curx + 1, cury + 1), path[i][3]));
                    if(coordinatesVal[make_pair(curx + 1, cury + 2)]){
                        cout << "There is a overlap at " << path[i] << "\n";
                        break;
                    }
                    coordinatesVal[make_pair(curx + 1, cury + 2)]++;
                    coordinates.insert(make_pair(make_pair(curx + 1, cury + 2), path[i][0]));
                    if(coordinatesVal[make_pair(curx + 2, cury + 1)]){
                        works = false;
                        break;
                    }
                    coordinatesVal[make_pair(curx + 2, cury + 1)]++;
                    coordinates.insert(make_pair(make_pair(curx + 2, cury + 1), path[i][2]));
                    if(coordinatesVal[make_pair(curx + 2, cury + 2)]){
                        works = false;
                        break;
                    }
                    coordinatesVal[make_pair(curx + 2, cury + 2)]++;
                    coordinates.insert(make_pair(make_pair(curx + 2, cury + 2), path[i][1]));
                    coordinates.insert(make_pair(make_pair(curx + 1, cury), '-'));
                    coordinates.insert(make_pair(make_pair(curx + 2, cury), '-'));
                    coordinates.insert(make_pair(make_pair(curx + 3, cury), ' '));
                    coordinates.insert(make_pair(make_pair(curx, cury + 1), '|'));
                    coordinates.insert(make_pair(make_pair(curx, cury + 2), '|'));
                    coordinates.insert(make_pair(make_pair(curx, cury + 3), ' '));
                    coordinates.insert(make_pair(make_pair(curx + 3, cury + 1), '|'));
                    coordinates.insert(make_pair(make_pair(curx + 3, cury + 2), '|'));
                    coordinates.insert(make_pair(make_pair(curx + 3, cury + 3), ' '));
                    coordinates.insert(make_pair(make_pair(curx + 1, cury + 3), '-'));
                    coordinates.insert(make_pair(make_pair(curx + 2, cury + 3), '-'));
                }
                else if(idx == 1){
                    vector<string> x = possible(path[i]);
                    for(string y : x){
                        if(y[0] == path[i - 1][idx] && y[3] == path[i - 1][(idx + 1) % 4]){
                            path[i] = y;
                        }
                    }
                    curx += 4;
                    coordinates.insert(make_pair(make_pair(curx, cury), ' '));
                    if(coordinatesVal[make_pair(curx + 1, cury + 1)]){
                        works = false;
                        break;
                    }
                    coordinatesVal[make_pair(curx + 1, cury + 1)]++;
                    coordinates.insert(make_pair(make_pair(curx + 1, cury + 1), path[i][3]));
                    if(coordinatesVal[make_pair(curx + 1, cury + 2)]){
                        works = false;
                        break;
                    }
                    coordinatesVal[make_pair(curx + 1, cury + 2)]++;
                    coordinates.insert(make_pair(make_pair(curx + 1, cury + 2), path[i][0]));
                    if(coordinatesVal[make_pair(curx + 2, cury + 1)]){
                        works = false;
                        break;
                    }
                    coordinatesVal[make_pair(curx + 2, cury + 1)]++;
                    coordinates.insert(make_pair(make_pair(curx + 2, cury + 1), path[i][2]));
                    if(coordinatesVal[make_pair(curx + 2, cury + 2)]){
                        works = false;
                        break;
                    }
                    coordinatesVal[make_pair(curx + 2, cury + 2)]++;
                    coordinates.insert(make_pair(make_pair(curx + 2, cury + 2), path[i][1]));
                    coordinates.insert(make_pair(make_pair(curx + 1, cury), '-'));
                    coordinates.insert(make_pair(make_pair(curx + 2, cury), '-'));
                    coordinates.insert(make_pair(make_pair(curx + 3, cury), ' '));
                    coordinates.insert(make_pair(make_pair(curx, cury + 1), '|'));
                    coordinates.insert(make_pair(make_pair(curx, cury + 2), '|'));
                    coordinates.insert(make_pair(make_pair(curx, cury + 3), ' '));
                    coordinates.insert(make_pair(make_pair(curx + 3, cury + 1), '|'));
                    coordinates.insert(make_pair(make_pair(curx + 3, cury + 2), '|'));
                    coordinates.insert(make_pair(make_pair(curx + 3, cury + 3), ' '));
                    coordinates.insert(make_pair(make_pair(curx + 1, cury + 3), '-'));
                    coordinates.insert(make_pair(make_pair(curx + 2, cury + 3), '-'));
                }
                else if(idx == 2){
                    vector<string> x = possible(path[i]);
                    for(string y : x){
                        if(y[1] == path[i - 1][idx] && y[0] == path[i - 1][(idx + 1) % 4]){
                            path[i] = y;
                        }
                    }
                    cury -= 4;
                    coordinates.insert(make_pair(make_pair(curx, cury), ' '));
                    if(coordinatesVal[make_pair(curx + 1, cury + 1)]){
                        works = false;
                        break;
                    }
                    coordinatesVal[make_pair(curx + 1, cury + 1)]++;
                    coordinates.insert(make_pair(make_pair(curx + 1, cury + 1), path[i][3]));
                    if(coordinatesVal[make_pair(curx + 1, cury + 2)]){
                        works = false;
                        break;
                    }
                    coordinatesVal[make_pair(curx + 1, cury + 2)]++;
                    coordinates.insert(make_pair(make_pair(curx + 1, cury + 2), path[i][0]));
                    if(coordinatesVal[make_pair(curx + 2, cury + 1)]){
                        works = false;
                        break;
                    }
                    coordinatesVal[make_pair(curx + 2, cury + 1)]++;
                    coordinates.insert(make_pair(make_pair(curx + 2, cury + 1), path[i][2]));
                    if(coordinatesVal[make_pair(curx + 2, cury + 2)]){
                        works = false;
                        break;
                    }
                    coordinatesVal[make_pair(curx + 2, cury + 2)]++;
                    coordinates.insert(make_pair(make_pair(curx + 2, cury + 2), path[i][1]));
                    coordinates.insert(make_pair(make_pair(curx + 1, cury), '-'));
                    coordinates.insert(make_pair(make_pair(curx + 2, cury), '-'));
                    coordinates.insert(make_pair(make_pair(curx + 3, cury), ' '));
                    coordinates.insert(make_pair(make_pair(curx, cury + 1), '|'));
                    coordinates.insert(make_pair(make_pair(curx, cury + 2), '|'));
                    coordinates.insert(make_pair(make_pair(curx, cury + 3), ' '));
                    coordinates.insert(make_pair(make_pair(curx + 3, cury + 1), '|'));
                    coordinates.insert(make_pair(make_pair(curx + 3, cury + 2), '|'));
                    coordinates.insert(make_pair(make_pair(curx + 3, cury + 3), ' '));
                    coordinates.insert(make_pair(make_pair(curx + 1, cury + 3), '-'));
                    coordinates.insert(make_pair(make_pair(curx + 2, cury + 3), '-'));
                }
                else{
                    vector<string> x = possible(path[i]);
                    for(string y : x){
                        if(y[2] == path[i - 1][idx] && y[1] == path[i - 1][(idx + 1) % 4]){
                            path[i] = y;
                        }
                    }
                    curx -= 4;
                    coordinates.insert(make_pair(make_pair(curx, cury), ' '));
                    if(coordinatesVal[make_pair(curx + 1, cury + 1)]){
                        works = false;
                        break;
                    }
                    coordinatesVal[make_pair(curx + 1, cury + 1)]++;
                    coordinates.insert(make_pair(make_pair(curx + 1, cury + 1), path[i][3]));
                    if(coordinatesVal[make_pair(curx + 1, cury + 2)]){
                        works = false;
                        break;
                    }
                    coordinatesVal[make_pair(curx + 1, cury + 2)]++;
                    coordinates.insert(make_pair(make_pair(curx + 1, cury + 2), path[i][0]));
                    if(coordinatesVal[make_pair(curx + 2, cury + 1)]){
                        works = false;
                        break;
                    }
                    coordinatesVal[make_pair(curx + 2, cury + 1)]++;
                    coordinates.insert(make_pair(make_pair(curx + 2, cury + 1), path[i][2]));
                    if(coordinatesVal[make_pair(curx + 2, cury + 2)]){
                        works = false;
                        break;
                    }
                    coordinatesVal[make_pair(curx + 2, cury + 2)]++;
                    coordinates.insert(make_pair(make_pair(curx + 2, cury + 2), path[i][1]));
                    coordinates.insert(make_pair(make_pair(curx + 1, cury), '-'));
                    coordinates.insert(make_pair(make_pair(curx + 2, cury), '-'));
                    coordinates.insert(make_pair(make_pair(curx + 3, cury), ' '));
                    coordinates.insert(make_pair(make_pair(curx, cury + 1), '|'));
                    coordinates.insert(make_pair(make_pair(curx, cury + 2), '|'));
                    coordinates.insert(make_pair(make_pair(curx, cury + 3), ' '));
                    coordinates.insert(make_pair(make_pair(curx + 3, cury + 1), '|'));
                    coordinates.insert(make_pair(make_pair(curx + 3, cury + 2), '|'));
                    coordinates.insert(make_pair(make_pair(curx + 3, cury + 3), ' '));
                    coordinates.insert(make_pair(make_pair(curx + 1, cury + 3), '-'));
                    coordinates.insert(make_pair(make_pair(curx + 2, cury + 3), '-'));
                }
            }
            if(works){
                cout << "The following path works!\n";
                for(string s : path){
                    cout << s << "\n";
                }
                cout << "\n";
                cout << "-------------------------------------------------------\n";
                cout << "\n";
            }
            rotate(path.begin(), path.begin() + 1, path.end());
        }
    }
}
int main(){
    formPaths();
    PathToString();
    stringToConfig();
}