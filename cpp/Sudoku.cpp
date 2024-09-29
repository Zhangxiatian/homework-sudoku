#include "Sudoku.h"

// Sudoku类 构造函数
Sudoku::Sudoku(const std::string &input)
{
    parse(input);
}

// 解析字符串输入
void Sudoku::parse(const std::string &input)
{
    inputIsSafe(input);
    grid.resize(GRID_SIZE, std::vector<int>(GRID_SIZE, 0));
    int cnt = 0;
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            grid[i][j] = input[cnt++] - '0';
        }
    }
}

// 检查输入是否正确
void Sudoku::inputIsSafe(const std::string &input)
{
    if (input.size() != 81)
    {
        throw std::invalid_argument("The input string length must be 81");
    }
}

// 获取指定行的内容
std::vector<int> Sudoku::getRow(int row)
{
    return grid[row];
}

// 获取指定列的内容
std::vector<int> Sudoku::getColumn(int col)
{
    std::vector<int> column(GRID_SIZE, 0);
    for (int i = 0; i < GRID_SIZE; i++)
    {
        column[i] = grid[i][col];
    }
    return column;
}

// 获取指定九宫格的内容
std::vector<int> Sudoku::getBox(int row, int col)
{
    std::vector<int> box(BOX_SIZE * BOX_SIZE, 0);
    int cnt = 0;
    int startRow = (row / BOX_SIZE) * BOX_SIZE;
    int startCol = (col / BOX_SIZE) * BOX_SIZE;
    for (int i = startRow; i < startRow + BOX_SIZE; i++)
    {
        for (int j = startCol; j < startCol + BOX_SIZE; j++)
        {
            box[cnt++] = grid[i][j];
        }
    }
    return box;
}

// 深度优先搜索法尝试解决问题
bool Sudoku::inference()
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            if (grid[i][j] == 0)
            {
                std::set<int> candidates = getCandidateValues(i, j);
                for (std::set<int>::iterator it = candidates.begin(); it != candidates.end(); it++)
                {
                    grid[i][j] = *it; // 填入候选值
                    if (inference())
                    { // 搜索下一格
                        return true;
                    }
                    grid[i][j] = 0; // 回溯时重置相关值
                }
                return false;
            }
        }
    }
    return true; // 成功找到一种解决方法
}

// 检查特定位置的候选值
std::set<int> Sudoku::getCandidateValues(int row, int col)
{

    std::set<int> candidates{1, 2, 3, 4, 5, 6, 7, 8, 9};

    // 检查所在行
    std::vector<int> rowValues = getRow(row);
    for (int i = 0; i < GRID_SIZE; i++)
    {
        candidates.erase(rowValues[i]);
    }

    // 检查所在列
    std::vector<int> columnValues = getColumn(col);
    for (int i = 0; i < GRID_SIZE; i++)
    {
        candidates.erase(columnValues[i]);
    }

    // 检查所在的宫格
    std::vector<int> boxValues = getBox(row, col);
    for (int i = 0; i < BOX_SIZE * BOX_SIZE; i++)
    {
        candidates.erase(boxValues[i]);
    }

    return candidates;
}

void Sudoku::getAnswer()
{
    if (inference())
    {
        std::cout << "One of the sudoku answers is:" << std::endl;
        printGrid();
    }
    else{
        std::cout << "The sudoku has no solution." << std::endl;
    }
}

//输出数独
void Sudoku::printGrid()
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::string input = "017903600000080000900000507072010430000402070064370250701000065000030000005601720";
    Sudoku sudoku(input);

    sudoku.getAnswer();

    return 0;
}