#include<bits/stdc++.h>
using namespace std;
int main(){
    vector<pair<int, int> > nodes(12);
    for(int i = 0; i < 12; i++){
        cin >> nodes[i].first >> nodes[i].second;
    }
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
    for(int i = 0; i < 12; i++){
        if(nodes[i].second == 0){
            cout << first[nodes[i].first] << "\n";
        }
        else{
            cout << second[nodes[i].first] << "\n";
        }
        cout << inbetween[min(nodes[i].first, nodes[(i + 1) % 12].first)][max(nodes[i].first, nodes[(i + 1) % 12].first)] << "\n";
    }
    cout << "\n";
}