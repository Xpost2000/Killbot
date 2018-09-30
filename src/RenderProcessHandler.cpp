#include "RenderProcessHandler.h"
#include "constants.h"

#include "Engine.h"

#include <cstdio>
#include <cstdlib>

// TODO: Remove that giant comment in the other file...

RenderProcessApplication::RenderProcessApplication(){
//	freopen("render_process_log.txt", "a", stdout);
	_BulletCounts[0] = 0;	_BulletCounts[1] = 0;	_BulletCounts[2] = 0;	_BulletCounts[3] = 0;
}

RenderProcessApplication::~RenderProcessApplication(){
//	fclose(stdout);
}

void RenderProcessApplication::OnRenderThreadCreated(CefRefPtr<CefListValue> extra_info){
	std::printf("RenderProcess:: Thread created!\n");
	//MessageBox(NULL, "Thread created..", "RendererTHREAD", MB_ICONINFORMATION);
}

void RenderProcessApplication::OnWebKitInitialized(){
	std::printf("RenderProcess:: WebKit Initialized!\n");
	//MessageBox(NULL, "WEB KIT INITI..", "RendererTHREAD", MB_ICONINFORMATION);
}

void RenderProcessApplication::OnBrowserCreatesd(CefRefPtr<CefBrowser> browser){

}

void RenderProcessApplication::OnBrowserDestroyed(CefRefPtr<CefBrowser> browser){

}

/*
 * This is OnContextCreated.
 *
 * This is performed whenever a webpage is loaded and it creates
 * a context for Javascript to work on, and also for the browser to draw on.
 *
 * It's basically like giving a paper for someone to do work on.
 */

void RenderProcessApplication::OnContextCreated(
	CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefV8Context> context
	){
	std::printf("Javascript context created!\n");
	accessor = new JavascriptAccessor;
	jsHandler = new JavascriptFunctionHandler;
	//MessageBox(NULL, "JAVASCRIPT CONTEXT CREATED", "RendererTHREAD", MB_ICONINFORMATION);

	browser->SendProcessMessage(PID_BROWSER, CefProcessMessage::Create(EngineRequestDisplayModes));

	/*
	 * So this is the most important part of the renderer process.
	 *
	 * Now these two functions below aren't abstract functions from CEF, I made those so I can read my own code more easily.
	 *
	 * CreateNativeFunctions()   : Native refers to the program I'm running the page on, AKA: the game. It is a native program.
	 * 			       What I do in that function/method is generate the javascript versions of some native functions that are important to the
	 * 			       engine. This is how I can do stuff like change my engine window and start the game from a webpage.
	 *
	 * RegisterNativeFunctions() : This function registers or basically makes the functions that I make in CreateNativeFunctions() actually exist to the web browser. 
	 */
	CreateNativeFunctions(browser, frame, context);
	RegisterNativeFunctions(browser, frame, context);
}

//Creating Functions
void RenderProcessApplication::CreateNativeFunctions(
	CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefV8Context> context
	){

	// keep making functions.
	
	/*
	 * Alright so as you can see this ridiculously big function ( sorry it's like a 100 lines or something, so almost big. )
	 *
	 * Anyways in this function you'll see a lot of 
	 *
	 * jsHandler->addFunction.
	 *
	 * jsHandler is a javascript handler that I implement to register the functions.
	 *
	 * The javascript handler basically takes 
	 * -the name of the function as it should be called in javascript
	 * -then a normal native function to map it to.
	 *
	 *  Basically
	 *
	 *  IN			OUT
	 *  "LoadURL"  ----->   AFunctionInC++() { 
	 *  				LoadWebPage( URL from "LoadURL" );
	 *  			}
	 *
	 * You may also notice I'm doing a lot of
	 *
	 * curBrowser->SendProcessMessage();
	 *
	 * So this uses a system called messaging. It's pretty self explanatory.
	 * This is done since Chrome uses a multi process system.
	 *
	 *
	 * Right well because of the multi process ways of CEF I have to use messaging to receive and send
	 * requests to my game engine.
	 *
	 * Most of the functions here basically request the game engine to do stuff based on the contents of the message.
	 */
	jsHandler->addFunction("LoadURL", [&](CefRefPtr<CefV8Value> obj, const CefV8ValueList& args, CefString& exception){
		CefV8Context::GetCurrentContext()->GetFrame()->LoadURL(args[0]->GetStringValue());
		return CefV8Value::CreateBool(true);
	});

	// mimics the statemachine method of a similar name.
	jsHandler->addFunction("SetCurrentState", [&](CefRefPtr<CefV8Value> obj, const CefV8ValueList& args, CefString& exception){
		CefRefPtr<CefBrowser>& curBrowser = CefV8Context::GetCurrentContext()->GetBrowser();
		CefRefPtr<CefProcessMessage> fsmSetState = CefProcessMessage::Create(StateMachineSetCurrent);
		CefRefPtr<CefListValue> argumentsOf = fsmSetState->GetArgumentList();

		argumentsOf->SetSize(1);
		argumentsOf->SetString(0, args[0]->GetStringValue());

		curBrowser->SendProcessMessage(PID_BROWSER, fsmSetState);
		return CefV8Value::CreateBool(true);
	});

	jsHandler->addFunction("SetupGame", [&](CefRefPtr<CefV8Value> obj, const CefV8ValueList& args, CefString& exception){
		CefRefPtr<CefBrowser>& curBrowser = CefV8Context::GetCurrentContext()->GetBrowser();
		CefRefPtr<CefProcessMessage> startGameProper = CefProcessMessage::Create(UpgradeScreenPlayGame);
		CefRefPtr<CefListValue> argumentsOf = startGameProper->GetArgumentList();

		argumentsOf->SetSize(1);
		argumentsOf->SetInt(0, args[0]->GetIntValue());

		curBrowser->SendProcessMessage(PID_BROWSER, startGameProper);
		return CefV8Value::CreateBool(true);
	});

	jsHandler->addFunction("GetFightBoss", [&](CefRefPtr<CefV8Value> obj, const CefV8ValueList& args, CefString& exception){
		CefRefPtr<CefBrowser>& curBrowser = CefV8Context::GetCurrentContext()->GetBrowser();
		CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(GetBossVariableUpgrade);
		curBrowser->SendProcessMessage(PID_RENDERER, message);

		return CefV8Value::CreateBool(_canWeFightBoss);
	});

	jsHandler->addFunction("IsThereABoss", [&](CefRefPtr<CefV8Value> obj, const CefV8ValueList& args, CefString& exception){
		CefRefPtr<CefBrowser>& curBrowser = CefV8Context::GetCurrentContext()->GetBrowser();
		CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(IsThereABoss);
		curBrowser->SendProcessMessage(PID_RENDERER, message);

		return CefV8Value::CreateBool(_isThereABoss);
	});

	jsHandler->addFunction("GetBossMaxHealth", [&](CefRefPtr<CefV8Value> obj, const CefV8ValueList& args, CefString& exception){
		CefRefPtr<CefBrowser>& curBrowser = CefV8Context::GetCurrentContext()->GetBrowser();
		CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(CurrentBossMaxHealth);
		curBrowser->SendProcessMessage(PID_RENDERER, message);

		return CefV8Value::CreateInt(_bossMaxHealth);
	});

	jsHandler->addFunction("GetBossHealth", [&](CefRefPtr<CefV8Value> obj, const CefV8ValueList& args, CefString& exception){
		CefRefPtr<CefBrowser>& curBrowser = CefV8Context::GetCurrentContext()->GetBrowser();
		CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(CurrentBossCurrentHealth);
		curBrowser->SendProcessMessage(PID_RENDERER, message);

		return CefV8Value::CreateInt(_currentBossHealth);
	});

	jsHandler->addFunction("GetPlayerMaxHealth", [&](CefRefPtr<CefV8Value> obj, const CefV8ValueList& args, CefString& exception){
		CefRefPtr<CefBrowser>& curBrowser = CefV8Context::GetCurrentContext()->GetBrowser();
		CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(CurrentPlayerMaxHealth);
		curBrowser->SendProcessMessage(PID_RENDERER, message);

		return CefV8Value::CreateInt(_playerMaxHealth);
	});

	jsHandler->addFunction("GetPlayerHealth", [&](CefRefPtr<CefV8Value> obj, const CefV8ValueList& args, CefString& exception){
		CefRefPtr<CefBrowser>& curBrowser = CefV8Context::GetCurrentContext()->GetBrowser();
		CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(CurrentPlayerCurrentHealth);
		curBrowser->SendProcessMessage(PID_RENDERER, message);

		return CefV8Value::CreateInt(_currentPlayerHealth);
	});

	jsHandler->addFunction("GetMessagebarText", [&](CefRefPtr<CefV8Value> obj, const CefV8ValueList& args, CefString& exception){
		CefRefPtr<CefBrowser>& curBrowser = CefV8Context::GetCurrentContext()->GetBrowser();
		CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(RequestMessageBarMessage);
		curBrowser->SendProcessMessage(PID_RENDERER, message);

		return CefV8Value::CreateString(_txtBarMessage);
	});

	jsHandler->addFunction("ForceBossEligibility", [&](CefRefPtr<CefV8Value> obj, const CefV8ValueList& args, CefString& exception){
		CefRefPtr<CefBrowser>& curBrowser = CefV8Context::GetCurrentContext()->GetBrowser();
		CefRefPtr<CefProcessMessage> devCheat1 = CefProcessMessage::Create(UpgradeDeveloperCheat1);

		curBrowser->SendProcessMessage(PID_BROWSER, devCheat1);
		return CefV8Value::CreateBool(true);
	});

	// Two arguments
	// File name.
	// then an string dictating the file contents. No serialization or binary writting.
	jsHandler->addFunction("WriteFile", [&](CefRefPtr<CefV8Value> obj, const CefV8ValueList& args, CefString& exception){
		CefRefPtr<CefBrowser>& curBrowser = CefV8Context::GetCurrentContext()->GetBrowser();
		CefRefPtr<CefProcessMessage> writeFileMessage = CefProcessMessage::Create(WriteFileMessageId);
		CefRefPtr<CefListValue> argumentsOf = writeFileMessage->GetArgumentList();

		argumentsOf->SetSize(2);
		argumentsOf->SetString(0, args[0]->GetStringValue());
		argumentsOf->SetString(1, args[1]->GetStringValue());

		curBrowser->SendProcessMessage(PID_BROWSER, writeFileMessage);
		return CefV8Value::CreateBool(true);
	});

	// sadly I cannot get this one to work....
	jsHandler->addFunction("RequestDisplayModes", [&](CefRefPtr<CefV8Value> obj, const CefV8ValueList& args, CefString& exception){
		CefRefPtr<CefBrowser>& curBrowser = CefV8Context::GetCurrentContext()->GetBrowser();
		CefRefPtr<CefV8Value> array = CefV8Value::CreateArray(4*displayModes.size());
		for (int i = 0; i < displayModes.size(); ++i){
			array->SetValue(i, CefV8Value::CreateInt(displayModes[i].w));
			array->SetValue(i+1, CefV8Value::CreateInt(displayModes[i].h));
			array->SetValue(i+2, CefV8Value::CreateInt(displayModes[i].refresh_rate));
			array->SetValue(i+3, CefV8Value::CreateInt(displayModes[i].format));
		}
		return array;
	});

	jsHandler->addFunction("ApplySettings", [&](CefRefPtr<CefV8Value> obj, const CefV8ValueList& args, CefString& exception){
		CefRefPtr<CefBrowser>& curBrowser = CefV8Context::GetCurrentContext()->GetBrowser();
		CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(EngineApplySettings);
		message->GetArgumentList()->SetInt(0, args[0]->GetIntValue());
		message->GetArgumentList()->SetInt(1, args[1]->GetIntValue());

		message->GetArgumentList()->SetBool(2, args[2]->GetBoolValue());
		message->GetArgumentList()->SetBool(3, args[3]->GetBoolValue());
		curBrowser->SendProcessMessage(PID_BROWSER, message);
		return CefV8Value::CreateBool(true);
	});

	jsHandler->addFunction("GetCurrentRound", [&](CefRefPtr<CefV8Value> obj, const CefV8ValueList& args, CefString& exception){
		CefRefPtr<CefBrowser>& curBrowser = CefV8Context::GetCurrentContext()->GetBrowser();
		CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(RequestCurrentGameRound);
		curBrowser->SendProcessMessage(PID_RENDERER, message);

		return CefV8Value::CreateInt(_currentGameRound);
	});

	jsHandler->addFunction("GetCurrentBulletIndex", [&](CefRefPtr<CefV8Value> obj, const CefV8ValueList& args, CefString& exception){
		CefRefPtr<CefBrowser>& curBrowser = CefV8Context::GetCurrentContext()->GetBrowser();
		CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(RequestBulletIndexPlayer);
		curBrowser->SendProcessMessage(PID_RENDERER, message);

		return CefV8Value::CreateInt(_currentBulletIndex);
	});

	jsHandler->addFunction("GetCurrentBulletCount", [&](CefRefPtr<CefV8Value> obj, const CefV8ValueList& args, CefString& exception){
		CefRefPtr<CefBrowser>& curBrowser = CefV8Context::GetCurrentContext()->GetBrowser();
		CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(RequestCurrentBulletCount);
		curBrowser->SendProcessMessage(PID_RENDERER, message);

		return CefV8Value::CreateInt(_currentBulletCount);
	});

	jsHandler->addFunction("GetBulletCountForIndex", [&](CefRefPtr<CefV8Value> obj, const CefV8ValueList& args, CefString& exception){
		CefRefPtr<CefBrowser>& curBrowser = CefV8Context::GetCurrentContext()->GetBrowser();
		CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(RequestBulletCountForIndex);
		curBrowser->SendProcessMessage(PID_RENDERER, message);

		return CefV8Value::CreateInt(_BulletCounts[args[0]->GetIntValue()]);
	});

	jsHandler->addFunction("RestorePlayerHP", [&](CefRefPtr<CefV8Value> obj, const CefV8ValueList& args, CefString& exception){
		CefRefPtr<CefBrowser>& curBrowser = CefV8Context::GetCurrentContext()->GetBrowser();
		CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(RestorePointsToPlayerHP);
		message->GetArgumentList()->SetSize(1);
		message->GetArgumentList()->SetInt(0, args[0]->GetIntValue());

		curBrowser->SendProcessMessage(PID_RENDERER, message);
		return CefV8Value::CreateBool(true);
	});

	jsHandler->addFunction("IncreasePlayerMaxHP", [&](CefRefPtr<CefV8Value> obj, const CefV8ValueList& args, CefString& exception){
		CefRefPtr<CefBrowser>& curBrowser = CefV8Context::GetCurrentContext()->GetBrowser();
		CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(AddMaxHealthToPlayer);
		message->GetArgumentList()->SetSize(1);
		message->GetArgumentList()->SetInt(0, args[0]->GetIntValue());

		curBrowser->SendProcessMessage(PID_RENDERER, message);
		return CefV8Value::CreateBool(true);
	});

	jsHandler->addFunction("IncreaseBulletCountForIndex", [&](CefRefPtr<CefV8Value> obj, const CefV8ValueList& args, CefString& exception){
		CefRefPtr<CefBrowser>& curBrowser = CefV8Context::GetCurrentContext()->GetBrowser();
		CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(AddToBullet);
		message->GetArgumentList()->SetSize(2);
		message->GetArgumentList()->SetInt(0, args[0]->GetIntValue());
		message->GetArgumentList()->SetInt(1, args[1]->GetIntValue());

		curBrowser->SendProcessMessage(PID_RENDERER, message);
		return CefV8Value::CreateBool(true);
	});

	jsHandler->addFunction("SubtractGameScore", [&](CefRefPtr<CefV8Value> obj, const CefV8ValueList& args, CefString& exception){
		CefRefPtr<CefBrowser>& curBrowser = CefV8Context::GetCurrentContext()->GetBrowser();
		CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(SubtractGameScore);
		message->GetArgumentList()->SetSize(1);
		message->GetArgumentList()->SetInt(0, args[0]->GetIntValue());

		curBrowser->SendProcessMessage(PID_RENDERER, message);
		return CefV8Value::CreateBool(true);
	});

	jsHandler->addFunction("AddGameScore", [&](CefRefPtr<CefV8Value> obj, const CefV8ValueList& args, CefString& exception){
		CefRefPtr<CefBrowser>& curBrowser = CefV8Context::GetCurrentContext()->GetBrowser();
		CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(AddGameScore);
		message->GetArgumentList()->SetSize(1);
		message->GetArgumentList()->SetInt(0, args[0]->GetIntValue());

		curBrowser->SendProcessMessage(PID_RENDERER, message);
		return CefV8Value::CreateBool(true);
	});

	jsHandler->addFunction("GetGameScore", [&](CefRefPtr<CefV8Value> obj, const CefV8ValueList& args, CefString& exception){
		CefRefPtr<CefBrowser>& curBrowser = CefV8Context::GetCurrentContext()->GetBrowser();
		CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(GetGameScore);
		curBrowser->SendProcessMessage(PID_RENDERER, message);
		return CefV8Value::CreateInt(_currentGameScore);
	});

	jsHandler->addFunction("GetPlayerLives", [&](CefRefPtr<CefV8Value> obj, const CefV8ValueList& args, CefString& exception){
		CefRefPtr<CefBrowser>& curBrowser = CefV8Context::GetCurrentContext()->GetBrowser();
		CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(GetPlayerLives);
		curBrowser->SendProcessMessage(PID_RENDERER, message);
		return CefV8Value::CreateInt(_playerLives);
	});
}

//Registering them to the browser.
void RenderProcessApplication::RegisterNativeFunctions(
	CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame, 
	CefRefPtr<CefV8Context> context
	){
	CefRefPtr<CefV8Value> globalWindowObject = context->GetGlobal();
	CefRefPtr<CefV8Value> killbotEngineObject = CefV8Value::CreateObject(accessor, nullptr);
	CefRefPtr<CefV8Value> gameObject = CefV8Value::CreateObject(accessor, nullptr);

	/*
	 * Don't worry about this much, it fundamentally binds the functions to javascript objects so I can use the functions
	 * this is how the functions are registered.
	 *
	 * IN		INTERMIDIATE		OUT
	 * "LoadURL"	registerTo(WINDOW)	window.LoadURL();
	 */

	globalWindowObject->SetValue("killbotEngine", killbotEngineObject, V8_PROPERTY_ATTRIBUTE_NONE);
	killbotEngineObject->SetValue("SetupGame", gameObject, V8_PROPERTY_ATTRIBUTE_NONE);
	killbotEngineObject->SetValue("game", gameObject, V8_PROPERTY_ATTRIBUTE_NONE);
	// Start registering the functions here
	jsHandler->RegisterToObject("LoadURL", killbotEngineObject);
	jsHandler->RegisterToObject("WriteFile", killbotEngineObject);
	jsHandler->RegisterToObject("RequestDisplayModes", killbotEngineObject);
	jsHandler->RegisterToObject("ApplySettings", killbotEngineObject);

	jsHandler->RegisterToObject("SetCurrentState", gameObject);
	jsHandler->RegisterToObject("GetFightBoss", gameObject);
	jsHandler->RegisterToObject("SetupGame", gameObject);
	jsHandler->RegisterToObject("ForceBossEligibility", gameObject);
	jsHandler->RegisterToObject("IsThereABoss", gameObject);
	jsHandler->RegisterToObject("GetBossMaxHealth", gameObject);
	jsHandler->RegisterToObject("GetBossHealth", gameObject);
	jsHandler->RegisterToObject("GetPlayerMaxHealth", gameObject);
	jsHandler->RegisterToObject("GetPlayerHealth", gameObject);

	jsHandler->RegisterToObject("GetCurrentBulletIndex", gameObject);
	jsHandler->RegisterToObject("GetCurrentRound", gameObject);
	jsHandler->RegisterToObject("GetBulletCountForIndex", gameObject);
	jsHandler->RegisterToObject("GetCurrentBulletCount", gameObject);
	jsHandler->RegisterToObject("GetMessagebarText", gameObject);

	jsHandler->RegisterToObject("RestorePlayerHP", gameObject);
	jsHandler->RegisterToObject("IncreasePlayerMaxHP", gameObject);
	jsHandler->RegisterToObject("IncreaseBulletCountForIndex", gameObject);
	jsHandler->RegisterToObject("SubtractGameScore", gameObject);
	jsHandler->RegisterToObject("AddGameScore", gameObject);
	jsHandler->RegisterToObject("GetGameScore", gameObject);
	jsHandler->RegisterToObject("GetPlayerLives", gameObject);
	//jsHandler->RegisterToObject("SendMessageToBrowser", killbotEngineObject);
}

void RenderProcessApplication::OnContextReleased(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefV8Context> context){

}

void RenderProcessApplication::OnFocusedNodeChanged(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefDOMNode> node){

}

bool RenderProcessApplication::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
	CefProcessId source_process,
	CefRefPtr<CefProcessMessage> message){
		std::string name = message->GetName().ToString();
		CefRefPtr<CefListValue> arguments = message->GetArgumentList();

		std::printf("Received a message.... : %s\n", name.c_str());

		switch (source_process){
		case PID_RENDERER:
			std::printf("Somehow this is from the renderer... Please fix me.\n");
			break;
		case PID_BROWSER:
			std::printf("This was from the browser.\n");
			break;
		}

		// Ok now as I just showed in my rushed example
		// of messaging I fundamentally check the type of message that was sent
		// and decide if it's worth it to process.
		// now of course unlike my generic *FORGOT HOW TO SPELL TEMPORARILY*
		// every message will be intercepted, none of the messages waste space.
		//
		// I mean I'm sending messages of one type, a command.
		//
		// This function basically just reads the message and based on the message "name"
		// I determine how to extract any data that may have been put in the message.
		//
		// This part is pretty simple. Well relatively.

		if (name == GetBossVariableUpgrade){
			_canWeFightBoss = arguments->GetBool(0);
		}

		if (name == IsThereABoss){
			_isThereABoss = arguments->GetBool(0);
		}

		if (name == CurrentPlayerCurrentHealth){
			_currentPlayerHealth = arguments->GetInt(0);
		}

		if (name == CurrentPlayerMaxHealth){
			_playerMaxHealth = arguments->GetInt(0);
		}

		if (name == CurrentBossCurrentHealth){
			_currentBossHealth = arguments->GetInt(0);
		}

		if (name == CurrentBossMaxHealth){
			_bossMaxHealth = arguments->GetInt(0);
		}

		if (name == EngineRequestDisplayModes){
			// I think I did the math correctly.
			for (int i = 0; i < message->GetArgumentList()->GetSize(); ++i){
				if ((i % 5) == 0){
					//TODO: Actually make this work.
					displayModes.push_back(SDL_DisplayMode{ SDL_PIXELFORMAT_UNKNOWN, 0, 0, 0, 0 });
					displayModes[i % 5].w = message->GetArgumentList()->GetInt(i - 5);
					displayModes[i % 5].h = message->GetArgumentList()->GetInt(i - 4);
					displayModes[i % 5].format = message->GetArgumentList()->GetInt(i - 3);
					displayModes[i % 5].refresh_rate = message->GetArgumentList()->GetInt(i - 2);
			//		displayModes[i % 5].driverdata = (void*)message->GetArgumentList()->GetInt(i - 1);
				}
			}
		}

		if (name == RequestCurrentGameRound){
			_currentGameRound = message->GetArgumentList()->GetInt(0);
		}

		if (name == RequestBulletIndexPlayer){
			_currentBulletIndex = message->GetArgumentList()->GetInt(0);
		}

		if (name == RequestBulletCountForIndex){
			_BulletCounts[0] = message->GetArgumentList()->GetInt(0);
			_BulletCounts[1] = message->GetArgumentList()->GetInt(1);
			_BulletCounts[2] = message->GetArgumentList()->GetInt(2);
			_BulletCounts[3] = message->GetArgumentList()->GetInt(3);
			_BulletCounts[4] = message->GetArgumentList()->GetInt(4);
		}

		if (name == RequestCurrentBulletCount){
			_currentBulletCount = message->GetArgumentList()->GetInt(0);
		}

		if (name == GetGameScore){
			_currentGameScore = message->GetArgumentList()->GetInt(0);
		}

		// I made a copy and paste mistake here... S**t, I don't know what it was for!!!!
		//if (name == GetGameScore){
		//	_currentGameScore = message->GetArgumentList()->GetInt(0);
		//}

		if (name == RequestMessageBarMessage){
			_txtBarMessage = message->GetArgumentList()->GetString(0);
		}

		if (name == GetPlayerLives){
			_playerLives = message->GetArgumentList()->GetInt(0);
		}

		_didWeReceiveAMessage = true;
		// didn't handle message technically.
		return false;
}
