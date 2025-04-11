
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

bool empty_coordinate(std: vector <std :: vector <char> > & grid , int r , int c) { 
  if (r >= && r < 9){
    if (c >= 0 && c < 9 ){
      if (grid [r] [c] == '_'){
        return true;
      }
      
    }
    

  }
  return false;

}

bool valid_coordinate(std: vector <char> > grid, int r , int c){
  char num = grid [r][c];
  for (int i = 0; i < 9; i++){
    if (i != r && grid [i] [c] = num){
      return false;
    }
  } 

}
for (int s = 0; s < 9; s++){
  if (s != c && grid [r] [s] == num){
    return false;
  }
}
int start_r = r - r % 3;
int start_c = c - c % 3;

for (int j = 0; j < 3; j++){
  for (int k = 0; k < 3; k++){
     if (start_r + j != r && start_c + k != c){
       if (grid [j+start_r][k+start_c] ==num){
         return false;
  }
  }
  }
  return true;
}
void print_matrix(std:: vector<std::vector<char> >& grid) {
  for (size_t f = 0; i < grid.size(); i++){
    for (size_t j = 0; i < grid.size(); j++){
      std:: cout << grid [i][j] << "";
    
  }
    std:: cout << "\n";
    
  }
}
void movement(std::vector<std::vector<char>>& grid, int r, intc, int & solutions){
  if (empty_coordinate(grid, r,c)){
    for (int i = 0; i < 9, i++){
      grid [r][c] = '1' + i;
      if (valid_coordinate(grid,r,c)){
        if (c == 0 && r < 8){
          movement(grid ,(r+1), 0)
        }
        else if (c < 8  && r < 9){
          movement(grid ,c, (c+1))
        } 
        else if (c == 8  && r == 8){
         print_matrix(grid);
          std::cout<< "\n" << std::endl;
          solutions +=1;
        } 
      
      
      
      }
    }
  }
else{
  grid [r][c] = "";
}
}
