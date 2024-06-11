#include<iostream>
#include<vector>
#include<random>

#include "piece.hpp"
#include "board.hpp"
#include "game.hpp"


//局面に必要な情報を整理する
/*
まずは、盤面情報、手駒の情報が必要
各盤面のマスに置くべき情報
駒の種類
9種類*2（成りか不成）*2（先手が後手か）＝36種類必要
ここに手駒の情報が必要
8種類（王以外）*9（取れる最大枚数）
*/
#ifndef KYOKUMEN_HPP
#define KYOKUMEN_HPP

class Kyokumen{
private:
    const int SORT_PIECE = 9;
    const int NARIFUNARI = 2;
    const int NUM_PLAYER = 2;
    std::vector<uint64_t> kyokumenHash;//各ターンのハッシュ値を保持するためのベクタ
    std::mt19937_64 rng;//乱数生成器

public:
    Kyokumen();//コンストラクタ
    void initializeKyokumenHash();//初期化関数
    uint64_t getBoardHash(const Board& board);//その盤面でのハッシュ値を生成する関数
    uint64_t getHandPieceHash(const Game& game);//その手駒でのハッシュ値を生成する関数（両プレイヤー分つくる）
    uint64_t getHash();//盤面ハッシュと手駒ハッシュを組み合わせる関数
};  

#endif