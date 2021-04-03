//
// Created by luoxiYun on 2021/4/1.
//

#include "common.h"
#include "Trie.h"

class wordBreak{

public:

    void dfsAlongString( int begin, string &s, vector<string> &path,
                                   TrieNode *root, vector<string> &res) {
        if( begin == s.length() ){
            string sentence = "";
            for( string &ele: path)
                sentence += (ele+" ");
            sentence.pop_back();
            res.push_back(sentence);
            return;
        }

        TrieNode *trav = root;
        for( int i = begin; i < s.length(); i++ ){
            int pos = s[i] - 'a';
            if( trav->children[pos] == nullptr )
                return;
            if( trav->children[pos]->isEndOfWord ){
                path.emplace_back( s.substr(begin, i - begin+1) );
                dfsAlongString( i+1, s, path, root, res );
                path.pop_back();
            }
            trav = trav->children[pos];
        }

    }

    vector<string> enumWordBreak( string &s, vector<string> &wordDict ){
        Trie trie;
        for( string &ele : wordDict ){
            trie.insert( ele );
        }
        vector<string> path;
        vector<string> result;
        dfsAlongString(0, s,path, trie.getRoot(), result );
        for( string &ele: result )
            cout<<ele<<endl;
        return result;
    }

    bool canWordBreak( string &s, vector<string> &wordDict ){
        vector<bool> dp(s.length(), false);
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        for( int i = 0; i < s.length(); i++ ){
            string complete = s.substr( 0 , i+1 );
            if( dict.find( complete) != dict.end() ) {
                dp[i] = true;
            }else {
                for (int j = i - 1; j >= 0; j--) {
                    //dp[0...j] && s.substr[j+1...i]
                    string temp = s.substr(j + 1, i - j);
                    if (dict.find(temp) != dict.end()) {
                        dp[i] = dp[j];
                        if( dp[i] )
                            break;
                    }
                }
            }
        }
        return dp[s.length()-1];
    }

};

int main(){
    string s = "leetcode";
    vector<string> dict = { "lee", "tco","de" ,"leet", "code" };
    wordBreak wBreak;
    //cout<<(wBreak.canWordBreak(s, dict)?1:0)<<endl;
    wBreak.enumWordBreak( s, dict );
    return 0;
}
