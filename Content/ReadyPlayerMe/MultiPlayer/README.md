# Multiplayer Example

![Screenshot 2022-10-26 141117](https://user-images.githubusercontent.com/108666572/198023314-57c84fbc-6221-4cd2-b7df-743eb4485f72.png)

Example demonstrates demonstrates how to add Ready Player Me avatars to a multiplayer game that requires replication in regards to avatar and mesh loading for multiple game clients.

# Quick Start

The map is located in `Content > ReadyPlayerMe > Multiplayer > Maps`. With the map open click on the three tods next to the Play button and set the `Number of Players` and set `Net Mode` to `Play As Listen Server` as below.

![Screenshot 2022-10-26 134506](https://user-images.githubusercontent.com/108666572/198020307-833db847-3090-409b-aa2b-b6fd2a9c79cf.png)

Now when you hit play you should see 3 instances of that game running with the main editor window acting as a server.

From here you can select a game client window, and press "Q" on the keyboard to display the avatar loader UI widget.

![Screenshot 2022-10-26 134613](https://user-images.githubusercontent.com/108666572/198020361-1c19774c-e066-44a6-b53d-d0c6e945ef93.png)

With that open paste in a Ready Player Me Url (or shortcode) and click load. 

![Screenshot 2022-10-26 134646](https://user-images.githubusercontent.com/108666572/198020498-8035bf22-6d70-4488-9646-149937219f6e.png)

After it has complete the UI widget should close and you should see the avatar loaded into the map on all 3 game clients, updating the appropriate players avatar.

The next sections will look at and explain the logic and blueprint setup used to make this example.

# Avatar Loader widget

![Screenshot 2022-10-26 134727](https://user-images.githubusercontent.com/108666572/198020564-1db68a92-2aa7-44df-beae-5497077d1321.png)

The `AvatarLoaderWidget` is a rather simple widget blueprint used to trigger the loading of a Ready Player Me avatar. If you open up the blueprint Designer tab you will see it has a `Load_Panel` and a `HintPanel`. 

![Screenshot 2022-10-26 134801](https://user-images.githubusercontent.com/108666572/198020660-3b3a892b-c273-4382-84fa-9d2fe2c43558.png)

The load panel has a text input field for entering in a Ready Player Me Avatar Url (or shortcode), an "X" button for closing the panel and a Load button for loading the avatar using the Url provided in the input field.
The `HintPanel`, as the name suggests, simply has some text to tell the player they can display the Load Panel by pressing L on the keyboard.

If you switch to the Graph tab you will see a network of nodes in the Event Graph. Firstly there is a few variables and event dispatches here.

![Screenshot 2022-10-26 134849](https://user-images.githubusercontent.com/108666572/198020787-1a5ac967-de0f-4ffd-aee8-a35bba86bd91.png)

`EditableText_Url` is a reference to the text input field which is needed so that we can get the value entered by the player.
The `HintPanel` and `LoadPanel` references are used to show and hide the panels using the `SetLoaderVisibility` function.

The`SetLoaderVisibilty`, as the name suggests this is just a small network of nodes that is used to show or hide the Hint and Load panels as you can see below.
 
![Screenshot 2022-10-26 134911](https://user-images.githubusercontent.com/108666572/198020899-bd248fd3-b765-4d43-acab-1913ef6597ce.png)

There are 2 event dispatchers `OnLoadUrl` and `OnCloseLoaderPanel`, these are here so that we can run trigger other functions whenever the Load button is clicked or if the close button is clicked.

## Event Graph 

 Inside the Event Graph we can see the `OnClicked(Button_Load)` event that is triggered when the player clicks the Load button. This runs some basic logic to check that the Url in the input field is not empty before calling the OnLoadUrl event.
 
![Screenshot 2022-10-26 134931](https://user-images.githubusercontent.com/108666572/198020992-5544b064-9d92-4814-8900-054d55a61c03.png)

 The` OnClicked(Button_Close)` event is triggered when the close or "X" button is clicked and it simply calls the `OnCloseLoaderPanel` event.

![Screenshot 2022-10-26 134941](https://user-images.githubusercontent.com/108666572/198021037-da358dc3-53e7-463e-a136-089d4bac517f.png)

 # Player Character blueprint

 The `RPM_Character` blueprint located at `Content > ReadyPlayerMe > Blueprints` is a Character blueprint with some added components and functionality. Firstly, it has a `ReadyPlayerMeActor` component much like the `BP_RPM_Actor` provided with our Ready Player Me plugin.

![Screenshot 2022-10-26 135107](https://user-images.githubusercontent.com/108666572/198021112-6ded3295-fc37-4d2a-b6ae-63c9ae9e27df.png)

 It also has 2 extra events used to trigger avatar loading on the server and then on each avatar client using the following network of nodes.

![Screenshot 2022-10-26 135136](https://user-images.githubusercontent.com/108666572/198021160-694231eb-448f-41e6-864d-68450ede99b6.png)

 To get that avatar loading correctly for each player (server and clients), the player that triggers the loading will always call the `LoadAvatarServer` function. So for example Player 2 opens the avatar Loader widget, enters a Url and clicks the "Load" button, this will then call the `LoadAvatarServer` function. Then the server will set the `AvatarUrl` and tell all the clients (everyone but the server) to run `LoadAvatarClient` function, before running the `LoadNewAvatar` function itself.
 
 ## Replication

 To ensure the character updates are replicated too all clients (and server) select the actor root "RPM_Character" and check that the following options are enabled as in the picture below. 
- Always relevant
- Replicate Movement
- Replicates

![Screenshot 2022-10-26 135223](https://user-images.githubusercontent.com/108666572/198021230-a8ca4ea4-f5a7-4e41-8409-a044825e1688.png)

 # Player Controller

 The player controller RPM_PlayerController located at `Content > ReadyPlayerMe > Blueprints` also has some custom properties and functionality added to it.
 
 ## Toggle Loader Function 
 Firstly there is a ToggleLoader function which is used to toggle the AvatarLoaderWidget panels to display either the HintPanel or the LoaderPanel while also updating the input mode and enabling or disabling the input so that the mouse cursor can be used when the Loader panel is displayed. You can see the two groups of nodes below.
 
![Screenshot 2022-10-26 135434](https://user-images.githubusercontent.com/108666572/198021311-eabad073-d8fe-4af7-8e49-95a8d734b2a0.png)

![Screenshot 2022-10-26 135449](https://user-images.githubusercontent.com/108666572/198021330-71544024-2e80-4c22-98c7-577a7e837901.png)

  ## Toggle Loader On Input
 This function is run whenever the Q button is pressed as you will see below from the Event Graph.
 
![Screenshot 2022-10-26 135525](https://user-images.githubusercontent.com/108666572/198021433-25cdad7e-524d-42f9-b516-36c12e118c4c.png)

 The blueprint also has a `AvatarLoaderWidget` variable which we use to store a reference to the AvatarLoaderWidget that we use for loading the avatar. Storing a reference enables us to access the `SetLoaderVisibilty` functions and also bind events to the Event Dispatchers like `OnCloseLoaderPanel` or `OnLoadUrl`.

 ## Create Loader widget
 If you open up the event graph we can see a group of nodes labeled Create Loader Widget. This is run on BeginPlay so that when the Map is loaded it will create the AvatarLoaderWidget, store a reference in the variable mentioned before and also add it to the viewport.
After creating the widget the loader panel is hidden. If you would like to have the Loader panel display when the map is loaded you can remove this part.

![Screenshot 2022-10-26 135614](https://user-images.githubusercontent.com/108666572/198021578-4e80019f-7f20-491e-81b6-944adaa2e694.png)

 ## Bind events to Avatar Loader Widget
 Next we get a reference to the controlled pawn, cast it to an RPM_Character and bind an event to the widgets OnLoadUrl event so that it will run LoadAvatarServer each time the Load button is clicked.
 
![Screenshot 2022-10-26 135716](https://user-images.githubusercontent.com/108666572/198021640-98c67102-2c85-4c62-849a-6e09aa01315e.png)

 Finally we bind an event to the panel close button to hide/show the avatar loader panel as shown below.
 
![Screenshot 2022-10-26 135726](https://user-images.githubusercontent.com/108666572/198021673-46224515-e2cd-4d8d-9ce1-ff7335535af9.png)

