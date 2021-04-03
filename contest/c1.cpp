//
// Created by luoxiYun on 2021/3/28.
//

#include <string>
#include <iostream>
#include <unordered_set>

using namespace std;

class S1{

public:
    int numDifferentIntegr( string &word ){
        for( char &ele : word ){
            if( isalpha(ele) )
                ele = ' ';
        }
        //cout<<word<<endl;
        unordered_set<string> result;
        int trav = 0;
        while ( trav < word.length() ) {
            if( word[trav] == ' ' ){
                trav++;
                continue;
            }
            int pos = word.find_first_of(' ', trav);
            while( word[trav] == '0' ) trav++;
            if( pos != string::npos) {

                result.insert(word.substr(trav, pos - trav));
                trav = pos+1;
            }
            else{
                result.insert( word.substr( trav, word.length() - trav ));
                break;
            }
        }
        /*for( auto ele : result )
            cout<<ele<<" ";
        cout<<endl;*/
        return result.size();
    }
};

int main(){
    string s = "167278959591294";
    S1 s1;
    cout<<s1.numDifferentIntegr( s )<<endl;
    return 0;
}