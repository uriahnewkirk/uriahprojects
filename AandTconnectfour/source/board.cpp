#include "board.h"
#include "ui_board.h"
#include "mainwindow.h"
#include "congratulations.h"
#include <iostream>
#include <sstream>
class mainWindow;
using namespace std;

int game_the[7][7];
int board::playerturn = 0, board::turnCount;

int board::playerC;
int board::p1Time=2;
int board::p2Time=2;
int board::p3Time=2;
int board::p4Time=2;

QString board::p1Name, board::p2Name, board::p3Name, board::p4Name;

bool flag;

int board::winP;

bool board::p1T=false, board::p2T=false, board::p3T=false, board::p4T=false;

bool board::p1Status, board::p2Status, board::p3Status, board::p4Status;

board::board(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::board)
{
    ui->setupUi(this);

    ui->placeTText->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");
    ui->playerTurnText->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");
//USE TEXT EDIT INSTEAD IDIOT!

    //create text-based version of our connect four game (using 2d array) to help with calculations
    for(int i=0;i<7;i++)
    {
        for(int j=0;j<7;j++)
        {
        game_the[i][j]=-1;
        }
    }

    //initialize all spots on the board to being empty (visually)
    QLabel label_the;
    QPixmap pix("/home/uriahnewkirk/Desktop/water/comp410/project/img/emptySMALL.png");
    QPixmap pix1("/home/uriahnewkirk/Desktop/water/comp410/project/img/redToken.png");
    QPixmap pix2("/home/uriahnewkirk/Desktop/water/comp410/project/img/cyanToken.png");
    QPixmap pix3("/home/uriahnewkirk/Desktop/water/comp410/project/img/greenToken.png");
    QPixmap pix4("/home/uriahnewkirk/Desktop/water/comp410/project/img/yellowToken.png");


    ui->r1c1->setPixmap(pix);
    ui->r1c2->setPixmap(pix);
    ui->r1c3->setPixmap(pix);
    ui->r1c4->setPixmap(pix);
    ui->r1c5->setPixmap(pix);
    ui->r1c6->setPixmap(pix);
    ui->r1c7->setPixmap(pix);

    ui->r2c1->setPixmap(pix);
    ui->r2c2->setPixmap(pix);
    ui->r2c3->setPixmap(pix);
    ui->r2c4->setPixmap(pix);
    ui->r2c5->setPixmap(pix);
    ui->r2c6->setPixmap(pix);
    ui->r2c7->setPixmap(pix);

    ui->r3c1->setPixmap(pix);
    ui->r3c2->setPixmap(pix);
    ui->r3c3->setPixmap(pix);
    ui->r3c4->setPixmap(pix);
    ui->r3c5->setPixmap(pix);
    ui->r3c6->setPixmap(pix);
    ui->r3c7->setPixmap(pix);

    ui->r4c1->setPixmap(pix);
    ui->r4c2->setPixmap(pix);
    ui->r4c3->setPixmap(pix);
    ui->r4c4->setPixmap(pix);
    ui->r4c5->setPixmap(pix);
    ui->r4c6->setPixmap(pix);
    ui->r4c7->setPixmap(pix);

    ui->r5c1->setPixmap(pix);
    ui->r5c2->setPixmap(pix);
    ui->r5c3->setPixmap(pix);
    ui->r5c4->setPixmap(pix);
    ui->r5c5->setPixmap(pix);
    ui->r5c6->setPixmap(pix);
    ui->r5c7->setPixmap(pix);

    ui->r6c1->setPixmap(pix);
    ui->r6c2->setPixmap(pix);
    ui->r6c3->setPixmap(pix);
    ui->r6c4->setPixmap(pix);
    ui->r6c5->setPixmap(pix);
    ui->r6c6->setPixmap(pix);
    ui->r6c7->setPixmap(pix);

    ui->r7c1->setPixmap(pix);
    ui->r7c2->setPixmap(pix);
    ui->r7c3->setPixmap(pix);
    ui->r7c4->setPixmap(pix);
    ui->r7c5->setPixmap(pix);
    ui->r7c6->setPixmap(pix);
    ui->r7c7->setPixmap(pix);
    //end of initializing all to empty




//switch statement to determine which players are actually playing
//setting those who are not playing to a false status.
    switch(playerC) {
    case 2:
        p1Status=true;
        p2Status=true;
        p3Status=false;
        p4Status=false;
    case 3:
        p1Status=true;
        p2Status=true;
        p3Status=true;
        p4Status=false;
    default:
        p1Status=true;
        p2Status=true;
        p3Status=true;
        p4Status=true;
    }
    //this doesn't actually do anything, refer to switchturn for how
    //players are enabled/disabled

    startGame();

    showBoard();

    winner();






}

board::~board()
{
    delete ui;
}


void board::on_mMenu_clicked()
{
    hide();
    mainW = new MainWindow(this);
    mainW->show();
}


bool board::boardFull() {

     turnCount++;
     if(turnCount==49) {
        //cout<<"The match is draw /n";
        return true;
     }
     return false;
}

void board::switchTurn() {
//this method actually dictates which players get a turn
    std::stringstream streamS;
    QString turnI;
    int mud;
    playerturn++;

    mud=playerturn%playerC;

    if(mud==1) {
        playerturn = 1;
    }
    else if(mud==2) {
        playerturn = 2;
    }
    else if(mud==3 && playerC>2) {
        playerturn = 3;
    }
    else if(mud==0 && playerC>3) {
        playerturn = 4;
    }
    //depending on the number of players, only allow certain players
    //to actually get a turn

    streamS << "Player "<< playerturn << ", it's your turn!";
    turnI = QString::fromStdString(streamS.str());
    ui->playerTurnText->setPlainText(turnI);

}

void board::showBoard() {
//display the board in the terminal (primarily for testing purposes)
//remove for final product

     for(int i=0;i<7;i++)
     {
      std::cout<<"\t\t";
      for(int j=0;j<7;j++)
      {
       std::cout<<game_the[i][j];
      }
      cout<<endl;
     }
     cout<<endl;
}


bool board::winner() {

    for(int i=6;i>=0;i--) {
        for(int j=0;j<4;j++) {
            if((game_the[i][j]==1 && game_the[i][j+1]==1 && game_the[i][j+2]==1 && game_the[i][j+3]==1) || (game_the[i][j]==2 && game_the[i][j+1]==2 && game_the[i][j+2]==2 && game_the[i][j+3]==2) || (game_the[i][j]==3 && game_the[i][j+1]==3 && game_the[i][j+2]==3 && game_the[i][j+3]==3) || (game_the[i][j]==4 && game_the[i][j+1]==4 && game_the[i][j+2]==4 && game_the[i][j+3]==4)) {
                if(game_the[i][j]==1 && game_the[i][j+1]==1 && game_the[i][j+2]==1 && game_the[i][j+3]==1) {
                    ui->playerTurnText->setPlainText("player 1 wins!");
                    return true;
                }
                else if(game_the[i][j]==2 && game_the[i][j+1]==2 && game_the[i][j+2]==2 && game_the[i][j+3]==2) {
                    ui->playerTurnText->setPlainText("Player 2 wins!");
                    return true;
                }
                else if(game_the[i][j]==3 && game_the[i][j+1]==3 && game_the[i][j+2]==3 && game_the[i][j+3]==3) {
                    ui->playerTurnText->setPlainText("PLayer 3 wins!");
                    return true;
                }
                else if(game_the[i][j]==4 && game_the[i][j+1]==4 && game_the[i][j+2]==4 && game_the[i][j+3]==4) {
                    ui->playerTurnText->setPlainText("Player 4 wins!");
                    return true;
                }
            }
        }
     }

    // vertically check whether the sum of alternate 4 rows are 4 or 8 and also check all the rows are filled
   for(int j=0;j<7;j++)
   {
       for(int i=6;i>2;i--)
       {
           if((game_the[i][j]==1 && game_the[i-1][j]==1 && game_the[i-2][j]==1 && game_the[i-3][j]==1) || (game_the[i][j]==2 && game_the[i-1][j]==2 && game_the[i-2][j]==2 && game_the[i-3][j]==2) || (game_the[i][j]==3 && game_the[i-1][j]==3 && game_the[i-2][j]==3 && game_the[i-3][j]==3) || (game_the[i][j]==4 && game_the[i-1][j]==4 && game_the[i-2][j]==4 && game_the[i-3][j]==4)) {
               if(game_the[i][j]==1 && game_the[i-1][j]==1 && game_the[i-2][j]==1 && game_the[i-3][j]==1)                                                                                                                                          // player won
               {
                   ui->playerTurnText->setPlainText("player 1 wins!");
                   return true;
               }
               else if(game_the[i][j]==2 && game_the[i-1][j]==2 && game_the[i-2][j]==2 && game_the[i-3][j]==2)
               {
                   ui->playerTurnText->setPlainText("player 2 wins");
//                   cout<<"player 1 won !\n";
                   return true;
               }
               else if(game_the[i][j]==3 && game_the[i-1][j]==3 && game_the[i-2][j]==3 && game_the[i-3][j]==3){
                     ui->playerTurnText->setPlainText("player 3 wins");
                     return true;
               }
               else {
                   ui->playerTurnText->setPlainText("player 4 wins");
                   return true;
               }
           }
       }

   }
   // diagnally check whether the sum of diagonal 4 rows are 4 or 8 and also check all the 4 cell are filled
   for(int i=6;i>2;i--)
   {
       for(int j=0;j<4;j++)
       {
           if(j==0&&i==6)
           {
               for(int c=0;c<4;c++)
               {
                   if((game_the[i-c][j+c]==1 && game_the[i-(c+1)][j+(c+1)]==1 && game_the[i-(c+2)][j+(c+2)]==1 && game_the[i-(c+3)][j+(c+3)]==1) || (game_the[i-c][j+c]==2 && game_the[i-(c+1)][j+(c+1)]==2 && game_the[i-(c+2)][j+(c+2)]==2 && game_the[i-(c+3)][j+(c+3)]==4) || (game_the[i-c][j+c]==3 && game_the[i-(c+1)][j+(c+1)]==3 && game_the[i-(c+2)][j+(c+2)]==3 && game_the[i-(c+3)][j+(c+3)]==3) || (game_the[i-c][j+c]==4 && game_the[i-(c+1)][j+(c+1)]==4 && game_the[i-(c+2)][j+(c+2)]==4 && game_the[i-(c+3)][j+(c+3)]==4)) {
                       if(game_the[i-c][j+c]==1 && game_the[i-(c+1)][j+(c+1)]==1 && game_the[i-(c+2)][j+(c+2)]==1 && game_the[i-(c+3)][j+(c+3)]==1)
                       {
                           ui->playerTurnText->setPlainText("player 1 wins!");
                           return true;
                       }
                       else if(game_the[i-c][j+c]==2 && game_the[i-(c+1)][j+(c+1)]==2 && game_the[i-(c+2)][j+(c+2)]==2 && game_the[i-(c+3)][j+(c+3)]==2)
                       {
                           ui->playerTurnText->setPlainText("player 2 wins");
//                           cout<<"player 1 won !\n";
                           return true;
                       }
                       else if(game_the[i-c][j+c]==3 && game_the[i-(c+1)][j+(c+1)]==3 && game_the[i-(c+2)][j+(c+2)]==3 && game_the[i-(c+3)][j+(c+3)]==3){
                            ui->playerTurnText->setPlainText("player 3 wins");
//                            cout<< "player 3 won! \n";
                            return true;
                       }
                       else {

                            ui->playerTurnText->setPlainText("player 4 wins");
                            return true;
                       }
                   }

               }
           }

           if((j==1&&i==6)||(j==0&&i==5))
           {
               for(int c=0;c<3;c++)
               {
                   if((game_the[i-c][j+c]==1 && game_the[i-(c+1)][j+(c+1)]==1 && game_the[i-(c+2)][j+(c+2)]==1 && game_the[i-(c+3)][j+(c+3)]==1)|| (game_the[i-c][j+c]==2 && game_the[i-(c+1)][j+(c+1)]==2 && game_the[i-(c+2)][j+(c+2)]==2 && game_the[i-(c+3)][j+(c+3)]==4) || (game_the[i-c][j+c]==3 && game_the[i-(c+1)][j+(c+1)]==3 && game_the[i-(c+2)][j+(c+2)]==3 && game_the[i-(c+3)][j+(c+3)]==3) || (game_the[i-c][j+c]==4 && game_the[i-(c+1)][j+(c+1)]==4 && game_the[i-(c+2)][j+(c+2)]==4 && game_the[i-(c+3)][j+(c+3)]==4))
                   {
                       if(game_the[i-c][j+c]==1 && game_the[i-(c+1)][j+(c+1)]==1 && game_the[i-(c+2)][j+(c+2)]==1 && game_the[i-(c+3)][j+(c+3)]==1)
                       {
                           ui->playerTurnText->setPlainText("player 1 wins!");
//                           cout<<"player 2 won! \n";
                           return true;
                       }
                       else if(game_the[i-c][j+c]==2 && game_the[i-(c+1)][j+(c+1)]==2 && game_the[i-(c+2)][j+(c+2)]==2 && game_the[i-(c+3)][j+(c+3)]==4)
                       {
                           ui->playerTurnText->setPlainText("player 2 wins");
//                           cout<<"player 1 won! \n";
                           return true;
                       }
                       else if(game_the[i-c][j+c]==3 && game_the[i-(c+1)][j+(c+1)]==3 && game_the[i-(c+2)][j+(c+2)]==3 && game_the[i-(c+3)][j+(c+3)]==3){
                           ui->playerTurnText->setPlainText("player 3 wins");
//                           cout<< "player 3 won! \n";
                           return true;
                       }
                       else {
                           ui->playerTurnText->setPlainText("player 4 wins");
//                           cout<< "player 4 won! \n";
                           return true;
                       }
                   }

               }
           }

           if((j==2&&i==6)||(j==0&&i==4))
           {
               for(int c=0;c<2;c++)
               {
                   if((game_the[i-c][j+c]==1 && game_the[i-(c+1)][j+(c+1)]==1 && game_the[i-(c+2)][j+(c+2)]==1 && game_the[i-(c+3)][j+(c+3)]==1) || (game_the[i-c][j+c]==2 && game_the[i-(c+1)][j+(c+1)]==2 && game_the[i-(c+2)][j+(c+2)]==2 && game_the[i-(c+3)][j+(c+3)]==2) || (game_the[i-c][j+c]==3 && game_the[i-(c+1)][j+(c+1)]==3 && game_the[i-(c+2)][j+(c+2)]==3 && game_the[i-(c+3)][j+(c+3)]==3) || (game_the[i-c][j+c]==3 && game_the[i-(c+1)][j+(c+1)]==4 && game_the[i-(c+2)][j+(c+2)]==4 && game_the[i-(c+3)][j+(c+3)]==4)) {
                       if(game_the[i-c][j+c]==1 && game_the[i-(c+1)][j+(c+1)]==1 && game_the[i-(c+2)][j+(c+2)]==1 && game_the[i-(c+3)][j+(c+3)]==1)
                       {
                           ui->playerTurnText->setPlainText("player 1 wins!");
//                           cout<<"player 2 won! \n";
                           return true;
                       }
                       else if(game_the[i-c][j+c]==2 && game_the[i-(c+1)][j+(c+1)]==2 && game_the[i-(c+2)][j+(c+2)]==2 && game_the[i-(c+3)][j+(c+3)]==2)
                       {
                           ui->playerTurnText->setPlainText("player 2 wins");
//                           cout<<"player 1 won! \n";
                           return true;
                       }
                       else if(game_the[i-c][j+c]==3 && game_the[i-(c+1)][j+(c+1)]==3 && game_the[i-(c+2)][j+(c+2)]==3 && game_the[i-(c+3)][j+(c+3)]==3){
                           ui->playerTurnText->setPlainText("player 3 wins");
//                           cout << "player 3 won! \n";
                            return true;
                       }
                       else{
                           ui->playerTurnText->setPlainText("player 4 wins");
//                           cout<< "player 4 won! \n";
                           return true;
                       }
                   }
               }
           }

           if((i==6&&j==3)||(j==0&&i==3))
           {
               if((game_the[i][j]==1 && game_the[i-1][j+1]==1 && game_the[i-2][j+2]==1 && game_the[i-3][j+3]==1) || (game_the[i][j]==2 && game_the[i-1][j+1]==2 && game_the[i-2][j+2]==2 && game_the[i-3][j+3]==2) || (game_the[i][j]==3 && game_the[i-1][j+1]==3 && game_the[i-2][j+2]==3 && game_the[i-3][j+3]==3) || (game_the[i][j]==4 && game_the[i-1][j+1]==4 && game_the[i-2][j+2]==4 && game_the[i-3][j+3]==4)) {
                   if(game_the[i][j]==1 && game_the[i-1][j+1]==1 && game_the[i-2][j+2]==1 && game_the[i-3][j+3]==1)
                   {
                       ui->playerTurnText->setPlainText("player 1 wins!");
//                       cout<<"player 2 won !\n";
                       return true;
                   }
                   else if(game_the[i][j]==2 && game_the[i-1][j+1]==2 && game_the[i-2][j+2]==2 && game_the[i-3][j+3]==2)
                   {
                       ui->playerTurnText->setPlainText("player 2 wins");
//                       cout<<"player 1 won !\n";
                       return true;
                   }
                   else if(game_the[i][j]==3 && game_the[i-1][j+1]==3 && game_the[i-2][j+2]==3 && game_the[i-3][j+3]==3) {
                       ui->playerTurnText->setPlainText("player 3 wins");
//                       cout<<"player 1 won !\n";
                       return true;
                   }
                   else {
                       ui->playerTurnText->setPlainText("player 4 wins");
//                       cout<<"player 1 won !\n";
                       return true;
                   }
               }
           }

       }
   }
   for(int i=6;i>2;i--)
   {
       for(int j=6;j>2;j--)
       {
           if(j==6&&i==6)
           {
               for(int c=0;c<4;c++)
               {
                   if((game_the[i-c][j-c]==1 && game_the[i-(c+1)][j-(c+1)]==1 && game_the[i-(c+2)][j-(c+2)]==1 && game_the[i-(c+3)][j-(c+3)]==1) || (game_the[i-c][j-c]==2 && game_the[i-(c+1)][j-(c+1)]==2 && game_the[i-(c+2)][j-(c+2)]==2 && game_the[i-(c+3)][j-(c+3)]==2) || (game_the[i-c][j-c]==3 && game_the[i-(c+1)][j-(c+1)]==3 && game_the[i-(c+2)][j-(c+2)]==3 && game_the[i-(c+3)][j-(c+3)]==3) || (game_the[i-c][j-c]==4 && game_the[i-(c+1)][j-(c+1)]==4 && game_the[i-(c+2)][j-(c+2)]==4 && game_the[i-(c+3)][j-(c+3)]==4)) {
                       if(game_the[i-c][j-c]==1 && game_the[i-(c+1)][j-(c+1)]==1 && game_the[i-(c+2)][j-(c+2)]==1 && game_the[i-(c+3)][j-(c+3)]==1)
                       {
                           ui->playerTurnText->setPlainText("player 1 wins!");
//                           cout<<"player 2 won! \n";
                           return true;
                       }
                       else if(game_the[i-c][j-c]==2 && game_the[i-(c+1)][j-(c+1)]==2 && game_the[i-(c+2)][j-(c+2)]==2 && game_the[i-(c+3)][j-(c+3)]==2)
                       {
                           ui->playerTurnText->setPlainText("player 2 wins");
//                           cout<<"player 1 won! \n";
                           return true;
                       }
                       else if(game_the[i-c][j-c]==3 && game_the[i-(c+1)][j-(c+1)]==3 && game_the[i-(c+2)][j-(c+2)]==3 && game_the[i-(c+3)][j-(c+3)]==3){
                           ui->playerTurnText->setPlainText("player 3 wins");
//                           cout << "player 3 won! \n";
                           return true;
                       }
                       else{
                           ui->playerTurnText->setPlainText("player 4 wins");
//                           cout << "player 4 won! \n";
                           return true;
                       }
                   }

               }
           }

           if((j==5&&i==6)||(j==6&&i==5))
           {
               for(int c=0;c<3;c++)
               {
                   if((game_the[i-c][j-c]==1 && game_the[i-(c+1)][j-(c+1)]==1 && game_the[i-(c+2)][j-(c+2)]==1 && game_the[i-(c+3)][j-(c+3)]==1) || (game_the[i-c][j-c]==2 && game_the[i-(c+1)][j-(c+1)]==2 && game_the[i-(c+2)][j-(c+2)]==2 && game_the[i-(c+3)][j-(c+3)]==2) || (game_the[i-c][j-c]==3 && game_the[i-(c+1)][j-(c+1)]==3 && game_the[i-(c+2)][j-(c+2)]==3 && game_the[i-(c+3)][j-(c+3)]==3) || (game_the[i-c][j-c]==4 && game_the[i-(c+1)][j-(c+1)]==4 && game_the[i-(c+2)][j-(c+2)]==4 && game_the[i-(c+3)][j-(c+3)]==4)) {
                       if(game_the[i-c][j-c]==1 && game_the[i-(c+1)][j-(c+1)]==1 && game_the[i-(c+2)][j-(c+2)]==1 && game_the[i-(c+3)][j-(c+3)]==1)
                       {
                           ui->playerTurnText->setPlainText("player 1 wins!");
                           return true;
                       }
                       else if(game_the[i-c][j-c]==2 && game_the[i-(c+1)][j-(c+1)]==2 && game_the[i-(c+2)][j-(c+2)]==2 && game_the[i-(c+3)][j-(c+3)]==2){
                           ui->playerTurnText->setPlainText("player 2 wins");
//                           cout << "player 1 won! \n";
                           return true;

                       }
                       else if(game_the[i-c][j-c]==3 && game_the[i-(c+1)][j-(c+1)]==3 && game_the[i-(c+2)][j-(c+2)]==3 && game_the[i-(c+3)][j-(c+3)]==3)
                       {
                           ui->playerTurnText->setPlainText("player 3 wins");
//                           cout<<"player 3 won !\n";
                           return true;
                       }

                       else {
                           ui->playerTurnText->setPlainText("player 4 wins");
//                           cout << "player 4 won! \n";
                           return true;
                       }
                   }

               }
           }

           if((j==4&&i==6)||(j==6&&i==4))
           {
               for(int c=0;c<2;c++)
               {
                   if((game_the[i-c][j-c]==1 && game_the[i-(c+1)][j-(c+1)]==1 && game_the[i-(c+2)][j-(c+2)]==1 && game_the[i-(c+3)][j-(c+3)]==1) || (game_the[i-c][j-c]==2 && game_the[i-(c+1)][j-(c+1)]==2 && game_the[i-(c+2)][j-(c+2)]==2 && game_the[i-(c+3)][j-(c+3)]==2) || (game_the[i-c][j-c]==3 && game_the[i-(c+1)][j-(c+1)]==3 && game_the[i-(c+2)][j-(c+2)]==3 && game_the[i-(c+3)][j-(c+3)]==3) || (game_the[i-c][j-c]==4 && game_the[i-(c+1)][j-(c+1)]==4 && game_the[i-(c+2)][j-(c+2)]==4 && game_the[i-(c+3)][j-(c+3)]==4)) {
                        if(game_the[i-c][j-c]==1 && game_the[i-(c+1)][j-(c+1)]==1 && game_the[i-(c+2)][j-(c+2)]==1 && game_the[i-(c+3)][j-(c+3)]==1)

                       {
                            ui->playerTurnText->setPlainText("player 1 wins!");
//                           cout<<"player 2 won !\n";
                           return true;
                       }
                       else if(game_the[i-c][j-c]==2 && game_the[i-(c+1)][j-(c+1)]==2 && game_the[i-(c+2)][j-(c+2)]==2 && game_the[i-(c+3)][j-(c+3)]==2)
                       {
                            ui->playerTurnText->setPlainText("player 2 wins");
//                           cout<<"player 1 won !\n";
                           return true;
                       }
                       else if(game_the[i-c][j-c]==3 && game_the[i-(c+1)][j-(c+1)]==3 && game_the[i-(c+2)][j-(c+2)]==3 && game_the[i-(c+3)][j-(c+3)]==3){
                           ui->playerTurnText->setPlainText("player 3 wins");
//                            cout << "player 3 won !\n";
                            return true;
                       }
                       else {
                            ui->playerTurnText->setPlainText("player 4 wins");
//                           cout << "player 4 won ! \n";
                            return true;
                       }
                   }

               }
           }

           if((i==6&&j==3)||(j==6&&i==3))
           {
               if((game_the[i][j]==1 && game_the[i][j+1]==1 && game_the[i][j+2]==1 && game_the[i][j+3]==1) || (game_the[i][j]==2 && game_the[i][j+1]==2 && game_the[i][j+2]==2 && game_the[i][j+3]==2) || (game_the[i][j]==3 && game_the[i][j+1]==3 && game_the[i][j+2]==3 && game_the[i][j+3]==3) || (game_the[i][j]==4 && game_the[i][j+1]==4 && game_the[i][j+2]==4 && game_the[i][j+3]==4))
               {
                   if(game_the[i][j]==1 && game_the[i][j+1]==1 && game_the[i][j+2]==1 && game_the[i][j+3]==1)
                   {
                       ui->playerTurnText->setPlainText("player 1 wins!");
//                       cout<<"player 2 won !\n";
                       return true;
                   }
                   else if(game_the[i][j]==2 && game_the[i-1][j-1]==2 && game_the[i-2][j-2]==2 && game_the[i-3][j-3]==2)
                   {
                       ui->playerTurnText->setPlainText("player 2 wins");
//                       cout<<"player 1 won !\n";
                       return true;
                   }
                   else if(game_the[i][j]==3 && game_the[i-1][j-1]==3 && game_the[i-2][j-2]==3 && game_the[i-3][j-3]==3) {
                       ui->playerTurnText->setPlainText("player 3 wins");
//                       cout<< "player 3 won! \n";
                       return true;
                   }

                   else{
                       ui->playerTurnText->setPlainText("player 4 wins");
//                       cout << "whoops";
                       return true;
                   }
               }
           }
       }
   }
   return false;
}


void board::startGame() {
    p1T=true;
    turnCount=0;
    playerturn=1;
    showBoard();


}


void board::on_placeToken_clicked()
{
    int input, row;
    std::stringstream streamS;
    bool flag2=true;
    input = ui->userC->currentIndex();
    QLabel *label_the = new QLabel(this);
    QPixmap pixr("/home/uriahnewkirk/Desktop/water/comp410/project/img/redToken.png");
    QPixmap pixc("/home/uriahnewkirk/Desktop/water/comp410/project/img/cyanToken.png");
    QPixmap pixg("/home/uriahnewkirk/Desktop/water/comp410/project/img/greenToken.png");
    QPixmap pixy("/home/uriahnewkirk/Desktop/water/comp410/project/img/yellowToken.png");
    QPixmap c;
    QString turnI;
//    QLayout *lay = new QGridLayout;



    if(playerturn==1) {
        label_the->setPixmap(pixr);
//        c = pixy;
    }
    else if(playerturn==2) {
        label_the->setPixmap(pixc);
//        c = pixc;
    }
    else if(playerturn==3) {
        label_the->setPixmap(pixy);
//        c = pixg;
    }
    else {
        label_the->setPixmap(pixg);
//        c = pixr;
    }




    for(int y=6;y>=0 && flag2==true;y--) {
        if(game_the[y][input]==-1) {
            game_the[y][input]=playerturn;
            row = y;
            flag2 = false;
        }
        else {
//            streamS << "Invalid move, your turn is now over";
//            turnI = QString::fromStdString(streamS.str());
//            ui->playerTurnText->clear();
//            ui->playerTurnText->setPlainText(turnI);
//            break;
        }

    }
    if(flag2==false) {
        if(row==0) {
            ui->row7->takeAt(input);
            ui->row7->insertWidget(input, label_the);
            ui->row7->update();
        }
        else if(row==1) {
            ui->row6->takeAt(input);
            ui->row6->insertWidget(input, label_the);
            ui->row6->update();
        }
        else if(row==2) {
            ui->row5->takeAt(input);
            ui->row5->insertWidget(input, label_the);
            ui->row5->update();
        }
        else if(row==3) {
            ui->row4->takeAt(input);
            ui->row4->insertWidget(input, label_the);
            ui->row4->update();
        }
        else if(row==4) {

            ui->row3->takeAt(input);
            ui->row3->insertWidget(input, label_the);
            ui->row3->update();
        }
        else if(row==5) {
            ui->row2->takeAt(input);
            ui->row2->insertWidget(input, label_the);
            ui->row2->update();
        }
        else {
            ui->row1->takeAt(input);
            ui->row1->insertWidget(input, label_the);
            ui->row1->update();
        }
            ui->layout_the->update();

    }


    if(flag2) {
        streamS << "Player " << playerturn << ", it's your turn";
        turnI = QString::fromStdString(streamS.str());
        ui->playerTurnText->clear();
        ui->playerTurnText->setPlainText(turnI);
    }


    showBoard();

    flag = winner();

    if(flag==false) {
        flag=boardFull();
        if(flag==false) {
            switchTurn();
            flag = true;
        }
        else {
            flag = false;
        }
    }
        else {
            winP = playerturn;
            endGame();
            flag=false;
        }

}


void board::endGame() {
    hide();
    done = new congratulations(this);
    done->show();
}


