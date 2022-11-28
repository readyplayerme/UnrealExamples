# Ready Player Me UE5 Examples

![Screenshot 2022-10-06 141418](https://user-images.githubusercontent.com/108666572/194309906-d7dc5108-2cb4-4005-baf7-b0d88af69c50.png)

This repository contains examples of Ready Player Me integration into Unreal Engine 5 project. This is to serve as a reference for anybody that wants to integrate our 3D avatars into their Unreal Engine project.

# Examples

The examples are located in `Content > ReadyPlayerMe` folder. Each example has dedicated Map and game mode for demonstration.

## Animation Retargeting

![Screenshot 2022-10-06 141418](https://user-images.githubusercontent.com/108666572/194309906-d7dc5108-2cb4-4005-baf7-b0d88af69c50.png)

[**Example**](https://github.com/readyplayerme/UnrealExamples/tree/main/Content/ReadyPlayerMe/AnimationRetargeting#readme)

Example demonstrates the animation retargeting from the UE5 Mannequin to ReadyPlayerMe avatar, and creating a controllable character.

## Runtime Animation Retargeting

![Screenshot 2022-10-10 095350](https://user-images.githubusercontent.com/108666572/194822530-ef52c70e-7e7b-4e2a-95c8-82a16b48770b.png)

[**Example**](https://github.com/readyplayerme/UnrealExamples/tree/main/Content/ReadyPlayerMe/RuntimeRetargeting#readme)

Example demonstrates how to use the runtime retargeting to retarget the animations from the Mannequin to the ReadyPlayerMe character. The runtime retargeting can be applied to retarget the animations from any character to the ReadyPlayerMe avatar.

## Avatar Creator

![Screenshot 2022-10-26 121009](https://user-images.githubusercontent.com/108666572/198000086-7771d6a5-70cc-4b39-b087-b0533257d9be.png)

[**Example**](https://github.com/readyplayerme/UnrealExamples/tree/main/Content/ReadyPlayerMe/WebBrowser#readme)

Example Demonstrates the use of the Unreal Engine Web Browser module (and Web Browser Widget) to embed the ReadyPlayerMe Avatar Creator inside an application to create a seamless integration.

## Multiplayer

![Screenshot 2022-10-26 141117](https://user-images.githubusercontent.com/108666572/198023314-57c84fbc-6221-4cd2-b7df-743eb4485f72.png)

[**Example**](https://github.com/readyplayerme/UnrealExamples/tree/main/Content/ReadyPlayerMe/Multiplayer#readme)

Example demonstrates how to add ReadyPlayerMe avatars to a multiplayer game that requires replication in regards to avatar and mesh loading for multiple game clients.

## Live Link

![Screenshot 2022-10-26 132002](https://user-images.githubusercontent.com/108666572/198013412-b54d087e-7b87-4504-a37d-40f8a53d1edd.png)

[**Example**](https://github.com/readyplayerme/UnrealExamples/tree/main/Content/ReadyPlayerMe/LiveLink#readme)

Example demonstrates how to use the Live Link plugin to apply facial tracking and animations onto a ReadyPlayerMe Avatar.

## In-Engine Rendering

![Screenshot 2022-10-25 230024](https://user-images.githubusercontent.com/108666572/197881399-d36a2f7d-c958-4bb2-be64-c267c2b27c1e.png)

[**Example**](https://github.com/readyplayerme/UnrealExamples/tree/main/Content/ReadyPlayerMe/InEngineRendering#readme)

Example demonstrates how to render the ReadyPlayerMe avatars in the 2D space, to create images or 2D Animations.

## Note

Currently the runtime retargeting doesn't work with the loaded RPM avatars.

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



