#include<iostream>
#include<vector>
#include<algorithm>
#include<bitset>

#include "piece.hpp"

std::string Piece::getPieceName() const {
        std::string prefix = (checkPromoted())?"+":" ";
        std::string name;
        switch (getOriginalPieceType()) {//元の駒の種類で表示
            case 0:
                return "--";
            case 1:
                name = this->isTurnFirst ? "P" : "p";
                break;
            case 2:
                name = this->isTurnFirst ? "L" : "l";
                break;
            case 3:
                name = this->isTurnFirst ? "N" : "n";
                break;
            case 4:
                name = this->isTurnFirst ? "S" : "s";
                break;
            case 5:
                name = this->isTurnFirst ? "G" : "g";
                break;
            case 6:
                name = this->isTurnFirst ? "B" : "b";
                break;
            case 7:
                name = this->isTurnFirst ? "R" : "r";
                break;
            case 8:
                name = this->isTurnFirst ? "K" : "k";
                break;
            default:
                return "**";
        }
        return prefix + name;
};
unsigned Piece::getPieceNum() const{
    return this->numPiece;
}
unsigned Piece::getMovableDir(){
    unsigned flagMovable = 0;
    if((this->numPiece&promoteFlag)==0){//駒が成っていない場合
        switch(this->numPiece){
            case PAWN:
                flagMovable |= (!isTurnFirst) ? UPPER : LOWER;
                break;
            case LANCE:
                flagMovable |= (!isTurnFirst) ? UPPER : LOWER;
                break;
            case KNIGHT:
                if (!isTurnFirst) {
                    flagMovable |= UPPER_LEFT_KNIGHT | UPPER_RIGHT_KNIGHT;
                } else {
                    flagMovable |= LOWER_LEFT_KNIGHT | LOWER_RIGHT_KNIGHT;
                }
                break;
            case SILVER: // 銀の場合
                flagMovable |= (!isTurnFirst) ? 
                    (UPPER | UPPER_LEFT | UPPER_RIGHT | LOWER_LEFT | LOWER_RIGHT) : 
                    (LOWER | LOWER_LEFT | LOWER_RIGHT | UPPER_LEFT | UPPER_RIGHT);
                break;
            case GOLD: // 金の場合
                flagMovable |= (!isTurnFirst) ? 
                    (UPPER | LOWER | LEFT | RIGHT | UPPER_LEFT | UPPER_RIGHT) :
                    (LOWER | UPPER | LEFT | RIGHT | LOWER_LEFT | LOWER_RIGHT);
                break;
            case BISHOP: // 角の場合
                flagMovable |= (UPPER_LEFT | UPPER_RIGHT | LOWER_LEFT | LOWER_RIGHT);
                break;
            case ROOK: // 飛車の場合
                flagMovable |= (UPPER | LOWER | LEFT | RIGHT);
                break;
            case KING: // 王の場合
                flagMovable |= (UPPER | LOWER | LEFT | RIGHT | UPPER_LEFT | UPPER_RIGHT | LOWER_LEFT | LOWER_RIGHT);
                break;
            default:
                break;
        }        
    }else{
        if((numPiece==(promoteFlag|BISHOP))||(numPiece==(promoteFlag|ROOK))){
            flagMovable|=(UPPER|LOWER|LEFT|RIGHT|UPPER_LEFT | UPPER_RIGHT | LOWER_LEFT | LOWER_RIGHT);
        }else{
        flagMovable |= (!isTurnFirst) ? //この場合金と一緒
                    (UPPER | LOWER | LEFT | RIGHT | UPPER_LEFT | UPPER_RIGHT) :
                    (LOWER | UPPER | LEFT | RIGHT | LOWER_LEFT | LOWER_RIGHT); 
    }}
    return flagMovable;
}
unsigned Piece::getDirEternal(){//どこまでも動けるかのフラグを受け取る
    unsigned dirEternal = 0;
    switch (this->numPiece)
    {
    case LANCE:
        dirEternal |= (!isTurnFirst) ? E_UPPER : E_LOWER; 
        break;
    case BISHOP:
    case BISHOP|promoteFlag:
        dirEternal |= E_UPPER_LEFT | E_UPPER_RIGHT | E_LOWER_LEFT | E_LOWER_RIGHT;
        break;
    case ROOK:
    case ROOK|promoteFlag:
        dirEternal |= E_UPPER | E_LOWER | E_LEFT | E_RIGHT;       
        break;
    default:
        break;
    }
    return dirEternal;
}
bool Piece::checkFirst(){
    if(this->isTurnFirst){
        return true;
    }else{return false;}
}

Piece::Piece(int num_piece,bool isTurnFirst){
    this->numPiece = num_piece;
    this->namePiece = getPieceName();
    this->dirMovable = getMovableDir();
    this->dirEternal = getDirEternal();
    this->isTurnFirst = isTurnFirst;
};
bool Piece::checkPromotable(){
    if(this->numPiece ==PAWN||LANCE||KNIGHT||SILVER||BISHOP||ROOK){
        return true;
    }
    return false;
}
bool Piece::checkPromoted() const{
    return (this->numPiece&Piece::promoteFlag)!=0;
}
Piece::NumPiece Piece::getOriginalPieceType() const{
    return this->numPiece & ~promoteFlag;
}