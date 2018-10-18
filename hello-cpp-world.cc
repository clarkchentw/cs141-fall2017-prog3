#include <iostream>
#include <math.h>
#include <stdio.h> // for getchar()
#include <time.h> // for srand()'s time
using namespace std;

int main() {
    char userInput;
    int newValue = 999;
    cout << "Begin input: ";
        for (int i = 0; i < 8; i++){
            for (int x = 0; i < 2; i++){
            while(true){
                userInput = getchar();
                if (userInput != ' '){
                    if (newValue == 999){
                        newValue = userInput - '0';
                        cout << endl << newValue;
                    }
                    newValue = newValue * 10 + (userInput - '0');
                }
                else{
                    break;
                }
            }
            }
        }
}
