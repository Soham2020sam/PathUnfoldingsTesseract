#include<bits/stdc++.h>
using namespace std;
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
int main(){
    ifstream fin("pathin.txt");
    ofstream fout("pathout.txt");
    vector<string> path;
    map<pair<int, char>, int> mp;
    for(string x : verticesTesseract){
        vertices[x]++;
    }
    for(int i = 0; i < 24; i++){
        string x;
        fin >> x;
        if(!face(x)){
            cout << x << " is not a face in the tesseract\n";
        }
        for(int j = 0; j < 4; j++){
            mp[make_pair(i, x[j])]++;
        }
        path.push_back(x);
    }
    map<pair<int, int>, int> coordinatesVal;
    set<pair<pair<int, int>, char> > coordinates;
    int curx = 0;
    int cury = 0;
    coordinates.insert(make_pair(make_pair(curx, cury), '+'));
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
    coordinates.insert(make_pair(make_pair(curx + 3, cury), '+'));
    coordinates.insert(make_pair(make_pair(curx, cury + 1), '|'));
    coordinates.insert(make_pair(make_pair(curx, cury + 2), '|'));
    coordinates.insert(make_pair(make_pair(curx, cury + 3), '+'));
    coordinates.insert(make_pair(make_pair(curx + 3, cury + 1), '|'));
    coordinates.insert(make_pair(make_pair(curx + 3, cury + 2), '|'));
    coordinates.insert(make_pair(make_pair(curx + 3, cury + 3), '+'));
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
            coordinates.insert(make_pair(make_pair(curx, cury), '+'));
            if(coordinatesVal[make_pair(curx + 1, cury + 1)]){
                cout << "There is a overlap at " << path[i] << "\n";
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
                cout << "There is a overlap at " << path[i] << "\n";
                break;
            }
            coordinatesVal[make_pair(curx + 2, cury + 1)]++;
            coordinates.insert(make_pair(make_pair(curx + 2, cury + 1), path[i][2]));
            if(coordinatesVal[make_pair(curx + 2, cury + 2)]){
                cout << "There is a overlap at " << path[i] << "\n";
                break;
            }
            coordinatesVal[make_pair(curx + 2, cury + 2)]++;
            coordinates.insert(make_pair(make_pair(curx + 2, cury + 2), path[i][1]));
            coordinates.insert(make_pair(make_pair(curx + 1, cury), '-'));
            coordinates.insert(make_pair(make_pair(curx + 2, cury), '-'));
            coordinates.insert(make_pair(make_pair(curx + 3, cury), '+'));
            coordinates.insert(make_pair(make_pair(curx, cury + 1), '|'));
            coordinates.insert(make_pair(make_pair(curx, cury + 2), '|'));
            coordinates.insert(make_pair(make_pair(curx, cury + 3), '+'));
            coordinates.insert(make_pair(make_pair(curx + 3, cury + 1), '|'));
            coordinates.insert(make_pair(make_pair(curx + 3, cury + 2), '|'));
            coordinates.insert(make_pair(make_pair(curx + 3, cury + 3), '+'));
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
            coordinates.insert(make_pair(make_pair(curx, cury), '+'));
            if(coordinatesVal[make_pair(curx + 1, cury + 1)]){
                cout << "There is a overlap at " << path[i] << "\n";
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
                cout << "There is a overlap at " << path[i] << "\n";
                break;
            }
            coordinatesVal[make_pair(curx + 2, cury + 1)]++;
            coordinates.insert(make_pair(make_pair(curx + 2, cury + 1), path[i][2]));
            if(coordinatesVal[make_pair(curx + 2, cury + 2)]){
                cout << "There is a overlap at " << path[i] << "\n";
                break;
            }
            coordinatesVal[make_pair(curx + 2, cury + 2)]++;
            coordinates.insert(make_pair(make_pair(curx + 2, cury + 2), path[i][1]));
            coordinates.insert(make_pair(make_pair(curx + 1, cury), '-'));
            coordinates.insert(make_pair(make_pair(curx + 2, cury), '-'));
            coordinates.insert(make_pair(make_pair(curx + 3, cury), '+'));
            coordinates.insert(make_pair(make_pair(curx, cury + 1), '|'));
            coordinates.insert(make_pair(make_pair(curx, cury + 2), '|'));
            coordinates.insert(make_pair(make_pair(curx, cury + 3), '+'));
            coordinates.insert(make_pair(make_pair(curx + 3, cury + 1), '|'));
            coordinates.insert(make_pair(make_pair(curx + 3, cury + 2), '|'));
            coordinates.insert(make_pair(make_pair(curx + 3, cury + 3), '+'));
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
            coordinates.insert(make_pair(make_pair(curx, cury), '+'));
            if(coordinatesVal[make_pair(curx + 1, cury + 1)]){
                cout << "There is a overlap at " << path[i] << "\n";
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
                cout << "There is a overlap at " << path[i] << "\n";
                break;
            }
            coordinatesVal[make_pair(curx + 2, cury + 1)]++;
            coordinates.insert(make_pair(make_pair(curx + 2, cury + 1), path[i][2]));
            if(coordinatesVal[make_pair(curx + 2, cury + 2)]){
                cout << "There is a overlap at " << path[i] << "\n";
                break;
            }
            coordinatesVal[make_pair(curx + 2, cury + 2)]++;
            coordinates.insert(make_pair(make_pair(curx + 2, cury + 2), path[i][1]));
            coordinates.insert(make_pair(make_pair(curx + 1, cury), '-'));
            coordinates.insert(make_pair(make_pair(curx + 2, cury), '-'));
            coordinates.insert(make_pair(make_pair(curx + 3, cury), '+'));
            coordinates.insert(make_pair(make_pair(curx, cury + 1), '|'));
            coordinates.insert(make_pair(make_pair(curx, cury + 2), '|'));
            coordinates.insert(make_pair(make_pair(curx, cury + 3), '+'));
            coordinates.insert(make_pair(make_pair(curx + 3, cury + 1), '|'));
            coordinates.insert(make_pair(make_pair(curx + 3, cury + 2), '|'));
            coordinates.insert(make_pair(make_pair(curx + 3, cury + 3), '+'));
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
            coordinates.insert(make_pair(make_pair(curx, cury), '+'));
            if(coordinatesVal[make_pair(curx + 1, cury + 1)]){
                cout << "There is a overlap at " << path[i] << "\n";
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
                cout << "There is a overlap at " << path[i] << "\n";
                break;
            }
            coordinatesVal[make_pair(curx + 2, cury + 1)]++;
            coordinates.insert(make_pair(make_pair(curx + 2, cury + 1), path[i][2]));
            if(coordinatesVal[make_pair(curx + 2, cury + 2)]){
                cout << "There is a overlap at " << path[i] << "\n";
                break;
            }
            coordinatesVal[make_pair(curx + 2, cury + 2)]++;
            coordinates.insert(make_pair(make_pair(curx + 2, cury + 2), path[i][1]));
            coordinates.insert(make_pair(make_pair(curx + 1, cury), '-'));
            coordinates.insert(make_pair(make_pair(curx + 2, cury), '-'));
            coordinates.insert(make_pair(make_pair(curx + 3, cury), '+'));
            coordinates.insert(make_pair(make_pair(curx, cury + 1), '|'));
            coordinates.insert(make_pair(make_pair(curx, cury + 2), '|'));
            coordinates.insert(make_pair(make_pair(curx, cury + 3), '+'));
            coordinates.insert(make_pair(make_pair(curx + 3, cury + 1), '|'));
            coordinates.insert(make_pair(make_pair(curx + 3, cury + 2), '|'));
            coordinates.insert(make_pair(make_pair(curx + 3, cury + 3), '+'));
            coordinates.insert(make_pair(make_pair(curx + 1, cury + 3), '-'));
            coordinates.insert(make_pair(make_pair(curx + 2, cury + 3), '-'));
        }
    }
    int maxY = 0;
    int minX = 0;
    int maxX = 0;
    int minY = 0;
    for(auto it : coordinates){
        minX = min(minX, it.first.first);
        maxY = max(maxY, it.first.second);
        maxX = max(maxX, it.first.first);
        minY = min(minY, it.first.second);
    }
    vector<vector<char> > grid(maxY - minY + 1, vector<char>(maxX - minX + 1, ' '));
    for(auto it : coordinates){
        grid[maxY - it.first.second][it.first.first - minX] = it.second;
    }
    for(int i = 0; i < grid.size(); i++){
        for(int j = 0; j < grid[i].size(); j++){
            fout << grid[i][j];
        }
        fout << "\n";
    }
}

/*

ABCD
BCGF
FGgf
BbfF
ABba
abfe
efgh
bcgf
BCcb
CcgG
HGgh
cdhg
abcd
adhe
EHhe
DdhH
DCcd
DCGH
EFGH
ADHE
ADda
AaeE
EFfe
ABFE
 --  --
|AB||BG|
|FE||EF|
 --  --
*/