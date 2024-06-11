#include<iostream>
#include<vector>
#include<algorithm>
#include<bitset>

#include "board.hpp"


Board::Board(){
    for(int i = 0;i<BOARD_SIZE+2;i++){
        for(int j=0;j<BOARD_SIZE+2;j++){
            RawBoard[i][j] = Piece();
        }
    }
    //壁を定義、-1としておく（範囲外をマイナスで処理できるように）
    for(int i=0;i<BOARD_SIZE+2;i++){
        RawBoard[0][i]=Piece(Piece::WALL);
        RawBoard[BOARD_SIZE+1][i]=Piece(Piece::WALL);
    }for(int i=0;i<BOARD_SIZE+2;i++){
        RawBoard[i][0]=Piece(Piece::WALL);
        RawBoard[i][BOARD_SIZE+1]=Piece(Piece::WALL);
    }
}
Piece Board::getPiece(const Point& point) const{
    if(point.x<1||point.x> BOARD_SIZE||point.y<1||point.y>BOARD_SIZE){
        std::cerr << "Invalid point: (" << point.x << ", " << point.y << ")" << std::endl;
        return Piece();
    }
    return RawBoard[point.x][point.y];
}
void Board::setPiece(const Point& point,Piece piece){//そこにおけるかどうかはgame.putPieceで判定する
    if(point.x<1||point.x> BOARD_SIZE||point.y<1||point.y>BOARD_SIZE){
        std::cerr << "Invalid point: (" << point.x << ", " << point.y << ")" << std::endl;
        return;
    }
    if(piece.getPieceNum()>=Piece::NONE&&piece.getPieceNum()<=Piece::KING|Piece::promoteFlag){
        RawBoard[point.x][point.y] = piece;
    }
    else{
        std::cout << "Invalid piece"<<std::endl;
        return;
    }
}
//そこに駒が置けるかどうか判定する
bool Board::checkPuttable(const Point& point) const{
    if(point.x>=1&&point.x<=BOARD_SIZE&&point.y>=1&&point.y<=BOARD_SIZE){
        if(RawBoard[point.x][point.y].getPieceNum()>0) return false;
        return true;
    }else{
        std::cout<<"Invalid Input(point invalid)"<<std::endl;
        return false;
    }
}
//ボードの範囲をチェックする関数
bool Board::isWithinBoard(const Point& point) const{
    return point.x>=1 && point.x<=BOARD_SIZE && point.y>=1 && point.y<=BOARD_SIZE;
}
std::vector<Point> Board::getMovablePos(const Point& from) const{
    std::vector<Point> candidateMoves;
    //候補手一覧、まずは1マスだけ動く場合もしくは桂馬の動きであり得る移動先一覧を取得
    //移動先のポイントが自分の駒でないか判定する
    unsigned flagMovable = getPiece(from).getMovableDir();
    if(flagMovable&Piece::UPPER)candidateMoves.push_back(Point(from.x,from.y-1));
    if(flagMovable&Piece::LOWER)candidateMoves.push_back(Point(from.x,from.y+1));
    if(flagMovable&Piece::LEFT)candidateMoves.push_back(Point(from.x-1,from.y));
    if(flagMovable&Piece::RIGHT)candidateMoves.push_back(Point(from.x+1,from.y));
    if(flagMovable&Piece::UPPER_LEFT)candidateMoves.push_back(Point(from.x-1,from.y-1));
    if(flagMovable&Piece::UPPER_RIGHT)candidateMoves.push_back(Point(from.x+1,from.y-1));
    if(flagMovable&Piece::LOWER_LEFT)candidateMoves.push_back(Point(from.x-1,from.y+1));
    if(flagMovable&Piece::LOWER_RIGHT)candidateMoves.push_back(Point(from.x+1,from.y+1));
    if(flagMovable&Piece::UPPER_LEFT_KNIGHT)candidateMoves.push_back(Point(from.x-1,from.y-2));
    if(flagMovable&Piece::UPPER_RIGHT_KNIGHT)candidateMoves.push_back(Point(from.x+1,from.y-2));
    if(flagMovable&Piece::LOWER_LEFT_KNIGHT)candidateMoves.push_back(Point(from.x-1,from.y+2));
    if(flagMovable&Piece::LOWER_RIGHT_KNIGHT)candidateMoves.push_back(Point(from.x+1,from.y+2));
    //次に、1マス以上動ける場合の候補手を取得
        unsigned flagEternal = getPiece(from).getDirEternal();
        if(flagEternal&Piece::E_UPPER){
            Point objPoint(from.x,from.y-1);
            while(isWithinBoard(objPoint)&&getPiece(objPoint).getPieceNum()!=Piece::WALL){//壁にならない限り
                
                if(std::find(candidateMoves.begin(),candidateMoves.end(),objPoint)==candidateMoves.end())candidateMoves.push_back(objPoint);//候補手を追加し続ける
                if (getPiece(objPoint).getPieceNum() > 0) break;//途中に駒があった場合、そこで駒をとるので終了
                objPoint = Point(objPoint.x,objPoint.y-1);//１つ上に移動する
            }}
        if(flagEternal&Piece::E_LOWER){
            Point objPoint(from.x,from.y+1);
            while(isWithinBoard(objPoint)&&getPiece(objPoint).getPieceNum()!=Piece::WALL){//壁にならない限り
                if(std::find(candidateMoves.begin(),candidateMoves.end(),objPoint)==candidateMoves.end())candidateMoves.push_back(objPoint);//候補手を追加し続ける
                if (getPiece(objPoint).getPieceNum() > 0) break;
                objPoint = Point(objPoint.x,objPoint.y+1);//１つ下に移動する
            }}     
        if(flagEternal&Piece::E_LEFT){
            Point objPoint(from.x-1,from.y);
            while(isWithinBoard(objPoint)&&getPiece(objPoint).getPieceNum()!=Piece::WALL){//壁にならない限り
                if(std::find(candidateMoves.begin(),candidateMoves.end(),objPoint)==candidateMoves.end())candidateMoves.push_back(objPoint);//候補手を追加し続ける
                if (getPiece(objPoint).getPieceNum() > 0) break;
                objPoint = Point(objPoint.x-1,objPoint.y);//１つ左に移動する
            }}         
        if(flagEternal&Piece::E_RIGHT){
            Point objPoint(from.x+1,from.y);
            while(isWithinBoard(objPoint)&&getPiece(objPoint).getPieceNum()!=Piece::WALL){//壁にならない限り
                if(std::find(candidateMoves.begin(),candidateMoves.end(),objPoint)==candidateMoves.end())candidateMoves.push_back(objPoint);//候補手を追加し続ける
                if (getPiece(objPoint).getPieceNum() > 0) break;
                objPoint = Point(objPoint.x+1,objPoint.y);//１つ右に移動する
            }} 
        if(flagEternal&Piece::E_UPPER_LEFT){
            Point objPoint(from.x-1,from.y-1);
            while(isWithinBoard(objPoint)&&getPiece(objPoint).getPieceNum()!=Piece::WALL){//壁にならない限り
                if(std::find(candidateMoves.begin(),candidateMoves.end(),objPoint)==candidateMoves.end())candidateMoves.push_back(objPoint);//候補手を追加し続ける
                if (getPiece(objPoint).getPieceNum() > 0) break;
                objPoint = Point(objPoint.x-1,objPoint.y-1);//１つ左上に移動する
            }}
        if(flagEternal&Piece::E_UPPER_RIGHT){
            Point objPoint(from.x+1,from.y-1);
            while(isWithinBoard(objPoint)&&getPiece(objPoint).getPieceNum()!=Piece::WALL){//壁にならない限り
                if(std::find(candidateMoves.begin(),candidateMoves.end(),objPoint)==candidateMoves.end())candidateMoves.push_back(objPoint);//候補手を追加し続ける
                if (getPiece(objPoint).getPieceNum() > 0) break;
                objPoint = Point(objPoint.x+1,objPoint.y-1);//１つ右上に移動する
            }}
        if(flagEternal&Piece::E_LOWER_LEFT){
            Point objPoint(from.x-1,from.y+1);
            while(isWithinBoard(objPoint)&&getPiece(objPoint).getPieceNum()!=Piece::WALL){//壁にならない限り
                if(std::find(candidateMoves.begin(),candidateMoves.end(),objPoint)==candidateMoves.end())candidateMoves.push_back(objPoint);//候補手を追加し続ける
                if (getPiece(objPoint).getPieceNum() > 0) break;
                objPoint = Point(objPoint.x-1,objPoint.y+1);//１つ左下に移動する
            }}
        if(flagEternal&Piece::E_LOWER_RIGHT){
            Point objPoint(from.x+1,from.y+1);
            while(isWithinBoard(objPoint)&&getPiece(objPoint).getPieceNum()!=Piece::WALL){//壁にならない限り
                if(std::find(candidateMoves.begin(),candidateMoves.end(),objPoint)==candidateMoves.end())candidateMoves.push_back(objPoint);//候補手を追加し続ける
                if (getPiece(objPoint).getPieceNum() > 0) break;
                objPoint = Point(objPoint.x+1,objPoint.y+1);//１つ右下に移動する
            }}
    return candidateMoves;
}
bool Board::isMoveValid(const Point& from, const Point& to) const{
    std::vector<Point> candidateMoves;
    // 移動元と移動先の範囲をチェック
    if (from.x < 1 || from.x > BOARD_SIZE || from.y < 1 || from.y > BOARD_SIZE ||
        to.x < 1 || to.x > BOARD_SIZE || to.y < 1 || to.y > BOARD_SIZE) {
        std::cout << "Invalid Input (invalid point)" << std::endl;
        return false;
    }

    // 移動元に駒があるかチェック
    if (getPiece(from).getPieceNum() <= 0) {
        std::cout << "The place does not have a piece" << std::endl;
        return false;
    }

    // 移動元と移動先の駒の所有者を取得
    int fromPieceOwner = getPiece(from).checkFirst() ? 1 : 2;
    int toPieceOwner = getPiece(to).checkFirst() ? 1 : 2;

    // 移動先に自分の駒がある場合は動けない
    if (getPiece(to).getPieceNum() > 0 && fromPieceOwner == toPieceOwner) {
        std::cout << "Target Place has your piece, so you can't move." << std::endl;
        return false;
    }

    // 動ける候補手を取得して合法手かどうかチェック
    candidateMoves = getMovablePos(from);
    if (std::find(candidateMoves.begin(), candidateMoves.end(), to) != candidateMoves.end()) {
        return true;
    } else {
        std::cout << "The move is illegal." << std::endl;
        return false;
}}

bool Board::checkPiecePutted(const Point& point) const{
    if(point.x>=0&&point.x<=BOARD_SIZE&&point.y>=0&&point.y<=BOARD_SIZE){
        if(getPiece(point).getPieceNum()>0){
            return true;
        }
    }else{
        std::cout<<"Invalid Input(invalid point)"<<std::endl;
    }return false;
}
bool Board::checkPromotable(const Point& from,const Point& to) const{
    if(from.x>=1&&from.x<=BOARD_SIZE&&from.y>=1&&from.y<=BOARD_SIZE&&to.x>=1&&to.x<=BOARD_SIZE&&to.y>=1&&to.y<=BOARD_SIZE){
        //有効な範囲の場合
        //移動先が相手陣内かどうか
        if(getPiece(from).checkFirst()){//先攻の場合
            if(to.y>=BOARD_SIZE-2){
                //その駒が金と王でなければ
                if(getPiece(from).checkPromotable()){
                    std::cout<<"The piece can be promoted."<<std::endl;
                    return true;
                }else{
                    std::cout<<"The piece cannot be promoted."<<std::endl;
                }
            }
        }else{
            if(to.y<=3){
                //その駒が金と王でなければ
                if(getPiece(from).checkPromotable()){
                    std::cout<<"The piece can be promoted."<<std::endl;
                    return true;
                }else{
                    std::cout<<"The piece cannot be promoted."<<std::endl;
                }
            }
        }
    }else{
        std::cout<<"Invalid Input(invalid point)"<<std::endl;
    }return false;
}
