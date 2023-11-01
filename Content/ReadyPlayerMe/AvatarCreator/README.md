# Custom Avatar Creator Integration Example

The example uses the **Custom Avatar Creator** to add the avatar creator widget to the scene. 

![Screenshot 2023-03-03 165756](https://user-images.githubusercontent.com/3124894/233410933-077ec3c3-c53c-4ed1-b442-3639ed9348f8.png)

It is an in-engine version of the web avatar creator. Unlike the [web browser integration](https://github.com/readyplayerme/UnrealExamples/tree/main/Content/ReadyPlayerMe/WebBrowser#readme), custom avatar creator works on all supported platforms and it supports Unreal Engine 4.27 and higher.

## Important

The **AvatarCreator** is currently in the **alpha** stage. We recommend not to use it in production until the stable version is released.

## Avatar Creator Widget Blueprint

The QuickStart map is located in the `Content > ReadyPlayerMe > QuickStart > Maps` folder, it contains a simple logic of adding a wrapper widget **WBP_AvatarCreatorContainer** that contains the avatar creator to the viewport.
The wrapper widget is added to have better control over the avatar creator layout. In this case, we add padding for the avatar creator to have the map visible behind of the widget.

Inside the **WBP_AvatarCreatorContainer** we add the **WBP_AvatarCreator** widget. **WBP_AvatarCreator** widget can be added to any other widget, it can also be added directly to the viewport.

![Screenshot 2023-11-01 125927](https://github.com/readyplayerme/UnrealExamples/assets/3124894/3cd4840d-5b2e-425a-ba2b-4bcc02bbc8a1)

We need to set the customization options for the avatar creator in the properties section.

![Screenshot 2023-11-01 125908](https://github.com/readyplayerme/UnrealExamples/assets/3124894/0f0ac46c-26cb-4e12-9621-483dc354f76f)

### Customization options
- **Select Gender** Allows skipping the gender selection screen
- **Allow Close Button** Hides the close button
- **Allow Webcam** Enables the selfie selection screen if the webcam is available
- **Is Half Body** For creating half body avatars

To be notified when the avatar is saved or selected in the avatar creator, we need to subscribe to the **Avatar Saved** and **Avatar Selected** events. Both of these events will have the avatar URL that we can use afterward.
When the avatar is saved or selected we can close widgets and spawn a new avatar with the avatar URL that was passed through the events.

![Screenshot 2023-11-01 125834](https://github.com/readyplayerme/UnrealExamples/assets/3124894/2c1b26a0-fe95-4b2d-b81d-8142a7fe8f66)

![Screenshot 2023-11-01 125356](https://github.com/readyplayerme/UnrealExamples/assets/3124894/51b36fd4-49d3-4b53-be78-a4078b6efd1c)

To enable the webcam support for your project, you might need to add engine plugins like **Android Camera Player** or **Electra Player**.
