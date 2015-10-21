//Author: Evan Glazer


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Costs for buying and selling a chip.
#define CHIP_BUY 11
#define CHIP_SELL 10

// Used to determine the status of a game.
#define WIN 1
#define LOSS 0
#define CONTINUE 2

int pairofdice();
int craps();
int craps_outcome(int roll);
int arupsdice();
int arups_outcome(int roll);
void statusreport(int numchips, int cash);
int buychips(int *cash, int *chips);
int sellchips(int numchips);
void dobuy(int *cash, int *numchips);
void dosell(int *cash, int *numchips);

int menu();
int validchips(int *chipsbet, int numchips);

int main() {

    // Set up variables and initial values.
    int choice, cash=1000;
    int numchips=0, chipsbet, numsell;

    srand(time(0)); // Initialize random number generator.

    // Continue until the user quits.
    while ((choice = menu()) != 6) {

        // Execute the appropriate choice.
        if (choice == 1) {
            dobuy(&cash, &numchips);
        }
        else if (choice == 2) {
            dosell(&cash, &numchips);
        }
        else if (choice == 3) {

            // Only play if a valid number of chips is bet.
            if (validchips(&chipsbet, numchips)) {

                // Adjust current number of chips based on the game outcome.
                if (craps())
                    numchips += chipsbet;
                else
                    numchips -= chipsbet;
            }
        }
        else if (choice == 4) {

            // Only play if a valid number of chips is bet.
            if (validchips(&chipsbet, numchips)) {

                // Adjust current number of chips based on the game outcome.
                if (arupsdice())
                    numchips += chipsbet;
                else
                    numchips -= chipsbet;
            }
        }
        else if (choice == 5) {
            statusreport(numchips, cash);
        }
    }

    // Sell the remaining chips and print out the final message.
    cash += sellchips(numchips);
    printf("After selling your chips, you have $%d.",cash);
    printf(" Thanks for playing!\n");

    return 0;
}

// Returns an integer in between 2 and 12, inclusive, representing the
// result of rolling two fair six-sided dice.
int pairofdice() {
   int randNum;
   srand(time(0));
   randNum = 2+rand()%12+1;
    return 0;
}

// Let's the user play craps. Returns 1 if the user wins, 0 otherwise.
int craps() {
	int diceCount, user;
	diceCount = pairofdice();
    if (diceCount == 7 || diceCount == 11)
    	user = WIN;
    else
    	user = LOSS;
    return 0;
}

// Returns the status of a craps game based on the first roll.
int craps_outcome(int roll) {
    roll = craps();
    return 0;
}

// Let's the user play Arup's Game of Dice.
// Returns 1 if the user wins, 0 otherwise.
int arupsdice() {

    int first_roll, second_roll, status;
    char dummy[50];

    // Execute the first die roll.
    printf("Press 'r' and hit enter for your first roll.\n");
    scanf("%s", dummy);
    first_roll = pairofdice();
    printf("You rolled a %d.\n", first_roll);

    // Determine the current game status.
    status = arups_outcome(first_roll);

    // Go ahead and execute the second die roll if necessary.
    if (status == CONTINUE) {

        // Execute the second die roll.
        printf("Press 'r' and hit enter for your next roll.\n");
        scanf("%s", dummy);
        second_roll = pairofdice();
        printf("You rolled a %d.\n", second_roll);

        // Determine if the user won or not.
        if (second_roll > first_roll)
            status = WIN;
        else
            status = LOSS;
    }

    // Return the final outcome of the game.
    if (status == WIN) {
        printf("You win!\n");
        return WIN;
    }
    else {
        printf("Sorry, you have lost.\n");
        return LOSS;
    }
}

// Returns the status of Arup's Game of Dice, based on the first roll.
int arups_outcome(int roll) {
	int diceCount;
	diceCount = arupsdice();
    if (diceCount == 11 || diceCount == 12)
    	roll = WIN;
    else
    	roll = LOSS;
    return 0;
}

// Prints out the user's current status.
void statusreport(int numchips, int cash) {
    printf("You currently have $ %d left "), buychips(cash);
  
   }

// Adjusts the variable pointed to by cash to equal the change received
// from purchasing the maximum possible number of chips for the value
// of that variable, originally. Returns the total number of purchased
// chips.
void buychips(int *cash, int *chips) {
    printf("How much cash do you want to spend for chips? \n");
    scanf("%d", &cash);
    *chips = (cash)/(*CHIP_BUY);

    return buychips(*chips);

}

// Returns the cash gained by selling numchips chips.
int sellchips(int numchips) {
   numchips = numchips * CHIP_SELL;
   return sellchips(numchips);
}

// Prints out the menu for the user and returns the user's choice.
int menu() {
     int choice = 0;

  printf("Welcome to the Casino. Here are your choices: \n");
  printf("1. Buy Chips\n");
  printf("2. Sell Chips\n");
  printf("3. Play Craps\n");
  printf("4. Play Arup's Game of Dice'\n");
  printf("5. Status Report\n");
  printf("6. Quit.\n");

  // Loop until a valid answer is entered.
  while (1) {
    scanf( "%d", &choice);
    if (choice < 1 || choice > 6)
      printf("Sorry, that is not a valid choice, try again.\n");
    else
      break;
  }

  return choice;
}

// Determines if the user has entered a valid number of chips to bet.
// chipsbet is a pointer to the variable storing the number of chips the
// user is betting and numchips is the current number of chips the user
// has. 1 is returned if the bet is valid, 0 is returned otherwise.
int validchips(int *chipsbet, int numchips) {
   	if (chipsbet == numchips){
   		return 1;
   }
   	else if (numchips > chipsbet){
   		return 1;
   }
    else{
    	return 0;
    }
}

// Executes buying chips. Both cash and numchips are pointers to the
// variables storing the user's amount of cash and number of chips,
// respectively.
void dobuy(int *cash, int *numchips) {
  	*cash = (CHIP_BUY)*(numchips);
  	*numchips = (*cash / *numchips);
  	return dobuy(cash, numchips);
  	}

// Executes selling chips. Both cash and numchips are pointers to the
// variables storing the user's amount of cash and number of chips,
// respectively.
void dosell(int *cash, int *numchips) {

    int numsell;

    // Determine the number of chips to be sold.
    printf("How many chips do you want to sell?\n");
    scanf("%d", &numsell);

    // Print out the error message if this is too much.
    if (numsell > *numchips)
        printf("Sorry, you do not have that many chips. No chips sold.\n");

    // Execute the transaction.
    else {
        (*cash) += sellchips(numsell);
        (*numchips) -= numsell;
    }
}
