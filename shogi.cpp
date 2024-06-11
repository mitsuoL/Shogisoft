//王：K　飛車；R　角；B　金；G　銀：S　桂馬：N　香車：L　歩：P
#include "Shogi.h"
#include "game.hpp"
#include "board.hpp"
#include "piece.hpp"
#include "player.hpp"
#include "point.hpp"
using namespace std;

int main(){
    Game game;
    game.printBoard();
    game.printHandPieces();
    game.movePiece(Point(1,3),Point(1,4),true);
    game.movePiece(Point(1,4),Point(1,5),true);
    game.movePiece(Point(1,5),Point(1,6),true);
    game.movePiece(Point(1,6),Point(1,7),true);
    game.printPieceMovableDir(Point(1,7));
    game.movePiece(Point(1,7),Point(1,8));
    game.movePiece(Point(3,2),Point(1,2),true);
    game.movePiece(Point(1,2),Point(1,7),true);
    game.printPieceNum(Point(1,7));
    game.printPieceMovableDir(Point(1,7));
    game.printBoard();
    game.printHandPieces();
    return 0;
}
