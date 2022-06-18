//
// Created by luoxiYun on 2021/8/22.
//

#include "common.h"

int main(){
    int car_num;
    cin>>car_num;
    vector<int> car_speed(car_num);
    for( int i = 0; i < car_num; i++ ){
        cin>>car_speed[i];
    }
    sort( car_speed.begin(), car_speed.end() );
    int left = 0, right = 0;
    int res = -1;
    while ( right < car_num ){
        int threshold = car_speed[left] + 10;
        while ( right < car_num && car_speed[right] <= threshold )
            right++;
        res = max( res, right - left );
        left++;
    }
    cout<<res<<endl;
    return 0;
}