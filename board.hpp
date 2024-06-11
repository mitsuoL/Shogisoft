#ifndef BOARD_HPP
#define BOARD_HPP

#include<iostream>
#include<vector>
#include<algorithm>
#include<bitset>

#include "point.hpp"
#include "piece.hpp"

class Board{
    public:
    static const int BOARD_SIZE = 9;
    static const int MAX_NUM_HAND = BOARD_SIZE*BOARD_SIZE; 
    Piece RawBoard[BOARD_SIZE+2][BOARD_SIZE+2];
    Board();//コンストラクタ
    Piece getPiece(const Point& point) const;//そのマスの駒を取得する関数
    void setPiece(const Point& point,Piece piece);//そこにおけるかどうかはgame.putPieceで判定する
    bool checkPuttable(const Point& point) const;//そこに駒が置けるかどうか判定する
    bool isWithinBoard(const Point& point) const;//ボードの範囲をチェックする関数
    std::vector<Point>getMovablePos(const Point& from) const;
    bool isMoveValid(const Point& from, const Point& to) const;//その動きが正しいかどうか判定する関数
    bool checkPiecePutted(const Point& point) const;//そこに駒が置いてあるかチェックする関数
    bool checkPromotable(const Point& from,const Point& to) const;//その動きで駒が成ることができるか判定する関数
};

#endif