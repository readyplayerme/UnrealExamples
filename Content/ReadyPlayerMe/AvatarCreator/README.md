# Custom Avatar Creator Integration Example

Example uses the **Custom Avatar Creator** to add the avatar creator widget to the scene. 

![Screenshot 2023-03-03 165756](https://user-images.githubusercontent.com/3124894/233410933-077ec3c3-c53c-4ed1-b442-3639ed9348f8.png)

It is an in-engine version of the web avatar creator. Unlike the [web browser integration](https://github.com/readyplayerme/UnrealExamples/tree/main/Content/ReadyPlayerMe/WebBrowser#readme), custom avatar creator work on all supported platforms and it supports Unreal Engine 4.27 and higher.

## Important

The **AvatarCreator** is currently in **alpha** stage. We recommend not to use it in the production until the stable version is released.

## Avatar Creator Widget Blueprint

The QuickStart map located in the `Content > ReadyPlayerMe > QuickStart > Maps` folder, it contains a simple logic of adding a wrapper widget **WBP_AvatarCreatorContainer** that contains the avatar creator to the viewport.
The wrapper widget is added to have better control over avatar creator layout. In this case we add padding for the avatar creator to have the map visible behind of the widget.

Inside of the **WBP_AvatarCreatorContainer** we add **WBP_AvatarCreator** widget. **WBP_AvatarCreator** widget can be added to any other widget, it can also be added directly to the viewport.

![Screenshot 2023-03-13 214725](https://user-images.githubusercontent.com/3124894/233412475-9a017528-b625-4b92-af79-8c8fcb66d990.png)

We need to set the customization options for the avatar creator in the properties section.

![Screenshot 2023-03-13 214816](https://user-images.githubusercontent.com/3124894/233412512-138d218d-53f0-488b-aa44-236c0cf04d44.png)

### Customization options
- **Select Gender** Allows skipping the gender selection screen
- **Allow Close Button** Hides the close button
- **Allow Webcam** Enables the selfie selection screen if the webcam is available

In order to be notified when the avatar is saved or selected in the avatar creator, we need to subscribe to the **Avatar Saved** and **Avatar Selected** events. Both of these events will have the avatar URL that we can use afterwards.
When the avatar is saved or selected we can close widgets and spawn a new avatar with the avatar URL that was passed through the events.

![Screenshot 2023-03-13 214725](https://user-images.githubusercontent.com/3124894/233413004-ced8b3ce-fff8-404f-ab96-f8ae613993d6.png)

To enable the webcam support for your project, you might need to add engine plugins like **Android Camera Player** or **Electra Player**.
