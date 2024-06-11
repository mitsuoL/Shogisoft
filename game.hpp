#ifndef GAME_HPP
#define GAME_HPP

#include<iostream>
#include<vector>
#include<algorithm>
#include<bitset>

#include "board.hpp"
#include "piece.hpp"
#include "player.hpp"
#include "point.hpp"

class Game{
private:
    Player player1;
    Player player2;
    Board board;
    int Turn;
public:
    Game();//コンストラクタ
    void printBoard();//ボードをコンソール表示する
    void putPiece(Point point,int num_piece,Player &player);//指定したポイントに駒を置く
    void movePiece(Point from,Point to,bool promote=false);//指定した場所から駒を動かす
    void promotePiece(Point from,Point to);//駒をなる
    void printMovablePos(Point from);//動けるポイントを表示する
    void printHandPieces();//手駒を表示する
    void printPieceMovableDir(Point point);//駒が動ける方向を表示する
    void printPieceMovableDirEternal(Point point);//駒が永続的に動ける方向を表示する
    void printIsMovable(Point from,Point to);//駒が指定した場所から場所へ動けるかどうか判定する
    void printPieceNum(Point point);//指定した駒の番号を取得する
};

#endif