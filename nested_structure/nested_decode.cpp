//
// Created by luoxiYun on 2021/8/17.
//

#include "common.h"

struct Node{
    int depth;
    string partial;
};

bool isHex( char c ){
    return ( c >= '0' && c <= '9' ) || ( c >= 'A' && c <= 'F' ) || ( c >= 'a' && c <= 'f' );
}
int hexchar_to_value( char c ){
    if(c >= '0' && c <= '9')
        return c - '0';
    if( c >= 'a' && c <= 'f' )
        return c - 'a' + 10;
    if( c >= 'A' && c <= 'F' )
        return c - 'A' + 10;
}

Node eval( const string &codec, int begin ){
    if( isalnum(codec[begin]) ){
        Node node;
        node.depth = 1;
        node.partial = codec[begin];
        return node;
    }
    Node left, right, merge;
    if ( codec[begin] == '%' ) {
        left = eval(codec, begin + 1);
        right = eval(codec, begin + left.depth+1);
    }
    merge.depth = left.depth + right.depth + 1;
    char left_char = left.partial[0];
    char right_char = right.partial[0];
    if ( isHex(left_char) && isHex(right_char) ) {
        char decode = char(hexchar_to_value(left_char) * 16 + hexchar_to_value(right_char));
        merge.partial = decode;
    }
    else
        merge.partial = '%' + ( left.partial + right.partial );
    return merge;
}

string nested_decode( const string &str ){
    string res = "";
    int trav = 0;
    while ( trav < str.length() ){
        if( str[trav] != '%' ){
            res +=str[trav];
            trav++;
        }else{
            Node dfs = eval( str, trav );
            int offset = dfs.depth;
            trav +=offset;
            res +=dfs.partial;
        }
    }
    return res;
}

string nested_decode_using_stack( const string &str ){
    vector<char> str_stack;
    for( int i = 0; i < str.length(); i++ ){
        str_stack.push_back( str[i] );
        while ( str_stack.size() > 2 && (str_stack[str_stack.size()-3] == '%')
        && isHex(str_stack[str_stack.size()-2]) && isHex(str_stack[str_stack.size()-1]) ){
            char decode = char(hexchar_to_value(str_stack[str_stack.size()-2]) * 16 +
                    hexchar_to_value(str_stack[str_stack.size()-1]) );
            str_stack.pop_back();
            str_stack.pop_back();
            str_stack.pop_back();
            str_stack.push_back(decode);
        }

    }
    string res = "";
    for ( char ele : str_stack )
        res +=ele;
    return res;
}

int main(){
    string exp = "b%%%253%332%256%31ca.2%%3%%3%33%%32532%25%325%25%33%3%%332%%%%33%%33335%344%2%352B%25%2533%33/%%331";
    cout<<nested_decode_using_stack(exp)<<endl;
    return 0;
}