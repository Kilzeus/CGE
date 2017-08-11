#include"D3D11Core.h"
#include"W32RenderWindow.h"
#include"W32Pump.h"

using namespace Renderer;
D3D11Core::D3D11Core()
:device(0)
{
}


D3D11Core::~D3D11Core()
{

}


RenderWindow* D3D11Core::createRenderWindow(
	Uint2 resolution,MessagePump::Pump* pump
)
{
	HWND windowHandle;
	WNDCLASSEX windowClassDesc;
	ZeroMemory(&windowClassDesc,sizeof(WNDCLASSEX));

	std::string windowClassName = "game window class";
	std::string windowName = "game window";
	HINSTANCE hInstance = GetModuleHandle(NULL);

	windowClassDesc.lpfnWndProc = (WNDPROC)MessagePump::W32Pump::windowProcedure;
	windowClassDesc.cbSize = sizeof(WNDCLASSEX);
	windowClassDesc.style = CS_VREDRAW | CS_HREDRAW;
	windowClassDesc.cbWndExtra = DLGWINDOWEXTRA;
	windowClassDesc.cbClsExtra = 0;
    windowClassDesc.hIcon = ExtractIcon(hInstance,"Test.ico",0);		//"Test.ico";
	windowClassDesc.hCursor = LoadCursorFromFile ( "Cursor1.cur" );
	windowClassDesc.lpszClassName = windowClassName.c_str();
	windowClassDesc.hbrBackground = GetSysColorBrush(COLOR_BTNFACE);
	windowClassDesc.hInstance = hInstance;

	RegisterClassEx(&windowClassDesc);

	windowHandle = CreateWindowEx(
		0,windowClassName.c_str(),windowName.c_str(),WS_POPUP,
		0,0,resolution.x,resolution.y,0,0,hInstance,0
	);
	W32RenderWindow* window = new W32RenderWindow(windowHandle);
	return window;
}


Device* D3D11Core::createDevice(RenderWindow* renderWindow,const DeviceProperties& properties)
{
	if(!device) 
	{
		ID3D11Device* iDevice = 0;
		IDXGIFactory1* iDXGIFactory = 0;
		IDXGIAdapter1* iDXGIAdapter = 0;
		IDXGIOutput* iDXGIOutput = 0;
		UINT numModes = 0;
		DXGI_MODE_DESC* displayModes = 0;
		IDXGISwapChain* swapChain = 0;
		ID3D11DeviceContext* deviceContext = 0;

		DXGI_SWAP_CHAIN_DESC desc;
		ZeroMemory(&desc,sizeof(DXGI_SWAP_CHAIN_DESC));

		HRESULT hresult = CreateDXGIFactory1(__uuidof(IDXGIFactory1),(void**)&iDXGIFactory);
		hresult = iDXGIFactory->EnumAdapters1(0,&iDXGIAdapter);
		hresult = iDXGIAdapter->EnumOutputs(0,&iDXGIOutput);
		hresult = iDXGIOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, 
			DXGI_ENUM_MODES_INTERLACED, &numModes, 0);

		displayModes = new DXGI_MODE_DESC[numModes];
		hresult = iDXGIOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, 
			DXGI_ENUM_MODES_INTERLACED, &numModes, displayModes);

		// fill swap chain description with proper settings
		if(properties.vSync)
		{
			for(int i=0;i<numModes;i++)
			{
				if(displayModes[i].Width == properties.resolution.x)
				{
					if(displayModes[i].Height == properties.resolution.y)
					{
						desc.BufferDesc.RefreshRate.Numerator =
							 displayModes[i].RefreshRate.Numerator;
						desc.BufferDesc.RefreshRate.Denominator = 
							displayModes[i].RefreshRate.Denominator;
					}
				}
			}
		}
		else
		{
			desc.BufferDesc.RefreshRate.Numerator = 0;
			desc.BufferDesc.RefreshRate.Denominator = 1;
		}
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.Windowed = !properties.fullScreen;
		desc.BufferCount = 1;
		desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BufferDesc.Width = properties.resolution.x;
		desc.BufferDesc.Height = properties.resolution.y;
		desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		desc.OutputWindow = ((W32RenderWindow*)properties.window)->getWindowHandle();
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;

		D3D_FEATURE_LEVEL featureLevel;

#ifdef DEBUG
		hresult = D3D11CreateDeviceAndSwapChain(
			0,D3D_DRIVER_TYPE_HARDWARE,0,D3D11_CREATE_DEVICE_DEBUG,
			0,0,D3D11_SDK_VERSION,&desc,&swapChain,&iDevice,&featureLevel,&deviceContext
		);
#endif
#ifndef DEBUG
		hresult = D3D11CreateDeviceAndSwapChain(
			0,D3D_DRIVER_TYPE_HARDWARE,0,0,
			0,0,D3D11_SDK_VERSION,&desc,&swapChain,&iDevice,&featureLevel,&deviceContext
		);
#endif
		//depth stencil creation
		ID3D11Texture2D* depthTexture = 0;
		D3D11_TEXTURE2D_DESC texDesc;
		ZeroMemory(&texDesc,sizeof(D3D11_TEXTURE2D_DESC));
		texDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		texDesc.Width = properties.resolution.x;
		texDesc.Height = properties.resolution.y;
		texDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		texDesc.ArraySize = 1;
		texDesc.MipLevels = 1;
		texDesc.SampleDesc.Count = 1;

		hresult = iDevice->CreateTexture2D(&texDesc,0,&depthTexture);

		D3D11_DEPTH_STENCIL_VIEW_DESC depthDesc;
		ZeroMemory(&depthDesc,sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
		depthDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		depthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

		ID3D11DepthStencilView* depthView = 0;
		hresult = iDevice->CreateDepthStencilView(
			depthTexture,&depthDesc,&depthView
		);
		depthTexture->Release();

		//get swapchain backbuffer
		ID3D11Texture2D* backBufferTexture = 0;
		ID3D11RenderTargetView* backBufferView = 0;
		swapChain->GetBuffer(0,__uuidof(ID3D11Texture2D),(LPVOID*)&backBufferTexture);
		hresult = iDevice->CreateRenderTargetView(backBufferTexture,0,&backBufferView);

		device = new D3D11Device(
			properties,iDevice,deviceContext,swapChain,featureLevel,depthView,backBufferView
		);
		device->createDefaultSampler();
		deviceContext->VSSetSamplers(1, 0, &device->defaultSamplerState);
		deviceContext->PSSetSamplers(1, 0, &device->defaultSamplerState);

		device->resolution.x = properties.resolution.x;
		device->resolution.y = properties.resolution.y;
	}
	return device;
}