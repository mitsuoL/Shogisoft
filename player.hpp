#ifndef PLAYER_HPP
#define PLAYER_HPP

#include<iostream>
#include<vector>
#include<algorithm>
#include<bitset>

#include "board.hpp"
#include "piece.hpp"

class Player{
public:
    typedef int FirstPlayer;
private:
    FirstPlayer firstPlayer;
    int handPieces[Board::MAX_NUM_HAND];
public:
    Player(bool isGyoku);//コンストラクタ
    int getHandPieces(int index) const;//プレイヤーの手駒を得る関数（指定したインデックスに対して）
    void setHandPiece(int index,int numPiece);//指定したインデックスに指定した種類の駒を得る
    bool isPlayerFirst();//そのプレイヤーが最初のプレイヤーか判定する関数
    void addHandPiece(int numPiece);//手駒に指定した駒を追加する関数
    int useHandPiece(int num_piece);//指定した種類の駒を使用する関数
    void printHandPieces() const;//手駒を表示する関数
};

#endif