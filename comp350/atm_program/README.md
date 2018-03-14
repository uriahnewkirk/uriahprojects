Assignment 2 (ATM)
3 -13- 18 11PM

Automated Teller Machines (ATM)

Consider this scenario. Suppose that 8 people in the company have access to the Mt. Tabor Pumpkin account. Each person (thread) 
can make a deposit (D) followed by an amount in dollars (integer), a withdrawal (W) followed by an amount in dollars (integer) and
can check the ballance (B) of the account. Your job is to accurately keep track of the balance in the Mt. Tabor Pumpkin account. 
The input for this file will be a series of lines representing the activity of each person's tranactions on the account for a given week. 
The file name for input will be trans.txt.After each successful transaction (D,W,B) your program should record the transaction to a 
file named activity.txt. Clearly viewing the current account balance can be accessed by more than one user at a time. However, modification
to the account, should be protected and only allowed by one person at a time. You may assume that the initial value of the Mt. 
Tabor Pumpkin account is 10,000. If negative balance occurs no problem.

Example of input:

B W 100 D 50 D 10 B
W 50 B D 100
B B B D 10 D 100 D 100 W 50
W 50 D 10 D 10 D 10 D 5
W 10 B B D 1000
B W 500
B
W 100 W 100 W 100 B D 500 D 500 D 500

Example output:

Thread 0 checks balance, balance is : 1000

Thread 3 withdraws 50, balance is : 950

.
.
.


Name this program atm.cpp and place it in your pgm directory. 
