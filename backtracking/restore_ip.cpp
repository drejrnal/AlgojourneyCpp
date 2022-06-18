//
// Created by luoxiYun on 2021/8/24.
//

/*
 * 力扣题目95：恢复IP地址
 */
#include "common.h"

vector<string> ip_addrs;
vector<string> on_fly;  //存储递归过程中中间产生的结果

void enum_ip_addrs( const string &digits, int cur, int depth ){
    if( cur == digits.length() && on_fly.size() == 4 ) {
        //assert( on_fly.size() == 4 );
        string ip_addr = "";
        for( int i = 0; i < on_fly.size(); i++ ){
            ip_addr +=on_fly[i];
            if( i != on_fly.size()-1 )
                ip_addr+=".";
        }
        ip_addrs.push_back( ip_addr );
        return;
    }
    //递归深度不能超过4
    if( depth == 4 )
        return;
    //首位是0，则以此字符作为ip addr一部分
    if( digits[cur] == '0' ){
        on_fly.emplace_back("0");
        enum_ip_addrs( digits, cur+1, depth+1 );
        on_fly.pop_back();
        return;
    }
    string addr = "";
    for( int i = 0; i < 3; i++ ){
        addr +=digits[cur+i];
        if( atoi(addr.c_str()) > 255 )
            break;
        on_fly.push_back( addr );
        enum_ip_addrs( digits,cur+i+1, depth+1 );
        //恢复on_fly
        on_fly.pop_back();
    }
}

int main(){
    string ip_integer = "101023";
    enum_ip_addrs( ip_integer, 0, 0 );
    for( string &ele : ip_addrs )
        cout<<ele<<" ";
    cout<<endl;
    return 0;
}