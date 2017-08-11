#pragma once
#include<irrKlang.h>
namespace Sound
{
	class Source
	{
		friend class Core;
		irrklang::ISoundSource* sound;
		Source(irrklang::ISoundSource* sound);
	public:
		~Source();
	};
}

