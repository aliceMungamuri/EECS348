// EECS 348 Assignment 6 
// Input: A file containing a Sudoku grid with '_' for blanks.
// Output: The original puzzle and all possible solutions.
// Author: Alice J Mungamuri
//  April 10, 2025
// Other sources: Stack OVerfoow (vectors )ChatGPT (OpenAI), C++ documentation - a little cclaude ai

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class SudokuSolver { // class sudoku solver - courtesy stack overflow :)
private:
    std::vector<std::vector<char>> grid; //grid: holds the current state of the puzzle
    int solutions = 0; //solutions: counts how many  solutions have been found

public:
    // Constructor: loads grid from file
    SudokuSolver(const std::string& filename) { //Opens the input file
        std::ifstream inFile(filename); // If it fails to ope
        if (!inFile) {
            std::cerr << "Error opening file " << filename << std::endl; //it prints an error
            exit(1); //exits
        }

        std::string line; //  Reads the file line by line
        while (std::getline(inFile, line)) { // //  line by line
            std::vector<char> row; //extracts non-space characters 
            for (char ch : line) { // for char in line pulls each 
                if (ch != ' ' && ch != '\n') {
                    row.push_back(ch); 
                }
            }
            if (!row.empty()) grid.push_back(row); //builds the 2D grid.
        }

        inFile.close(); // close the file

        if (grid.size() != 9 || grid[0].size() != 9) { //is the puzzle is 9x9
            std::cerr << "Invalid puzzle size in " << filename << std::endl; // makes sure its valid
            exit(1); // exit
        }
    }

    
    void print_matrix() const { // Print the Sudoku grid
        for (int i = 0; i < 9; i++) { // print ing the gir row by col
            for (int j = 0; j < 9; j++) {
                std::cout << grid[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

  
    bool is_valid(int r, int c) const {  // Check if placing a number at (r, c) is valid
        char num = grid[r][c]; //Checks if placing num at row r, column c is valid
     
        for (int j = 0; j < 9; j++) {   // Check row
            if (j != c && grid[r][j] == num) return false;
        }

     
        for (int i = 0; i < 9; i++) {   // Check column
            if (i != r && grid[i][c] == num) return false;
        }

     
        int boxRow = r - r % 3;   // Check 3x3 box
        int boxCol = c - c % 3; // col
        for (int i = 0; i < 3; i++) { //📘 Checks the 3x3 subgrid that the cell belongs to
            for (int j = 0; j < 3; j++) {
                int ri = boxRow + i;
                int cj = boxCol + j;
                if ((ri != r || cj != c) && grid[ri][cj] == num) return false;
            }
        }

        return true;
    }

    
    void solve_recursive(int r, int c) {// Recursive backtracking solver
    
        if (r == 9) { // Base case we reach row 9, the puzzle is complete
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

   
    void solve(const std::string& filename) { // Solve entry point
        std::cout << "Puzzle: " << filename << "\n\n";
        print_matrix();
        std::cout << "\nSolutions:\n";
        solve_recursive(0, 0); // Starts solving from the top-left

        if (solutions == 0) {
            std::cout << "No solution found.\n";
        } else {
            std::cout << "Total solutions: " << solutions << "\n";
        }
    }
};

int main() {
    std::vector<std::string> files = {// Main function to run all puzzles
        "puzzle1.txt", // all the puzzles
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
