//
// Created by luoxiYun on 2021/3/10.
//

#include "include/common.h"

using namespace std;
int main(){


    string line;

    while(getline(cin,line)) {
        istringstream is(line);
        string ele;
        vector<string> eles;
        while (is >> ele)
            eles.push_back(ele);

        sort(eles.begin(), eles.end());
        for (int i = 0; i < eles.size()-1; i++)
            cout << eles[i] << ",";
        cout<<eles.back()<<endl;
    }
    return 0;


}