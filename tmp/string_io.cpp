//
// Created by luoxiYun on 2021/3/10.
//

#include "include/common.h"


int main(){
    string line;

    string delimiter =",";
    int pos = 0;
    while(getline(cin,line)) {
        pos = 0;
        size_t position;
        vector<string> eles;
        while( (position = line.find_first_of( delimiter, pos )) != string::npos ) {
            //cout<<position<<endl;
            eles.push_back(line.substr( pos, position-pos));
            pos = position + 1;
        }
        eles.push_back(line.substr(pos));
        sort(eles.begin(), eles.end());
        for( int i = 0; i < eles.size(); i++)
            cout<<eles[i]<<",";
        cout<<endl;
    }
    return 0;


}