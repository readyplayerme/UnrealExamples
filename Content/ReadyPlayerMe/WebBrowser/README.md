# UE Avatar Creator Integration Example

This repository contains an Unreal Engine 5 sample project that uses the Unreal Engine Web Browser module (and Web Browser Widget) to embed the Ready Player Me Avatar Creator inside an application to create a seamless integration.

![img-web-browser-in-game](https://user-images.githubusercontent.com/7085672/163359540-e51de977-89ac-440b-8723-b9217681b00d.png)

![img-loaded-avatar](https://user-images.githubusercontent.com/7085672/163359554-7cb22446-5a96-4353-ac30-2d02b37468b5.png)


*NOTE: The Web Browser module will only work with our readyplayer.me website in Unreal Engine 5. The Web Browser module in Unreal Engine 4 uses a very old version of chromium which does not support all the modern web browser features.*

# Web Browser Demo Map

The WebBrowserDemo map located in the `Content` folder is a good starting point for anybody wanting to use the Web Browser module to seamlessly integrate our RPM Avatar Creator into you game or application.  The logic for this is rather simple, if you open up the Level Blueprint you will see this network of nodes.

![img-browser-bp](https://user-images.githubusercontent.com/7085672/163360368-c277f209-0cd5-4dc5-a9e4-df9bc1fec58b.png)

In the first group of nodes, connected to the `BeginPlay` event we create and add our custom Ready Player Me Browser widget to the viewport before setting `ShowMouseCursor` to true so that the user can see the cursor and interact with the browser widget.

![img-create-widget-nodes](https://user-images.githubusercontent.com/7085672/163360441-e907ae6a-eda4-48c4-9de0-aa0ee1e552e9.png)

Next we bind the RPM Browser widget's Avatar Generated Event to run the Load New Avatar event on a RPM Actor blueprint present in the map. The Avatar Generated Event is called from the web browser widget once the avatar creation process is complete and it returns a URL to the RPM avatar GLB file, which we subsequently load into the scene.

![img-bind-event](https://user-images.githubusercontent.com/7085672/163360486-14c3aa31-d19c-46df-a825-623bccc10d1c.png)

# Browser Widget Blueprint

To display and interact with the a web browser inside unreal you need to use a UI Widget. For this demo we created the RPM_BrowserWidget located in `Content > Blueprints`. If you open up the widget you will in the Hierarchy panel that it consists of a **CanvasPanel** and a **RPM Web Browser widget** inside of it.

![img-widget-hierarchy](https://user-images.githubusercontent.com/7085672/163364100-75cc563b-3e78-418f-ab1a-47b79cfabf45.png)

It is set up this way so that the RPM Browser Widgets position, padding and anchor settings can be easily adjusted relative to the Canvas Panel. If you select the `RPM_Browser` object in the hierachy you will most likely need to update the `InitialUrl` setting. This is the Url that will be loaded when this Widget is created/added to the scene.

![img-initial-url](https://user-images.githubusercontent.com/7085672/163363941-bdf5ef85-b3b2-4069-ae23-733282017894.png)

By default we set it to demo.readyplayer.me/avatar however as the name suggests this is only recommended for demo's. we highly recommend you become a Ready Player Me partner and get your own partner space. For example "yourprojectname.readyplayer.me". Once you have your own partner space setup you update this Initial Url accordingly.

We can also set the parameters for the AvatarCreator WebPage. The **CleanCache** provides a Kiosk experience, by selecting the BodyType and Gender we can skip a step when opening the avatar view.

![Screenshot 2022-10-12 105150](https://user-images.githubusercontent.com/108666572/195347112-0f077374-24af-40fc-9887-8806e427f8ef.png)

Next open up the Graph for the Ready Player Me Browser Widget and you will see this network of nodes.

![img-browser-widget-bp](https://user-images.githubusercontent.com/7085672/163359928-7e915cc0-6076-4195-91f8-cda06d7120bb.png)

Lets take at the first group of nodes connected to the widget's construct event. Here bind a custom event to the WebBrowserWidgets `OnUrlChanged` event that runs the `RunBrowserSetup` function. This is done on `OnUrlChanged` to ensure the the browser has actually started loading the website before starting to load the initial Url. Without this there is issues when it comes to injecting custom javascript. Additionaly you can also call `ClearAvatarData` to clear previously created avatar data, to be able to create a new avatar. Lastly we also unbind the event so it doesn't run the setup again.

![img-setup-and-bind](https://user-images.githubusercontent.com/7085672/163365180-1a498452-8f3c-4ec3-b735-d62199ac6817.png)

As you may have noticed the Setup Browser function above has a callback function called Response. To make use of this there is the `AvatarGeneratedCallback` event which will call the `AvatarGeneratedEvent`. The `AvatarGenerated` event it a an Event Dispatcher that can be subscribed to. This was added to make it easy to connect callback functions whenever an avatar has been created. Next we also have a groud of nodes to handle an optional AutoHide feature. If the `HideAfterAvatarGeneration` property is set to true it will automatically hide the widget after character creation is complete.

![img-callback-and-hide](https://user-images.githubusercontent.com/7085672/163376787-073c89ad-bea5-4f6f-9855-62472f9e600b.png)

# Web Link Class

The Web Link class is a simple UObject with the sole purpose of linking Web Browser javascript events back to Unreal engine via a dynamic delegate. By doing this we can listen to specific javascript events inside the Web Browser Widget to trigger functions and receive data from the browser.

The `SetAvatarUrlCallback` function is what we use to assign the callback (delegate) function to be run once the avatar creation process is complete.
```cpp
void UWebLink::SetAvatarUrlCallback(FReadyPlayerWebBrowserResponse WebBrowserCallback)
{
	UWebLink::WebBrowserResponse = WebBrowserCallback;
}
```
The `AvatarGenerated` function is run when the browser event is triggered upon completion of avatar creation. In here we simply check the response is a Ready Player Me avatar url by searching for ".glb", otherwise it exits the function.
```cpp
FString Url = "";
if (JsonResponse.Contains(TEXT(".glb"))) {
  UE_LOG(LogTemp, Warning, TEXT(".glb found "));
  Url = JsonResponse;
}
if (Url.IsEmpty()) {
  return;
}
```
If a Ready Player Me avatar url is found then we run the callback function, passing the `Url` as a parameter. We also store the url in in a `LastAvatarUrl` property in case we need to check it later.
```cpp
UWebLink::WebBrowserResponse.Execute(Url);
LastAvatarUrl = Url;
```

# Ready Player Me Browser Class

This is another rather simple class, based on the` UWebBrowser` class it adds a few extra functions for setting up the connection between the Web Browser and Unreal engine using the Web Link object we covered previously.

To understand how this works we will first look at the ``BindBrowserToObject()`` function.
Initially it creates a UWebLink object, if it doesn't already exist.
Set the name of the link object, this part is important as the **name is used as an ID** when linking back the javascript event.
```cpp
UReadyPlayerMeWebBrowser::WebLinkObject = NewObject<UWebLink>(this, LinkObjectName);
```

Lastly we bind the WebLink object to the browser widget to ensure it's permanantly connected.
```cpp
WebBrowserWidget->BindUObject(LinkObjectName, WebLinkObject, true);
```
Now lets take a look at the ```SetupBrowser(FReadyPlayerWebBrowserResponse WebBrowserCallback)``` function.
To begin it runs the ```BindBrowserToObject``` function mentioned previously.
```cpp
UReadyPlayerMeWebBrowser::BindBrowserToObject();
```
Next we set the callback function (delegate) to be run once creation is complete.
```cpp
WebLinkObject->SetAvatarUrlCallback(WebBrowserCallback);
```
Finally we execute the custom javascript that we use to listen to the website event that fires when the avatar creation process is complete.
```cpp
this->ExecuteJavascript(JavascriptSnippet);
```

## Dependencies
- Ready Player Me Unreal SDK
- glTFRuntime (Third party plugin)

## Links
**Ready Player Me Unreal SDK**
- [Documentation](https://docs.readyplayer.me/ready-player-me/integration-guides/unreal-engine-4)
- [Download](https://docs.readyplayer.me/ready-player-me/integration-guides/unreal-engine-4/unreal-plugin-download)
- [Support](https://docs.readyplayer.me/ready-player-me/integration-guides/unreal-engine-4/troubleshooting)

**glTFRuntime**
- [Documentation](https://github.com/rdeioris/glTFRuntime-docs/blob/master/README.md)
