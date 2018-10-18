#include <iostream>
using namespace std;

//------------------------------------------------------------------------------
// Print out the Game Information
void printGameInfo(){
    cout << "Author:  Clark Chen" << endl;
    cout << "Lab:     Tue 9am" << endl;
    cout << "Program: #3, 0/1 Guessing Game " << endl << endl;

    cout << "Welcome to the 0/1 guessing game!" << endl << endl;

    cout << "Enter 0 or 1, trying to outsmart the computer, which is going to" << endl;
    cout << "attempt to forecast your guesses.  On each move the score indicator" << endl;
    cout << "moves to the right if the computer guesses correctly, and moves" << endl;
    cout << "to the left if the computer does not." << endl;
    cout << "    Enter 't' to toggle displaying the data table." << endl;
    cout << "    Enter 'r' to reset the board." << endl;
    cout << "    Enter 'x' to exit." << endl;
    cout << "Good luck, you'll need it!" << endl << endl;
}

//------------------------------------------------------------------------------
// Print out the current win/lose progress of the game
void printCurrentProgress(const int currentScore){
    int numOfSpace;
    cout << "Computer          Human" << endl;
    cout << "x---------x+++++++++x" << endl;
    for (int i = currentScore+10; i > 0; i--){
        cout << " ";
    }
    cout << "^" << endl;
}

//------------------------------------------------------------------------------
// binary to decimal conversion for binary 000~111
int binaryToDecimal(const int binaryNum){
    int arrayAddress;
    switch(binaryNum){
        case 0: arrayAddress = 0;
                break;
        case 1: arrayAddress = 1;
                break;
        case 10: arrayAddress = 2;
                break;
        case 11: arrayAddress = 3;
                break;
        case 100: arrayAddress = 4;
                break;
        case 101: arrayAddress = 5;
                break;
        case 110: arrayAddress = 6;
                break;
        case 111: arrayAddress = 7;
                break;
    }
    return arrayAddress;
    
}

//------------------------------------------------------------------------------
// showDataTable, to show the data table that computer is using
void showDataTable(const int playerMindData[8][2], const bool last3Guess[], const bool nextPredictedNum){
    cout << "         0   1" << endl;
    cout << "       --- ---" << endl;
    cout << "   000   " << playerMindData[0][0] << "   " << playerMindData[0][1] << endl;
    cout << "   001   " << playerMindData[1][0] << "   " << playerMindData[1][1] << endl;
    cout << "   010   " << playerMindData[2][0] << "   " << playerMindData[2][1] << endl;
    cout << "   011   " << playerMindData[3][0] << "   " << playerMindData[3][1] << endl;
    cout << "   100   " << playerMindData[4][0] << "   " << playerMindData[4][1] << endl;
    cout << "   101   " << playerMindData[5][0] << "   " << playerMindData[5][1] << endl;
    cout << "   110   " << playerMindData[6][0] << "   " << playerMindData[6][1] << endl;
    cout << "   111   " << playerMindData[7][0] << "   " << playerMindData[7][1] << endl;
    cout << "   Previous three: " << last3Guess[0] << last3Guess[1] << last3Guess[2] << ".  ";
    cout << "Forecast: " << nextPredictedNum <<endl;
}

//------------------------------------------------------------------------------
// Reset Game, reset all variable to default
void resetGame(int& currentScore, bool (&last3Guess)[3], int (&playerMindData)[8][2], int& numOfMove){
    currentScore = 0;
    numOfMove = 1;
    for (int i = 0; i < 3; i++){
        last3Guess[i] = 1;
    }

    for (int i = 0; i < 8; i++){
        for (int x = 0; x < 2; x++){
            playerMindData[i][x] = 0;
        }
    }
}

//------------------------------------------------------------------------------
// Update last3Guess variable with new data
void updateLast3Guess(bool (&last3Guess)[3], const int newGuess){
    last3Guess[0] = last3Guess[1];
    last3Guess[1] = last3Guess[2];
    last3Guess[2] = newGuess;
}

//------------------------------------------------------------------------------
// record current last3Guess to database
void recordToDatabase(const int numOfMove, const bool last3Guess[3], const bool userInput, int (&playerMindData)[8][2]){
    // Only record data begin from 4th moves
    if (numOfMove < 4){
        return;
    }
    int binaryNum = last3Guess[0]*100 + last3Guess[1]*10 + last3Guess[2];
    int arrayAddress = binaryToDecimal(binaryNum);
    playerMindData[arrayAddress][userInput]++;
}

//------------------------------------------------------------------------------
// Input Check: check for special function key, and make sure user
void customTable(int (&playerMindData)[8][2]){
    char userInput[64];
    // Prepare store the user input into an one dementional array first before
    // import into two dementional array
    int prepareEntry[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    
    // indicate the current process address for custom table
    int currentAddress = 0;
    
    cout << "You have initialized the custom table function" << endl;
    cout << "begin enter 16 custom table value, seperate each value by space:" << endl;
    
    // To ignore all other cin input before here
    cin.ignore();
    cin.getline (userInput, 64);
    
    
    // Process user input data
    for (int i = 0; i < 64; i++){
        // Ignore any additional input after 16th
        if (currentAddress >= 16){break;}
        if (isdigit(userInput[i])){
            prepareEntry[currentAddress] = prepareEntry[currentAddress] * 10 + (userInput[i] - '0');
        }
        else{
            currentAddress++;
        }
    }
    
    // Destination array address for the loop below
    int destAddr = 0;
    
    // Import the processed user input into the database
    for (int i = 0; i < 16; i+=2){
        playerMindData[destAddr][0] = prepareEntry[i];
        playerMindData[destAddr][1] = prepareEntry[i+1];
        destAddr++;
    }
    cout << endl;

}

//------------------------------------------------------------------------------
// Predict user's number using the database
void generateNextPredict(const bool last3Guess[], const int playerMindData[8][2], bool& nextPredictedNum){
    int binaryNum = last3Guess[0]*100 + last3Guess[1]*10 + last3Guess[2];
    int arrayAddress = binaryToDecimal(binaryNum);
    if (playerMindData[arrayAddress][0] > playerMindData[arrayAddress][1]){
        nextPredictedNum = 0;
    }
    else if (playerMindData[arrayAddress][0] < playerMindData[arrayAddress][1]){
        nextPredictedNum = 1;
    }
    else{
        // if not enough data to predict user's number, use the opposite of the previous entry
        nextPredictedNum = !last3Guess[2];
    }
    
}

//------------------------------------------------------------------------------
// control current score
void scoreControl(int& currentScore, bool& gameNotEnd, const bool humanWin){
    // Restriction for score range, and process if win or lose
    if (currentScore > -10 && currentScore < 10){
        if (humanWin){
            if (currentScore == 9){
                gameNotEnd = false;
            }
            cout << "Human gets a point." << endl;
            currentScore++;
        }
        else{
            if (currentScore == -9){
                gameNotEnd = false;
            }
            cout << "Computer gets a point." << endl;
            currentScore--;
        }
        
        // Mid point message
        if (currentScore == -5){
            cout << ">>> You're going to lose! <<<" << endl;
        }
        else if (currentScore == 5){
            cout << ">>> You're a step closer to win!! <<<" << endl;
        }
        cout << endl;
    }
    else{
        gameNotEnd = false;
    }
}

int main() {
    int currentScore = 0;
    bool last3Guess[3];
    int playerMindData[8][2];
    int numOfMove = 1;
    char userInput;
    bool gameNotEnd = true;
    bool displayDataTable = false;
    bool nextPredictedNum = 0;
    
    // reset game before the game start
    resetGame(currentScore, last3Guess, playerMindData, numOfMove);
    
    printGameInfo();
    
    while(gameNotEnd){
        printCurrentProgress(currentScore);
        
        // Display User data only if toggled
        if (displayDataTable){
            showDataTable(playerMindData, last3Guess, nextPredictedNum);
        }
        
        
        // receive input
        cout << numOfMove << ". Your input: ";
        cin >> userInput;
        
        // User Input Control
        if (!isdigit(userInput)){
            switch(toupper(userInput)){
                case 'T':   if (displayDataTable){
                                displayDataTable = false;
                            }
                            else{
                                displayDataTable = true;
                            }
                            break;
                case 'X': gameNotEnd = false; break;
                case 'R':   resetGame(currentScore, last3Guess, playerMindData, numOfMove);
                            customTable(playerMindData);
                            generateNextPredict(last3Guess, playerMindData, nextPredictedNum);
                            break;
                default: cout << endl << "invalid input detected, please re-enter again" << endl; break;
            }
        }
        
        // Execute User's playing action
        else if (userInput - '0' == 0 || userInput - '0' == 1){
            userInput -= '0';
            recordToDatabase(numOfMove, last3Guess, userInput, playerMindData);
            updateLast3Guess(last3Guess, userInput);
            if (userInput == nextPredictedNum){
                scoreControl(currentScore, gameNotEnd, false);
            }
            else{
                scoreControl(currentScore, gameNotEnd, true);
            }
            generateNextPredict(last3Guess, playerMindData, nextPredictedNum);
            numOfMove++;
        }
        
        // Invalid Input Message
        else{
            cout << endl << "invalid input detected, please re-enter again" << endl;
        }
        
        // Space between each input
        cout << endl;
    }
    
    // Game Ending... Procedure
    printCurrentProgress(currentScore);
    if (currentScore == 10){
        cout << "Congratulation!! Human beat the computer!!";
    }
    else if (currentScore == -10){
        cout << "Sorry to say that, but human lost...";
    }
    else{
        cout << "Exiting...";
    }
    
}
