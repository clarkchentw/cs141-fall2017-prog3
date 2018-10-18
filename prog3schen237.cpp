#include <iostream>
#include <math.h>
#include <stdio.h> // for getchar()
using namespace std;


// Global Variable
int playerMindData[8][2];
int currentScore = 0;
int numOfMove = 1;
bool gameNotEnd = true;
bool displayDataTable = false;
bool nextPredictedNum = 0;

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
void printCurrentProgress(){
    int numOfSpace;
    cout << "Computer          Human" << endl;
    cout << "x---------x+++++++++x" << endl;
    for (int i = currentScore+10; i > 0; i--){
        cout << " ";
    }
    cout << "^" << endl;
}



//------------------------------------------------------------------------------
// Reset Game
void resetGame(bool last3Guess[]){
    currentScore = 0;
    numOfMove = 1;
    for (int i = 0; i < 3; i++){
        last3Guess[i] = 0;
    }
    
    for (int i = 0; i < 8; i++){
        for (int x = 0; x < 2; x++){
            playerMindData[i][x] = 0;
        }
    }
}


//------------------------------------------------------------------------------
// showDataTable, to show how computer is work
void showDataTable(bool last3Guess[]){
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
// Update last3Guess variable with new data
void updateLast3Guess(bool last3Guess[], int newGuess){
    last3Guess[0] = last3Guess[1];
    last3Guess[1] = last3Guess[2];
    last3Guess[2] = newGuess;
}

//------------------------------------------------------------------------------
// binary to decimal conversion for binary 000~111
int binaryToDecimal(int binaryNum){
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
// Predict user's number
void generateNextPredict(bool last3Guess[]){
    int binaryNum = last3Guess[0]*100 + last3Guess[1]*10 + last3Guess[2];
    int arrayAddress = binaryToDecimal(binaryNum);
    if (playerMindData[arrayAddress][0] > playerMindData[arrayAddress][1]){
        nextPredictedNum = 0;
    }
    else if (playerMindData[arrayAddress][0] < playerMindData[arrayAddress][1]){
        nextPredictedNum = 1;
    }
    else{
        nextPredictedNum = !last3Guess[2];
    }
    
}

//------------------------------------------------------------------------------
// record current last3Guess to database
void recordToDatabase(bool last3Guess[], bool userInput){
    if (numOfMove < 5){
        return;
    }
    int binaryNum = last3Guess[0]*100 + last3Guess[1]*10 + last3Guess[2];
    int arrayAddress = binaryToDecimal(binaryNum);
    playerMindData[arrayAddress][userInput]++;
}



//------------------------------------------------------------------------------
// Process for game end;
void gameEnd(){
    printCurrentProgress();
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

//------------------------------------------------------------------------------
// control current score
void scoreControl(bool humanWin){
    if (currentScore > -10 && currentScore < 10){
        if (humanWin){
            if (currentScore == 9){
                gameNotEnd = false;
            }
            currentScore++;
        }
        else{
            if (currentScore == -9){
                gameNotEnd = false;
            }
            currentScore--;
        }
    }
    else{
        gameNotEnd = false;
    }
}

//------------------------------------------------------------------------------
// process when human win
void humanWin(){
    scoreControl(true);
    cout << "Human gets a point." << endl << endl;
    
}

//------------------------------------------------------------------------------
// process when human lose
void humanLose(){
    scoreControl(false);
    cout << "Computer gets a point." << endl << endl;
}

//------------------------------------------------------------------------------
// Main Work after the validation
void mainProcess(bool last3Guess[], bool& validUserInput){
    // numOfMove + 1 when user input is valid
    ++numOfMove;
    recordToDatabase(validUserInput, last3Guess);
    updateLast3Guess(validUserInput, last3Guess);
    
    if (validUserInput == nextPredictedNum){
        humanLose();
    }
    else{
        humanWin();
    }
    
    
    generateNextPredict();
}
//(5 points) User input of 'r' or 'R' will prompt for and read in 16 single-digit numbers separated by spaces to set the moves table to the values that are provided.  It should also reset the last three moves and the move number should be reset to 1.
//------------------------------------------------------------------------------
// Input Check: check for special function key, and make sure user
void customTable(){
    char userInput[64];
    int prepareEntry[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    // indicate the current process address for custom tab;e
    int currentAddress = 0;
    // highestValidAddress
    cout << "You have initialized the custom table function" << endl;
    cout << "begin enter 16 custom table value, seperate each value by space:" << endl;
    
    cin.getline (userInput, 64);
    for (int i = 0; i < 64; i++){
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
    for (int i = 0; i < 16; i+=2){
        //cout << prepareEntry[i] << " " << prepareEntry[i+1] << endl;
        playerMindData[destAddr][0] = prepareEntry[i];
        playerMindData[destAddr][1] = prepareEntry[i+1];
        destAddr++;
    }
    // for (int i = 0; i < 64; i+=1){
    //     cout << i << ": " << userInput[i] << endl;
    // }
    cout << endl;

}

//------------------------------------------------------------------------------
// Input Check: check for special function key, and make sure user
// input a valid command length
void inputControl(bool last3Guess[]){
    bool validUserInput;
    char userInput = getchar();
    
    if (userInput == '\n'){
        return;
    }
    
    char userlessValue = getchar();
    if (userInput == '1' || userInput == '0'){
        if (userInput == '1'){
            validUserInput = true;
        }
        else{
            validUserInput = false;
        }
        mainProcess(last3Guess, validUserInput);
        return;
    }
    else if (toupper(userInput) == 'X'){
        customTable();
    }
    else if (toupper(userInput) == 'T'){
        if (displayDataTable){
            displayDataTable = false;
        }
        else
        {
            displayDataTable = true;
        }
        return;
    }
    else if (toupper(userInput) == 'R'){
        resetGame(last3Guess);
        return;
    }
    else{
        cout << endl << "invalid input detected, please re-enter again" << endl;
        return;
    }
} //end inputControl(bool& validUserInput)

//------------------------------------------------------------------------------
// Control all the user input, and process them
void controlUnit(bool last3Guess[]){
    
    printCurrentProgress();
    if (displayDataTable){
        showDataTable();
    }
    char userInput;
    cout << numOfMove << ". Your input: ";
    
    inputControl(last3Guess);
    
    cout << endl;
}

int main() {
    
    bool last3Guess[3];
    
    
    resetGame();
    printGameInfo();
    
    while(gameNotEnd){
        controlUnit(last3Guess);
        //cout << endl << endl << currentScore << endl << endl;
    }
    
    gameEnd();
    
}
