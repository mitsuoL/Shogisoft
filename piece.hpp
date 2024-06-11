#ifndef PIECE_HPP
#define PIECE_HPP

#include<iostream>
#include<vector>
#include<algorithm>
#include<bitset>

class Piece{//駒を表すクラス
public:
    //それぞれの駒を数値化
    typedef int NumPiece;
    static const NumPiece NONE = 0;//空白も定義しておく
    static const NumPiece WALL = -1;//空白も定義しておく
    static const NumPiece PAWN = 1;
    static const NumPiece LANCE = 2;
    static const NumPiece KNIGHT = 3;
    static const NumPiece SILVER = 4;
    static const NumPiece GOLD = 5;
    static const NumPiece BISHOP = 6;
    static const NumPiece ROOK = 7;
    static const NumPiece KING = 8;
    static const int promoteFlag = 1<<4;

    enum moveDir{
        UPPER = 1 << 0,
        LOWER = 1 << 1,
        LEFT = 1 << 2,
        RIGHT = 1 << 3,
        UPPER_LEFT = 1 << 4,
        UPPER_RIGHT = 1 << 5,
        LOWER_LEFT = 1 << 6,
        LOWER_RIGHT = 1 << 7,
        UPPER_LEFT_KNIGHT = 1 << 8,
        UPPER_RIGHT_KNIGHT  = 1 << 9,  // 0000001000000000
        LOWER_LEFT_KNIGHT   = 1 << 10, // 0000010000000000
        LOWER_RIGHT_KNIGHT  = 1 << 11,  // 0000100000000000
    };

    enum eternalDir{
        E_UPPER = 1<<0,
        E_LOWER = 1<<1,
        E_LEFT = 1<<2,
        E_RIGHT = 1<<3,
        E_UPPER_LEFT = 1<<4,
        E_UPPER_RIGHT = 1<<5,
        E_LOWER_LEFT = 1<<6,
        E_LOWER_RIGHT = 1<<7,
    };

private:
    NumPiece numPiece;
    typedef std::string NamePiece;
    NamePiece namePiece;
    typedef unsigned int DirMovable;
    DirMovable dirMovable;
    typedef unsigned DirEternal;
    DirEternal dirEternal;
    bool isTurnFirst;
    bool isPromoted;
public:
    std::string getPieceName() const;//駒の名前を取得する関数
    unsigned getPieceNum() const;//駒の番号を取得する関数
    unsigned getMovableDir();//その駒が動ける方向を取得する関数
    unsigned getDirEternal();//その駒が永続的に動ける方向を取得する関数
    bool checkFirst();//その駒が先行の駒かどうか判定する関数
    Piece(int num_piece=0,bool isTurnFirst=true);//駒のコンストラクタ
    bool checkPromotable();//その駒が成ることができるか判定する関数
    bool checkPromoted() const;
    NumPiece getOriginalPieceType() const;
};

#endif