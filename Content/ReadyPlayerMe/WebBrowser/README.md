# Web Browser Integration Example

Example uses the Unreal Engine Web Browser module (and Web Browser Widget) to embed the Ready Player Me Web Avatar Creator inside an application to create a seamless integration. 

![Screenshot 2022-10-26 121009](https://user-images.githubusercontent.com/108666572/198000086-7771d6a5-70cc-4b39-b087-b0533257d9be.png)

![Screenshot 2022-10-26 121106](https://user-images.githubusercontent.com/108666572/198000119-79ea06ea-4a12-458d-8c7d-88cf7d7ab208.png)

*NOTE: The Web Browser module will only work with our readyplayer.me website in Unreal Engine 5 on Windows platform. The Web Browser module in Unreal Engine 4 uses a very old version of chromium which does not support all the modern web browser features.*

# Dependencies

To enable the WebBrowser support for our project, WebBrowserWidget plugins need to be enabled in the uproject file.
Additionally to ba able to access it through the C++ code we need to add the followwing modules to our `UnrealExamplesBuild.cs`file `WebBrowserWidget`, `WebBrowser`, `UMG`.

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

Select the RPM_Browser object in the hierachy, in the ReadyPlayerMe category there are several parameters that can be used to generate the initial url of the WebBrowser.
- **Partner Domain**: By default it's set to demo, however as the name suggests this is only recommended for demo's. We highly recommend you become a Ready Player Me partner and get your own partner space. Once you have your own partner space setup you update this parameter accordingly.
- **Clean Cache**: Provides a Kiosk experience
- **Quick Start**: Enters the Quicks Start view.
- **Body Type**: Skip the body type selection step when opening the avatar view.
- **Gender**: Skip the gender selection step when opening the avatar view.
- **Language**: By default the system language will be used for opening the browser, However the language can be customized.

![Screenshot 2022-12-02 173148](https://user-images.githubusercontent.com/3124894/205340278-cc75a168-7813-4e32-bfdb-e44e41f00555.png)

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
