//
// Created by luoxiYun on 2021/4/1.
//

#include "common.h"
#include "Trie.h"

class wordBreak{

public:

    void dfsAlongString( int begin, string &s, vector<string> &path,
                                   TrieNode *root, vector<string> &res, const vector<bool> &dp) {
        if( !dp[begin] )
            return;
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
            //查找s.substr[begin,i]是否在前缀树中
            int pos = s[i] - 'a';
            if( trav->children[pos] == nullptr )
                return;
            if( trav->children[pos]->isEndOfWord ){
                path.emplace_back( s.substr(begin, i - begin+1) );
                dfsAlongString( i+1, s, path, root, res, dp );
                path.pop_back();
            }
            trav = trav->children[pos];
        }
    }

    //dp[i]表示s[i...s.length()-1]子字符串是否能拆成字典中的单词
    vector<bool> calcuDp( string &s, TrieNode *root ){
        vector<bool> dp( s.length()+1, false );
        dp[s.length()] = true;

        for( int i = s.length()-1; i >= 0; i-- ){
            //以s[i]为起点查找前缀树中包含s[i...]的前缀
            TrieNode *trav = root;
            for( int j = i; j < s.length(); j++ ){
                int pos = s[j] - 'a';
                if( trav->children[pos] == nullptr )
                    break;
                trav = trav->children[pos];
                if ( trav->isEndOfWord )
                    dp[i] = dp[j+1];
                if( dp[i] )
                    break;
            }
        }

        return dp;
    }

    vector<string> enumWordBreak( string &s, vector<string> &wordDict ){
        Trie trie;

        for( string &ele : wordDict ){
            trie.insert( ele );
        }
        vector<string> path;
        vector<string> result;
        vector<bool> dp = calcuDp( s, trie.getRoot() );
        dfsAlongString(0, s,path, trie.getRoot(), result, dp );
        for( string &ele: result )
            cout<<ele<<endl;
        return result;
    }

    //dp[i]表示s[0...i]能否拆成字典中的单词
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
    //string s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    //vector<string> dict = { "a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"};
    string s = "leetcode";
    vector<string> dict = { "leet", "lee", "code", "tcod","e"};
    wordBreak wBreak;
    //cout<<(wBreak.canWordBreak(s, dict)?1:0)<<endl;
    wBreak.enumWordBreak( s, dict );
    return 0;
}
