/*
* Connect 6
* Brian Skinner, Essoniwa Pitoko, Tizanae Nziramasanga
* 9 long, by 8 high
*/
#include <stdlib.h>
#include <time.h>
#include <iostream>
int board[9][8] = {0};
    //    x,y
//0 = free
//1 = red
//2 = blue
int human = 0;
int AI = 0;

int game_over = 0;

void showBoard();
int pushchip(int player, int slot);
int is_win(int slot);
void AI_move();
int removechip(int player, int slot);
int is_draw();


int main(void) {
  //board[0][0] = 1;
  //board[5][1] = 2;
  int s = 0;



  std::cout << "Are you player 1 or 2?:";
  std::cin >> s;

  if(s == 1){
    human = s;
    AI = 2;
  }
  else if(s == 2){
    human = s;
    AI = 1;
  }


  while(game_over == 0) {
    if(is_draw() == 1){
      std::cout << "DRAW\n";
      exit(0);
    }
    //ai goes first
    if(human == 2) {
      AI_move();
      std::cout << std::endl;
      showBoard();
      std::cout << "Enter a vertical slot # (0-8) to play:";
      std::cin >> s;
      while(s > 8 || s < 0)
      {
        std::cout << "Error, invalid chip placement. Try again." << std::endl;
        std::cout << "Enter a slot to play:";
        std::cin >> s;
      }

      while(pushchip(human, s) == -1)
      {
        std::cout << "Error, invalid chip placement. Try again." << std::endl;
        std::cout << "Enter a slot to play:";
        std::cin >> s;
      }
      if(is_win(s) == human){
        std::cout << "HUMAN WINS!" << std::endl;
        game_over=1;
      }
      // std::cout << is_win(s) << std::endl;
      showBoard();


    }

    //human goes first
    if(human == 1){
      std::cout << "Enter a vertical slot # (0-8) to play:";
      std::cin >> s;
    while(s > 8 || s < 0)
    {
      std::cout << "Error, invalid chip placement. Try again." << std::endl;
      std::cout << "Enter a slot to play:";
      std::cin >> s;
    }

    while(pushchip(human, s) == -1)
    {
      std::cout << "Error, invalid chip placement. Try again." << std::endl;
      std::cout << "Enter a slot to play:";
      std::cin >> s;
    }
    if(is_win(s) == human){
      std::cout << "HUMAN WINS!" << std::endl;
      game_over=1;
    }
    // std::cout << is_win(s) << std::endl;
    AI_move();
    showBoard();

  }

  }


  return 1;
}

int is_draw(){
  for(int x = 0; x <= 8; x++){
    if(board[x][7] == 0) //if a free spot exsists, game is not over
      return 0;
  }
  return 1;
}



//try to win, else try to block player, else random move
void AI_move() {
//check if any moves allow ai to win
for(int x = 0; x<= 8; x++){
  if(pushchip(AI,x) != -1){
    if(is_win(x) == AI){ //ai wins, game is over
      std::cout << "AI WINS!" << std::endl;
        game_over = 1;
        return;
    }
    else {
      removechip(AI, x);
    }
  }
}

  //no good move for ai, time to check for moves against human
  for(int x = 0; x<= 8; x++){
    if(pushchip(human,x) != -1){
      if(is_win(x) == human){
        removechip(human,x);
        pushchip(AI,x);
        return;
      }
      else
        removechip(human,x);
    }
  }


  //make a random move
  int rand_num = 0;
  srand (time(NULL));
  rand_num = rand() % 9;

  while(pushchip(AI, rand_num) == -1){
    rand_num = rand() % 9;
  }
}

//removes a chip from the board, used for simulating moves
int removechip(int player, int slot) {
  int y = 7;

  for(; y >= 0; y--) {
    if(board[slot][y] == player){
      board[slot][y] = 0;
      return 1;
    }
  }
    return -1;
}




//checks for 6 in a row, returns the value of the player who won, player 1 or 2. 0 for no win
int is_win(int slot) {
int count = 0;
int player = 0;

int x_pos = 0;
int y_pos = 0;
//find the slot player value
for(int y = 7; y>= 0; y--) {
  if(board[slot][y] != 0){
    player = board[slot][y];
    x_pos = slot;
    y_pos = y;
    break;
  }
}

//we know know the player to check, along where where to start checking at.


//check left + right
for(int x = x_pos; x>= 0; x--) { //check left
  if(board[x][y_pos] != player)
    break;

  count++;
}

for(int x = x_pos; x<= 8; x++) { //check right
  if(board[x][y_pos] != player)
    break;

  count++;
}

//remove overlap
count--;

//std::cout << "left + right "<< count << " " << std::endl;
//check for win
if(count >= 6)
  return player; //player id of win

count = 0; //reset

//check up + down
for(int y = y_pos; y<= 7; y++) { //check up
  if(board[x_pos][y] != player)
    break;

  count++;
}

for(int y = y_pos; y>= 0; y--) { //check down
  if(board[x_pos][y] != player)
    break;

  count++;
}
count--;
//check for win
if(count >= 6)
  return player; //player id of win
//std::cout << "up + down "<< count << " " << std::endl;

count = 0;
//check "/"
int x = x_pos;
int y = y_pos;

while(x<= 8 && y<= 7)//up-right
{
  if(board[x][y] != player)
    break;

  count++;
  x++;
  y++;
}

x = x_pos;
y = y_pos;

while(x >= 0 && y >= 0)//down-left
{
  if(board[x][y] != player)
    break;

  count++;
  x--;
  y--;
}

//remove overlap
count--;
if(count >= 6)
  return player; //player id of win
//std::cout << " / "<< count << " " << std::endl;


count = 0;
//check "\"
x = x_pos;
y = y_pos;
while(x>= 0 && y<= 7)//up-left
{
  if(board[x][y] != player)
    break;

  count++;
  x--;
  y++;
}

x = x_pos;
y = y_pos;

while(x <= 8 && y >= 0)//down-right
{
  if(board[x][y] != player)
    break;

  count++;
  x++;
  y--;
}

//remove overlap
count--;
if(count >= 6)
  return player; //player id of win
//std::cout << " \\ "<< count << " " << std::endl;


return 0;
}



//put the chip into the board, pushes to bottem
int pushchip(int player, int slot) {
  int y = 7;
  if(board[slot][7] == 1 || board[slot][7] == 2) {
    //std::cout << "error slot full!" << std::endl;
    return -1;
  }
  else {
    while(1) {
      if(y < 0) {
        board[slot][0] = player;
        return 1;
      }

      else if(board[slot][y] == 0 && (board[slot][y-1] == 1 || board[slot][y-1] == 2)) {
        board[slot][y] = player;
        return 1;
      }
      else
        y--;
    }
  }

  return 1;
}

//show the board
void showBoard() {

  for(int y = 7; y >= 0; y--) {
    std::cout << "|";
    for(int x = 0; x < 9; x++){
      if(board[x][y] == 1)
        std::cout << "\033[1;31m0\033[0m";
      else if(board[x][y] == 2)
          std::cout << "\033[1;34m0\033[0m";
      else
        std::cout << board[x][y];
      if(x != 8)
        std::cout << " ";
    }
    std::cout <<"|" << std::endl;
  }
}
