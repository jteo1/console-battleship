# console-based battleship

# Usage
An already built version of the executable is provided by default in this repository. To compile a new version of the project,
simply use "make" in the appropriate directory and ./battleship to run. Certain lines in Computer.cpp can be uncommented to
describe the advanced AI's thought process.

# Gameplay
The game is played on a 10x10 board, using numeric characters along the columns and alphabetic characters along the rows.
The player and computer each get the standard five ships: a 5-length ship, a 4-length ship, two 3-length ships, and a 2-length
ship. Since the game is written as console output, console inputs are used to interact with the board and the computer. When 
the console asks for the  input specifying CPU level, you may append the character 'a' to view the computer's hidden board and
see it's ship placement (for example, input 0a and 1a are valid). Other basic instructions on interacting with the console are
given during the game.

Specific characters are used to indicate the status of each coordinate on the board:<br>
'.': coordinate that has not yet been fired at<br>
'x': coordinate that has struck a ship<br>
'~': coordinate that missed<br>

On your own board, the characters '1', '2', '3', '4', and '5' correspond to the placement of your ships, where '1' is the 
2-length ship, '2' and '3' are the 3-length ships, '4' is the 4-length ship, and '5' is the 5-length ship.

During gameplay, it is recommended that you extend the console screen downwards so that you can see all the appropriate 
console output on each turn without having to scroll up to see it.

# Rules
The rules implemented are consistent with the standard game of battleship. The goal of the game is to sink all of the 
opponent's ships by guessing coordinates on their board. The console will keep track of your misses and hits for you. When
a ship is sunk, the computer will notify you of which length ship was sunk.

#Final notes on the AI
This section will describe the capabilities and limitations of the advanced AI that was implemented in this version.
The AI begins by guessing randomly (without re-guessing the same coordinate) until a hit occurs. Then as a human would,
the AI begins to investigate the surrounding area, or more particularly the x and y-axes along this point. Therefore, it 
starts to guess coordinates along each axis until a ship is sunk or there are no more surrounding coordinates to guess
(which may happen due to board boundaries or other coordinates that have already been hit/missed). After this, it continues
to guess randomly and repeat the process. 

While this process is quite effective for most typical human ship placements, there are some complex cases that the AI
is unable to resolve the same way a human would. More specifically, if ships are grouped together contiguously, the AI
will still conduct guesses along the x and y-axes of the initial hit, but would be unable to comprehend a higher level of
spatial awareness that would allow it to deduce where the rest of a ship is. As an example case:
<pre>
Player Board:
  0 1 2 3 4 5 6 7 8 9 
A . ~ . . . . . . . . 
B . ~ . . . . . . ~ . 
C . . . ~ . . ~ . . . 
D . . . x x x x ~ ~ . 
E . . . x 5 x x 5 . ~ 
F . . x x 2 x x ~ . . 
G . . . x x x ~ . . . 
H . . ~ ~ . ~ ~ . . . 
I . . . . . . . ~ . . 
J . . . . . . . ~ ~ . 
</pre>

In this case, the AI might hit E7. However, it wouldn't deduce that the rest of the 5-length ship must be somewhere along
the x-axis since all the surrounding coordinates are already shot at or empty.

In general, the AI has a few shortcomings, but still performs quite well in a majority of player ship configurations.
