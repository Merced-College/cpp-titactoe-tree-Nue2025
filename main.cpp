/* Nue Lopez
 * 4/17/2025
 * CPSC-25
 * Assignment: TicTacToe with Trees
 */
//Description in the README.md file.
#include <iostream>
#include <vector>
#include <limits>
using namespace std;

const char HUMAN = 'X';
const char COMPUTER = 'O';
const char EMPTY = ' ';

class GameState {
private:
    vector<char> board; // 9 cells for Tic-Tac-Toe

public:
    GameState() : board(9, EMPTY) {}

    GameState(const vector<char>& b) : board(b) {}

    void printBoard() const {
        for (int i = 0; i < 9; ++i) {
            cout << (board[i] == EMPTY ? '-' : board[i]) << " ";
            if ((i + 1) % 3 == 0) cout << endl;
        }
    }

    bool isFull() const {
        for (char c : board)
            if (c == EMPTY) return false;
        return true;
    }

    bool isGameOver() const {
        return checkWinner() != EMPTY || isFull();
    }

    char checkWinner() const {
        const int winPatterns[8][3] = {
            {0,1,2}, {3,4,5}, {6,7,8},
            {0,3,6}, {1,4,7}, {2,5,8},
            {0,4,8}, {2,4,6}
        };

        for (auto& pattern : winPatterns) {
            if (board[pattern[0]] != EMPTY &&
                board[pattern[0]] == board[pattern[1]] &&
                board[pattern[1]] == board[pattern[2]]) {
                return board[pattern[0]];
            }
        }
        return EMPTY;
    }

    vector<int> getAvailableMoves() const {
        vector<int> moves;
        for (int i = 0; i < 9; ++i)
            if (board[i] == EMPTY) moves.push_back(i); //checks to see if the board is empty, and then pushes it into a vector.
        return moves;
    }

    GameState makeMove(int index, char player) const { //returns it to a game state object. takes the index and the player move.
        vector<char> newBoard = board; //creates vector based off the old board.
        newBoard[index] = player; 
        return GameState(newBoard); //returs the game state object.
    }

    const vector<char>& getBoard() const {
        return board;
    }
};

class TicTacToeTree {
public:
    int minimax(const GameState& state, bool isMaximizing) {
        char winner = state.checkWinner();  
        if (winner == COMPUTER) return 1;   //the next three are base case scenarios. if the checkWinner function comes back with the winner,
        if (winner == HUMAN) return -1;    //then if the winner is the computer, it returns 1. if the winner is the human,
        if (state.isFull()) return 0;//it returns -1. if the board is full, it returns 0.

        if (isMaximizing) { //this has to be a boolean value since it is a minimax function.
            int bestScore = numeric_limits<int>::min();
            for(int move : state.getAvailableMoves()) { //getting the game state and the available moves. the vector has all the available moves.
                GameState newState = state.makeMove(move, COMPUTER);
                int score = minimax(newState, false); //this is the recursive call to the minimax function. it's going to throw it back to the recursive call.// then, it will check the base case. 
                bestScore = max(bestScore, score); 
            }
            return bestScore;
        }else{ //if we are not maximizing, then we are minimizing.
            int bestScore = numeric_limits<int>::max();
            for (int move : state.getAvailableMoves()) {
                GameState newState = state.makeMove(move, HUMAN); //this is maximizing for the human.
                int score = minimax(newState, true);
                bestScore = min(bestScore, score);
            }
            return bestScore;
        }
    }

    int findBestMove(const GameState& state) {
        int bestScore = numeric_limits<int>::min();
        int bestMove = -1; // Track the move number
        int moveNumber = 1; 
    
        cout << "AI Decision Process:\n";
        for (int move : state.getAvailableMoves()) {
            GameState newState = state.makeMove(move, COMPUTER);
            int score = minimax(newState, false);
    
            // Print the move number, move position, and score
            if (score == -1){
                cout << "Move " << moveNumber << ": Position " << move << ", Score: bad spot (" << score << ")" << endl;

            }else{
                cout << "Move " << moveNumber << ": Position " << move << ", Score: good spot (" << score << ")" << endl;
            }

            if (score > bestScore) {
                bestScore = score;
                bestMove = move;
            }
            moveNumber++; // Increment the move number
        }
    
        cout << "AI chooses position " << bestMove;
        cout<<" with score " << bestScore << endl;
        return bestMove;
    }
};

void playGame() {//start playGame()
    GameState state; //creates a game state object.
    TicTacToeTree ai; 

    //Try to use a random class to pick who goes first...
    char playFirst;
    char currentPlayer;
    //currentPlayer = HUMAN; //Old code setting the current player to human.
    //Removed to allow the user to pick who goes first.

    //Play again as well as while !gameOver.
    bool gameOver = false;
    char playAgain;
    int aiWin = 0;
    int playerWin = 0;
    int draw = 0;

    while (!gameOver){
        cout <<"Who is playing first? c for computer, h for human: ";
        cin >> playFirst;
        if (playFirst == 'c' || playFirst == 'C'){
            currentPlayer = COMPUTER;
        }
        else{
            currentPlayer = HUMAN;
        }
        while (!state.isGameOver()) { //keeps the game going while it is NOT over.
            state.printBoard();
            if (currentPlayer == HUMAN) {
                int move;
                cout << "Enter your move (0-8): ";
                cin >> move;
                if (move >= 0 && move < 9 && state.getBoard()[move] == EMPTY) {
                    state = state.makeMove(move, HUMAN);
                    currentPlayer = COMPUTER;
                } else {
                    cout << "Invalid move. Try again.\n";
                }
            } else {
                int move = ai.findBestMove(state);
                state = state.makeMove(move, COMPUTER);
                cout << "Computer plays at position " << move << endl;
                currentPlayer = HUMAN;
            }
        }
    
        state.printBoard();
        char winner = state.checkWinner();
        if (winner == COMPUTER){
            cout << "Computer wins!\n";
            aiWin++; //Added total winnings code here.
        }
        else if (winner == HUMAN){
            cout << "You win!\n";
            playerWin++; //Added total winnings code here.
        }
        else {
            cout << "It's a draw!\n";
            draw++; //Added total winnings code here.
        }

        //Play again (added)
        cout<<"Play again? (y/n) ";
        cin >> playAgain;
        if (playAgain == 'y' || playAgain == 'Y') {
            state = GameState(); //reset the game state.
            currentPlayer = HUMAN; //reset the current player.
            gameOver = false; //reset the game over condition.
        }else{
            cout<<"AI Wins: " << aiWin << " Player Wins: " << playerWin << " Draw: " << draw << endl; //Added the total winnings.
            cout << "Thanks for playing!\n";
            gameOver = true;
        }
    }
}//end playGame()

int main() {
    playGame(); //If you want to debug, you can use the debugger by-
    return 0; //-adding a breakpoint, and this will go through the code step by step through the debugger.
}