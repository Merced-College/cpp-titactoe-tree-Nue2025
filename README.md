[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=19079057)
# cpp_tictactoe_tree
Part 1: Exploration and Explanation
What is the purpose of the minimax function?
The purpose of the minimax function is thinking ahead through programming. It is a recursive algorithm that looks through the events that follow to find the most optimal move, assuming that they play strategically. The computer maximizes the score by uing its recurive algorithm. The player tries to win the game.

How does the GameState class represent the tree?
The GameState class represents nodes in the decision tree of the game. Each GameState object stores the current state of the board. It creates all the possible moves through getAvailableMove(). The structure is where each node is a board, each child node in the program is a possible move, and the root node is the board state it is currently in. Through this, it will explore the possible outcome to "maximize" the win.

When does the recursion stop in the minimax algorithm?
Recursion stops when the winner is either the HUMAN, COMPUTER, or if the base is full. It will check these statements first. If none apply, then it calls the function for each new move. It traverses throughout the entire tree looking at the leaf nodes. 

Part 2: Modify the Code
Added "Play Again?" functionality, tracked the recursion calls/moves, and created who plays first.

Part 3: Reflection
What did you learn about recursion and trees?
I learned a lot about recursion. I think recursion is a great way to find possible scenarios in small tree cases. Tree's help find a way to the leaf node and help explain this to us. 

Was the AI “smart”? What were its limitations?
I don't think the AI was smart. It was given all the possible chances to winning the game. Since it only has 8 win scenarios, it is easy to give the AI all 8 solutions. 
If the programmer gave the AI one less solution, the player will have a chance of winning if the AI doesn't know the win scenario.

If you had more time, how would you improve it?
I would try making it less difficult or give the AI levels. I would make an easy mode, which doesn't use much recursion and maybe a few case scenarios. Another mode would be medium difficulty, where the computer can do cases but on a 50% chance. Lastly, I would keep how it is now, hard/impossible difficulty. 