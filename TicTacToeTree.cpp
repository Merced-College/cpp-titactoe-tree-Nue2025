#include <iostream>
#include <vector>
#include <limits>
using namespace std;

const char HUMAN = 'X';
const char COMPUTER = 'O';

#include "GameState.cpp"

class TicTacToeTree {
    public:
        int minimax(const GameState& state, bool isMaximizing) {
            char winner = state.checkWinner();  
            if (winner == COMPUTER) return 1;   //the next three are base case scenarios. if the checkWinner function comes back with the winner,
            if (winner == HUMAN) return -1;    //then if the winner is the computer, it returns 1. if the winner is the human,
            if (state.isFull()) return 0;     //it returns -1. if the board is full, it returns 0.
    
            if (isMaximizing) { //this has to be a boolean value since it is a minimax function.
                int bestScore = numeric_limits<int>::min();
                for (int move : state.getAvailableMoves()) { //getting the game state and the available moves. the vector has all the available moves.
                    GameState newState = state.makeMove(move, COMPUTER);
                    int score = minimax(newState, false); //this is the recursive call to the minimax function. it's going to throw it back to the recursive call.// then, it will check the base case. 
                    bestScore = max(bestScore, score); 
                }
                return bestScore;
            } else { //if we are not maximizing, then we are minimizing.
                int bestScore = numeric_limits<int>::max();
                for (int move : state.getAvailableMoves()) {
                    GameState newState = state.makeMove(move, HUMAN); //this is maximizing for the human.
                    int score = minimax(newState, true);
                    bestScore = min(bestScore, score);
                }
                return bestScore;
            }
        }
    
        int findBestMove(const GameState& state) { //sending the board to this function.
            int bestScore = numeric_limits<int>::min();
            int bestMove = -1;
    
            for (int move : state.getAvailableMoves()) {
                GameState newState = state.makeMove(move, COMPUTER);
                int score = minimax(newState, false);
                if (score > bestScore) {
                    bestScore = score;
                    bestMove = move;
                }
            }
            return bestMove;
        }
    };