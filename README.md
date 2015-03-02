# SoliPort
This began as a quick and dirty attempt to modify my game Soliton to use the SFML graphics library instead of the command terminal. However, I want to move on, so this is now the official version of Soliton that will be released.

Its web site is: https://sites.google.com/site/solitongame

Binaries will be available soon for Windows, OS-X, and Linux.

# Level Creation
https://sites.google.com/site/solitongame/home/level-creation

Level creation in Soliton is simple! Just open up your favorite text editor, and start placing characters to shape out your level. Here is what each character means:

\+ - | are wall tiles. Players and enemies cannot walk on these tiles, so use them to shape your level.

. are floor tiles. Players and enemies CAN walk on floor tiles. This is where the action happens in the level.

Spaces are empty space. They signify the outside of the level.

E is the end of level tile. This signifies where the player needs to go to win the level.

@ is the player start tile. This signifies where the player starts the level.

< v > ^ are enemy start tiles. These signify where enemies will start in the level, and which direction they face. The open end is where they are facing.

$ is the end of map tile. This signifies where your level file stops mapping out the level and starts loading in the enemy paths. There should only be enemy path codes after it.

The enemies are numbered from left to right, up to down. Enemies can be given paths by using the # character, and paths by typing pairs of characters separated by spaces. 'm' means move one space, 'l' means look without moving. 'r' 'u' 'l' and 'd' mean right, up, left, and down respectively. They move once per turn, and once they reach the end of their path, they start over from the beginning.

# Credits
Joshua Trahan (josht0288@gmail.com) - Programming, game design, level design

Morgan Larson - Level 3 design

Player, enemy, and enemy corpse sprites are from SpriteLib. Special thanks to everybody who has worked on that project!
