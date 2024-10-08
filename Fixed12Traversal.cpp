#include<bits/stdc++.h>
using namespace std;
ofstream output("res.txt");
vector<vector<int> > allPosPaths;
vector<vector<string> > stringPath;
set<vector<string> > correctPaths;
bool moveable(string a, string b){
    int val = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(a[i] == b[j]){
                val++;
            }
        }
    }
    return val >= 2;
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
// 4 -> 10 -> 3 -> 9 -> 5 -> 11 -> 1 -> 7 -> 2 -> 8 -> 0 -> 6
void formPaths(){
    vector<int> order;
    for(int i= 0; i < 12; i++){
        order.push_back(i);
    }
    do{
        bool works = true;
        for(int i = 0; i < 12; i++){
            int val1 = order[i]/6;
            int val2 = order[i] % 6;
            int val3 = order[(i + 1) % 12]/6;
            int val4 = order[(i + 1) % 12] % 6;
            if(val1 == val3){
                works = false;
                break;
            }
            if(val2 + val4 == 5){
                works = false;
                break;
            }
            // if(val2 == val4){
            //     works = false;
            //     break;
            // }
        }
        if(works){
            allPosPaths.push_back(order);
        }
    } while(next_permutation(order.begin(), order.end()));
}
void PathToString(){
    output << allPosPaths.size() << "\n";
    for(vector<int> x : allPosPaths){
        string first[6];
        first[0] = "ABCD";
        first[1] = "ADda";
        first[2] = "ABba";
        first[3] = "DCcd";
        first[4] = "BCcb";
        first[5] = "abcd";
        string second[6];
        second[0] = "EFGH";
        second[1] = "EHhe";
        second[2] = "EFfe";
        second[3] = "HGgh";
        second[4] = "FGgf";
        second[5] = "efgh";
        string inbetween[6][6];
        inbetween[0][1] = "ADHE";
        inbetween[0][2] = "ABFE";
        inbetween[0][3] = "CDHG";
        inbetween[0][4] = "BCGF";
        inbetween[1][2] = "AEea";
        inbetween[1][3] = "DHhd";
        inbetween[1][5] = "adhe";
        inbetween[2][4] = "BbfF";
        inbetween[2][5] = "abfe";
        inbetween[3][4] = "CcgG";
        inbetween[3][5] = "dcgh";
        inbetween[4][5] = "bcgf";
        vector<string> currents;
        // map<string, bool> done;
        set<string> s;
        s.insert("ADHE");
        s.insert("ABFE");
        s.insert("CDHG");
        s.insert("BCGF");
        s.insert("AEea");
        s.insert("DHhd");
        s.insert("adhe");
        s.insert("BbfF");
        s.insert("abfe");
        s.insert("CcgG");
        s.insert("dcgh");
        s.insert("bcgf");
        bool notgood = false;
        for(int i = 0; i < 12; i++){
            if(x[i] < 6){
                currents.push_back(first[x[i]]);
            }
            else{
                currents.push_back(second[x[i] - 6]);
            }
            if(x[i] % 6 == x[(i + 1) % 12] % 6 || i == 11){
                currents.push_back("");
                // cout << "HRER\n";
            }
            else{
                currents.push_back(inbetween[min(x[i] % 6, x[(i + 1) % 12] % 6)][max(x[i] % 6, x[(i + 1) % 12] % 6)]);
                // done[currents.back()] = true;
                if(s.find(currents.back()) == s.end()){
                    notgood = true;
                    break;
                }
                s.erase(currents.back());
            }
        }
        if(notgood){
            continue;
        }
        vector<string> rem;
        for(string s2 : s){
            rem.push_back(s2);
        }
        vector<int> idx;
        for(int i = 0; i < 24; i++){
            if((int)currents[i].size() != 4){
                idx.push_back(i);
                assert(i % 2 == 1);
            }
        }
        // cout << idx.size() << " " << rem.size() << "\n";
        assert(idx.size() == rem.size());
        do{
            vector<string> cur = currents;
            bool works = true;
            for(int j =0 ; j < idx.size(); j++){
                if(moveable(currents[idx[j] - 1], rem[j]) && (idx[j] == 23 || moveable(rem[j], currents[(idx[j] + 1) % 24]))){
                    cur[idx[j]] = rem[j];
                }
                else{
                    works = false;
                    break;
                }
            }
            if(works){
                stringPath.push_back(cur);
            }
        } while(next_permutation(rem.begin(), rem.end()));
        if(idx.empty()){
            stringPath.push_back(currents);
        }
    }
}
void stringToConfig(){
    cout << stringPath.size() << "\n";
    for(vector<string> path : stringPath){
        vector<string> path3;
        for(int i = 0; i < 24; i++){
            path3.push_back(path[i]);
        }
        bool thingy = true;
        for(int i = 0; i < 24 ;i++){
            if(!moveable(path3[i], path3[(i + 1) % 24])){
                thingy = false;
                break;
            }
        }
        if(thingy){
            for(int g = 0; g < 24; g++){
                vector<string> path2(24);
                map<pair<int, char>, int> mp;
                bool works = true;
                for(int i = 0; i < 24; i++){
                    path2[i] = path3[i];
                    for(int j = 0; j < 4; j++){
                        mp[make_pair(i, path3[i][j])]++;
                    }
                }
                map<pair<int, int>, int> coordinatesVal;
                set<pair<pair<int, int>, char> > coordinates;
                int curx = 0;
                int cury = 0;
                coordinates.insert(make_pair(make_pair(curx, cury), ' '));
                coordinatesVal[make_pair(curx + 1, cury + 1)]++;
                coordinates.insert(make_pair(make_pair(curx + 1, cury + 1), path2[0][3]));
                coordinatesVal[make_pair(curx + 1, cury + 2)]++;
                coordinates.insert(make_pair(make_pair(curx + 1, cury + 2), path2[0][0]));
                coordinatesVal[make_pair(curx + 2, cury + 1)]++;
                coordinates.insert(make_pair(make_pair(curx + 2, cury + 1), path2[0][2]));
                coordinatesVal[make_pair(curx + 2, cury + 2)]++;
                coordinates.insert(make_pair(make_pair(curx + 2, cury + 2), path2[0][1]));
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
                        if(mp[make_pair(i, path2[i - 1][j])] == 1 && mp[make_pair(i, path2[i - 1][(j + 1) % 4])] == 1){
                            idx = j;
                            break;
                        }
                    }
                    if(idx == 0){
                        vector<string> x = possible(path2[i]);
                        for(string y : x){
                            if(y[3] == path2[i - 1][idx] && y[2] == path2[i - 1][(idx + 1) % 4]){
                                path2[i] = y;
                            }
                        }
                        cury += 4;
                        coordinates.insert(make_pair(make_pair(curx, cury), ' '));
                        if(coordinatesVal.find(make_pair(curx + 1, cury + 1)) != coordinatesVal.end()){
                            works = false;
                            // output << "There is a overlap at " << path2[i] << "\n";
                            break;
                        }
                        coordinatesVal[make_pair(curx + 1, cury + 1)]++;
                        coordinates.insert(make_pair(make_pair(curx + 1, cury + 1), path2[i][3]));
                        if(coordinatesVal.find(make_pair(curx + 1, cury + 2)) != coordinatesVal.end()){
                            works = false;
                            // output << "There is a overlap at " << path2[i] << "\n";
                            break;
                        }
                        coordinatesVal[make_pair(curx + 1, cury + 2)]++;
                        coordinates.insert(make_pair(make_pair(curx + 1, cury + 2), path2[i][0]));
                        if(coordinatesVal.find(make_pair(curx + 2, cury + 1)) != coordinatesVal.end()){
                            works = false;
                            // output << "There is a overlap at " << path2[i] << "\n";
                            break;
                        }
                        coordinatesVal[make_pair(curx + 2, cury + 1)]++;
                        coordinates.insert(make_pair(make_pair(curx + 2, cury + 1), path2[i][2]));
                        if(coordinatesVal.find(make_pair(curx + 2, cury + 2)) != coordinatesVal.end()){
                            works = false;
                            // output << "There is a overlap at " << path2[i] << "\n";
                            break;
                        }
                        coordinatesVal[make_pair(curx + 2, cury + 2)]++;
                        coordinates.insert(make_pair(make_pair(curx + 2, cury + 2), path2[i][1]));
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
                        vector<string> x = possible(path2[i]);
                        for(string y : x){
                            if(y[0] == path2[i - 1][idx] && y[3] == path2[i - 1][(idx + 1) % 4]){
                                path2[i] = y;
                            }
                        }
                        curx += 4;
                        coordinates.insert(make_pair(make_pair(curx, cury), ' '));
                        if(coordinatesVal[make_pair(curx + 1, cury + 1)]){
                            works = false;
                            // output << "There is a overlap at " << path2[i] << "\n";
                            break;
                        }
                        coordinatesVal[make_pair(curx + 1, cury + 1)]++;
                        coordinates.insert(make_pair(make_pair(curx + 1, cury + 1), path2[i][3]));
                        if(coordinatesVal.find(make_pair(curx + 1, cury + 2)) != coordinatesVal.end()){
                            works = false;
                            // output << "There is a overlap at " << path2[i] << "\n";
                            break;
                        }
                        coordinatesVal[make_pair(curx + 1, cury + 2)]++;
                        coordinates.insert(make_pair(make_pair(curx + 1, cury + 2), path2[i][0]));
                        if(coordinatesVal.find(make_pair(curx + 2, cury + 1)) != coordinatesVal.end()){
                            works = false;
                            // output << "There is a overlap at " << path2[i] << "\n";
                            break;
                        }
                        coordinatesVal[make_pair(curx + 2, cury + 1)]++;
                        coordinates.insert(make_pair(make_pair(curx + 2, cury + 1), path2[i][2]));
                        if(coordinatesVal.find(make_pair(curx + 2, cury + 2)) != coordinatesVal.end()){
                            works = false;
                            // output << "There is a overlap at " << path2[i] << "\n";
                            break;
                        }
                        coordinatesVal[make_pair(curx + 2, cury + 2)]++;
                        coordinates.insert(make_pair(make_pair(curx + 2, cury + 2), path2[i][1]));
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
                        vector<string> x = possible(path2[i]);
                        for(string y : x){
                            if(y[1] == path2[i - 1][idx] && y[0] == path2[i - 1][(idx + 1) % 4]){
                                path2[i] = y;
                            }
                        }
                        cury -= 4;
                        coordinates.insert(make_pair(make_pair(curx, cury), ' '));
                        if(coordinatesVal.find(make_pair(curx + 1, cury + 1)) != coordinatesVal.end()){
                            works = false;
                            // output << "There is a overlap at " << path2[i] << "\n";
                            break;
                        }
                        coordinatesVal[make_pair(curx + 1, cury + 1)]++;
                        coordinates.insert(make_pair(make_pair(curx + 1, cury + 1), path2[i][3]));
                        if(coordinatesVal.find(make_pair(curx + 1, cury + 2)) != coordinatesVal.end()){
                            works = false;
                            // output << "There is a overlap at " << path2[i] << "\n";
                            break;
                        }
                        coordinatesVal[make_pair(curx + 1, cury + 2)]++;
                        coordinates.insert(make_pair(make_pair(curx + 1, cury + 2), path2[i][0]));
                        if(coordinatesVal.find(make_pair(curx + 2, cury + 1)) != coordinatesVal.end()){
                            works = false;
                            // output << "There is a overlap at " << path2[i] << "\n";
                            break;
                        }
                        coordinatesVal[make_pair(curx + 2, cury + 1)]++;
                        coordinates.insert(make_pair(make_pair(curx + 2, cury + 1), path2[i][2]));
                        if(coordinatesVal.find(make_pair(curx + 2, cury + 2)) != coordinatesVal.end()){
                            works = false;
                            // output << "There is a overlap at " << path2[i] << "\n";
                            break;
                        }
                        coordinatesVal[make_pair(curx + 2, cury + 2)]++;
                        coordinates.insert(make_pair(make_pair(curx + 2, cury + 2), path2[i][1]));
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
                        vector<string> x = possible(path2[i]);
                        for(string y : x){
                            if(y[2] == path2[i - 1][idx] && y[1] == path2[i - 1][(idx + 1) % 4]){
                                path2[i] = y;
                            }
                        }
                        curx -= 4;
                        coordinates.insert(make_pair(make_pair(curx, cury), ' '));
                        if(coordinatesVal.find(make_pair(curx + 1, cury + 1)) != coordinatesVal.end()){
                            works = false;
                            // output << "There is a overlap at " << path2[i] << "\n";
                            break;
                        }
                        coordinatesVal[make_pair(curx + 1, cury + 1)]++;
                        coordinates.insert(make_pair(make_pair(curx + 1, cury + 1), path2[i][3]));
                        if(coordinatesVal.find(make_pair(curx + 1, cury + 2)) != coordinatesVal.end()){
                            works = false;
                            // output << "There is a overlap at " << path2[i] << "\n";
                            break;
                        }
                        coordinatesVal[make_pair(curx + 1, cury + 2)]++;
                        coordinates.insert(make_pair(make_pair(curx + 1, cury + 2), path2[i][0]));
                        if(coordinatesVal.find(make_pair(curx + 2, cury + 1)) != coordinatesVal.end()){
                            works = false;
                            // output << "There is a overlap at " << path2[i] << "\n";
                            break;
                        }
                        coordinatesVal[make_pair(curx + 2, cury + 1)]++;
                        coordinates.insert(make_pair(make_pair(curx + 2, cury + 1), path2[i][2]));
                        if(coordinatesVal.find(make_pair(curx + 2, cury + 2)) != coordinatesVal.end()){
                            works = false;
                            // output << "There is a overlap at " << path2[i] << "\n";
                            break;
                        }
                        coordinatesVal[make_pair(curx + 2, cury + 2)]++;
                        coordinates.insert(make_pair(make_pair(curx + 2, cury + 2), path2[i][1]));
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
                    if(correctPaths.find(path3) == correctPaths.end()){
                        output << "The following path works!\n";
                        for(string s : path3){
                            output << s << "\n";
                        }
                        output << "\n";
                        output << "-------------------------------------------------------\n";
                        output << "\n";
                        correctPaths.insert(path3);
                    }
                }
                path3.push_back(path3[0]);
                path3.erase(path3.begin());
            }
        }
        else{
            // cout << "HERE\n";
            map<pair<int, char>, int> mp;
            bool works = true;
            vector<string> path2(24);
            for(int i = 0; i < 24; i++){
                path2[i] = path3[i];
                for(int j = 0; j < 4; j++){
                    mp[make_pair(i, path2[i][j])]++;
                }
            }
            map<pair<int, int>, int> coordinatesVal;
            set<pair<pair<int, int>, char> > coordinates;
            int curx = 0;
            int cury = 0;
            coordinates.insert(make_pair(make_pair(curx, cury), ' '));
            coordinatesVal[make_pair(curx + 1, cury + 1)]++;
            coordinates.insert(make_pair(make_pair(curx + 1, cury + 1), path2[0][3]));
            coordinatesVal[make_pair(curx + 1, cury + 2)]++;
            coordinates.insert(make_pair(make_pair(curx + 1, cury + 2), path2[0][0]));
            coordinatesVal[make_pair(curx + 2, cury + 1)]++;
            coordinates.insert(make_pair(make_pair(curx + 2, cury + 1), path2[0][2]));
            coordinatesVal[make_pair(curx + 2, cury + 2)]++;
            coordinates.insert(make_pair(make_pair(curx + 2, cury + 2), path2[0][1]));
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
                    if(mp[make_pair(i, path2[i - 1][j])] == 1 && mp[make_pair(i, path2[i - 1][(j + 1) % 4])] == 1){
                        idx = j;
                        break;
                    }
                }
                if(idx == 0){
                    vector<string> x = possible(path2[i]);
                    for(string y : x){
                        if(y[3] == path2[i - 1][idx] && y[2] == path2[i - 1][(idx + 1) % 4]){
                            path2[i] = y;
                        }
                    }
                    cury += 4;
                    coordinates.insert(make_pair(make_pair(curx, cury), ' '));
                    if(coordinatesVal.find(make_pair(curx + 1, cury + 1)) != coordinatesVal.end()){
                        works = false;
                        // output << "There is a overlap at " << path2[i] << "\n";
                        break;
                    }
                    coordinatesVal[make_pair(curx + 1, cury + 1)]++;
                    coordinates.insert(make_pair(make_pair(curx + 1, cury + 1), path2[i][3]));
                    if(coordinatesVal.find(make_pair(curx + 1, cury + 2)) != coordinatesVal.end()){
                        works = false;
                        // output << "There is a overlap at " << path2[i] << "\n";
                        break;
                    }
                    coordinatesVal[make_pair(curx + 1, cury + 2)]++;
                    coordinates.insert(make_pair(make_pair(curx + 1, cury + 2), path2[i][0]));
                    if(coordinatesVal.find(make_pair(curx + 2, cury + 1)) != coordinatesVal.end()){
                        works = false;
                        // output << "There is a overlap at " << path2[i] << "\n";
                        break;
                    }
                    coordinatesVal[make_pair(curx + 2, cury + 1)]++;
                    coordinates.insert(make_pair(make_pair(curx + 2, cury + 1), path2[i][2]));
                    if(coordinatesVal.find(make_pair(curx + 2, cury + 2)) != coordinatesVal.end()){
                        works = false;
                        // output << "There is a overlap at " << path2[i] << "\n";
                        break;
                    }
                    coordinatesVal[make_pair(curx + 2, cury + 2)]++;
                    coordinates.insert(make_pair(make_pair(curx + 2, cury + 2), path2[i][1]));
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
                    vector<string> x = possible(path2[i]);
                    for(string y : x){
                        if(y[0] == path2[i - 1][idx] && y[3] == path2[i - 1][(idx + 1) % 4]){
                            path2[i] = y;
                        }
                    }
                    curx += 4;
                    coordinates.insert(make_pair(make_pair(curx, cury), ' '));
                    if(coordinatesVal[make_pair(curx + 1, cury + 1)]){
                        works = false;
                        // output << "There is a overlap at " << path2[i] << "\n";
                        break;
                    }
                    coordinatesVal[make_pair(curx + 1, cury + 1)]++;
                    coordinates.insert(make_pair(make_pair(curx + 1, cury + 1), path2[i][3]));
                    if(coordinatesVal.find(make_pair(curx + 1, cury + 2)) != coordinatesVal.end()){
                        works = false;
                        // output << "There is a overlap at " << path2[i] << "\n";
                        break;
                    }
                    coordinatesVal[make_pair(curx + 1, cury + 2)]++;
                    coordinates.insert(make_pair(make_pair(curx + 1, cury + 2), path2[i][0]));
                    if(coordinatesVal.find(make_pair(curx + 2, cury + 1)) != coordinatesVal.end()){
                        works = false;
                        // output << "There is a overlap at " << path2[i] << "\n";
                        break;
                    }
                    coordinatesVal[make_pair(curx + 2, cury + 1)]++;
                    coordinates.insert(make_pair(make_pair(curx + 2, cury + 1), path2[i][2]));
                    if(coordinatesVal.find(make_pair(curx + 2, cury + 2)) != coordinatesVal.end()){
                        works = false;
                        // output << "There is a overlap at " << path2[i] << "\n";
                        break;
                    }
                    coordinatesVal[make_pair(curx + 2, cury + 2)]++;
                    coordinates.insert(make_pair(make_pair(curx + 2, cury + 2), path2[i][1]));
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
                    vector<string> x = possible(path2[i]);
                    for(string y : x){
                        if(y[1] == path2[i - 1][idx] && y[0] == path2[i - 1][(idx + 1) % 4]){
                            path2[i] = y;
                        }
                    }
                    cury -= 4;
                    coordinates.insert(make_pair(make_pair(curx, cury), ' '));
                    if(coordinatesVal.find(make_pair(curx + 1, cury + 1)) != coordinatesVal.end()){
                        works = false;
                        // output << "There is a overlap at " << path2[i] << "\n";
                        break;
                    }
                    coordinatesVal[make_pair(curx + 1, cury + 1)]++;
                    coordinates.insert(make_pair(make_pair(curx + 1, cury + 1), path2[i][3]));
                    if(coordinatesVal.find(make_pair(curx + 1, cury + 2)) != coordinatesVal.end()){
                        works = false;
                        // output << "There is a overlap at " << path2[i] << "\n";
                        break;
                    }
                    coordinatesVal[make_pair(curx + 1, cury + 2)]++;
                    coordinates.insert(make_pair(make_pair(curx + 1, cury + 2), path2[i][0]));
                    if(coordinatesVal.find(make_pair(curx + 2, cury + 1)) != coordinatesVal.end()){
                        works = false;
                        // output << "There is a overlap at " << path2[i] << "\n";
                        break;
                    }
                    coordinatesVal[make_pair(curx + 2, cury + 1)]++;
                    coordinates.insert(make_pair(make_pair(curx + 2, cury + 1), path2[i][2]));
                    if(coordinatesVal.find(make_pair(curx + 2, cury + 2)) != coordinatesVal.end()){
                        works = false;
                        // output << "There is a overlap at " << path2[i] << "\n";
                        break;
                    }
                    coordinatesVal[make_pair(curx + 2, cury + 2)]++;
                    coordinates.insert(make_pair(make_pair(curx + 2, cury + 2), path2[i][1]));
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
                    vector<string> x = possible(path2[i]);
                    for(string y : x){
                        if(y[2] == path2[i - 1][idx] && y[1] == path2[i - 1][(idx + 1) % 4]){
                            path2[i] = y;
                        }
                    }
                    curx -= 4;
                    coordinates.insert(make_pair(make_pair(curx, cury), ' '));
                    if(coordinatesVal.find(make_pair(curx + 1, cury + 1)) != coordinatesVal.end()){
                        works = false;
                        // output << "There is a overlap at " << path2[i] << "\n";
                        break;
                    }
                    coordinatesVal[make_pair(curx + 1, cury + 1)]++;
                    coordinates.insert(make_pair(make_pair(curx + 1, cury + 1), path2[i][3]));
                    if(coordinatesVal.find(make_pair(curx + 1, cury + 2)) != coordinatesVal.end()){
                        works = false;
                        // output << "There is a overlap at " << path2[i] << "\n";
                        break;
                    }
                    coordinatesVal[make_pair(curx + 1, cury + 2)]++;
                    coordinates.insert(make_pair(make_pair(curx + 1, cury + 2), path2[i][0]));
                    if(coordinatesVal.find(make_pair(curx + 2, cury + 1)) != coordinatesVal.end()){
                        works = false;
                        // output << "There is a overlap at " << path2[i] << "\n";
                        break;
                    }
                    coordinatesVal[make_pair(curx + 2, cury + 1)]++;
                    coordinates.insert(make_pair(make_pair(curx + 2, cury + 1), path2[i][2]));
                    if(coordinatesVal.find(make_pair(curx + 2, cury + 2)) != coordinatesVal.end()){
                        works = false;
                        // output << "There is a overlap at " << path2[i] << "\n";
                        break;
                    }
                    coordinatesVal[make_pair(curx + 2, cury + 2)]++;
                    coordinates.insert(make_pair(make_pair(curx + 2, cury + 2), path2[i][1]));
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
                if(correctPaths.find(path3) == correctPaths.end()){
                    output << "The following path works!\n";
                    for(string s : path3){
                        output << s << "\n";
                    }
                    output << "\n";
                    output << "-------------------------------------------------------\n";
                    output << "\n";
                    correctPaths.insert(path3);
                }
            }
        }
    }
}
int main(){
    formPaths();
    PathToString();
    stringToConfig();
}