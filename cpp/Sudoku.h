#ifndef SUDOKU_H
#define SUDOKU_H

#include <bits/stdc++.h>

class Sudoku {
public:
    std::vector<std::vector<int>> grid;
    const int GRID_SIZE = 9; //定义为9列9行
    const int BOX_SIZE = 3;  //定义同一个块为3

    Sudoku(const std::string& input);
    void parse(const std::string& input);
    std::vector<int> getRow(int row);
    std::vector<int> getColumn(int col);
    std::vector<int> getBox(int row, int col);
    std::set<int> getCandidateValues(int row, int col);
    bool inference();
    void inputIsSafe(const std::string& input);
    void getAnswer();
    void printGrid();
};

#endif // SUDOKU_H