#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int row = 0;
    int col = 0;
    bool isFind = false;
    vector<vector<char>> board;
    vector<vector<bool>> way;
    string word;

    void finder(int i, int j, int idx) {
        if(isFind) { return;}
        if(i < 0||j < 0||i >= row||j >= col||way[i][j]) { return;}
        if(board[i][j] != word[idx]) { return;}

        if(idx == word.size() - 1) {
            isFind = true;
            return;
        }

        way[i][j] = true;
        finder(i + 1, j, idx + 1);
        finder(i - 1, j, idx + 1);
        finder(i, j + 1, idx + 1);
        finder(i, j - 1, idx + 1);
        way[i][j] = false;
    }

    bool exist(vector<vector<char>>& board, string word) {
        this -> board = board;
        this -> word = word;
        row = board.size();
        col = board[0].size();
        if(row * col < word.size()) { return false;}
        way = vector<vector<bool>>(row, vector<bool>(col, false));
        
        for(int i = 0; i < row; ++i) {
            for(int j = 0; j < col; ++j) {
                finder(i, j, 0);
                if(isFind) { return true;};
            }
        }

        return isFind;
    }
};

int main() {
    Solution slu;
    vector<vector<char>> board = {{'A','B','C','E'},{'S','F','E','S'},{'A','D','E','E'}};
    string word = "ABCESEEEFS";
    slu.exist(board, word);
    return 0;
}