import Sudoku


if __name__ == "__main__":
    input_str = "017903600000080000900000507072010430000402070064370250701000065000030000005601720"
    sudoku = Sudoku.Sudoku(input_str)
    sudoku.get_answer()