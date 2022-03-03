# Artificial-Intelligence-BattleGround-PlayerBot

The task for the playerBot and rules of the game:

It was a foggy and quiet night we hadn't seen in months.
Shipwrecks, planks and remnants of ship's equipment could be seen for miles away from the scene of the clash. After a battle that will be remembered as the biggest pirate skirmish in history, the turbulent sea has finally returned to balance.
Captain Vukobradi used to be the scariest pirate in the Stormy Sea. He had the largest and fastest ship, with the strongest, most ruthless crew. The treasure he stole after the fateful battle was invaluable.
The battle is over, but at what cost?
The fleet on both sides was blown to pieces.
In addition to the many lives lost, the Captain knew that he did not have much time left before the next battle. As soon as word of his weakened crew spread, other pirate captains would seize the opportunity. The desire not to lose his reputation, respect and his treasure pushed him into a corner. He had to act fast.
Pirate voyages were full of dangers, both from the open sea and from wild, mysterious creatures that need to be dealt with. After so many years on the high seas, the Captain knew the sea like a little finger. He knew exactly where and in what way to bury the treasure so that it would not be found, which he did.
Then ... several small waves lapped the Captain's ship. That was it!
When a storm strikes, every captain will become greedy and eager for destruction, which is an ideal time to attack.
Any rival ship can easily sneak up on you in these unfavorable conditions.
Help your crew find lost treasure and become the most notorious fleet on the high seas.

AI Battleground 2021 is a TBS (Turn Based Strategy) game in which four artificial intelligences take on the role and powers of an avatar to fight for victory. The moves take place in order, from the first to the fourth player.
You are on a sea of **hexagonal shape**, 29 diagonals long, and you can't get out of it. The map is of **constant size**. The game can last a maximum of **5000** moves, ie. 1250 moves per player.
Gold coins (points) can be won in several ways. At all times, there is a flag on the map. The player who reaches her first wins the flag, as well as the gold coins she hides. In addition, the player can win gold by eliminating opponents or NPCs (Non-Playable Characters).
The task is to create a computer program that will play the game as one of the pirate ships, as intelligently as possible, by sending requests to the server and obtaining server responses in JSON format.

Maps are generated depending on the round of the competition. The closer you get to the finals, the harder the map gets. The map is fair to all players.


![alt text](https://github.com/Una865/Artificial-Intelligence-BattleGround-Bot/blob/main/Map.png)

## Fields:
**1.Normal:**
here players can move. However, vortex-shaped obstacle can also be found in the field, as well as pirates.
**2.Island**
there is an island in this field. The islands are impassable. There may be a shop or a flag on the island.

The map is generated based on the JSON sent by the server. The following are examples of fields that can be found on the map. If the field is normal, a vortex or nothing can be found on it. In each field on the map you can find:
- boat (avatar or NPC)
- shop
- islandflag
- vortex

**Player number one starts the game with coordinates (-7, -7.14), player number two with coordinates (14, -7, -7), player number three with coordinates (7.7, -14) and player number four with coordinates (-14,7,7).
At the beginning of the game, two NPCs are also created on the map. They circle a fixed radius from the center of the map until they see one of the players, after which they start chasing them. If a player manages to escape them, they return to their course by the shortest route.**

## Coordinate system

The map uses an offset coordinate system based on offsets from the main diagonals. The three coordinates that are tracked are:
- q : marks the offset from the main diagonal;
- r : marks the offset from the midline;
- s : marks the offset from the side diagonal;
**An important feature of this coordinate system is always valid q + r + s = 0**
 


 
