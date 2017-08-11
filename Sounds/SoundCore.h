#pragma once
#include"Source.h"
#include<string>
namespace Sound
{
	class Core
	{
		irrklang::ISoundEngine* engine;
	public:
		Core();
		~Core();
		Source* createSourceFromFile(std::string filename);
		void playSource(Source* source);
		void update();
	};
}

