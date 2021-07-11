//
// Created by luoxiYun on 2021/4/3.
// modify on 2021/4/10 2021/6/20
//

#include "common.h"

class WordLadder {

private:
    unordered_set<string> dictionary; //类依赖的资源：字典
    unordered_map<string, vector<string>> graph_path; //bfs过程中构建的图，便于dfs构建从beginWord->endWord的路径
    vector<vector<string>> path_result;
public:
    explicit WordLadder(vector<string> &wordSet) : dictionary(wordSet.begin(), wordSet.end()) {

    }

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
    */

    bool diffOneS2(string &word1, string &word2) {
        int res = 0;
        int bucket[26] = {0};
        for (int i = 0; i < word1.length(); ++i) {
            bucket[word1[i] - 'a']++;
        }
        for (int i = 0; i < word2.length(); ++i) {
            if (res > 1)
                break;
            int index = word2[i] - 'a';
            if (bucket[index] == 0)
                res++;
            else
                bucket[index]--;
        }
        return res <= 1;
    }

    vector<string> findNeighbor(string &source, unordered_set<string> &candidates) {
        string temp;
        vector<string> res;
        for (int i = 0; i < source.length(); i++) {
            string pre = source.substr(0, i);
            string pos = source.substr(i + 1, source.length() - i - 1);
            for (int j = 0; j < 26; ++j) {
                temp = pre;
                temp += (j + 'a');
                temp += pos;
                if (candidates.find(temp) != candidates.end())
                    res.push_back(temp);
            }
        }
        return res;
    }

    bool findNeighborS2(string &source, unordered_set<string> &candidates,
                        unordered_set<string> &nextLevelList,
                        unordered_set<string> &endList,
                        unordered_set<string> &visited) {
        string temp;

        for (int i = 0; i < source.length(); i++) {
            string pre = source.substr(0, i);
            string pos = source.substr(i + 1, source.length() - i - 1);
            for (int j = 0; j < 26; ++j) {
                temp = pre;
                temp += (j + 'a');
                temp += pos;
                //source的某一邻接点已经被另一端访问过，即两端节点相遇
                if (endList.find(temp) != endList.end())
                    return true;
                if (visited.find(temp) == visited.end() && candidates.find(temp) != candidates.end()) {
                    visited.insert(temp);
                    nextLevelList.insert(temp);
                }
            }
        }
        return false;
    }

    int ladderLength(string &beginWord, string &endWord, vector<string> &wordList) {
        queue<string> q;

        unordered_map<string, int> distance;
        distance[beginWord] = 1;
        q.push(beginWord);
        while (!q.empty()) {
            string top = q.front();
            q.pop();
            for (string &candidate : findNeighbor(top, dictionary)) {
                if (distance.find(candidate) == distance.end()) {
                    q.push(candidate);
                    distance[candidate] = distance[top] + 1;
                    if (candidate == endWord) {
                        return distance[candidate];
                    }
                }
            }
        }
        return distance.count(endWord) == 0 ? 0 : distance[endWord];
    }

    /*
     * 双向搜索：使用两个集合表示两个方向下一层的候选元素集
     * 当其中一个集合为空的时候，表示对应的方向无法遍历到目标节点，
     * 因此不存在beginWord->endWord的转换
     */
    int BiDirectionLadder(string &beginWord, string &endWord, vector<string> &wordList) {
        unordered_set<string> beginDirection, endDirection, visited;

        if (dictionary.find(endWord) == dictionary.end())
            return 0;
        int step = 1;

        beginDirection.insert(beginWord);
        endDirection.insert(endWord);
        while (!beginDirection.empty() && !endDirection.empty()) {
            if (beginDirection.size() > endDirection.size())
                std::swap(beginDirection, endDirection);
            unordered_set<string> nextLevel;
            for (string word : beginDirection) {
                if (findNeighborS2(word, dictionary, nextLevel, endDirection, visited)) {
                    return step + 1;
                }
            }
            step++;
            beginDirection = nextLevel;
        }
        return 0;
    }

    /**
     * @details 使用队列实现双向BFS搜索，关键在于如何确定两方向节点相遇
     * 两种方法：1. 使用两个队列，分别记录两方向的搜索空间
     *         2.使用一个队列，正向和反向交替访问图中元素
     * @param reverse: if true, 则表示从endWord开始搜索; if false, 则表示从beginWord开始搜索
     * @param distFrom*: 从beginWord/endWord到其他单词的距离
     */
    int neighborTraverse(string &word, unordered_set<string> &dict,
                         queue<string> &direction,
                         map<string, int> &distFromBegin, map<string, int> &distFromEnd, bool reverse) {
        string temp;
        int res = -1;
        for (int i = 0; i < word.length(); i++) {
            string pre = word.substr(0, i);
            string pos = word.substr(i + 1, word.length() - i - 1);
            for (int j = 0; j < 26; ++j) {
                temp = pre;
                temp += (j + 'a');
                temp += pos;
                /**
                 * @details 与word只相差一个字母的候选单词，此时未相遇
                 * 这里需要分情况讨论：1. 如果temp是第一次遍历到：则更新到temp的距离
                 * 2. 如果temp不是第一次遍历到，此时我们需要确保 @if(distFromBegin[temp] == distFromBegin[word] + 1)
                 */
                if (  dict.contains(temp) ) {
                    if(!distFromBegin.contains(temp)) {
                        distFromBegin[temp] = distFromBegin[word] + 1;
                    }
                    if( distFromBegin[temp] == distFromBegin[word] + 1 ) {
                        direction.push(temp);
                        if (reverse) {
                            graph_path[temp].push_back(word);
                        } else {
                            graph_path[word].push_back(temp);
                        }
                    }
                }
               if ( distFromEnd.contains(temp) ) {
                   res = distFromEnd[temp] + distFromBegin[temp] + 1;
               }
            }
        }
        return res;
    }

    int BiDirectionLadderUsingQueue(string &beginWord, string &endWord, vector<string> &wordList) {

        if (dictionary.find(endWord) == dictionary.end())
            return 0;
        queue<string> beginDirection, endDirection;
        map<string, int> distanceFromBegin, distanceFromEnd;
        distanceFromBegin.insert({beginWord, 0});
        distanceFromEnd.insert({endWord, 0});
        beginDirection.push(beginWord);
        endDirection.push(endWord);
        int res = -1;
        while ( !beginDirection.empty() && !endDirection.empty() ) {
            string top;
            int begin_size = beginDirection.size(), end_size = endDirection.size();
            if (beginDirection.size() <= endDirection.size()) {
                for( int i = 0; i < begin_size; i++ ) {
                    top = beginDirection.front();
                    beginDirection.pop();
                    res = neighborTraverse(top, dictionary, beginDirection, distanceFromBegin, distanceFromEnd, false);
                }

            } else {
                for( int i = 0; i < end_size; i++ ) {
                    top = endDirection.front();
                    endDirection.pop();
                    res = neighborTraverse(top, dictionary, endDirection, distanceFromEnd, distanceFromBegin, true);
                }

            }
            if (res != -1)
                break;
        }
        return res;
    }

    /**
     * @details retrieve path from @private graph_path via DFS
     * @return vector<string>
     */
    vector<vector<string>> retrievePath(string &beginWord, string &endWord) {
        vector<string> path;
        path.push_back(beginWord);
        dfs(beginWord, endWord, path);
        return path_result;
    }

    void dfs(string &node, const string &terminate, vector<string> &path) {
        if (node == terminate) {
            path_result.push_back( path );
            return;
        }
        for (string &adj : graph_path[node]) {

            path.push_back(adj);
            dfs( adj, terminate, path );
            path.pop_back();

        }
        return;
    }

    void printPartialGraph() {
        for (auto map_pair : graph_path) {
            cout << "node: " << map_pair.first << " [";
            for (string adj: map_pair.second) {
                cout << " " << adj;
            }
            cout << " ]" << endl;
        }
    }

};

int main() {
    /*
    string beginWord = "cet", endWord = "ism";
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
    string beginWord = "cet", endWord = "ism";
    vector<string> wordList = {
            "kid","tag","pup","ail","tun","woo","erg","luz",
            "brr","gay","sip","kay","per","val","mes","ohs",
            "now","boa","cet","pal","bar","die","war","hay",
            "eco","pub","lob","rue","fry","lit","rex","jan",
            "cot","bid","ali","pay","col","gum","ger","row",
            "won","dan","rum","fad","tut","sag","yip","sui",
            "ark","has","zip","fez","own","ump","dis","ads",
            "max","jaw","out","btu","ana","gap","cry","led",
            "abe","box","ore","pig","fie","toy","fat","cal",
            "lie","noh","sew","ono","tam","flu","mgm","ply",
            "awe","pry","tit","tie","yet","too","tax","jim",
            "san","pan","map","ski","ova","wed","non","wac",
            "nut","why","bye","lye","oct","old","fin","feb",
            "chi","sap","owl","log","tod","dot","bow","fob",
            "for","joe","ivy","fan","age","fax","hip","jib",
            "mel","hus","sob","ifs","tab","ara","dab","jag",
            "jar","arm","lot","tom","sax","tex","yum","pei",
            "wen","wry","ire","irk","far","mew","wit","doe",
            "gas","rte","ian","pot","ask","wag","hag","amy",
            "nag","ron","soy","gin","don","tug","fay","vic","boo","nam","ave","buy","sop","but","orb","fen","paw","his","sub","bob","yea","oft","inn","rod","yam","pew","web","hod","hun","gyp","wei","wis","rob","gad","pie","mon","dog","bib","rub","ere","dig","era","cat","fox","bee","mod","day","apr","vie","nev","jam","pam","new","aye","ani","and","ibm","yap","can","pyx","tar","kin","fog","hum","pip","cup","dye","lyx","jog","nun","par","wan","fey","bus","oak","bad","ats","set","qom","vat","eat","pus","rev","axe","ion","six","ila","lao","mom","mas","pro","few","opt","poe","art","ash","oar","cap","lop","may","shy","rid","bat","sum","rim","fee","bmw","sky","maj","hue","thy","ava","rap","den","fla","auk","cox","ibo","hey","saw","vim","sec","ltd","you","its","tat","dew","eva","tog","ram","let","see","zit","maw","nix","ate","gig","rep","owe","ind","hog","eve","sam","zoo","any","dow","cod","bed","vet","ham","sis","hex","via","fir","nod","mao","aug","mum","hoe","bah","hal","keg","hew","zed","tow","gog","ass","dem","who","bet","gos","son","ear","spy","kit","boy","due","sen","oaf","mix","hep","fur","ada","bin","nil","mia","ewe","hit","fix","sad","rib","eye","hop","haw","wax","mid","tad","ken","wad","rye","pap","bog","gut","ito","woe","our","ado","sin","mad","ray","hon","roy","dip","hen","iva","lug","asp","hui","yak","bay","poi","yep","bun","try","lad","elm","nat","wyo","gym","dug","toe","dee","wig","sly","rip","geo","cog","pas","zen","odd","nan","lay","pod","fit","hem","joy","bum","rio","yon","dec","leg","put","sue","dim","pet","yaw","nub","bit","bur","sid","sun","oil","red","doc","moe","caw","eel","dix","cub","end","gem","off","yew","hug","pop","tub","sgt","lid","pun","ton","sol","din","yup","jab","pea","bug","gag","mil","jig","hub","low","did","tin","get","gte","sox","lei","mig","fig","lon","use","ban","flo","nov","jut","bag","mir","sty","lap","two","ins","con","ant","net","tux","ode","stu","mug","cad","nap","gun","fop","tot","sow","sal","sic","ted","wot","del","imp","cob","way","ann","tan","mci","job","wet","ism","err","him","all","pad","hah","hie","aim","ike","jed","ego","mac","baa","min","com","ill","was","cab","ago","ina","big","ilk","gal","tap","duh","ola","ran","lab","top","gob","hot","ora","tia","kip","han","met","hut","she","sac","fed","goo","tee","ell","not","act","gil","rut","ala","ape","rig","cid","god","duo","lin","aid","gel","awl","lag","elf","liz","ref","aha","fib","oho","tho","her","nor","ace","adz","fun","ned","coo","win","tao","coy","van","man","pit","guy","foe","hid","mai","sup","jay","hob","mow","jot","are","pol","arc","lax","aft","alb","len","air","pug","pox","vow","got","meg","zoe","amp","ale","bud","gee","pin","dun","pat","ten","mob"
    };*/
    string beginWord = "red", endWord = "tax";
    vector<string> wordList = {
            "ted","tex","red","tax","tad","den","rex","pee"
    };
    WordLadder wordLadder(wordList);
    cout << wordLadder.ladderLength(beginWord, endWord, wordList) << endl;
    cout << wordLadder.BiDirectionLadder(beginWord, endWord, wordList) << endl;
    cout << wordLadder.BiDirectionLadderUsingQueue(beginWord, endWord, wordList) << endl;
    //wordLadder.BiDirectionLadderUsingQueue( beginWord, endWord, wordList );
    wordLadder.printPartialGraph();
    vector<vector<string>> result = wordLadder.retrievePath( beginWord, endWord );
    for( auto &path : result ){
        for( string word : path )
            cout<<word<<" ";
        cout<<endl;
    }
    cout<<endl;
    return 0;
}