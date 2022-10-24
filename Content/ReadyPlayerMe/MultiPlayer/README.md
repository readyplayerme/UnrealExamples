# Ready Player Me UE4 Multiplayer Example

![img-multiplayer](https://user-images.githubusercontent.com/7085672/164045214-41aebb0a-671f-4dd4-b62b-9ba783819372.png)

This repository contains an Unreal Engine 4 example project that demonstrates how to add Ready Player Me avatars to a multiplayer game that requires replication in regards to avatar and mesh loading for multiple game clients.

# Quick Start

By default the project should open the ThirdPersonExampleMap when you open up the project. If not you can find it in `Content > ReadyPlayerMe > Maps`. With the map open click on the small arrow next to the Play button and set the `Number of Players` and set `Net Mode = Play As Listen Server` as below.

![img-play-settings](https://user-images.githubusercontent.com/7085672/164045622-92d4efa3-a9d1-4a95-9ea2-fe7286e22585.png)

Now when you hit play you should see 3 instances of that game running with the main editor window acting as a server.

From here you can select a game client window, and press "Q" on the keyboard to display the avatar loader UI widget.

![image](https://user-images.githubusercontent.com/7085672/164045907-2ea13f81-8124-464f-819d-ff4482bea6e9.png)

With that open paste in a Ready Player Me Url (or shortcode) and click load. 

![img-copy-url](https://user-images.githubusercontent.com/7085672/164046060-115a00ce-6759-444e-b4cc-467972d2d1e7.png)
After it has complete the UI widget should close and you should see the avatar loaded into the map on all 3 game clients, updating the appropriate players avatar.

The next sections will look at and explain the logic and blueprint setup used to make this example.

# Avatar Loader widget

![img-canvas-panel](https://user-images.githubusercontent.com/7085672/164046596-12ea1285-2936-40d0-bc38-c1d1e8c2f31f.png)

The `AvatarLoaderWidget` is a rather simple widget blueprint used to trigger the loading of a Ready Player Me avatar. If you open up the blueprint Designer tab you will see it has a `Load_Panel` and a `HintPanel`. 

![img-hierarchy](https://user-images.githubusercontent.com/7085672/164046632-d3fb352f-2ecc-4be3-aa05-b2e73341716c.png)

The load panel has a text input field for entering in a Ready Player Me Avatar Url (or shortcode), an "X" button for closing the panel and a Load button for loading the avatar using the Url provided in the input field.
The `HintPanel`, as the name suggests, simply has some text to tell the player they can display the Load Panel by pressing L on the keyboard.

If you switch to the Graph tab you will see a network of nodes in the Event Graph. Firstly there is a few variables and event dispatches here.

![img-widget-properties](https://user-images.githubusercontent.com/7085672/164046959-b68ca721-c66e-4465-b17c-beb060c55743.png)

`EditableText_Url` is a reference to the text input field which is needed so that we can get the value entered by the player.
The `HintPanel` and `LoadPanel` references are used to show and hide the panels using the `SetLoaderVisibility` function.

The`SetLoaderVisibilty`, as the name suggests this is just a small network of nodes that is used to show or hide the Hint and Load panels as you can see below.
 
 ![img-set-loader](https://user-images.githubusercontent.com/7085672/164048021-f6d7a890-7500-44c3-b3e9-ac5cc6d894eb.png)

There are 2 event dispatchers `OnLoadUrl` and `OnCloseLoaderPanel`, these are here so that we can run trigger other functions whenever the Load button is clicked or if the close button is clicked.

## Event Graph 

 Inside the Event Graph we can see the `OnClicked(Button_Load)` event that is triggered when the player clicks the Load button. This runs some basic logic to check that the Url in the input field is not empty before calling the OnLoadUrl event.
 
 ![img-button-load-1](https://user-images.githubusercontent.com/108666572/186247816-158eb922-ad13-49cb-a6f4-52acdee1cd7a.png)

 The` OnClicked(Button_Close)` event is triggered when the close or "X" button is clicked and it simply calls the `OnCloseLoaderPanel` event.
 
 ![img-button-close](https://user-images.githubusercontent.com/7085672/164047910-379406a6-e65f-4718-af5a-83316f5e2e77.png)

 # Player Character blueprint

 The `RPM_Character` blueprint located at `Content > ReadyPlayerMe > Blueprints` is a Character blueprint with some added components and functionality. Firstly, it has a `ReadyPlayerMeActor` component much like the `BP_RPM_Actor` provided with our Ready Player Me plugin.

![img-components](https://user-images.githubusercontent.com/7085672/164048675-520671a4-22c9-47d6-bdf4-6f156f424239.png)

 It also has 2 extra events used to trigger avatar loading on the server and then on each avatar client using the following network of nodes.

![img-character-event-graph](https://user-images.githubusercontent.com/7085672/164048749-4278f4bd-5011-4fe3-b210-e993460a73a0.png)

 To get that avatar loading correctly for each player (server and clients), the player that triggers the loading will always call the `LoadAvatarServer` function. So for example Player 2 opens the avatar Loader widget, enters a Url and clicks the "Load" button, this will then call the `LoadAvatarServer` function. Then the server will set the `AvatarUrl` and tell all the clients (everyone but the server) to run `LoadAvatarClient` function, before running the `LoadNewAvatar` function itself.
 
 ## Replication

 To ensure the character updates are replicated too all clients (and server) select the actor root "RPM_Character" and check that the following options are enabled as in the picture below. 
- Always relevant
- Replicate Movement
- Replicates

![img-replication](https://user-images.githubusercontent.com/7085672/164052398-49531d1e-9d02-49ae-a772-5bb5e6e1e071.png)

 # Player Controller

 The player controller RPM_PlayerController located at `Content > ReadyPlayerMe > Blueprints` also has some custom properties and functionality added to it.
 
 ## Toggle Loader Function 
 Firstly there is a ToggleLoader function which is used to toggle the AvatarLoaderWidget panels to display either the HintPanel or the LoaderPanel while also updating the input mode and enabling or disabling the input so that the mouse cursor can be used when the Loader panel is displayed. You can see the two groups of nodes below.
 
 ![img-set-visibility](https://user-images.githubusercontent.com/7085672/164051612-412c2bfe-cda9-49dc-a617-1e50c184ced0.png)

 ![img-set-input](https://user-images.githubusercontent.com/7085672/164051629-6e36ace7-733e-45b2-a94d-9098de25c652.png)

  ## Toggle Loader On Input
 This function is run whenever the Q button is pressed as you will see below from the Event Graph.
 
![img-input-toggle](https://user-images.githubusercontent.com/7085672/164051035-4c3b5d57-17e0-475f-8251-1298b11ac728.png)

 The blueprint also has a `AvatarLoaderWidget` variable which we use to store a reference to the AvatarLoaderWidget that we use for loading the avatar. Storing a reference enables us to access the `SetLoaderVisibilty` functions and also bind events to the Event Dispatchers like `OnCloseLoaderPanel` or `OnLoadUrl`.

 ## Create Loader widget
 If you open up the event graph we can see a group of nodes labeled Create Loader Widget. This is run on BeginPlay so that when the Map is loaded it will create the AvatarLoaderWidget, store a reference in the variable mentioned before and also add it to the viewport.
 
![img-create-loader-widget](https://user-images.githubusercontent.com/7085672/164050999-4ad45722-15ad-432f-a65f-5256ba9c27a4.png)

 ## Hide Panel On startup
After creating the widget the loader panel is hidden. If you would like to have the Loader panel display when the map is loaded you can remove this.

![hide-panel-on-start](https://user-images.githubusercontent.com/7085672/164051193-93dcd30a-47db-46b9-ac71-c4bb483926a3.png)

 ## Bind events to Avatar Loader Widget
 Next we get a reference to the controlled pawn, cast it to an RPM_Character and bind an event to the widgets OnLoadUrl event so that it will run LoadAvatarServer each time the Load button is clicked.
 
![img-bind-load](https://user-images.githubusercontent.com/7085672/164051099-0ec1c1f1-86fe-4c5c-b9ea-d9aae163f1f4.png)

 Finally we bind an event to the panel close button to hide/show the avatar loader panel as shown below.
 
![img-bind-close](https://user-images.githubusercontent.com/7085672/164051116-e94acdeb-5c80-4519-bf2b-524f6ab7a02e.png)

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
 


