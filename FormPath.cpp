#include<bits/stdc++.h>
using namespace std;
int main(){
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
                            int curColor = 0; //0 is pink, 1 is green
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
                                        // cout << curnode << " " << curColor << "\n";
                                    }
                                    else if(adj[curnode][val[nodes[curnode]].second] == prevnode){
                                        curColor += 1;
                                        curColor %= 2;
                                        curnode = adj[curnode][val[nodes[curnode]].first];
                                        // cout << curnode << " " << curColor << "\n";
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
                                        // cout << curnode << " " << curColor << "\n";
                                    }
                                    else if(adj[curnode][val2[nodes[curnode]].first] == prevnode){
                                        curColor += 1;
                                        curColor %= 2;
                                        curnode = adj[curnode][val2[nodes[curnode]].second];
                                        // cout << curnode << " " << curColor << "\n";
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
                                for(pair<int, int> x : path){
                                    cout << x.first << " " << x.second << " ";
                                }
                                cout << "\n";
                            }
                        }
                    }
                }
            }
        }
    }
}