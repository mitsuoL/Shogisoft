#include <iostream>
#include<vector>
#include<random>

#include "kyokumen.hpp"

Kyokumen::Kyokumen(){
    initializeKyokumenHash();
}

uint64_t Kyokumen::getBoardHash(const Board& board){
    //各マスについて、ランダムな手を生成する
    for(int y=1;y<=Board::BOARD_SIZE;y++){
        for(int x=1;x<=Board::BOARD_SIZE;x++){

        }
    }
}