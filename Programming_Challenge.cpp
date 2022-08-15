#include <iostream>
//#include <vector>

const int NUM_ROW = 3;
const int NUM_COL = 3;
const int NUM_OPEN_SPOTS = 9;

//class to work with array and open spaces
class TicTacToe { 
public:
    void PrintArray();
    void InitializeArray();
    void ChangeArray(std::string playerLetter, int x, int y);
    int openSquares[NUM_OPEN_SPOTS][2];
    int numOpenSquares = 0;
    std::string testArray[NUM_ROW][NUM_COL];
    int CheckWinner();
private:

};

bool PlayAgainQuestion();
bool BeginGameQuestion();
void playerTurn(TicTacToe& gameObject);
void computerTurn(TicTacToe& gameObject);


int main() {
    bool playAgain = true;
    bool playFirst = true;
    bool stillPlaying = true;
    srand(time(0));
    TicTacToe gameObject;

    std::cout << "Welcome to Tic-Tac-Toe!" << std::endl;

//main loop of game so you can replay
    do {
        gameObject.InitializeArray();
        int turnNum = 0;
        int winner = 0;
        playFirst = BeginGameQuestion();

        if (!playFirst) {
            turnNum = 1;
        }
//turns of game
        do {
            if (turnNum % 2 == 0) {
                playerTurn(gameObject);
            }
            else if (turnNum % 2 == 1) {
                computerTurn(gameObject);
            }
            gameObject.PrintArray();
            std::cout << std::endl;
            turnNum += 1;
            if (turnNum > 8) {
                stillPlaying = false;
            }
            winner = gameObject.CheckWinner();
            if (winner == 1){
                std::cout << "The Player Wins!!!" << std::endl;
                stillPlaying = false;
            }
            else if (winner == 2){
                std::cout << "The Computer Wins!!!" << std::endl;
                stillPlaying = false;
            }

        } while (stillPlaying);


        playAgain = PlayAgainQuestion();

    } while(playAgain);

    return 0;
}
//changes the array and then "deletes" the openSquare that represents the chosen square
void TicTacToe::ChangeArray(std::string playerLetter, int x, int y) {
    testArray[3 - y][x - 1] = playerLetter;
    for (int i = 0; i < numOpenSquares; ++i) {
        if ((3 - y + 1 == openSquares[i][1])&&(x + 1 == openSquares[i][0])) {
            openSquares[i][0] = -1;
            openSquares[i][1] = -1;
        }
    }
}

void TicTacToe::PrintArray() {
    std::cout << std::endl;
    for (int i = 0; i < NUM_ROW; ++i) {
        for (int j = 0; j < NUM_COL; ++j) {
            std::cout << testArray[i][j];
        }
        std::cout << std::endl;
    }
}

bool PlayAgainQuestion() {
    bool incorrectAnswer = true;
    bool playAgain = false;
    do {
        std::cout << "Would you like to play again? (y/n) : ";
        std::string playAgainAnswer = "";
        std::cin >> playAgainAnswer;
        std::cout << std::endl;
        if ((playAgainAnswer == "n")||(playAgainAnswer == "N")) {
            playAgain = false;
            incorrectAnswer = false;
        }
        else if ((playAgainAnswer == "y")||(playAgainAnswer == "Y")) {
            playAgain = true;
            incorrectAnswer = false;
        }
        else {
            continue;
        }
    } while (incorrectAnswer);
    return playAgain;
}

bool BeginGameQuestion() {
    std::string answer = "";
    bool playFirst = false;
    bool incorrectAnswer = false;

    do {
        std::cout << "Would you like to go first? (y/n) : ";
        std::cin >> answer;
        std::cout << std::endl;
        if ((answer == "y")||(answer == "Y")) {
            playFirst = true;
            incorrectAnswer = false;
        }
        else if ((answer == "n")||(answer == "N")) {
            playFirst = false;
            incorrectAnswer = false;
        }
        else {
            continue;
        }
    }
    while (incorrectAnswer);
    return playFirst;
}

void TicTacToe::InitializeArray() {
    int squareCount = 0;
    for (int i = 0; i < NUM_ROW; ++i) {
        for (int j = 0; j < NUM_COL; ++j) {
            testArray[i][j] = "-";
            openSquares[squareCount][0] = i + 1;
            openSquares[squareCount][1] = j + 1;
            squareCount += 1;
        }
    }
    numOpenSquares = 9;
}

void playerTurn(TicTacToe& gameObject) {
    int userX = 0;
    int userY = 0;
    bool invalidAnswer = true;

    do {
        bool openSquare = false;
        std::cout << "Which square do you want to go?" << std::endl << "Enter the x value (column) (1/2/3) : ";
        std::cin >> userX;
        std::cout << std::endl << "Enter the y value (row) (1/2/3) : ";
        std::cin >> userY;
        for (int i = 0; i < gameObject.numOpenSquares; ++i) {
            if ((3 - userY + 1 == gameObject.openSquares[i][0])&&(userX == gameObject.openSquares[i][1])) {
                openSquare = true;
            }
        }
        if (((userX > 3)||(userX < 1))||((userY > 3)||(userY < 0))) {
            std::cout << "Desired Square does not exist! Try Again." << std::endl;
            invalidAnswer = true;
        }
        else if (!openSquare) {
            std::cout << "Desired Square is already filled! Try Again." << std::endl;
            invalidAnswer = true;
        }
        else {
            invalidAnswer = false;
        }
        if (!invalidAnswer) {
            gameObject.ChangeArray("X", userX, userY);
        }
    } while(invalidAnswer);
}
//choses a random square that is open
void computerTurn(TicTacToe& gameObject) {
    bool invalidAnswer = true;
    int computerX = 0;
    int computerY = 0;
//    std::vector<int> currentOpenSquaresX;
//    std::vector<int> currentOpenSquaresY;
//
//    for (int i = 0; i < gameObject.numOpenSquares; ++i) {
//        if (gameObject.openSquares[i][0] != -1) {
//            currentOpenSquaresX.push_back(gameObject.openSquares[i][0]);
//            currentOpenSquaresY.push_back(gameObject.openSquares[i][1]);
//        }
//    }
//
//    int computerGuess = (rand()%currentOpenSquaresX.size() - 1);
//    std::cout << std::endl << currentOpenSquaresX.at(computerGuess) << " " << currentOpenSquaresY.at(computerGuess) << std::endl;
//    gameObject.ChangeArray("O", currentOpenSquaresX.at(computerGuess), currentOpenSquaresY.at(computerGuess));}
    do {
        bool openSquare = false;
        computerX = (rand() % 2) + 1;
        computerY = (rand() % 2) + 1;

        for (int i = 0; i < gameObject.numOpenSquares; ++i) {
            if ((3 - computerY + 1 == gameObject.openSquares[i][0]) &&
                (computerX + 1 == gameObject.openSquares[i][1])) {
                openSquare = true;
            }
        }
        if (((computerX > 3) || (computerX < 1)) || ((computerY > 3) || (computerY < 0))) {
            invalidAnswer = true;
        } else if (!openSquare) {
            invalidAnswer = true;
        } else {
            invalidAnswer = false;
        }
        if (!invalidAnswer) {
            gameObject.ChangeArray("O", computerX, computerY);
        }
    } while (invalidAnswer);
}
//checks winner first on rows, then columns, and then diagnol- returns 0 if no one won, 1 if player won, and 2 if the computer won.
int TicTacToe::CheckWinner() {
    int winner = 0;
    for (int i = 0; i < NUM_ROW; ++i) {
        int currentOInARow = 0;
        int currentXInARow = 0;
        int currentOInACol = 0;
        int currentXInACol = 0;
        for (int j = 0; j < NUM_COL; ++j) {
            if (testArray[i][j] == "O"){
                currentOInARow += 1;
                if (currentOInARow == 3){
                    winner = 2;
                    return winner;
                }
            }
            else if (testArray[i][j] == "X"){
                currentXInARow += 1;
                if (currentXInARow == 3){
                    winner = 1;
                    return winner;
                }
            }
            if (testArray[j][i] == "O"){
                currentOInACol += 1;
                if (currentOInACol == 3){
                    winner = 2;
                    return winner;
                }
            }
            else if (testArray[j][i] == "X"){
                currentXInACol += 1;
                if (currentXInACol == 3){
                    winner = 1;
                    return winner;
                }
            }

        }
    }
    for (int i = 0; i < NUM_ROW; ++i) {
        int currentXInLeftDiag = 0;
        int currentOInLeftDiag = 0;
        int currentXInRightDiag = 0;
        int currentOInRightDiag = 0;
        if (testArray[i][i] == "X"){
            currentXInLeftDiag += 1;
            if (currentXInLeftDiag == 3) {
                winner = 1;
                return winner;
            }
        }
        if (testArray[i][i] == "O"){
            currentOInLeftDiag += 1;
            if (currentOInLeftDiag == 3) {
                winner = 2;
                return winner;
            }
        }
        if (testArray[3 - i][3 - i] == "X"){
            currentXInRightDiag += 1;
            if (currentXInRightDiag == 3) {
                winner = 1;
                return winner;
            }
        }
        if (testArray[3 - i][3 - i] == "O"){
            currentOInRightDiag += 1;
            if (currentOInRightDiag == 3) {
                winner = 2;
                return winner;
            }
        }
    }
    return winner;
}