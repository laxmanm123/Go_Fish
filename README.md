# Go_Fish
Hello! Welcome to my rendition of 'Hey! That's my Fish!' 
created by Laxman Mohanarajan

This game is played on a 6x6 grid against an enemy AI, the goal being to
collect more fish than your opponent. The player with the higher score at the 
end wins! The game comes to an end when no more moves can be made.

P 1 1 1 1 1          The player and the AI start on opposite sides of the board, and can 
1 2 2 2 2 1          move in 8 directions, "UP", "DOWN", "LEFT", "RIGHT", "UPRIGHT", "UPLEFT",
1 2 3 3 3 1          "DOWNRIGHT", and "DOWNLEFT". The player also specifies how many tiles they
1 2 3 3 3 1          would like to move in that direction, as long as there is no empty tile
1 2 3 3 3 1          or enemyplayer in your way. The number on the tile represents the number of 
1 2 2 2 2 1          fish that will be added to your score if you move to that tile.
1 1 1 1 1 A 

Once the game has come to an end the winner as well as the final score, and the order in which the players
gained points, is printed out!
