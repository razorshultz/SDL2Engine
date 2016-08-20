# SDL2Engine
A game engine made using the SDL2 library

This is a game engine I'm working on in my spare time written using C++ and SDL2, a wrapper library for OpenGL. SDL2 provides a window context, and methods for drawing, processing events, and audio. 

The engine is Object-Oriented, and currently implemented features include texture resource management via the use of a static unordered map, which is shown in Texture.h. This ensures no resources are unnecessarily loaded multiple times. There is also a physics-based movement system utilising acceleration, velocity, and position, to give a fine degree of control over how weighty the character feels. There are sound chunks which play in a given sound channel, which are implemented using SDL2's SDL_Mixer functionality, shown in Sound.h. 

The engine works by using the Game class (shown in Game.h), to process events such as mouse clicks and keyboard inputs, and then the Update method adjusts the game based on these, performing tasks such as responding to clicks or movement input or changing the internal state of a Player object. The Render() method then presents the updated gtame state to the client area of the window.

Any visible entities inherit from Entity.h, and using polymorphism, the game class simply loops through a vector of entities to update the logic and render the game. The main derived entity is currently the Player class, shown in Player.h.

