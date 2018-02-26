//Uriah Newkirk
//February 5th, 2015
//GEEN 165 Homework Assignment #3
//Play the game of Nim against the computer, but always lose as the computer knows every winning strategy

public class nimGame
{

   static java.util.Random generate = new java.util.Random();     
   //java object to generate random numbers

   static int[][] urns = new int[15][3];     
   //static array used to keep track of all possible moves that can be made and which are more probable to result in a win
   
   static int[] choiceProb = new int[15];
   //static array used to keep track of the computer's choices throughout a single game

   public static void main(String[] colour) 
   {
   
      java.util.Scanner keyboard = new java.util.Scanner(System.in);    //scanner object to read keyboard inputs 
   
      int marbles=15;                                 //total marbles used in the game
      boolean playerturn=generate.nextBoolean();      //randomly choose who gets to go first
      int playerA=0;    //amount of marbles the computer chooses to take
      int playerB=0;    //amount of marbles the 2nd computer chooses to take
      int marker=0;     //store which choice was selected when calculating probability of that choice being successful
      int player1=0;    //amount of marbles the user chooses to take
   
      for(int j =0;j<urns.length;j++)     //for loop to run through the first dimension of the array
      {
      
         for(int y=0;y<urns[j].length;y++)   //for loop to run through the second dimension of the array
         {
         
            urns[j][y]=500;         
            //initialize all ints inside the array to the value of 500
         
         }
      }
   
      for(int z=0;z<100000;z++)
      {
      
         while(marbles>1)
         {
         
            if(playerturn)    //if it's playerA's turn
            {
            
               playerA = probPick(urns[generate.nextInt(15)]);
               //call the probPick method using a randomly chosen dimension of the 15x3 array
            
               choiceProb[marbles-1]=playerA;
               //record playerA's move in the array indexed to the number of marbles that were in the pile
            
               marbles-=playerA;
               //decrease total marble count by whatever number the user selected
               
               playerturn=false;
               //end playerA's turn so it's now playerB's turn
               
            }
            else
            {
            
               playerB=probPick(urns[generate.nextInt(15)]);
               //call the probPick method using a randomly chosen dimension of the 15x3 array
            
               marbles-=playerB;
               //decrease total marble count by whatever number the user selected
               
               playerturn=true;
               //end playerB's turn so it's now playerA's turn
               
            }
         }
      
         if(playerturn)       //if it's playerA's turn
         {
            
            for(int s=0;s<choiceProb.length;s++)
            {
            
               marker=choiceProb[s];
               //record the moves taken in the last game played to the 1 dimensional array
               if(marker>0)
               {
               
                  urns[s][marker-1]--;
                  //decrement the probability of choosing that move again since the computer (playerA) lost 
               
               }
            } 
         }
         else
         {
         
            for(int s=0;s<choiceProb.length;s++)
            {
            
               marker=choiceProb[s];
               //record the moves taken in the last game played to the 1 dimensional array 
               if(marker>0)
               {
               
                  urns[s][marker-1]++;
                  //increment the probability of choosing that move again since the computer (playerA) won  
               
               }
            }
         }
         marbles=15; 
         //reset marbles for next game program plays against itself
      }
   
      marbles=15;
      //reset marbles for next game program plays against itself
      playerturn=generate.nextBoolean();     
      //reset the playerturn and marble count values for the actual game you play against the program
      
      while(marbles>1)
      {
            
         if(playerturn)          //if it's the user's turn
         {
         
            System.out.println("Your turn, choose a number 1, 2, or 3");
            //inform the user it's their turn and let them know what numbers they can choose
            player1=keyboard.nextInt();
            //choose a number of marbles to take
            
            if(player1>0 && player1<4)
            {
            
               marbles-=player1;
               //decrease total marble count by whatever number the user selected
               System.out.println(marbles +" marbles remaining");
               //inform user of amount of marbles remaining
               playerturn=false;
               //end the user's turn so it's now the computer's turn
            
            }
            else
            {
            
               System.out.println("wrong number, please try again");    
               //inform the user their number is not in the range of possible choices
            
            }
         }
         else              //if it's the computer's turn
         {
         
            if(marbles<=4)
            {
            
               playerA=marbles-1;
               //at this point the computer wins by just leaving 1 marble for you to take away
               System.out.println("Computer chooses " +playerA);
               //inform the user of the computer's choice of marbles to take away
               marbles-=playerA;
               //decrease total marble count by whatever number the user selected
               System.out.println(marbles +" marble(s) remaining");
               //inform user of amount of marbles remaining
               playerturn=true;
               //end computer's turn so it's now the user's turn
               break;      
               //break since the computer wins in this if statement is true
            
            }
            playerA=probPick(urns[marbles-1]);
            //call the probPick method using the amount of marbles left so the program can determine the best possible move to result in a win
         
            System.out.println("Computer chooses " +playerA);
            //inform the user of the computer's choice of marbles to take away
         
            marbles-=playerA;       
            //decrease total marble count by whatever number the user selected
         
            System.out.println(marbles +" marble(s) remaining");  
            //inform user of amount of marbles remaining
         
            playerturn=true;     
            //end computer's turn so it's now the user's turn
         
         }   
      }
   
      if(playerturn)       //if it's the user's turn
      {
      
         System.out.println("Game Over...You lose!");    
         //inform user that they have lost
      
      }
      else                 //if it's the computer's turn
      {  
      
         System.out.println("Game Over...You win");      
         //unnecessary print statement since you'll always lose
      
      }
   
   }

   static int probPick(int[] odds) {
      int sum = odds[0] + odds[1] + odds[2]; // sum of all probabilities (of choices 1, 2, & 3) of for that many marbles left
      int randnum = generate.nextInt( sum ); // random number 0 to sum-1
      //as this program plays games, the odds shift to more favorable moves with that many particular marbles left
      if (odds[0] >= randnum) {
         return 1;
      }
      else if (odds[0]+odds[1] >= randnum) {
         return 2;
      }
      else {
         return 3;
      }
   }
}
