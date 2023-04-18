# Custom Avatar Creator Integration Example

Example uses the open-source **Custom Avatar Creator** plugin to add the avatar creator widget to the scene. 

![Screenshot 2022-10-26 121009](https://user-images.githubusercontent.com/108666572/198000086-7771d6a5-70cc-4b39-b087-b0533257d9be.png)

It is an in-engine version of the web avatar creator. Unlike the [web browser integration](https://github.com/readyplayerme/UnrealExamples/tree/main/Content/ReadyPlayerMe/WebBrowser#readme), custom avatar creator work on all supported platforms and it supports Unreal Engine 4.27 and higher.

# Dependencies

We need to add the [Custom Avatar Creator](https://github.com/readyplayerme/rpm-unreal-avatar-creator) plugin to our project, the setup steps are described in the readme of the plugin.
To enable the webcam support for your project, you might need to add engine plugins like **Android Camera Player** or **Electra Player**.

# Avatar Creator Demo Map

The AvatarCreatorDemo map located in the `Content > ReadyPlayerMe > AvatarCreator > Maps` folder, it contains a simple logic of adding a wrapper widget **WBP_AvatarCreatorContainer** that contains the avatar creator to the viewport.
The wrapper widget is added to have better control over avatar creator layout. In this case we add padding for the avatar creator to have the map visible behind of the widget.

# Avatar Creator Widget Blueprint

Inside of the **WBP_AvatarCreatorContainer** we add **WBP_AvatarCreator** widget. **WBP_AvatarCreator** widget can be added to any other widget, it can also be added directly to the viewport.

![img-widget-hierarchy](https://user-images.githubusercontent.com/7085672/163364100-75cc563b-3e78-418f-ab1a-47b79cfabf45.png)

We need to set the customization options for the avatar creator in the properties section.

![img-widget-hierarchy](https://user-images.githubusercontent.com/7085672/163364100-75cc563b-3e78-418f-ab1a-47b79cfabf45.png)

### Customization options
- **Partner Domain** Specify your partner domain
- **Select Body Type** Allows skipping the body type selection screen
- **Select Gender** Allows skipping the gender selection screen
- **Allow Close Button** Hides the close button
- **Allow Webcam** Enables the selfie selection screen if the webcam is available
- **Default Avatar Ids** Specify the avatar ids that will be shown on the **Pick An Avatar** page. **Important** this field needs to be filled with the avatar ids from the demo map.

In order to be notified when the avatar is saved or selected in the avatar creator, we need to subscribe to the **Avatar Saved** and **Avatar Selected** events. Both of these events will have the avatar URL that we can use afterwards.
When the avatar is saved or selected we can close widgets and spawn a new avatar with the avatar URL that was passed through the events.

![Screenshot_20230221_060932](https://user-images.githubusercontent.com/3124894/229149539-1ae0e7a5-c9ae-4671-b6e1-e267e14fd204.png)
