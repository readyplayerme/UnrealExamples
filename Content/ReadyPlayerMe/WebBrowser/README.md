# Web Browser Integration Example

Example uses the Unreal Engine Web Browser module (and Web Browser Widget) to embed the Ready Player Me Web Avatar Creator inside an application to create a seamless integration. 

![Screenshot 2022-10-26 121009](https://user-images.githubusercontent.com/108666572/198000086-7771d6a5-70cc-4b39-b087-b0533257d9be.png)

![Screenshot 2022-10-26 121106](https://user-images.githubusercontent.com/108666572/198000119-79ea06ea-4a12-458d-8c7d-88cf7d7ab208.png)

*NOTE: The Web Browser module will only work with our readyplayer.me website in Unreal Engine 5 on Windows platform. The Web Browser module in Unreal Engine 4 uses a very old version of chromium which does not support all the modern web browser features.*

# Dependencies

To enable the WebBrowser support for our project, WebBrowserWidget plugins need to be enabled in the uproject file.
Additionally to ba able to access it through the C++ code we need to add the following modules to our `UnrealExamplesBuild.cs`file `WebBrowserWidget`, `WebBrowser`, `UMG`.

# Web Browser Demo Map

The WebBrowserDemo map located in the `Content` folder is a good starting point for anybody wanting to use the Web Browser module to seamlessly integrate our RPM Web Avatar Creator into you game or application.  The logic for this is rather simple, if you open up the Level Blueprint you will see this network of nodes.

![Screenshot 2022-10-26 122813](https://user-images.githubusercontent.com/108666572/198003565-c192c23d-9d34-4b10-ac4b-783bc1db4061.png)

In the first group of nodes, connected to the `BeginPlay` event we create and add our custom Ready Player Me Browser widget to the viewport before setting `ShowMouseCursor` to true so that the user can see the cursor and interact with the browser widget.

![Screenshot 2022-10-26 122603](https://user-images.githubusercontent.com/108666572/198003525-3be3ec33-c514-4945-8c85-ea3250e92564.png)

Next we bind the RPM Browser widget's Avatar Generated Event to run the Load New Avatar event on a RPM Actor blueprint present in the map. The Avatar Generated Event is called from the web browser widget once the avatar creation process is complete and it returns a URL to the RPM avatar GLB file, which we subsequently load into the scene.

![Screenshot 2022-10-26 122603](https://user-images.githubusercontent.com/108666572/198003202-25142a00-e7ee-4077-9c3c-9f26cd12a43d.png)

# Browser Widget Blueprint

To display and interact with the a web browser inside unreal you need to use a UI Widget. For this demo we created the RPM_BrowserWidget located in `Content > Blueprints`. If you open up the widget you will in the Hierarchy panel that it consists of a **CanvasPanel** and a **RPM Web Browser widget** inside of it.

![img-widget-hierarchy](https://user-images.githubusercontent.com/7085672/163364100-75cc563b-3e78-418f-ab1a-47b79cfabf45.png)

It is set up this way so that the RPM Browser Widgets position, padding and anchor settings can be easily adjusted relative to the Canvas Panel. If you select the `RPM_Browser` object in the hierachy you will most likely need to update the `InitialUrl` setting. This is the Url that will be loaded when this Widget is created/added to the scene.

Select the RPM_Browser object in the hierarchy, in the ReadyPlayerMe category there are several parameters that can be used to generate the initial url of the WebBrowser.
- **Partner Domain**: By default it's set to demo, however as the name suggests this is only recommended for demo's. We highly recommend you become a Ready Player Me partner and get your own partner space. Once you have your own partner space setup you update this parameter accordingly.
- **Clean Cache**: Provides a Kiosk experience
- **Quick Start**: Enters the Quick Start view.
- **Body Type**: Skip the body type selection step when opening the avatar view.
- **Gender**: Skip the gender selection step when opening the avatar view.
- **Language**: By default the system language will be used for opening the browser, However the language can be customized.

![Screenshot 2022-12-02 173148](https://user-images.githubusercontent.com/3124894/205340278-cc75a168-7813-4e32-bfdb-e44e41f00555.png)

Further down in the Details panel you will also see a number of events that can be bound to. These events are called from the **WebBrowser Widget** when certain events occur. For example when the avatar creation process has been completed the `OnAvatarExported` event will be called. This event will return the URL to the GLB file of the avatar. This can then be used to load the avatar into the scene.

![Screenshot 2023-06-08 110535](https://github.com/readyplayerme/UnrealExamples/assets/7085672/1716ab37-a550-44af-966d-e31d12a46d32)

Next open up the Graph for the **Ready Player Me Browser Widget** and you will see this network of nodes.

![Screenshot 2023-06-08 110605](https://github.com/readyplayerme/UnrealExamples/assets/7085672/094e98ca-733c-44cc-b582-32ab00e84e51)

Lets take at the first group of nodes connected to the widget's construct event. Here bind a custom event to the WebBrowser Widgets `OnUrlChanged` event that runs the `BrowserSetup` function. This is done on `OnUrlChanged` to ensure the the browser has actually started loading the website before starting to load the initial Url. Without this there is issues when it comes to injecting custom javascript. Additionally you can also call `ClearAvatarData` to clear previously created avatar data, to be able to create a new avatar next time the browser is loaded. Lastly we also unbind the event so it doesn't run the setup again.

In the bottom half of the photo you can see the **Avatar Exported** callback section which shows the `OnAvatarExported` event we mentioned previous. Use this callback anbd the AvatarUrl property to retrieve the avatar url.
![Screenshot 2023-06-08 123434](https://github.com/readyplayerme/UnrealExamples/assets/7085672/44043a1e-7a2d-4974-a4d8-fffea13a5c4b)

In the last section of the graph labeled **Auto Hide (Optional)** we simply hide the browser widget by setting the visibility, this can be toggled with the `HideAfterAvatarGeneration` property.

# Ready Player Me Browser Class

Now let's tale a look at the `ReadyPlayerMeWebBrowser` class, based on the Unreal` UWebBrowser` class and it adds a few extra functions for setting up the connection between the Web Browser and Unreal engine using the Web Link object we covered previously.

To understand how this works lets take a look at the `SetupBrowser()` function. 
```cpp
void UReadyPlayerMeWebBrowser::SetupBrowser()
{
	BindBrowserToObject();
	const FString Path = FPaths::ProjectContentDir() / JavascriptPath;


	FString RpmSetupJavascript;
	if (FPaths::FileExists(Path))
	{
		FFileHelper::LoadFileToString(RpmSetupJavascript, *Path);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Script file not found: %s"), *Path);
		return;
	}

	ExecuteJavascript(RpmSetupJavascript);
}

```

This function is responsible for binding the Web Browser Widget to the Web Link object and setting up the javascript that listens to the website events that fire from the Ready Player Me website. These events include: 
- Avatar Exported
- User Set 
- Asset Unlock 
- User Authorized

More information about these events can be found in the [Web Browser Integration](https://docs.readyplayer.me/web-browser-integration) documentation.

The Javascript we run can be found in here `Content/ReadyPlayerMe/WebBrowser/Scripts/RpmFrameSetup.js`.

You will also notice that this function calls the `BindBrowserToObject()` function which we will cover next. 

```cpp
void UReadyPlayerMeWebBrowser::BindBrowserToObject()
{
	this->Rename(*LinkObjectName);
	WebBrowserWidget->BindUObject(LinkObjectName, this);
}
```
The `BindBrowserToObject()` function simply renames the Web Browser Widget and binds the web browser functionality to the widget using the [BindUObject](https://docs.unrealengine.com/4.27/en-US/API/Runtime/WebBrowser/SWebBrowser/BindUObject/) function. This is important as it enables communication between the web browser and Unreal engine API.

Next we can look at the `HandleEvent`s function which is responsible for handling the events that are fired from the Ready Player Me website and subsequently calling the appropriate delegate, passing the required data.

```cpp
void UReadyPlayerMeWebBrowser::HandleEvents(WebMessage WebMessage) const
{
	if (WebMessage.EventName == WebViewEvents::USER_SET)
	{
		if (OnUserSet.IsBound())
		{
			OnUserSet.Broadcast(WebMessage.GetId());
		}
	}
	else if (WebMessage.EventName == WebViewEvents::USER_AUTHORIZED)
	{
		if (OnUserAuthorized.IsBound())
		{
			OnUserAuthorized.Broadcast(WebMessage.GetUserId());
		}
	}
	else if (WebMessage.EventName == WebViewEvents::AVATAR_EXPORT)
	{
		if (OnAvatarExported.IsBound())
		{
			OnAvatarExported.Broadcast(WebMessage.GetUrl());
		}
	}
	else if (WebMessage.EventName == WebViewEvents::ASSET_UNLOCK)
	{
		if (OnAssetUnlock.IsBound())
		{
			OnAssetUnlock.Broadcast(WebMessage.GetAssetRecord());
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("WebEvent: %s"), *WebMessage.EventName);
}
```

The code itself should be quite self explanatory, it checks for the event name, and broadcasts the delegate with the required data. 

If you switch back to the `ReadyPlayerMeWebBrowser.h` file you will see the following delegates defined.

```cpp
	UPROPERTY(BlueprintAssignable)
	FOnAvatarCreated OnAvatarExported;
	UPROPERTY(BlueprintAssignable)
	FOnUserSet OnUserSet;
	UPROPERTY(BlueprintAssignable)
	FOnAssetUnlock OnAssetUnlock;
	UPROPERTY(BlueprintAssignable)
	FOnUserAuthorized OnUserAuthorized;
```

Notice that all of these have the macro `UPROPERTY(BlueprintAssignable)` which is required for the delegates to be accessible from the Widget Blueprint. By doing this we can easily bind the delegates to custom events from in the Widget Blueprint.

