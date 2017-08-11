#include "SoundCore.h"


using namespace Sound;
Core::Core()
{
	engine = irrklang::createIrrKlangDevice();
}


Core::~Core()
{
	engine->drop();
}


Source* Core::createSourceFromFile(std::string filename)
{
	irrklang::ISoundSource* sound = engine->addSoundSourceFromFile(filename.c_str());
	Source* source = new Source(sound);
	return source;
}


void Core::playSource(Source* source)
{
	source->sound->setDefaultVolume(1.f);
	engine->play2D(source->sound);
}


void Core::update()
{
	engine->update();
}
