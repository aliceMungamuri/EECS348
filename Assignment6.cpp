// EECS 348 Assignment 6 - Sudoku Solver
// Description: Solves a 9x9 Sudoku puzzle using backtracking.
// Input: A file containing a Sudoku grid with '_' for blanks.
// Output: The original puzzle and all possible solutions.
// Author: Alice J Mungamuri
// Creation Date: April 10, 2025
// Collaborators: None
// Other sources: ChatGPT (OpenAI), C++ documentation

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class SudokuSolver {
private:
    std::vector<std::vector<char>> grid;
    int solutions = 0;

public:
    // Constructor: loads grid from file
    SudokuSolver(const std::string& filename) {
        std::ifstream inFile(filename);
        if (!inFile) {
            std::cerr << "Error opening file " << filename << std::endl;
            exit(1);
        }

        std::string line;
        while (std::getline(inFile, line)) {
            std::vector<char> row;
            for (char ch : line) {
                if (ch != ' ' && ch != '\n') {
                    row.push_back(ch);
                }
            }
            if (!row.empty()) grid.push_back(row);
        }

        inFile.close();

        if (grid.size() != 9 || grid[0].size() != 9) {
            std::cerr << "Invalid puzzle size in " << filename << std::endl;
            exit(1);
        }
    }

    // Print the Sudoku grid
    void print_matrix() const {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                std::cout << grid[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    // Check if placing a number at (r, c) is valid
    bool is_valid(int r, int c) const {
        char num = grid[r][c];

        // Check row
        for (int j = 0; j < 9; j++) {
            if (j != c && grid[r][j] == num) return false;
        }

        // Check column
        for (int i = 0; i < 9; i++) {
            if (i != r && grid[i][c] == num) return false;
        }

        // Check 3x3 box
        int boxRow = r - r % 3;
        int boxCol = c - c % 3;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                int ri = boxRow + i;
                int cj = boxCol + j;
                if ((ri != r || cj != c) && grid[ri][cj] == num) return false;
            }
        }

        return true;
    }

    // Recursive backtracking solver
    void solve_recursive(int r, int c) {
        if (r == 9) {
            print_matrix();
            std::cout << std::endl;
            solutions++;
            return;
        }

        int next_r = (c == 8) ? r + 1 : r;
        int next_c = (c + 1) % 9;

        if (grid[r][c] != '_') {
            solve_recursive(next_r, next_c);
        } else {
            for (char ch = '1'; ch <= '9'; ch++) {
                grid[r][c] = ch;
                if (is_valid(r, c)) {
                    solve_recursive(next_r, next_c);
                }
                grid[r][c] = '_'; // Backtrack
            }
        }
    }

    // Solve entry point
    void solve(const std::string& filename) {
        std::cout << "Puzzle: " << filename << "\n\n";
        print_matrix();
        std::cout << "\nSolutions:\n";
        solve_recursive(0, 0);

        if (solutions == 0) {
            std::cout << "No solution found.\n";
        } else {
            std::cout << "Total solutions: " << solutions << "\n";
        }
    }
};

// Main function to run all puzzles
int main() {
    std::vector<std::string> files = {
        "puzzle1.txt",
        "puzzle2.txt",
        "puzzle3.txt",
        "puzzle4.txt",
        "puzzle5.txt"
    };

    for (const std::string& filename : files) {
        SudokuSolver solver(filename);
        solver.solve(filename);
        std::cout << "\n==============================\n\n";
    }

    return 0;
}
