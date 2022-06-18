//
// Created by luoxiYun on 2021/8/25.
//

#include "common.h"

bool is_invalid_ip(string &ip) {
    istringstream is_str(ip);
    string ip_value;
    int count = 0;
    while (getline(is_str, ip_value, '.')) {
        if ((++count) > 4 || ip_value.empty() || (stoi(ip_value)) > 255)
            return true;
    }
    return false;
}

bool is_invalid_netmask(string &mask) {
    istringstream is_str(mask);
    string mask_val;
    unsigned mask_to_decimal = 0;
    while (getline(is_str, mask_val, '.')) {
        mask_to_decimal = ((mask_to_decimal << 8) + stoi(mask_val));
    }

    if (mask_to_decimal <= 0 || mask_to_decimal >= 0xffffffff ||
        ((~mask_to_decimal + 1) | (mask_to_decimal)) != mask_to_decimal)
        return true;
    return false;
}

bool is_private(string &ip) {
    istringstream is_str(ip);
    string ip_val;
    vector<string> ip_vals;
    while (getline(is_str, ip_val, '.')) {
        ip_vals.push_back(ip_val);
    }
    if (ip_vals[0] == "10")
        return true;
    else if (ip_vals[0] == "172" && (ip_vals[1] == "16" || ip_vals[1] == "32"))
        return true;
    else if (ip_vals[0] == "192" && ip_vals[1] == "168")
        return true;
    else
        return false;
}

vector<string> extract_from_ip( string &ip ){
    vector<string> res;
    istringstream stream(ip);
    string ip_component;
    while ( getline( stream, ip_component, '.') )
        res.push_back( ip_component );
    return res;
}
bool is_same_subnet( string &ip1, string &ip2, string &subnet ){
    vector<string> ip1_component = extract_from_ip( ip1 );
    vector<string> ip2_component = extract_from_ip( ip2 );
    vector<string> subnet_component = extract_from_ip( subnet );
    for( int i = 0; i < ip1_component.size(); i++ ){
        if( (stoi(ip1_component[i])|stoi(subnet_component[i])) !=
                (stoi(ip2_component[i]) | stoi(subnet_component[i])) ){
            return false;
        }
    }
    return true;
}

int main() {
    string ip_range;
    vector<int> statistics(7, 0);
    while (getline(cin, ip_range)) {
        istringstream str_stream(ip_range);
        vector<string> ips;
        string ip;
        while (getline(str_stream, ip, '~'))
            ips.push_back(ip);
        if (is_invalid_ip(ips[1]) || is_invalid_netmask(ips[1]))
            statistics[5]++;
        else {
            if (is_invalid_ip(ips[0]))
                statistics[5]++;
            else {
                if (is_private(ips[0]))
                    statistics[6]++;

                istringstream in(ips[0]);
                string ip_first;
                getline(in, ip_first, '.');
                if (stoi(ip_first) >= 1 && stoi(ip_first) < 127)
                    statistics[0]++;
                else if (stoi(ip_first) >= 128 && stoi(ip_first) < 192)
                    statistics[1]++;
                else if (stoi(ip_first) >= 192 && stoi(ip_first) < 224)
                    statistics[2]++;
                else if (stoi(ip_first) >= 224 && stoi(ip_first) < 240)
                    statistics[3]++;
                else
                    statistics[4]++;
            }
        }
    }
    for (int state : statistics)
        cout << state << " ";
    cout << endl;
    return 0;
}