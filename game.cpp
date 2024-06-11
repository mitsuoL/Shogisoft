#include<iostream>
#include<vector>
#include<algorithm>
#include<bitset>

#include "board.hpp"
#include "piece.hpp"
#include "game.hpp"


Game::Game() : player1(true),player2(false),board(){
    Turn=1;//ターンは1ターン目からスタート
    //一旦すべてプレイヤーの手駒に全駒を追加
    for(int i=0;i<9;i++){
        player1.addHandPiece(Piece::PAWN);
        player2.addHandPiece(Piece::PAWN);
    }
    
    for(int i=0;i<2;i++){
        player1.addHandPiece(Piece::LANCE);
        player2.addHandPiece(Piece::LANCE);
    }
    for(int i=0;i<2;i++){
        player1.addHandPiece(Piece::KNIGHT);
        player2.addHandPiece(Piece::KNIGHT);
    }
    for(int i=0;i<2;i++){
        player1.addHandPiece(Piece::SILVER);
        player2.addHandPiece(Piece::SILVER);
    }
    for(int i=0;i<2;i++){
        player1.addHandPiece(Piece::GOLD);
        player2.addHandPiece(Piece::GOLD);
    }
    for(int i=0;i<1;i++){
        player1.addHandPiece(Piece::BISHOP);
        player2.addHandPiece(Piece::BISHOP);
    }
    for(int i=0;i<1;i++){
        player1.addHandPiece(Piece::ROOK);
        player2.addHandPiece(Piece::ROOK);
    }
    for(int i=0;i<1;i++){
        player1.addHandPiece(Piece::KING);
        player2.addHandPiece(Piece::KING);
    }
    
    //歩を盤面に置く
    for(int i=0;i<Board::BOARD_SIZE;i++){
        Point point(i+1,3);
        Point point2(i+1,Board::BOARD_SIZE-2);
        putPiece(point,Piece::PAWN,player1);
        putPiece(point2,Piece::PAWN,player2);          
    }
    //香車を盤面に置く
    for(int i=0;i<2;i++){
        Point point(9-8*i,1);
        Point point2(9-8*i,9);
        putPiece(point,Piece::LANCE,player1);
        putPiece(point2,Piece::LANCE,player2);               
    }
    //桂馬を盤面に置く
    for(int i=0;i<2;i++){
        Point point(2+6*i,1);
        Point point2(2+6*i,9);
        putPiece(point,Piece::KNIGHT,player1);
        putPiece(point2,Piece::KNIGHT,player2);          
    }
    //銀を盤面に置く
    for(int i=0;i<2;i++){
        Point point(3+4*i,1);
        Point point2(3+4*i,9);
        putPiece(point,Piece::SILVER,player1);
        putPiece(point2,Piece::SILVER,player2);          
    }
    //金を盤面に置く
    for(int i=0;i<2;i++){
        Point point(4+2*i,1);
        Point point2(4+2*i,9);
        putPiece(point,Piece::GOLD,player1);
        putPiece(point2,Piece::GOLD,player2);          
    }
    //角を盤面に置く
    for(int i=0;i<1;i++){
        Point point(7,2);
        Point point2(3,8);
        putPiece(point,Piece::BISHOP,player1);
        putPiece(point2,Piece::BISHOP,player2); 
    }        
    //飛車を盤面に置く
    for(int i=0;i<1;i++){
        Point point(3,2);
        Point point2(7,8);
        putPiece(point,Piece::ROOK,player1);
        putPiece(point2,Piece::ROOK,player2);  
    }
    //王将を盤面に置く
    for(int i=0;i<1;i++){
        Point point(5,1);
        Point point2(5,9);
        putPiece(point,Piece::KING,player1);
        putPiece(point2,Piece::KING,player2); 
    }            
}
void Game::printBoard(){
    for(int y=1;y<=Board::BOARD_SIZE;++y){
        for(int x=1;x<=Board::BOARD_SIZE;x++){
            std::cout<<board.RawBoard[x][y].getPieceName();
        }
        std::cout<<std::endl;
    }
}
void Game::putPiece(Point point,int num_piece,Player &player){
    Piece pieceUsed(player.useHandPiece(num_piece),(player.isPlayerFirst())?true:false);
    if (pieceUsed.getPieceNum() != -1) {
        if (board.checkPuttable(point)) {
            board.setPiece(point, pieceUsed);
        } else {
            std::cout << "Cannot place piece " << pieceUsed.getPieceNum() << " at (" << point.x << ", " << point.y << ")" << std::endl;
            player.addHandPiece(pieceUsed.getPieceNum()); // 手駒に戻す
        }
    }
}
void Game::movePiece(Point from,Point to,bool promote){
    if(board.isMoveValid(from,to)){
        if(board.checkPiecePutted(to)){//移動先に駒が置かれている場合
            if(player1.isPlayerFirst()==board.getPiece(from).checkFirst()){//先攻ならplayer1,後攻ならplayer2
                player1.addHandPiece(board.getPiece(to).getPieceNum());//その駒を手駒に追加
                
            }else{
                player2.addHandPiece(board.getPiece(to).getPieceNum());//その駒を手駒に追加
            }board.setPiece(to,Piece(Piece::NONE,board.getPiece(from).checkFirst()));//移動先の駒を削除               
        }
        board.setPiece(to,Piece(board.getPiece(from).getPieceNum(),board.getPiece(from).checkFirst()));//移動先に移動元の駒を置く
        board.setPiece(from,Piece(Piece::NONE,(Turn%2==1?true:false)));//移動元の駒を削除
        if(promote){
            promotePiece(from,to);
        }
    }
}
void Game::promotePiece(Point from,Point to){//基本的に成る場合は、movePiece関数を使用した後に実行すると想定
    //もしそこの駒が成ることができるなら
    if(board.checkPromotable(from,to)){
        //駒をなる、これは元の駒をなくし、新しいなり駒を作るという処理に変える
        board.setPiece(to,Piece(board.getPiece(to).getPieceNum()|Piece::promoteFlag,board.getPiece(from).checkFirst()));
    }
}
void Game::printMovablePos(Point from){
    std::vector<Point> candidatePos;
    candidatePos = board.getMovablePos(from);
    for(const Point& pos : candidatePos){
        std::cout<<pos<<" ";
    }
    std::cout<<std::endl;
}
void Game::printHandPieces(){
    std::cout<<"(player1)";
    player1.printHandPieces();
    std::cout<<"(Player2)";
    player2.printHandPieces();
}

/*デバッグ用なので以下の関数は最終的には消す*/
void Game::printPieceMovableDir(Point point){
    int movabledir = board.getPiece(point).getMovableDir();
    std::bitset<12> binary(movabledir);
    std::cout<<"MovableDir is "<<binary<<std::endl;
}
void Game::printPieceMovableDirEternal(Point point){
    int movabledireternal = board.getPiece(point).getDirEternal();
    std::bitset<8> binary(movabledireternal);
    std::cout<<"MovableDirEternal is "<<binary<<std::endl;
}
void Game::printIsMovable(Point from,Point to){
    std::cout<<board.isMoveValid(from,to)<<std::endl;
}
void Game::printPieceNum(Point point){
    std::cout<<board.getPiece(point).getPieceNum()<<std::endl;
}
