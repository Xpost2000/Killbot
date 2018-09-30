#include "BrowserClient.h"
#include "constants.h"
#include <fstream>

#include "Engine.h"

BrowserClient::BrowserClient(CefRefPtr<CefRenderHandler> renderHandler) : _renderHandler(renderHandler){

}
BrowserClient::~BrowserClient(){
	//_renderHandler = nullptr;
}

CefRefPtr<CefLifeSpanHandler> BrowserClient::GetLifeSpanHandler()
{
	return this;
}

CefRefPtr<CefLoadHandler> BrowserClient::GetLoadHandler()
{
	return this;
}

CefRefPtr<CefRenderHandler> BrowserClient::GetRenderHandler()
{
	return _renderHandler;
}

// CefLifeSpanHandler methods.
void BrowserClient::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
	// Must be executed on the UI thread.
	CEF_REQUIRE_UI_THREAD();

	browser_id = browser->GetIdentifier();
}

bool BrowserClient::DoClose(CefRefPtr<CefBrowser> browser)
{
	// Must be executed on the UI thread.
	CEF_REQUIRE_UI_THREAD();

	// Closing the main window requires special handling. See the DoClose()
	// documentation in the CEF header for a detailed description of this
	// process.
	if (browser->GetIdentifier() == browser_id)
	{
		// Set a flag to indicate that the window close should be allowed.
		closing = true;
	}

	// Allow the close. For windowed browsers this will result in the OS close
	// event being sent.
	return false;
}

void BrowserClient::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
}

void BrowserClient::OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode)
{
	loaded = true;
}

bool BrowserClient::OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefLoadHandler::ErrorCode errorCode, const CefString & failedUrl, CefString & errorText)
{
	loaded = true;
}

void BrowserClient::OnLoadingStateChange(CefRefPtr<CefBrowser> browser, bool isLoading, bool canGoBack, bool canGoForward)
{
}

void BrowserClient::OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame)
{
}

bool BrowserClient::closeAllowed() const
{
	if (closing) { std::printf("Closing Allowed!\n"); }
	return closing;
}

bool BrowserClient::isLoaded() const
{
	return loaded;
}

bool BrowserClient::OnProcessMessageReceived(
	CefRefPtr<CefBrowser> browser,
	CefProcessId source_process,
	CefRefPtr<CefProcessMessage> message
	){
	std::string name = message->GetName().ToString();
	CefRefPtr<CefListValue> arguments = message->GetArgumentList();

	/*
	std::printf("Received a message.... : %s\n", name.c_str());
	
	switch (source_process){
		case PID_RENDERER:
			std::printf("This was from the renderer.\n");
			break;
		case PID_BROWSER:
			std::printf("Somehow this is from the browser... Please fix me.\n");
			break;
	}*/

	if (name == WriteFileMessageId){
		std::string fileName = arguments->GetString(0).ToString();
		std::string fileContents = arguments->GetString(1).ToString();

		std::ofstream file(fileName);
		file << fileContents;
		file.close();
		return true;
	}

	if (name == StateMachineSetCurrent){
		std::string setStateTo = arguments->GetString(0).ToString();
		Engine::instance()->_stateMachine.setCurrent(setStateTo);
		return true;
	}

	if (name == UpgradeScreenPlayGame){
		GameUpgradeScreenState* ptr = (GameUpgradeScreenState*)Engine::instance()->_stateMachine.getState("upgradeScreen");
		bool result = ptr->SetupGame(arguments->GetInt(0));
		return true;
	}

	if (name == UpgradeDeveloperCheat1){
		GameUpgradeScreenState* ptr = (GameUpgradeScreenState*)Engine::instance()->_stateMachine.getState("upgradeScreen");
		ptr->ForceBossFight();
		return true;
	}

	if (name == GetBossVariableUpgrade){
		GameUpgradeScreenState* ptr = (GameUpgradeScreenState*)Engine::instance()->_stateMachine.getState("upgradeScreen");
		CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(GetBossVariableUpgrade);
		message->GetArgumentList()->SetSize(1);
		message->GetArgumentList()->SetBool(0, ptr->CanFightBoss());
		browser->SendProcessMessage(PID_RENDERER, message);
		return true;
	}


	if (name == IsThereABoss){
		GameState* ptr = (GameState*)Engine::instance()->_stateMachine.getState("game");
		CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(IsThereABoss);
		message->GetArgumentList()->SetSize(1);
		message->GetArgumentList()->SetBool(0, (ptr->getCurrentBoss() == nullptr ? false : true)&& (ptr->getGameMode() == GameModeBossGauntlet));
		browser->SendProcessMessage(PID_RENDERER, message);
	}

	if (name == CurrentPlayerCurrentHealth){
		GameState* ptr = (GameState*)Engine::instance()->_stateMachine.getState("game");
		CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(CurrentPlayerCurrentHealth);
		message->GetArgumentList()->SetSize(1);
		message->GetArgumentList()->SetInt(0, ptr->getPlayer()->getHealth());
		browser->SendProcessMessage(PID_RENDERER, message);
	}

	if (name == CurrentPlayerMaxHealth){
		GameState* ptr = (GameState*)Engine::instance()->_stateMachine.getState("game");
		CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(CurrentPlayerMaxHealth);
		message->GetArgumentList()->SetSize(1);
		message->GetArgumentList()->SetInt(0, ptr->getPlayer()->getMaxHealth());
		browser->SendProcessMessage(PID_RENDERER, message);
	}

	if (name == CurrentBossCurrentHealth){
		GameState* ptr = (GameState*)Engine::instance()->_stateMachine.getState("game");
		CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(CurrentBossCurrentHealth);
		message->GetArgumentList()->SetSize(1);
		message->GetArgumentList()->SetInt(0, ptr->getCurrentBoss()->getHealth());
		browser->SendProcessMessage(PID_RENDERER, message);
	}

	if (name == CurrentBossMaxHealth){
		GameState* ptr = (GameState*)Engine::instance()->_stateMachine.getState("game");
		CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(CurrentBossMaxHealth);
		message->GetArgumentList()->SetSize(1);
		message->GetArgumentList()->SetInt(0, ptr->getCurrentBoss()->getMaxHealth());
		browser->SendProcessMessage(PID_RENDERER, message);
	}

	if (name == EngineRequestDisplayModes){
		std::vector<SDL_DisplayMode> displayModes = Engine::instance()->getDisplayModes();
		CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(EngineRequestDisplayModes);
		message->GetArgumentList()->SetSize(displayModes.size());
		for (int i = 0; i < displayModes.size(); ++i){
			message->GetArgumentList()->SetInt(i, displayModes[i].w);
			message->GetArgumentList()->SetInt(i, displayModes[i].h);
			message->GetArgumentList()->SetInt(i, displayModes[i].format);
			message->GetArgumentList()->SetInt(i, displayModes[i].refresh_rate);
			message->GetArgumentList()->SetInt(i, 0);
			// so this is how I'm sending my data over.
		}
		browser->SendProcessMessage(PID_RENDERER, message);
	}

	if (name == EngineApplySettings){
		Engine::instance()->ApplyEngineSettings(message->GetArgumentList()->GetInt(0),
												message->GetArgumentList()->GetInt(1),
												message->GetArgumentList()->GetBool(2),
												message->GetArgumentList()->GetBool(3));
	}

	if (name == RequestCurrentGameRound){
		CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(RequestCurrentGameRound);

		GameState* ptr = (GameState*)Engine::instance()->_stateMachine.getState("game");

		message->GetArgumentList()->SetSize(1);
		message->GetArgumentList()->SetInt(0, ptr->getCurrentRound());
		browser->SendProcessMessage(PID_RENDERER, message);
	}
	
	if (name == RequestBulletIndexPlayer){
		CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(RequestBulletIndexPlayer);

		GameState* ptr = (GameState*)Engine::instance()->_stateMachine.getState("game");
		PlayerAI* playerPtr = (PlayerAI*)ptr->getPlayer()->getAI();

		message->GetArgumentList()->SetSize(1);
		message->GetArgumentList()->SetInt(0, playerPtr->getBulletIndex());
		browser->SendProcessMessage(PID_RENDERER, message);
	}

	if (name == GetPlayerLives){
		CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(GetPlayerLives);

		GameState* ptr = (GameState*)Engine::instance()->_stateMachine.getState("game");

		message->GetArgumentList()->SetSize(1);
		message->GetArgumentList()->SetInt(0, ptr->getPlayerLives());
		browser->SendProcessMessage(PID_RENDERER, message);
	}

	if (name == RequestBulletCountForIndex){
		CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(RequestBulletCountForIndex);

		GameState* ptr = (GameState*)Engine::instance()->_stateMachine.getState("game");
		PlayerAI* playerPtr = (PlayerAI*)ptr->getPlayer()->getAI();

		message->GetArgumentList()->SetSize(5);
		message->GetArgumentList()->SetInt(0, playerPtr->getBulletCountForIndex(0));
		message->GetArgumentList()->SetInt(1, playerPtr->getBulletCountForIndex(1));
		message->GetArgumentList()->SetInt(2, playerPtr->getBulletCountForIndex(2));
		message->GetArgumentList()->SetInt(3, playerPtr->getBulletCountForIndex(3));
		message->GetArgumentList()->SetInt(4, playerPtr->getBulletCountForIndex(4));
		browser->SendProcessMessage(PID_RENDERER, message);
	}

	if (name == RequestCurrentBulletCount){
		CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(RequestCurrentBulletCount);

		GameState* ptr = (GameState*)Engine::instance()->_stateMachine.getState("game");
		PlayerAI* playerPtr = (PlayerAI*)ptr->getPlayer()->getAI();

		message->GetArgumentList()->SetSize(1);
		message->GetArgumentList()->SetInt(0, playerPtr->getBulletCountForCurrentIndex());
		browser->SendProcessMessage(PID_RENDERER, message);
	}

	if (name == RestorePointsToPlayerHP){
		GameState* ptr = (GameState*)Engine::instance()->_stateMachine.getState("game");
		PlayerAI* playerPtr = (PlayerAI*)ptr->getPlayer()->getAI();

		playerPtr->getParent()->getHealth() += arguments->GetInt(0);
	}

	if (name == AddMaxHealthToPlayer){
		GameState* ptr = (GameState*)Engine::instance()->_stateMachine.getState("game");
		PlayerAI* playerPtr = (PlayerAI*)ptr->getPlayer()->getAI();

		playerPtr->getParent()->getMaxHealth() += arguments->GetInt(0);
	}

	if (name == AddToBullet){
		GameState* ptr = (GameState*)Engine::instance()->_stateMachine.getState("game");
		PlayerAI* playerPtr = (PlayerAI*)ptr->getPlayer()->getAI();

		playerPtr->getBulletCountForIndex(arguments->GetInt(0)) += arguments->GetInt(1);
	}

	if (name == SubtractGameScore){
		GameState* ptr = (GameState*)Engine::instance()->_stateMachine.getState("game");
		ptr->getGameScore() -= arguments->GetInt(0);
	}

	if (name == AddGameScore){
		GameState* ptr = (GameState*)Engine::instance()->_stateMachine.getState("game");
		ptr->getGameScore() += arguments->GetInt(0);
	}

	if (name == GetGameScore){
		CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(GetGameScore);

		GameState* ptr = (GameState*)Engine::instance()->_stateMachine.getState("game");

		message->GetArgumentList()->SetSize(1);
		message->GetArgumentList()->SetInt(0, ptr->getGameScore());
		browser->SendProcessMessage(PID_RENDERER, message);
	}
	
	if (name == RequestMessageBarMessage){
		CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(RequestMessageBarMessage);

		GameState* ptr = (GameState*)Engine::instance()->_stateMachine.getState("game");

		message->GetArgumentList()->SetSize(1);
		message->GetArgumentList()->SetString(0, ptr->getMessage());
		browser->SendProcessMessage(PID_RENDERER, message);
	}

	// didn't handle message technically.
	return false;
}