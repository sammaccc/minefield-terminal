#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>

struct piece {

    bool hasBomb;
    int x,y;
    short int number;
	bool showNumber;
	bool current;

    piece(int xset, int yset) {
        hasBomb = false;
        number = 0;
        x = xset;
        y = yset;
    	showNumber = false;
		current = false;

	}
	void setCurrent(bool val) {
		current = val;
	}	
	void setShowNumber() {
		showNumber = true;
	}

    void setBomb() {
        hasBomb = true;
    }

};



void calculate_numbers(piece*** pieces, int size) {


    for (int i = 0; i < size; ++i) {
        for (int ii = 0; ii < size; ++ii) {
            int x = (*pieces)[i][ii].x;
            int y = (*pieces)[i][ii].y;

            for (int checkX = x-1; checkX <= x+1; ++checkX) {

                for (int checkY = y-1; checkY <= y+1; ++checkY) {
                    if ( !(checkX < 0) && !(checkX >= size) && !(checkY < 0) &&
                        !(checkY >= size) && !((checkX == x) && (checkY == y)) ) 
                        {
                            if ((*pieces)[checkX][checkY].hasBomb) {
                                (*pieces)[x][y].number += 1;
                            }
                    }
                }
            }
        }
    }


}


void setup(piece*** pieces, int size, int numMines) {


    *pieces = (piece**) malloc(sizeof(piece*) * size);
    for (int i = 0; i < size; ++i) {
        (*pieces)[i] = (piece*) malloc(sizeof(piece) * size);

        for (int ii = 0; ii < size; ++ii) {

            (*pieces)[i][ii] = piece(i, ii);

        
    	}
	}   

    int minesPlaced = 0;
    while (minesPlaced < numMines) {

        int x = rand()%size;
        int y = rand()%size;

        if (!(*pieces)[x][y].hasBomb) {
            (*pieces)[x][y].setBomb();
            minesPlaced += 1;
        }

    }

    calculate_numbers(pieces, size);

}

void print_board(piece** pieces, int size) {


	system("cls");
    for (int i = 0; i < size; ++i) {
        for (int ii = 0; ii < size; ++ii) {
        
			std::cout << " ";
            
			if (pieces[ii][i].current) {
				std::cout << "_";
			} else if (pieces[ii][i].showNumber) {
                std::cout << pieces[ii][i].number;
            } else {
				std::cout << "*";
			}

			std::cout << " ";
        }

        std::cout << "\n";
    }
    std::cout << "\n\n";


}



void free_all(piece** pieces, int size) {
    for (int i = 0; i < size; ++i) {
        free(pieces[i]);
    }
    free(pieces);

}




void input(char input, piece*** pieces, int* totalFound, bool* gameOver, int size, int* currx, int* curry) {


            
		switch (input) {
            case 'w':
                
				(*pieces)[*currx][*curry].setCurrent(false);
				
				if (*curry > 0) {
					*curry -= 1;
				}
                break;
            case 'a':

				(*pieces)[*currx][*curry].setCurrent(false);
				if (*currx > 0) {
					*currx -= 1;
				}
                break;
            case 's':

				(*pieces)[*currx][*curry].setCurrent(false);
				if (*curry < (size-1)) {
					*curry += 1;
				}
                break;
            case 'd':

				(*pieces)[*currx][*curry].setCurrent(false);
				if (*currx < (size-1)) {
					*currx += 1;
				}
				break;
			case 'e':
				
				if ((*pieces)[*currx][*curry].hasBomb) {
					*gameOver = true;
				} else if (!(*pieces)[*currx][*curry].showNumber){
					

					(*pieces)[*currx][*curry].setShowNumber();
					*totalFound += 1;
				}
					
				break;
            default:
                break;
		};

		(*pieces)[*currx][*curry].setCurrent(true);
		print_board(*pieces, size);
}	

int play_game(int size, int numMines) {

    piece** pieces;
    setup(&pieces, size, numMines);

	

	bool gameOver = false;
	int trueSquares = (size*size - numMines);
	int totalFound = 0;
	int currx = size/2;
	int curry = size/2;
		
	pieces[currx][curry].setCurrent(true);
	print_board(pieces,size);

    while (!gameOver) {

       
		if (kbhit()) {
            input(getch(), &pieces, &totalFound, &gameOver, size, &currx, &curry);
        }
		if (totalFound == trueSquares) {
			break;
		}
		Sleep(300);
    }


	if (gameOver) {
    	std::cout << "boom\n";
    } else {
		std::cout << "u won :D\n";
	}
	
    free_all(pieces, size);
    return 1;
}

int main() {

	int size, numMines;
	std::cout << "enter board size\n";

	std::cin >> size;
	
	if (std::cin.fail()) {
		return -1;
	}
	std::cout << "and number of mines\n";

	std::cin >> numMines;
	if (std::cin.fail()) {
		return -1;
	}

    return play_game(size, numMines);
}
