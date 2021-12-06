#include "gameengine.h"
#include <iostream>

GameEngine::GameEngine(QObject* parent) : QObject(parent) {
    resetGame();
}

void GameEngine::resetGame() {
    for(int r = 0; r < 8; ++r)
        for(int c = 0; c < 8; ++c) {
            whitesMovesToCheckBoard[r][c] = NOT_TO_CHECK;
            blacksMovesToCheckBoard[r][c] = NOT_TO_CHECK;
            avaiableMoves[r][c] = "";
            boardToShow[c + r*8] = NONE;
        }

    whitesMovesToCheckBoard[3][3] = WHITE_PAWN;
    blacksMovesToCheckBoard[3][3] = WHITE_PAWN;
    boardToShow[3 + 3*8] = WHITE;

    whitesMovesToCheckBoard[4][4] = WHITE_PAWN;
    blacksMovesToCheckBoard[4][4] = WHITE_PAWN;
    boardToShow[4 + 4* 8] = WHITE;

    whitesMovesToCheckBoard[3][4]= BLACK_PAWN;
    blacksMovesToCheckBoard[3][4]= BLACK_PAWN;
    boardToShow[4+ 3*8] = BLACK;

    whitesMovesToCheckBoard[4][3]= BLACK_PAWN;
    blacksMovesToCheckBoard[4][3]= BLACK_PAWN;
    boardToShow[3 + 4*8] = BLACK;

    markNeighbours(3, 3, true, blacksMovesToCheckBoard);
    markNeighbours(4, 4, true, blacksMovesToCheckBoard);

    markNeighbours(3, 4, true, whitesMovesToCheckBoard);
    markNeighbours(4, 3, true, whitesMovesToCheckBoard);

    isBlacksTurn = true;
    areMovesToMake = true;
    hasGameEnded = false;

    avaiableMoves[2][3] += S;
    avaiableMoves[3][2] += E;
    avaiableMoves[5][4] += N;
    avaiableMoves[4][5] += W;

    message = "Gra czarnych pionków";

    emit messageChanged();
    emit boardToShowChanged();
}


void GameEngine::markNeighbours(int row, int col, bool isWorthChecking,
             int tab[8][8]) {

    int min_x = col - 1 > 0 ? col - 1 : 0;
    int min_y = row - 1 > 0 ? row - 1 : 0;

    int max_x = col + 1 < 8 ? col + 1 : 7;
    int max_y = row + 1 < 8 ? row + 1 : 7;

    for (int y = min_y; y <= max_y; ++y)
        for (int x = min_x; x <= max_x; ++x)
            if (tab[y][x] > NOT_TO_CHECK)
            {
                if(isWorthChecking)
                    tab[y][x] += 1;
                else
                    tab[y][x] -= 1;
            }
            else if(isWorthChecking && tab[y][x] == NOT_TO_CHECK)
                tab[y][x] += 1;

}

void GameEngine::clearAvaiableMovesTab() {
    for(int r = 0; r < 8; ++r)
        for(int c = 0; c < 8; ++c)
            avaiableMoves[r][c] = "";
}

void GameEngine::checkPosition(int row, int col) {
    for(int delta_y = -1; delta_y <= 1; ++delta_y) {
        for(int delta_x = -1; delta_x <= 1; ++delta_x) {
            bool isAvaiableDirection = false;
            if(delta_x == 0 && delta_y == 0)
                continue;

            int y = row + delta_y;
            int x = col + delta_x;
            if(x < 0 || y < 0 || x >= 8 || y >= 8)
                continue;

            if(isBlacksTurn) {
                if(blacksMovesToCheckBoard[y][x] != WHITE_PAWN)
                    continue;

                while(!isAvaiableDirection && x >= 0 && x < 8
                      && y >= 0 && y < 8) {
                    if(blacksMovesToCheckBoard[y][x] == WHITE_PAWN) {
                        y += delta_y;
                        x += delta_x;
                    }
                    else if(blacksMovesToCheckBoard[y][x] == BLACK_PAWN)
                        isAvaiableDirection = true;
                    else break;
                }

            }
            else {
                if(whitesMovesToCheckBoard[y][x] != BLACK_PAWN)
                    continue;

                while(!isAvaiableDirection && x >= 0 && x < 8
                      && y >= 0 && y < 8) {
                    if(whitesMovesToCheckBoard[y][x] == BLACK_PAWN) {
                        y += delta_y;
                        x += delta_x;
                    }
                    else if(whitesMovesToCheckBoard[y][x] == WHITE_PAWN)
                        isAvaiableDirection = true;
                    else break;
                }
            }

            if(isAvaiableDirection)     //saving avaiable direction
            {
                areMovesToMake = true;
                if(delta_y == -1) {
                    if (delta_x == -1)
                        avaiableMoves[row][col] += NW;
                    else if(delta_x == 1)
                        avaiableMoves[row][col] += NE;
                    else
                        avaiableMoves[row][col] += N;

                }
                else if(delta_y == 1) {
                    if (delta_x == -1)
                        avaiableMoves[row][col] += SW;
                    else if(delta_x == 1)
                        avaiableMoves[row][col] += SE;
                    else
                        avaiableMoves[row][col] += S;
                }
                else {
                    if(delta_x == -1)
                        avaiableMoves[row][col] += W;
                    else
                       avaiableMoves[row][col] += E;
                }
            }
        }
    }
}

void GameEngine::markAllAvaiablePositions() {
    areMovesToMake = false;
    if(isBlacksTurn) {
        for(int r = 0; r < 8; ++r)
            for(int c = 0; c < 8; ++c)
                if(blacksMovesToCheckBoard[r][c] > NOT_TO_CHECK)
                {
                    checkPosition(r, c);
                }
    } else {
        for(int r = 0; r < 8; ++r)
            for(int c = 0; c < 8; ++c)
                if(whitesMovesToCheckBoard[r][c] > NOT_TO_CHECK)
                {
                    checkPosition(r, c);
                }
    }
}

void GameEngine::swapPawnsInLine(int start_x, int start_y, char direction)
{
    int delta_x = 0, delta_y = 0, pawn_color, x = start_x, y = start_y;

    if(direction == N) {
        delta_y = -1;
    }
    else if(direction == S) {
        delta_y = 1;
    }
    else if(direction == E) {
        delta_x = 1;
    }
    else if(direction == W) {
        delta_x = -1;
    }
    else if(direction == NE) {
        delta_x = 1;
        delta_y = -1;
    }
    else if(direction == NW) {
        delta_x = -1;
        delta_y = -1;
    }
    else if(direction == SE) {
        delta_x = 1;
        delta_y = 1;
    }
    else if(direction == SW) {
        delta_x = -1;
        delta_y = 1;
    }

    if(isBlacksTurn)
        pawn_color = BLACK_PAWN;
    else
        pawn_color = WHITE_PAWN;

    x += delta_x;
    y += delta_y;

    do {

        if(pawn_color == BLACK_PAWN) {
            markNeighbours(y, x, true, whitesMovesToCheckBoard);
            markNeighbours(y, x, false, blacksMovesToCheckBoard);
        } else {
            markNeighbours(y, x, false, whitesMovesToCheckBoard);
            markNeighbours(y, x, true, blacksMovesToCheckBoard);
        }

        whitesMovesToCheckBoard[y][x] = pawn_color;
        blacksMovesToCheckBoard[y][x] = pawn_color;
        boardToShow[x + y*8] = isBlacksTurn? BLACK : WHITE;

        x += delta_x;
        y += delta_y;
    } while(whitesMovesToCheckBoard[y][x] != pawn_color);
}

void GameEngine::swapPawns(int field_x, int field_y) {
    std::string swapping_directions = avaiableMoves[field_y][field_x];

    if(isBlacksTurn) {
        markNeighbours(field_y, field_x, true, whitesMovesToCheckBoard);
        markNeighbours(field_y, field_x, false, blacksMovesToCheckBoard);
        whitesMovesToCheckBoard[field_y][field_x] = BLACK_PAWN;
        blacksMovesToCheckBoard[field_y][field_x] = BLACK_PAWN;
        boardToShow[field_x + field_y*8] = BLACK;
    } else {
        markNeighbours(field_y, field_x, false, whitesMovesToCheckBoard);
        markNeighbours(field_y, field_x, true, blacksMovesToCheckBoard);
        whitesMovesToCheckBoard[field_y][field_x] = WHITE_PAWN;
        blacksMovesToCheckBoard[field_y][field_x] = WHITE_PAWN;
        boardToShow[field_x + field_y*8] = WHITE;
    }


    for (char dir: swapping_directions) {
        swapPawnsInLine(field_x, field_y, dir);
    }
}

void GameEngine::processPlayersMove(int x, int y) {
    if( !hasGameEnded && avaiableMoves[y][x] != "")
    {
        swapPawns(x, y);
        clearAvaiableMovesTab();
        isBlacksTurn = !isBlacksTurn;
        markAllAvaiablePositions();

        if(isBlacksTurn) {
            message = "Gra czarnych pionków";
        }
        else {
            message = "Gra białych pionków";
        }

        if(!areMovesToMake) {   //cannot make move
            isBlacksTurn = !isBlacksTurn;
            clearAvaiableMovesTab();
            markAllAvaiablePositions();

            if(isBlacksTurn) {
                message = "Utrata tury białych pionków - gra czarnych";
            }
            else {
                message = "Utrata tury czarnych pionków - gra białych";
            }

            if(!areMovesToMake) //end of the game
            {
                hasGameEnded = true;

                int white_pawns = 0, black_pawns = 0;
                for(int r = 0; r < 8; ++r)
                    for(int c = 0; c < 8; ++c)
                    {
                        if(whitesMovesToCheckBoard[r][c] == WHITE_PAWN)
                            ++white_pawns;

                        if(whitesMovesToCheckBoard[r][c] == BLACK_PAWN)
                            ++black_pawns;
                    }

                if(white_pawns > black_pawns)
                   message = "Koniec gry - wygrywają białe pionki!";
                else if (white_pawns < black_pawns)
                    message = "Koniec gry - wygrywają czarne pionki";
                else
                    message = "Koniec gry - remis!";
            }
        }
    }

    emit messageChanged();
    emit boardToShowChanged();
}
