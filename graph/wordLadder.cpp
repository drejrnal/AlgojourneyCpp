//
// Created by luoxiYun on 2021/4/3.
//

#include "common.h"

class WordLadder{

public:

    /*
    bool diffOneS1(string &word1, string &word2 ){
        int count = 0;
        for( int i = 0; i < word1.length(); i++ ){
            if( word1[i] != word2[i] )
                count++;
            if( count > 1 )
                break;
        }
        return count <= 1;
    }

    bool diffOneS2(string &word1, string &word2 ){
        int res = 0;
        int bucket[26] = {0};
        for (int i = 0; i < word1.length(); ++i) {
            bucket[word1[i]-'a']++;
        }
        for (int i = 0; i < word2.length(); ++i) {
            if ( res > 1)
                break;
            int index = word2[i] - 'a';
            if( bucket[index] == 0 )
                res++;
            else
                bucket[index]--;
        }
        return res <= 1;
    }*/

    vector<string> findNeighbor( string &source, unordered_set<string> &candidates ){
        string temp;
        vector<string> res;
        for( int i = 0; i < source.length(); i++ ){
            string pre = source.substr(0, i);
            string pos = source.substr( i + 1, source.length() - i - 1 );
            for (int j = 0; j < 26; ++j) {
                temp =pre;
                temp += (j+'a');
                temp += pos;
                if( candidates.find( temp ) != candidates.end() )
                    res.push_back( temp );
            }
        }
        return res;
    }

    bool findNeighborS2( string &source, unordered_set<string> &candidates,
                                 unordered_set<string> &nextLevelList,
                                 unordered_set<string> &endList,
                                 unordered_set<string> &visited ){
        string temp;

        for( int i = 0; i < source.length(); i++ ){
            string pre = source.substr(0, i);
            string pos = source.substr( i + 1, source.length() - i - 1 );
            for (int j = 0; j < 26; ++j) {
                temp =pre;
                temp += (j+'a');
                temp += pos;
                //source的某一邻接点已经被另一端访问过，即两端节点相遇
                if( endList.find( temp ) != endList.end() )
                    return true;
                if( visited.find(temp) == visited.end() && candidates.find( temp ) != candidates.end() ) {
                    visited.insert( temp );
                    nextLevelList.insert(temp);
                }
            }
        }
        return false;
    }

    int ladderLength(string &beginWord, string &endWord, vector<string> &wordList ){
        queue<string> q;
        unordered_set<string> neighbors;
        for( string &ele : wordList )
            neighbors.insert( ele );
        unordered_map<string, int> distance;
        distance[beginWord] = 1;
        q.push( beginWord );
        while( !q.empty() ){
            string top = q.front();
            q.pop();
            for( string &candidate : findNeighbor(top, neighbors) ){
                if( distance.find(candidate) == distance.end()  ){
                    q.push( candidate );
                    distance[candidate] = distance[top] + 1;
                    if( candidate == endWord ) {
                        return distance[candidate];
                    }
                }
            }
        }
        return distance.count(endWord) == 0 ? 0 : distance[endWord];
    }

    //双向搜索
    int BiDirectionLadder( string &beginWord, string &endWord, vector<string> &wordList ){
        unordered_set<string> beginDirection, endDirection, neighbors, visited;
        for( string &ele : wordList )
            neighbors.insert( ele );
        int step = 1;

        beginDirection.insert( beginWord );
        endDirection.insert( endWord );
        while( !beginDirection.empty() && !endDirection.empty() ){
            if( beginDirection.size() > endDirection.size() )
                std::swap( beginDirection, endDirection );
            unordered_set<string> nextLevel;
            for( string word : beginDirection ){
                if( findNeighborS2( word, neighbors, nextLevel, endDirection, visited) ){
                    return step+1;
                }
            }
            step++;
            beginDirection = nextLevel;
        }
        return 0;
    }

};

int main(){
    WordLadder wordLadder;
    string beginWord = "qa", endWord = "sq";
    vector<string> wordList = { "si","go","se","cm","so","ph","mt","db","mb",
                                "sb","kr","ln","tm","le","av","sm","ar","ci","ca",
                                "br","ti","ba","to","ra","fa","yo","ow","sn","ya",
                                "cr","po","fe","ho","ma","re","or","rn","au","ur",
                                "rh","sr","tc","lt","lo","as","fr","nb","yb","if","pb",
                                "ge","th","pm","rb","sh","co","ga","li","ha","hz","no",
                                "bi","di","hi","qa","pi","os","uh","wm","an","me","mo",
                                "na","la","st","er","sc","ne","mn","mi","am","ex","pt",
                                "io","be","fm","ta","tb","ni","mr","pa","he","lr","sq","ye"
    };
    cout<<wordLadder.ladderLength( beginWord, endWord, wordList )<<endl;
    //cout<<wordLadder.BiDirectionLadder( beginWord, endWord, wordList )<<endl;
    return 0;
}