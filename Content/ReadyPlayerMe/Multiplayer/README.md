# Multiplayer Example

![Screenshot 2022-10-26 141117](https://user-images.githubusercontent.com/108666572/198023314-57c84fbc-6221-4cd2-b7df-743eb4485f72.png)

Example demonstrates demonstrates how to add Ready Player Me avatars to a multiplayer game that requires replication in regards to avatar and mesh loading for multiple game clients.

# Quick Start

The map is located in `Content > ReadyPlayerMe > Multiplayer > Maps`. With the map open click on the three dots next to the Play button and set the `Number of Players`.

![241892760-493b3906-aede-43e4-ab90-9816d93d4761](https://github.com/readyplayerme/UnrealExamples/assets/3124894/3d43aa99-9651-4baf-adb9-ece25bc356a4)

Now when you hit play you should see 3 instances of that game running.

From here you can select a game client window, and press "Q" on the keyboard to display the session setup UI widget.

![Screenshot_20230224_113524](https://github.com/readyplayerme/UnrealExamples/assets/3124894/38f416e6-2772-42a7-95a7-e998e0b79c1f)

From the session helper widget set avatar urls for each of the game glient. Afterwards create a session from one of the clients by clicking the create button. And from the other clients click the refresh button to see the newly created session and join it.

After creating a session with multiple players and setting avatar urls for each of the client you should see the avatars loaded into the map on all 3 game clients.

## Session Setup

The helper widget `WBP_SessionSetup` allows us to create multiplayer sessions, list all the available sessions and update the player avatar. Will go one by one through the implementations of these functionalities.

When `Create Session` button is clicked, we first destroy previously created session, if there was one.
When this is done we create a session and provide max allowed players to it.
When the session is created we close the popup and open a gameplay level where all the players will join. We need to set the Options parameter to `listen` in the `OpenLevel` node so that the clients would automatically jump to the map.

![Screenshot_20230224_113524](https://github.com/readyplayerme/UnrealExamples/assets/3124894/decfa1cb-0a49-49fc-aac2-e6862f369a15)

As a result, the player as a host of the session will automatically jump into the multiplayer gameplay map.
Unfortunately using only blueprint you will not be able to set the name of the session. This function is only available through C++.

For the clients to be able to see the existing sessions they have to manually check for it by clicking on the `Refresh` button.
When `Refresh` button is clicked we call the we call `Find Sessions` async node to get all the available sessions.
We clear the session list UI and add new list of session info UIs, that contains the info about the session.
We will use `GetServerName`, `GetCurrentPlayers` and `GetMaxPlayers` nodes to get the information about the session.

![Screenshot_20230224_044917](https://github.com/readyplayerme/UnrealExamples/assets/3124894/231c037a-00da-41c5-ac20-03442ce73f19)

When a session is selected from the session list we'll hide the popup, destroy previously created session, if there was one, and join the the selected session using the `JoinSession` node.

![Screenshot_20230221_061652](https://github.com/readyplayerme/UnrealExamples/assets/3124894/ecfefd1c-469e-4eaa-a1a1-bc88cf9668ce)

## Implementation details

There are two ways of implementing multiplayer functionality.
1. Using `Multicast` execution functions. In this case the multicast function is executed in all the clients.
2. Using `RepNotify` members. In this case all the clients get notified when the replicated member is updated.

In the current example we will use RepNotify execution functions.

# Player Character blueprint

The `RPM_Character` blueprint located at `Content > ReadyPlayerMe > Blueprints` is a Character blueprint with some added components and functionality.
Firstly, it has a `ReadyPlayerMe` component much like the `BP_RPM_Actor` provided with our Ready Player Me plugin.

![Screenshot 2022-10-26 135107](https://user-images.githubusercontent.com/108666572/198021112-6ded3295-fc37-4d2a-b6ae-63c9ae9e27df.png)

Here we add a string variable `AvatarUrl` and make it RepNotify. A function `OnRep_AvatarUrl` automatically will be created for it.
This function will be called on every client when the value of the variable gets changed.
Inside of this function we check if the url of the avatar is set and it is not the same as the avatar url for the ReadyPlayerMeComponent.
If the conditions are met, we load new avatar with the updated Url.

![Screenshot_20230224_044917](https://github.com/readyplayerme/UnrealExamples/assets/3124894/546866ca-2101-4d03-9028-61880b86408f)

If the avatar fails to load for a certen client the, the game can not contine for him, he needs to leave the session.
For that we call `DestroySession` node and open the multiplayer level for him.

![Screenshot_20230221_061652](https://github.com/readyplayerme/UnrealExamples/assets/3124894/a1d27ada-647b-47cf-99ce-b3eed7a4e270)

## Replication

To ensure the character updates are replicated to all clients (and server) select the actor root "RPM_Character" and check that the following options are enabled as in the picture below.
- Always relevant
- Replicate Movement
- Replicates

![Screenshot 2022-10-26 135223](https://user-images.githubusercontent.com/108666572/198021230-a8ca4ea4-f5a7-4e41-8409-a044825e1688.png)

# Game Instance

To be able to pass avatar id between different levels we would create a custom game instance `GI_RPM_Instance`.
It's also possible to save the AvatarId in the local storage instead, but in this example we will save the avatar id in the game instance.
We will create a string variable AvatarUrl to be able to use it in different levels.
We will set our game instance to be used in the project settings.

If network errors happen in the multiplayer session, we can catch those errors from  the game instance.
To handle the errors we will add handlers for the events `Event NetworkError` and `Event TravelError`.

# Player Controller

The player controller RPM_PlayerController located at `Content > ReadyPlayerMe > Blueprints`.
It's responsible for toggling the `Hit` and `Loader` widgets as well as loading the avatars for the clients in the multiplayer environment.

When the player changes his avatar we need to first save the new avatar url in the game instance to preserve it between the levels.
Then we want the new url to be loaded in all of the clients, for this we create a function `SetAvatarUrl`, We also change it's `replicates` property to `Execute On Server`.

![Screenshot_20230224_044917](https://github.com/readyplayerme/UnrealExamples/assets/3124894/eb11da88-baf6-4117-b2d5-3fca99c35efa)

This way the function will be executed on server. We will add a Url parameter to it for passing the avatar Url.
The function will simply get the controlled character and set it's replicated `AvatarUrl` property to newly passed url.

![Screenshot_20230224_113524](https://github.com/readyplayerme/UnrealExamples/assets/3124894/72c6a0a6-8af8-490f-822a-c36e624b7a73)

Now we are able to update the avatar at runtime and all of the clients would load the updated avatar.
We also need to add a logic for the case where the client is joining the multiplayer session and he already has AvatarUrl set for his own client in the game instance.
For this we will create a function `SetAvatarLocal` and set it's `replicates` property to `ExecuteOnOwningClient`. This function will execute only on the client that tries to join.
It will get the AvatarUrl from the game instance and call `SetAvatarServer` so that the server would set the url for all the clients.

![Screenshot_20230221_061652](https://github.com/readyplayerme/UnrealExamples/assets/3124894/d98867a5-5b8e-4c7b-a8b0-e8d4fad1ecc7)

Afterwards we will call `SetAvatarLocal` function from OnPossess node. Since OnPossess function is only called on the server, `SetAvatarLocal` function will be called only once on the client that need to set the avatar url.

![Screenshot_20230221_060838](https://github.com/readyplayerme/UnrealExamples/assets/3124894/055ede20-e3a9-4475-960a-6a970a590f13)

# Testing
For easily test the the multiplayer environment, you can run the packaged game on the single computer. You can also test it with a short command line script

```
powershell -Command "& '[Path To UE5]\Engine\Binaries\Win64\UnrealEditor.exe' '[Path To UnrealExamples project]\UnrealExamples.uproject' -Game -Windowed -ResX=800 -ResY=600 -WinX=0 -WinY=20 -Log -Nosteam"
```

# Online Services
While this setup will work fine for testing in the local environment, To be able to use sessions properly in production, you would need to integrate [Epic Online Services](https://docs.unrealengine.com/5.2/en-US/online-subsystem-eos-plugin-in-unreal-engine/) or [Steam Online Services](https://docs.unrealengine.com/5.2/en-US/online-subsystem-steam-interface-in-unreal-engine/).
