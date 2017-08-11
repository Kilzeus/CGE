#pragma once
//#include<Python.h>
#include"Core.h"
#include"VertexElement.h"
#include"D3D11Core.h"
#include"W32RenderWindow.h"
#include"D3D11RenderContext.h"
#include"W32Pump.h"
#include<boost/python.hpp>
using namespace boost::python;

BOOL APIENTRY DllMain( HANDLE hModule, DWORD ul_reason_for_call, LPVOID)
{	 
   //Renderer::D3D11Core::handle = (HINSTANCE)hModule;
   return TRUE;
}


class CoreWrap : public Renderer::Core,public wrapper<Renderer::Core>
{
	Renderer::RenderWindow* createRenderWindow(
		Renderer::Uint2 resolution, MessagePump::Pump* pump
	)
	{
		return this->get_override("createRenderWindow")(resolution,pump);
	}
	Renderer::Device* createDevice(
		Renderer::RenderWindow* renderWindow,const Renderer::DeviceProperties& properties
	)
	{
		return this->get_override("createDevice")(renderWindow,properties);
	}
};


class RenderContextWrap : public Renderer::RenderContext,public wrapper<Renderer::RenderContext>
{
	void setRenderTarget(Renderer::RenderTargetView* renderTarget)
	{
		this->get_override("setRenderTarget")(renderTarget);
	}
	//states
	void enableDepthTesting(bool state)
	{
		this->get_override("enableDepthTesting")(state);
	}
	void enableBackfaceCulling(bool state)
	{
		this->get_override("enableBackfaceCulling")(state);
	}
	void setAlphaBlendingState(Renderer::AlphaBlendingState state)
	{
		this->get_override("setAlphaBlendingState")(state);
	}
	void setPrimitiveTopology(Renderer::PrimitiveTopology state)
	{
		this->get_override("setPrimitiveTopology")(state);
	}
	//rendering
	void renderBegin()
	{
		this->get_override("renderBegin")();
	}
	void renderEnd()
	{
		this->get_override("renderEnd")();
	}
	void setGPUBuffer(UINT slot,Renderer::GPUBuffer* buffer)
	{
		this->get_override("setGPUBuffer")(slot,buffer);
	}
	void setVertexBuffer(Renderer::VertexBuffer* buffer)
	{
		this->get_override("setVertexBuffer")(buffer);
	}
	void setIndexBuffer(Renderer::IndexBuffer* buffer)
	{
		this->get_override("setIndexBuffer")(buffer);
	}
	void setInstanceBuffer(Renderer::InstanceBuffer* buffer)
	{
		this->get_override("setInstanceBuffer")(buffer);
	}
	void setVertexShader(Renderer::VertexShader* shader)
	{
		this->get_override("setVertexShader")(shader);
	}
	void setFragmentShader(Renderer::FragmentShader* shader)
	{
		this->get_override("setFragmentShader")(shader);
	}
	void setGeometryShader(Renderer::GeometryShader* shader)
	{
		this->get_override("setGeometryShader")(shader);
	}
	void setVertexFormat(Renderer::VertexFormat* format)
	{
		this->get_override("setVertexFormat")(format);
	}
	void draw()
	{
		this->get_override("draw")();
	}
	void drawIndexed()
	{
		this->get_override("drawIndexed")();
	}
	void drawInstanced()
	{
		this->get_override("drawInstanced")();
	}
	void drawIndexedInstanced()
	{
		this->get_override("drawIndexedInstanced")();
	}
	void setRenderTargets(Renderer::RenderTargetView** renderTarget,UINT RenderTargetCount)
	{
		this->get_override("setRenderTargets")(renderTarget,RenderTargetCount);
	}
	void setRenderTargetClearColor(float colors[4])
	{
		this->get_override("setRenderTargetClearColor")(colors);
	}
	void setRenderTargetClearColors(float** colors,UINT numColors)
	{
		this->get_override("setRenderTargetClearColors")(colors,numColors);
	}
	void setTexture(UINT slot,Renderer::Texture* texture)
	{
		this->get_override("setTexture")(slot,texture);
	}
};


class DeviceWrap : public Renderer::Device,public wrapper<Renderer::Device>
{
	Renderer::IndexBuffer* createIndexBuffer(UINT byteSize,Renderer::IndexDataFormat format)
	{
		return this->get_override("createIndexBuffer")(format);
	}
	Renderer::VertexBuffer* crateVertexBuffer(UINT byteSize,bool dynamic=false)
	{
		return this->get_override("crateVertexBuffer")(byteSize,dynamic);
	}
	Renderer::Texture* createTexture(Resource* resource,Renderer::Uint2 dimensions,
		Renderer::TextureFormat format,UINT arraySize,bool renderTarget=false)
	{
		return this->get_override("createTexture")(resource,dimensions,format,arraySize,renderTarget);
	}
	Renderer::RenderTargetView* createRenderTarget(Renderer::Texture* resource)
	{
		return this->get_override("createRenderTarget")(resource);
	}
	Renderer::VertexShader* createVertexShader(Resource* resource,Renderer::VertexFormat* format)
	{
		return this->get_override("createVertexShader")(resource,format);
	}
	Renderer::FragmentShader* createFragmentShader(Resource* resource)
	{
		return this->get_override("createFragmentShader")(resource);
	}
	Renderer::GeometryShader* createGeometryShader(Resource* resource)
	{
		return this->get_override("createGeometryShader")(resource);
	}
	Renderer::RenderContext* getRenderContext()
	{
		return this->get_override("getRenderContext")();
	}
	Renderer::GPUBuffer* createGPUBuffer(UINT byteSize)
	{
		return this->get_override("createGPUBuffer")(byteSize);
	}
	Resource* compileShaderFromFile(const std::wstring& filename,std::string shaderProfile)
	{
		return this->get_override("compileShaderFromFile")(filename,shaderProfile);
	}
	Renderer::VertexFormat* createVertexFormat()
	{
		return this->get_override("createVertexFormat")();
	}
	Renderer::RenderTargetView* getBackBuffer()
	{
		return this->get_override("getBackBuffer")();
	}
};

class MessagePumpWrap : public MessagePump::Pump, public wrapper<MessagePump::Pump>
{
	void process()
	{
		this->get_override("process")();
	}
};


class RenderWindowWrap 
: public Renderer::RenderWindow,public wrapper<Renderer::RenderWindow>
{
	void open()
	{
		this->get_override("open")();
	}
	void close()
	{
		this->get_override("close")();
	}
};


BOOST_PYTHON_MODULE(PythonRenderer)
{

	class_<Renderer::DeviceProperties>("DeviceProperties")
		.def_readwrite("fullScreen", &Renderer::DeviceProperties::fullScreen)
		.def_readwrite("vSync", &Renderer::DeviceProperties::vSync)
		.def_readwrite("resolution", &Renderer::DeviceProperties::resolution)
		.def_readwrite("window", &Renderer::DeviceProperties::window),

	class_<Renderer::Uint2>("Uint2")
		.def_readwrite("x", &Renderer::Uint2::x)
		.def_readwrite("y", &Renderer::Uint2::y);

	//class_<Renderer::Core,boost::noncopyable>("Abstract", no_init);
	//Core
	class_<CoreWrap, boost::noncopyable>("CoreWrap")
		.def("createRenderWindow", pure_virtual(&Renderer::Core::createRenderWindow),
			return_value_policy<manage_new_object>())
		.def("createDevice", pure_virtual(&Renderer::Core::createDevice),
			return_value_policy<manage_new_object>());

    class_<Renderer::D3D11Core,bases<Renderer::Core>>("D3D11Core")
        .def("createRenderWindow",&Renderer::D3D11Core::createRenderWindow,
			return_value_policy<manage_new_object>())
        .def("createDevice",&Renderer::D3D11Core::createDevice,
			return_value_policy<manage_new_object>());

	//class_<Renderer::RenderWindow,boost::noncopyable>("AbstractRenderWindow", no_init);
	//RenderWindow
	class_<RenderWindowWrap, boost::noncopyable>("RenderWindowWrap")
		.def("open", pure_virtual(&Renderer::RenderWindow::open))
		.def("close", pure_virtual(&Renderer::RenderWindow::close));

	class_<Renderer::W32RenderWindow,bases<Renderer::RenderWindow>>("W32RenderWindow",no_init)
        .def("open",&Renderer::RenderWindow::open)
        .def("close",&Renderer::RenderWindow::close);

	//MessagePump
	class_<MessagePumpWrap,boost::noncopyable>("MessagePumpWrap")
		.def("process",pure_virtual(&MessagePump::Pump::process));

	class_<MessagePump::W32Pump,bases<MessagePump::Pump>>("W32Pump")
		.def("process",&MessagePump::Pump::process);

	//Device
	class_<DeviceWrap, boost::noncopyable>("DeviceWrap")
		.def("crateVertexBuffer", pure_virtual(&Renderer::Device::crateVertexBuffer),
			return_value_policy<manage_new_object>())
		.def("createGeometryShader", pure_virtual(&Renderer::Device::createGeometryShader),
			return_value_policy<manage_new_object>())
		.def("createGPUBuffer", pure_virtual(&Renderer::Device::createGPUBuffer),
			return_value_policy<manage_new_object>())
		.def("createIndexBuffer", pure_virtual(&Renderer::Device::createIndexBuffer),
			return_value_policy<manage_new_object>())
		.def("createRenderTarget", pure_virtual(&Renderer::Device::createRenderTarget),
			return_value_policy<manage_new_object>())
		.def("createTexture", pure_virtual(&Renderer::Device::createTexture),
			return_value_policy<manage_new_object>())
		.def("createVertexShader", pure_virtual(&Renderer::Device::createVertexShader),
			return_value_policy<manage_new_object>())
		.def("getRenderContext", pure_virtual(&Renderer::Device::getRenderContext),
			return_value_policy<manage_new_object>())
		.def("createFragmentShader", pure_virtual(&Renderer::Device::createFragmentShader),
			return_value_policy<manage_new_object>());

	class_<Renderer::D3D11Device,bases<Renderer::Device>>("D3D11Device",no_init)
        .def("crateVertexBuffer",&Renderer::Device::crateVertexBuffer,
			return_value_policy<manage_new_object>())
		.def("createGeometryShader",&Renderer::Device::createGeometryShader,
			return_value_policy<manage_new_object>())
		.def("createGPUBuffer",&Renderer::Device::createGPUBuffer,
			return_value_policy<manage_new_object>())
		.def("createIndexBuffer",&Renderer::Device::createIndexBuffer,
			return_value_policy<manage_new_object>())
		.def("createRenderTarget",&Renderer::Device::createRenderTarget,
			return_value_policy<manage_new_object>())
		.def("createTexture",&Renderer::Device::createTexture,
			return_value_policy<manage_new_object>())
		.def("createVertexShader",&Renderer::Device::createVertexShader,
			return_value_policy<manage_new_object>())
		.def("getRenderContext",&Renderer::Device::getRenderContext,
			return_value_policy<manage_new_object>())
		.def("createFragmentShader",&Renderer::Device::createFragmentShader,
			return_value_policy<manage_new_object>());

	//RenderContext
	class_<RenderContextWrap, boost::noncopyable>("RenderContextWrap")
		.def("draw", pure_virtual(&Renderer::RenderContext::draw),
			return_value_policy<manage_new_object>())
		.def("drawindexedInstanced", pure_virtual(&Renderer::RenderContext::drawIndexedInstanced),
			return_value_policy<manage_new_object>())
		.def("drawInstanced", pure_virtual(&Renderer::RenderContext::drawInstanced),
			return_value_policy<manage_new_object>())
		.def("enableBackfaceCulling", pure_virtual(&Renderer::RenderContext::enableBackfaceCulling),
			return_value_policy<manage_new_object>())
		.def("enableDepthTesting", pure_virtual(&Renderer::RenderContext::enableDepthTesting),
			return_value_policy<manage_new_object>())
		.def("renderBegin", pure_virtual(&Renderer::RenderContext::renderBegin),
			return_value_policy<manage_new_object>())
		.def("renderEnd", pure_virtual(&Renderer::RenderContext::renderEnd),
			return_value_policy<manage_new_object>())
		.def("setAlphaBlendingState", pure_virtual(&Renderer::RenderContext::setAlphaBlendingState),
			return_value_policy<manage_new_object>())
		.def("setFragmentShader", pure_virtual(&Renderer::RenderContext::setFragmentShader),
			return_value_policy<manage_new_object>())
		.def("setGeometryShader", pure_virtual(&Renderer::RenderContext::setGeometryShader),
			return_value_policy<manage_new_object>())
		.def("setGPUBuffer", pure_virtual(&Renderer::RenderContext::setGPUBuffer),
			return_value_policy<manage_new_object>())
		.def("setIndexBuffer", pure_virtual(&Renderer::RenderContext::setIndexBuffer),
			return_value_policy<manage_new_object>())
		.def("setInstanceBuffer", pure_virtual(&Renderer::RenderContext::setInstanceBuffer),
			return_value_policy<manage_new_object>())
		.def("setPrimitiveTopology", pure_virtual(&Renderer::RenderContext::setPrimitiveTopology),
			return_value_policy<manage_new_object>())
		.def("setRenderTarget", pure_virtual(&Renderer::RenderContext::setRenderTargets),
			return_value_policy<manage_new_object>())
		.def("setVertexBuffer", pure_virtual(&Renderer::RenderContext::setVertexBuffer),
			return_value_policy<manage_new_object>())
		.def("setVertexFormat", pure_virtual(&Renderer::RenderContext::setVertexFormat),
			return_value_policy<manage_new_object>())
		.def("drawIndexed", pure_virtual(&Renderer::RenderContext::drawIndexed),
			return_value_policy<manage_new_object>());

	class_<Renderer::D3D11RenderContext,bases<Renderer::Core>>("D3D11RenderContext",no_init)
		.def("draw",&Renderer::RenderContext::draw,
			return_value_policy<manage_new_object>())
		.def("drawindexedInstanced",&Renderer::RenderContext::drawIndexedInstanced,
			return_value_policy<manage_new_object>())
		.def("drawInstanced",&Renderer::RenderContext::drawInstanced,
			return_value_policy<manage_new_object>())
		.def("enableBackfaceCulling",&Renderer::RenderContext::enableBackfaceCulling,
			return_value_policy<manage_new_object>())
		.def("enableDepthTesting",&Renderer::RenderContext::enableDepthTesting,
			return_value_policy<manage_new_object>())
		.def("renderBegin",&Renderer::RenderContext::renderBegin,
			return_value_policy<manage_new_object>())
		.def("renderEnd",&Renderer::RenderContext::renderEnd,
			return_value_policy<manage_new_object>())
		.def("setAlphaBlendingState",&Renderer::RenderContext::setAlphaBlendingState,
			return_value_policy<manage_new_object>())
		.def("setFragmentShader",&Renderer::RenderContext::setFragmentShader,
			return_value_policy<manage_new_object>())
		.def("setGeometryShader",&Renderer::RenderContext::setGeometryShader,
			return_value_policy<manage_new_object>())
		.def("setGPUBuffer",&Renderer::RenderContext::setGPUBuffer,
			return_value_policy<manage_new_object>())
		.def("setIndexBuffer",&Renderer::RenderContext::setIndexBuffer,
			return_value_policy<manage_new_object>())
		.def("setInstanceBuffer",&Renderer::RenderContext::setInstanceBuffer,
			return_value_policy<manage_new_object>())
		.def("setPrimitiveTopology",&Renderer::RenderContext::setPrimitiveTopology,
			return_value_policy<manage_new_object>())
		.def("setRenderTarget",&Renderer::RenderContext::setRenderTarget,
			return_value_policy<manage_new_object>())
		.def("setVertexBuffer",&Renderer::RenderContext::setVertexBuffer,
			return_value_policy<manage_new_object>())
		.def("setVertexFormat",&Renderer::RenderContext::setVertexFormat,
			return_value_policy<manage_new_object>())
		.def("drawIndexed",&Renderer::RenderContext::drawIndexed,
			return_value_policy<manage_new_object>());

}