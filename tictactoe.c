#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>






        /*
        int board[25]={

        :,:,:,:,:,
        :,0,0,0,:,
        :,0,0,0,:,
        :,0,0,0,:,
        :,:,:,:,:,

        }
        */

        int ply = 0;
        int positions = 0;
        int maxPly = 0;

        void initialization();
        void  printboard();
        void makemove();


        int inmiddle= 4;
        int corners[5]= {0,2,6,8};

        const int Directions[4] = { 1, 5, 4, 6 };

        enum { zero,one, border, EMPTY };
        enum { human, computer, draw };

        int convert[9]={
            6,7,8,
            11,12,13,
            16,17,18
        };

        int play=0;

  int GetNumForDir(int startSq,  int dir,  int *board,  int us) {
            int found = 0;
            while(board[startSq] != border) {
                if(board[startSq] != us) {
                    break;
                }
                found++;
                startSq += dir;
            }
            return found;
        }

        int FindThreeInARow( int *board,  int ourindex,  int us) {

            int DirIndex = 0;
            int Dir = 0;
            int threeCount = 1;

            for(DirIndex = 0; DirIndex < 4; ++DirIndex) {
                Dir = Directions[DirIndex];
                threeCount += GetNumForDir(ourindex + Dir, Dir, board, us);
                threeCount += GetNumForDir(ourindex + Dir * -1, Dir * -1, board, us);
                if(threeCount == 3)
                    {
                    break;
                }
                threeCount = 1;
            }
            return threeCount;
        }






        void initialization(int *board){

        int index = 0;

            for(index = 0; index < 25; ++index) {
                board[index] = border;
            }

            for(index = 0; index < 9; ++index) {
                board[convert[index]] = EMPTY;


                                    }
        }// end of initialization FUNCTION



        void  printboard( int *board, int a ){

        char *pt;
        int index=0;
        if(a==1){
        pt = "0X|-";
        }
        else{

        pt= "X0|-";
        }
        printf("\n Board: \n");

        for (index=0; index < 9;index++)
            {
            if(index!=0 && index%3==0){
                printf("\n \n");

            }

            printf("%4c ",pt[board[convert[index]]]);
        }
        printf("\n \n");
        }// end of printboard FUNCTION


                int GetHumanMove(int *board ){
                int Move=-1;
                int moveok=0;
                 char userinput[4];
                while (moveok==0){
                    printf("enter a move from 1 to 9\n");
                    fflush(stdin);
                    fgets(userinput,3,stdin);

                    fflush(stdin);//usefull when user enters more than 2 character in which case characters after the first border will be used for next loop

                    if(strlen(userinput)!=2)
                        {
                    printf("Invalid strlen()\n");
                    continue;

                    }
                    if( sscanf(userinput, "%d", &Move) != 1) { //to store the integer gave by the user and usefull when user enters strings like "dsgdfgs" to print invalid
                    Move = -1;
                    printf("Invalid sscanf()\n");
                    continue;

                }
                if( Move < 1 || Move > 9) {
                    Move = -1;
                    printf("Invalid range\n");
                    continue;
                }
                Move--;
                if(board[convert[Move]]!=EMPTY){
                        Move=-1;
                printf("already in use\n");
                continue;

                }

        moveok=1;

                }
                printf("Making Move...%d \n",Move+1);
        return convert[Move];
                }

        int hasEMPTY(int *board) {
            int index = 0;

            for(index = 0; index < 9; ++index)
            {
                if( board[convert[index]] == EMPTY)
                    return 1;
            }
            return 0;
        }

        int GetNextBest(int *board){

        int ourMove= convert[inmiddle];
        if(board[ourMove]==EMPTY){

            return ourMove;

        }
        ourMove=-1;
        int index=0;
        for(index=0;index<4;index++){
            ourMove= convert[corners[index]];
            if(board[ourMove]==EMPTY){
                break;
            }

            ourMove=-1;
        }
        return ourMove;

        }



        int GetWinningMove(int *board, const int side) {

            int ourMove = -1;
            int winFound = 0;
            int index = 0;

            for(index = 0; index < 9; ++index) {
                if( board[convert[index]] == EMPTY) {
                    ourMove = convert[index];
                    board[ourMove] = side;

                    if(FindThreeInARow(board, ourMove, side) == 3) {
                        winFound = 1;
                    }
                    board[ourMove] = EMPTY;
                    if(winFound == 1) {
                        break;
                    }
                    ourMove = -1;
                };
            }
            return ourMove;
        }



        int GetComputerMove( int *board, int side) {
            int index = 0;
            int numFree = 0;
            int availableMoves[9];
            int randommove;


            if(play==3){


                if(board[convert[0]]== zero && board[convert[8]]== zero)
                    {

                    return 7;
                }
                 if(board[convert[2]]== zero && board[convert[6]]== zero)
                    {

                    return 7;
                }
            }
            randommove = GetWinningMove(board, side);
            if(randommove != -1) {
                return randommove;
            }
            randommove = GetWinningMove(board, side^1);
            if(randommove != -1) {
                return randommove;
            }
        randommove = GetNextBest(board);
            if(randommove != -1) {
                return randommove;
            }


            for(index = 0; index < 9; ++index) {
                if( board[convert[index]] == EMPTY)
                    {
                    availableMoves[numFree++] = convert[index];
                }
            }

            randommove = (rand() % numFree);
            return  availableMoves[randommove];


        }




        void makemove( int *board, const int sq, int side)
        {
            board[sq] = side;    //to use 0 in the placeholder value EMPTY
        }





        //minmax algorithm


        /*************MINMAX-************/

        int FindThreeInARowAllBoard(int *board,int us) {
            int threeFound = 0;
            int index;
            for(index = 0; index < 9; ++index) {
                if(board[convert[index]] == us) {
                    if(FindThreeInARow(board,convert[index], us) == 3) {
                        threeFound = 1;
                        break;
                    }
                }
            }
            return threeFound;
        }

        int EvalForWin(int *board, const int us) {

            if(FindThreeInARowAllBoard(board, us) != 0)
                return 1;
            if(FindThreeInARowAllBoard(board, us ^ 1) != 0)
                return -1;

            return 0;
        }



        int MinMax(int *board, int side) {

              // check is a win
            // gen all moves for side
            // loop moves, make move, mimax() on move to get score
            // assess bestscore
            // end moves return bestscore


            int MoveList[9];
            int MoveCount = 0;
            int bestScore = -2;
            int score = -2;
            int bestMove = -1;
            int Move;
            int index;

            if(ply > maxPly) maxPly = ply;
            positions++;

            if(ply > 0) {
                score = EvalForWin(board, side);
                if(score != 0) {
                    return score;
                }
            }

            // fill Move List
            for(index = 0; index < 9; ++index) {
                if( board[convert[index]] == EMPTY) {
                    MoveList[MoveCount++] = convert[index];
                }
            }

            // loop all moves
            for(index = 0; index < MoveCount; ++index) {
                Move = MoveList[index];
                board[Move] = side;

                ply++;
                score = -MinMax(board, side^1);
                if(score > bestScore) {
                    bestScore = score;
                    bestMove = Move;
                }
                board[Move] = EMPTY;
                ply--;
            }

            if(MoveCount==0) {
                bestScore = FindThreeInARowAllBoard(board, side);
            }

            if(ply!=0)
                return bestScore;
            else
                return bestMove;
        }




        int MINMAX(int *board, int side){


            ply=0;
            positions=0;
            maxPly=0;
            int best = MinMax(board, side);
            printf("Finished Searching positions:%d maxDepth:%d bestMove:%d\n",positions,maxPly,best);
            return best;


        }



        void  rungame (int a, int b)
        {
                int GameOver = 0;
                int side ;
        if(b==1){
            side = zero;
            }
            else{
            side = one;
            }
            int LastMoveMade = 0;
            int board[25];
                     initialization(board);

                    printboard(board, a);

            while(!GameOver){


                if(side==zero) {
                    LastMoveMade=GetHumanMove(board);// get move from human, make move on board, change side
                makemove(board,LastMoveMade,side);
                side= one;
                } else {
                      LastMoveMade = GetComputerMove(&board[0], side);

                    makemove(&board[0],LastMoveMade,side);
                    side=zero;
                    printboard(&board[0], a);
                }

            play++;

            if( FindThreeInARow(board, LastMoveMade, side ^ 1) == 3) {
                    printf("Game over!\n");
                    GameOver = 1;
                    if(side==zero) {
                        printf("Computer Wins\n");
                    } else {
                        printf("Human Wins\n");
                    }
                }		// if EMPTY in a row exists Game is over

                // if no more moves, game is a draw
        if(!hasEMPTY(board)){

            printf("its a draw");

                GameOver = 1; // REMOVE ME !!

        }//end of hasempty

            }// end of WHile loop
         printboard(board, a);
        }//end of rungame FUNCTION











        int  main() {




            int decision;
            //char decision[4];
            int a;
            int b;
             label:
  	printf("choose your symbol  0/X (1 - for 0, 2 - for X)");
    	 scanf("%d",&a);
 fflush(stdin);
if (a!=1 && a!=2){
    printf("\t invalid Number \n");
    goto label;
}
label1:
printf("Do you want to go FIRST (YES =1 / NO=0)");
//scanf("%s",&decision);
scanf("%d",&decision);
 fflush(stdin);

 //if(strcmp(decision, "YES")!=0 && strcmp(decision, "Yes")!=0 && strcmp(decision, "yes")!=0&& strcmp(decision, "NO")!=0 && strcmp(decision, "No")!=0  &&strcmp(decision, "no")!=0){

   //printf("invalid Answer");
   //goto label1;

 //}
 //if(strcmp(decision, "YES")!=0 ||strcmp(decision, "yes")!=0 ||strcmp(decision, "Yes")!=0){
   // b=1;
 //}

 //else if(strcmp(decision, "NO")!=0 ||strcmp(decision, "no")!=0 ||strcmp(decision, "No")!=0){
   // b=0;
//}
//else{
  //      printf("invalid");
//}
if (decision==1){ //our turn
    b=1;
}
else if (decision==0){
    b=0;
}
else{
    printf("\t INVALID!!!! \n");
    goto label1;
}


                        srand(time(NULL));

                        rungame(a,b);

                        return 0;
                    }







