#include<iostream>
#include<vector>
#include<algorithm>
#include<bitset>

#include "board.hpp"
#include "piece.hpp"
#include "player.hpp"


Player::Player(bool isGyoku) : firstPlayer(isGyoku?1:0){
    for(int i=0;i<Board::MAX_NUM_HAND;i++){
        handPieces[i] = Piece::NONE;
    }
}
int Player::getHandPieces(int index) const{
    if(index>=0&&index<Board::MAX_NUM_HAND){
        return handPieces[index];
    }else{
        std::cout<<"Invalid index:"<<index<<std::endl;
        return -1;//エラー値
    }
}
void Player::setHandPiece(int index,int numPiece){
    if(index>=0&&index<Board::MAX_NUM_HAND){
        handPieces[index]=numPiece;
    }else{
        std::cerr << "Invalid index: " << index << std::endl;
    }
}
bool Player::isPlayerFirst(){
    return (firstPlayer==1)?true:false;
}
void Player::addHandPiece(int numPiece){
    for (int i = 0; i < Board::MAX_NUM_HAND; ++i) {
        if (handPieces[i] == 0) {
            handPieces[i] = numPiece;
            break;
        }
    }
}
int Player::useHandPiece(int num_piece){//手駒を使用する
    int pieceUsed = -1;
    if(num_piece>=Piece::NONE&&num_piece<=Piece::KING){
        for(int i=0;i<Board::MAX_NUM_HAND;i++){
        if(handPieces[i]==num_piece){
            pieceUsed = handPieces[i];
            handPieces[i]=0;
            return pieceUsed;
        }
    } std::cout<<"You don't have such a piece."<<std::endl;   
    }else{
        std::cout<<"Invalid input."<<std::endl;
    }
    return pieceUsed;
}
// 持ち駒の表示
void Player::printHandPieces() const {
    std::cout << "Hand pieces: ";
    for (int i = 0; i <Board::MAX_NUM_HAND; ++i) {
        if (handPieces[i] != 0) {
            std::cout << handPieces[i] << " ";
        }
    }
    std::cout << std::endl;
}
    
