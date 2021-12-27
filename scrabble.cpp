#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int whoWins(vector<vector<int>> trie, vector<bool> isWord, int curNode, vector<bool> letters) { //0 is draw, 1 is win, and 2 is lose
    if(isWord[curNode]) //other player made this word, so you lose
        return 2;
    bool canDraw = false;
    for(int i = 0; i < 26; i++) { //iterate through all the letters
        if(!letters[i]) continue; //if you can't place this letter, continue
        if(trie[curNode][i] == 0) { //placing this letter doesn't lead to any other words, so it causes a draw
            canDraw = true;
            continue;
        }
        int res = whoWins(trie, isWord, trie[curNode][i], letters); //try placing this letter
        if(res == 0) canDraw = true; //if your opponent draws when placing this letter, then you can draw by placing this letter
        if(res == 2) return 1; //if your opponent loses after placing this letter, you win
    }
    //if you got past the for loop, that means you can't win
    if(canDraw) return 0; //if you can draw, do that
    return 2; //else you lose
}

int main() {
    int g;
    cin >> g;
    int c = 1;

    while(g-->0) {
        int n, m, count = 26;
        cin >> n >> m;
        char word[10001];
        cin >> word;
        vector<bool> letters(26); //says if a letter is used

        for(int i = 0; i < strlen(word); i++) letters[word[i]-'a'] = true;

        vector<vector<int>> trie(200001); //gives next node in trie
        vector<bool> isWord(200001); //checks to see if node in trie is a word
        for(int i = 0; i < trie.size(); i++) //initialize trie
            trie[i] = vector<int>(26);
        int nextAvail = 1; //next available node in trie
        
        for(int i = 0; i < m; i++) {
            cin >> word;
            int curNode = 0;
            int len = strlen(word);
            for(int j = 0; j < len; j++) { //insert this word into the trie
                if(trie[curNode][word[j]-'a'] == 0)
                    trie[curNode][word[j]-'a'] = nextAvail++;
                curNode = trie[curNode][word[j]-'a'];
            }
            isWord[curNode] = true;
        }
        int res = whoWins(trie, isWord, 0, letters);
        if(res == 0)
            cout << "Game #" << c++ << ": Draw" << endl;
        else if(res == 1)
            cout << "Game #" << c++ << ": Alice wins" << endl;
        else
            cout << "Game #" << c++ << ": Bob wins" << endl;
    }

    return 0;
}
