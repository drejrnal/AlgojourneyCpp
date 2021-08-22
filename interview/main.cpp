//
// Created by luoxiYun on 2021/4/5.
//

/**
 * 判断一个 IP 是否属于一个子网。

例如 192.168.67.211 属于 192.168.64.0/20。

 */
#include "common.h"
using namespace std;

bool isValid( vector<string> &ipnum, vector<string> &subnet, int prefix ){
    int shift = 8;
    for( int i = 0; prefix > 0 && i < ipnum.size(); i++ ){
        shift = min( shift, prefix );
        int sub = (1 << (8 - shift)) - 1;
        if( ( atoi(ipnum[i].c_str()) & ( (1<<8)-1 ) - sub ) != atoi(subnet[i].c_str()) )
            return false;
        prefix -= 8;
    }
    return true;
}
int main() {
    string ip, subnet;
    cin>>ip>>subnet;
    int next = 0;
    vector<string> number;
    vector<string> net;
    for( int i = 0; i < ip.length(); i++ ){
        int pos = ip.find('.',next);
        int pos2 = subnet.find('.', next);
        number.push_back( ip.substr( next, pos - next ) );
        net.push_back( subnet.substr( next, pos2 - next ) );
        next = pos+1;
    }
    int pos2 = subnet.find('/', 0);
    string prefix_num = subnet.substr( pos2+1, subnet.length() - pos2); //得到前缀编号
    cout<<isValid( number, net, atoi(prefix_num.c_str()) )<<endl;
    return 0;
}