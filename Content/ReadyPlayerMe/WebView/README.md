# WebView Integration Example

Example uses the Ready Player Me WebView plugin to embed the Ready Player Me Web Avatar Creator inside an application to create a seamless integration. 

![Screenshot 2022-10-26 121009](https://user-images.githubusercontent.com/108666572/198000086-7771d6a5-70cc-4b39-b087-b0533257d9be.png)

![Screenshot 2022-10-26 121106](https://user-images.githubusercontent.com/108666572/198000119-79ea06ea-4a12-458d-8c7d-88cf7d7ab208.png)

*NOTE: The WebView plugin will only work with our readyplayer.me website in Unreal Engine 5 on Windows platform. The Web Browser module in Unreal Engine 4 uses a very old version of chromium which does not support all the modern web browser features.*

# Dependencies

We need to add the [Rpm Web View](https://github.com/readyplayerme/rpm-unreal-webview) plugin to our project, the setup steps are described in the readme of the plugin.

# WebView Demo Map

The WebViewDemo map located in the `Content > ReadyPlayerMe > WebView > Maps` folder is a good starting point for anybody wanting to use the WebView plugin to seamlessly integrate our RPM Web Avatar Creator into you game or application.  The logic for this is rather simple, if you open up the Level Blueprint you will see this network of nodes.

For ease of use, we will create a helper widget that will wrap the **RpmWebViewWidget** widget, we will call it `WBP_RPM_WebViewWrapper`.
Inside the WebViewDemo map, we create and add the helper widget to the viewport.
We then subscribe to the **Avatar Generated Event** event to get the URL when the avatar is saved.
Additionally, we change our player character by loading an avatar with this URL afterward.

![Screenshot 2023-03-03 171956](https://github.com/readyplayerme/rpm-unreal-webview/assets/3124894/41d93145-797f-45c0-86df-dc407b1497f0)

# WebView Wrapper Widget

`WBP_RPM_WebViewWrapper` widget is a helper widget, that wraps the **RpmWebViewWidget** widget. It's located in `Content > Widgets`.
The helper widget adds padding to the `RpmWebViewr` widget. It also adds listeners for the `RpmWebView` events.

## Avatar Creator Customization

RpmWebViewWidget widget has properties that can be tweaked to customize the avatar creator. By changing the parameters a custom Url will be generated for the web browser.
- **Partner Domain**: By default it's set to demo, however, as the name suggests this is only recommended for demos. We highly recommend you become a Ready Player Me partner and get your own partner space. Once you have your own partner space setup you update this parameter accordingly.
- **Clean Cache**: Provides a Kiosk experience
- **Quick Start**: Enters the Quick Start view.
- **Body Type**: Skip the body type selection step when opening the avatar view.
- **Gender**: Skip the gender selection step when opening the avatar view.
- **Language**: By default, the system language will be used for opening the browser, however, the language can be customized.

![Screenshot 2022-12-02 173148](https://user-images.githubusercontent.com/3124894/205340278-cc75a168-7813-4e32-bfdb-e44e41f00555.png)

## Subscribe To Events

Further down in the Details panel, you will see a number of events that can be bound to.
These events are called from the **WebView Widget** when certain events occur.
For example, when the avatar creation process has been completed the `OnAvatarExported` event will be called.
This event will return the URL to the GLB file of the avatar. This can then be used to load the avatar into the scene.

![Screenshot 2023-03-13 214725](https://github.com/readyplayerme/rpm-unreal-webview/assets/3124894/ecbf65cc-9231-4816-96c4-8ce1420077e4)

![Screenshot 2023-06-20 141228](https://github.com/readyplayerme/rpm-unreal-webview/assets/3124894/a21d733e-28f0-4f3f-b413-02ac3fb67c5c)

# Ready Player Me WebView Widget Class

The `URpmWebViewWidget` class, is inherited from the Unreal` UWebBrowser` class and it adds a few extra functions for setting up the connection between the Web Browser and **Ready Player Me** website.

It adds delegates for the events that are thrown from the **Ready Player Me** avatar creator web page.
The following delegates are available for subscription:
- OnAvatarExported
- OnUserSet
- OnAssetUnlock
- OnUserAuthorized
