//
// Created by luoxiYun on 2021/4/3.
//

#include "common.h"

class WordLadder{

public:
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
    }
    int ladderLength(string &beginWord, string &endWord, vector<string> &wordList ){
        queue<string> q;
        unordered_map<string, int> distance;
        distance[beginWord] = 1;
        q.push( beginWord );
        while( !q.empty() ){
            string &top = q.front();
            q.pop();
            for( string &candidate : wordList ){
                if( distance.find(candidate) == distance.end() && diffOneS1( top, candidate ) ){
                    q.push( candidate );
                    distance[candidate] = distance[top] + 1;
                    if( candidate == endWord )
                        return distance[candidate];
                }
            }
        }
        return distance.count(endWord) == 0 ? 0 : distance[endWord];
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
    return 0;

}