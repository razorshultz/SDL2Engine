# SDL2Engine
A game engine made using the SDL2 library

This is a game engine I'm working on in my spare time written using C++ and SDL2, a wrapper library for OpenGL. SDL2 provides a window context and methods for drawing, handling input, processing events, and audio. 

The engine is Object-Oriented, and currently implemented features include texture resource management via the use of a static unordered map, which is shown in Texture.h. There is also a simple physics-based movement system utilising acceleration, velocity, and position, to give a fine degree of control over how weighty the character feels. There are sound chunks which play in a given sound channel, which are implemented using SDL2's SDL_Mixer functionality. 

The engine works by using the Game class (shown in Game.h), to process events such as mouse clicks and keyboard inputs, and then the Update method adjusts the game based on these, performing tasks such as responding to clicks or movement input or changing the internal state of a Player object. The Draw()
