An advanced AI engine for Connect-K game which follows all the rules of the game similar to Connect-4 with additional features. Implemented Min-Max algorithm (gamestrategy) with alpha-beta pruning algorithm, iterative deepening search in order to achieve a depth of 7 within 5 seconds. The agent was ranked among top 10% of all the AI designed during the course.

Steps to build and run :

ConnectK.cpp has main function to get a current state from the java shell. AI agent is implemented in AIShell::makeMove(). AIShell::gameState has the current game state as array of integers. 0, 1 and -1 represent empty, AI piece and human piece respectively. 

Then compile your code and make an executable file (for example on Windows, myAI.exe). On Linux, open a terminal and type

g++ ConnectK.cpp Move.cpp AIShell.cpp -o myAI

Then you can test your AI agent by running ConnectK.jar with the following command. 

On Windows:
java -jar ConnectK.jar cpp:myAI.exe

On Linux:
java -jar ConnectK.jar cpp:myAI
