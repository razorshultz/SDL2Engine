#ifndef SOUND_H
#define SOUND_H

#include <string>
#include <SDL_mixer.h>
#include <memory>



class Sound
{
	public:

		struct chunk_deleter { void operator()(Mix_Chunk* p) { if (p) Mix_FreeChunk(p); } }; 
		Sound();
		Sound(std::string filename);
		bool CanPlayAgain() const { return mCanPlayAgain; };
		auto GetChunk() { return mChunk.get(); };
		


	private:
		std::unique_ptr<Mix_Chunk, chunk_deleter> mChunk;
		bool mCanPlayAgain;

};

#endif
