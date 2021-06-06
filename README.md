# MiniginQBert - Vincent Van Zele
Working on a Game Engine using Minigin. Trying to implement QBert. 

Engine:

Entity-component system
	  Scenes hold gameobjects with possible Components.

Input Manager: can handle input from keyboard and up to 4 controllers.
	  But the game runs with 1 Xinput controller and with a keyboard.

-------------------------------------------------------------------------------------
Uses different kinds of programming patterns: 
    Service Locator, Components, Game Loop, BitFlag, Update method, Commands, Event Queue, Observers, Singleton

- Components affect logic - gameplay - graphics...

- A Service locator can locate different services: 
	  Audio, GameTime, Renderer, SceneManager ResourceManager, InputManager & Windows Info. 

- Game Loop creates the main loop of the game.

- Bit Flag set a flag that tells the function something needs attention.

- Update Method is a addition to Game Loop, updating a collection of objects.

- Commands uses input and specific funtions to execute upon pressing the inputs.

- Event Queue was mainly used with Audio to add multiple specific sounds in a queue on a different thread.

- Oberservers where used to get the Score / Lives and Changed Tiles.

-------------------------------------------------------------------------------------

Uses smart pointers & raw pointers:
    smart pointers are used to englobe everything that needs memory management.
    And the main objects are smart pointers, the children don't need to pay that much attention (even to raw pointers).

Uses SDL2.
Uses SDL mixer.
Uses SDL image.
Uses SDL ttf.
Uses ImGui.
Uses VLD.

-------------------------------------------------------------------------------------
Game:

Players:
	  Can be either P1 or P2 (using respectively Controller and Keyboard input) they navigate the world and change the states of the tiles.
Enemies:
	  Can either be Eggs or Coily.
	  Eggs fall from the top of the screen onto the world and fall down the pyramid killing any player in its way.
	  Coily wanders the world (no efficient AI) killing any player in its way.
WorldGrid:
	  Pyramid with it's outer layer of tiles set to a deathplane.
	  Has 2 Disk tiles that will teleport the player to it's initial Tile spawn.

-------------------------------------------------------------------------------------

GitHub link: https://github.com/VincentVanZele/MiniginQBert 
