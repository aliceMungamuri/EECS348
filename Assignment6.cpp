// EECS 348 Assignment 6
// Sudoku Solver using recursive brute-force (backtracking)
// Inputs: Sudoku puzzle files (puzzle1.txt to puzzle5.txt)
// Output: Solved Sudoku grids or "No solution found"
// Author: Alice J Mungamuri
// Created: April 10, 2025
// Collaborators: None
// Sources: ChatGPT (code debugging and comments), StackOverflow (reference on vector handling)

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Check if a cell at (r, c) is empty
bool empty_coordinate(std::vector<std::vector<char>> &grid, int r, int c) {
    return (r >= 0 && r < 9 && c >= 0 && c < 9 && grid[r][c] == '_');
}

// Check if placing the current value at grid[r][c] is valid
bool valid_coordinate(std::vector<std::vector<char>> &grid, int r, int c) {
    char num = grid[r][c];

    // Check current column for duplicate
    for (int i = 0; i < 9; i++) {
        if (i != r && grid[i][c] == num) return false;
    }

    // Check current row for duplicate
    for (int j = 0; j < 9; j++) {
        if (j != c && grid[r][j] == num) return false;
    }

    // Check 3x3 subgrid for duplicate
    int start_r = r - r % 3;
    int start_c = c - c % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int row = start_r + i;
            int col = start_c + j;
            if ((row != r || col != c) && grid[row][col] == num) return false;
        }
    }
    return true;
}

// Print the grid
void print_matrix(std::vector<std::vector<char>> &grid) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            std::cout << grid[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

// Recursive function to solve the Sudoku grid
void movement(std::vector<std::vector<char>> &grid, int r, int c, int &solutions) {
    if (r == 9) {  // If reached the end of grid
        print_matrix(grid);
        std::cout << "\n";
        solutions++;
        return;
    }

    int next_r = (c == 8) ? r + 1 : r;
    int next_c = (c + 1) % 9;

    if (!empty_coordinate(grid, r, c)) {
        movement(grid, next_r, next_c, solutions);  // Skip filled cell
        return;
    }

    for (int i = 0; i < 9; i++) {
        grid[r][c] = '1' + i;  // Try placing 1 to 9
        if (valid_coordinate(grid, r, c)) {
            movement(grid, next_r, next_c, solutions);
        }
    }
    grid[r][c] = '_';  // Backtrack
}

// Load puzzle from file
std::vector<std::vector<char>> load_puzzle(const std::string &filename) {
    std::ifstream file(filename);
    std::vector<std::vector<char>> grid(9, std::vector<char>(9));
    std::string line;
    int row = 0;
    while (std::getline(file, line) && row < 9) {
        for (int col = 0; col < 9 && col < line.length(); col++) {
            grid[row][col] = line[col];
        }
        row++;
    }
    return grid;
}

int main() {
    for (int i = 1; i <= 5; i++) {
        std::string filename = "puzzle" + std::to_string(i) + ".txt";
        std::cout << "Solving: " << filename << std::endl;

        std::vector<std::vector<char>> grid = load_puzzle(filename);
        print_matrix(grid);

        int solutions = 0;
        movement(grid, 0, 0, solutions);

        if (solutions == 0) {
            std::cout << "No solution found.\n" << std::endl;
        }
    }
    return 0;
}
