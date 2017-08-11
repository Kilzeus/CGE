#pragma once
#include"Types.h"
namespace Renderer
{
	class RenderWindow
	{
		Uint2 dimensions;
		Uint2 position;
		bool fullScreen;
	public:
		RenderWindow();
		RenderWindow(const Uint2& position,const Uint2& dimensions);
		void setDimenstions(const Uint2& dimensions);
		const Uint2& getDimensions();
		//virtual void enableFullScreen(bool enable);
		bool isFullScreen() const;
		virtual void open()=0;
		virtual void close()=0;
	};
}
