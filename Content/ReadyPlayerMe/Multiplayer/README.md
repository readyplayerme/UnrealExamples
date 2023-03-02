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

After it has complete the UI widget should close and you should see the avatar loaded into the map on all 3 game clients, updating the appropriate players avatar.

## Implementation details

There are two ways of implementing multiplayer functionality.
1. Using `Multicast` execution functions. In this case the multicast function is executed in all the clients.
2. Using `RepNotify` members. In this case all the clients get notified when the replicated member is updated.

In the current example we will use multicast execution functions.

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

## Late joining clients

When the clients are joining the game after all the avatars are loaded, they will not be able to see the loaded avatars, because the LoadAvatarClient would not be called for them. We need to first make the Url variable replicated, so it would be updated when the player joins. In the begin play we need to load the avatar if the url is set.

![Screenshot 2022-11-08 134253](https://user-images.githubusercontent.com/3124894/200618285-17e4f538-4a56-43b5-8f3f-fb72527de5a9.png)

# Player Controller

The player controller RPM_PlayerController located at `Content > ReadyPlayerMe > Blueprints`. It's responsible for toggling the `Hit` and `Loader` widgets as well as loading the avatar when `Load` button is clicked.

## Bind events to Avatar Loader Widget
We get a reference to the controlled pawn, cast it to an RPM_Character and bind an event to the widgets OnLoadUrl event so that it will run LoadAvatarServer each time the Load button is clicked.

![Screenshot 2022-10-26 135716](https://user-images.githubusercontent.com/108666572/198021640-98c67102-2c85-4c62-849a-6e09aa01315e.png)
