#include "CefManager.h"
#include "RenderProcessHandler.h"
CefManager* CefManager::_instance = nullptr;

CefManager::CefManager(){
	
}

CefManager::~CefManager(){

}

void CefManager::ShutdownBrowser(){
	if (_cefBrowser.get())
		_cefBrowser->GetHost()->CloseBrowser(false); // For extra safe measure?

	// and make everything a nullptr.
	_cefBrowser = nullptr;
	_browserClient = nullptr;
	_renderHandler = nullptr;
}

void CefManager::ShutdownCEF(){
	CefShutdown();
	delete _instance;
}

void CefManager::InitBrowser(int w, int h, std::string url){
	CefWindowInfo windowInfo;
	CefBrowserSettings browserSettings;
	windowInfo.SetAsWindowless(nullptr);
	browserSettings.windowless_frame_rate = 60;
	_renderHandler = new BrowserRenderHandler(w, h);
	_browserClient = new BrowserClient(_renderHandler);
	_cefBrowser = CefBrowserHost::CreateBrowserSync(windowInfo, _browserClient.get(), url, browserSettings, nullptr);
}

int CefManager::InitializeCEF(int argc, char** argv){
	CefRefPtr<CefCommandLine> commandLine = CefCommandLine::CreateCommandLine();
#ifdef _WIN32
	commandLine->InitFromString(GetCommandLineW());
#endif
#ifdef __linux__
		// TODO
#endif
	// check for the type of subprocess
	CefRefPtr<CefApp> app = nullptr;
	std::printf("%s\n", commandLine->GetCommandLineString());
	if (commandLine->HasSwitch("type")){
		std::string process_type = commandLine->GetSwitchValue("type");
		if (process_type == "renderer"){
			app = new RenderProcessApplication();
			std::printf("A render subprocess will be created\n");
			//MessageBox(NULL, "Render Subprocess", "RENDER", MB_ICONEXCLAMATION);
		}
	}

	int result = CefExecuteProcess(_mainArgs, app.get(), nullptr);
	printf("CEF Manager::Initialize::ExecuteSubProcess\n");
	if (result >= 0){
		return result;
	}

	printf("CEF Manager Initializing CEF\n");
	CefString(&_settings.resources_dir_path) = std::string(std::string(SDL_GetBasePath()) + std::string("CEF Resources"));
	CefInitialize(_mainArgs, _settings, nullptr, nullptr);

	return -1;
}