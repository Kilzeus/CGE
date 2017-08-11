#pragma once
#include"TextureLoader.h"
#include<boost/python.hpp>
using namespace boost::python;

BOOST_PYTHON_MODULE(PythonAssets)
{

	class_<AssetSystem::TextureLoader>("TextureLoader",no_init)
		.def("loadTexture",&AssetSystem::TextureLoader::loadTexture,
			return_value_policy<manage_new_object>());
}