# Ready Player Me WebView

![Screenshot 2022-10-26 121009](https://user-images.githubusercontent.com/108666572/198000086-7771d6a5-70cc-4b39-b087-b0533257d9be.png)

Ready Player Me WebView is an extension to www.readyplayer.me avatar platform, which helps you to open an integrated web browser at runtime.

RpmWebView plugin uses the Unreal Engine Web Browser module (and Web Browser Widget) to embed the Ready Player Me Web Avatar Creator inside an application.

Please visit the online documentation and join our public `discord` community.

![](https://i.imgur.com/zGamwPM.png) **[Online Documentation]( https://docs.readyplayer.me/ready-player-me/integration-guides/unreal-sdk )**

![](https://i.imgur.com/FgbNsPN.png) **[Discord Channel]( https://discord.gg/9veRUu2 )**

## Constraints

**NOTE:** The WebView plugin will only work with our readyplayer.me website in Unreal Engine 5 on the Windows platform. The Web Browser module in Unreal Engine 4 uses a very old version of Chromium which does not support all the modern web browser features.

### Known Issues
- there is an issue that prevents the mouse interactions from working correctly on some windows machines when running in the application in fullscreen. It seems to be a limitation with the Web Browser plugin itself. 

## Requirements

- Unreal Engine Version 5.0 or higher

## Integration

### Add RpmWebView plugin

There are three ways you can add the **RpmAvatarCreator** plugin to your project. Add as submodules, paste the plugin inside of the **Plugins** folder, or add the blueprint version of the plugin to the Engine.

- To add the plugin to your project as a submodule, run the following command in the terminal from your project folder. This is the preferred way of setting up the plugin.

  ```
   git submodule add --name Plugins/RpmWebView -- https://github.com/readyplayerme/rpm-unreal-webview.git Plugins/RpmWebView
  ```

- To clone the plugin into your project, run the following command in the terminal from your project folder.

- To paste the plugin inside of the Plugins folder, create a **Plugins** folder from the root of your project, and download the latest tags of the [RpmWebView](https://github.com/readyplayerme/rpm-unreal-webview.git) plugin into it. Rename the **rpm-unreal-webview** plugin folder to the **RpmWebView**.

- To add the blueprint version of the plugin, find the plugin attached in the [Latest Release](https://github.com/readyplayerme/rpm-unreal-webview/releases/latest), add it to the Plugins/Runtime folder of the installed Unreal Engine.

### Update RpmWebView plugin submodule

To update the plugin submodule paste the following command in the terminal from your project folder. This will fetch and switch the plugin repositories to the latest stable release.

  ```
  cd Plugins/RpmWebView ; git fetch --tags ; git checkout $(git describe --tags $(git rev-list --tags --max-count=1)) ; cd ../..
  ```

## Quick Start

A demo map is included in the plugin for demonstrating how the **WebView** opens at runtime. It is located in the `RpmWebView\Content\Maps` folder.
The webview will not run properly until the **Subdomain** of your application is set in the project settings. You can find them in [**Ready Player Me Studio**](https://studio.readyplayer.me/signin) website.
The **Subdomain** should belong to the same application otherwise the webview will fail.
To add the `RpmWebView` to your project simply copy the existing blueprint logic from the demo map into your project.

**RpmWebViewWidget** is a widget that can be added to a map or another widget.
For ease of use, we will create a helper widget that will wrap the **RpmWebViewWidget** widget.
Inside the WebViewDemo map, we create and add the helper widget to the viewport.
**RpmWebViewWidget** can be customized by providing default values when the widget is created.
We need to subscribe to the **Avatar Generated Event** event to get the URL when the avatar is saved.
Additionally, we can load an avatar with this URL afterward.

![Screenshot 2023-03-03 171956](https://github.com/readyplayerme/rpm-unreal-webview/assets/3124894/41d93145-797f-45c0-86df-dc407b1497f0)

# WebView Wrapper Widget

`WBP_RPM_WebViewWrapper` widget is a helper widget, that wraps the **RpmWebViewWidget** widget. It's located in `Content > Widgets`.
The helper widget adds padding to the `RpmWebView` widget. It also adds listeners for the `RpmWebView` events.

## Avatar Creator Customization

RpmWebViewWidget widget has properties that can be tweaked to customize the avatar creator. Changing the parameters will generate a custom Url for the web browser.
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

The `URpmWebViewWidget` class, is inherited from the Unreal` UWebBrowser` class and it adds a few extra functions for setting up the connection between the Web Browser and the **Ready Player Me** website.

It adds delegates for the events that are thrown from the **Ready Player Me** avatar creator web page.
The following delegates are available for subscription: 
- OnAvatarExported
- OnUserSet
- OnAssetUnlock
- OnUserAuthorized

## Links
- [Documentation](https://docs.readyplayer.me/ready-player-me/integration-guides/unreal-engine)
- [Support](https://docs.readyplayer.me/ready-player-me/integration-guides/unreal-engine/troubleshooting)
