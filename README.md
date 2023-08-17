# Ready Player Me UE5 Examples

![Screenshot 2022-10-06 141418](https://user-images.githubusercontent.com/108666572/194309906-d7dc5108-2cb4-4005-baf7-b0d88af69c50.png)

This repository contains examples of Ready Player Me integration into Unreal Engine 5 project. This is to serve as a reference for anybody that wants to integrate our 3D avatars into their Unreal Engine project.

# Examples

The examples are located in `Content > ReadyPlayerMe` folder. Each example has dedicated Map and game mode for demonstration.

## Note

The dependency plugins are added as submodules to the project.
They are not automatically clonned when clonning the repository. Use the following command to initialize or update the dependency submodules.
```
git submodule update --init
```

If you are downloading the archive zip file of the project, you need to manually download the dependency plugins(`ReadyPlayerMe, RpmAvatarCreator, glTFRuntime`) and add them to 
the **Plugins** folder.

## Animation Retargeting

![Screenshot 2022-10-06 141418](https://user-images.githubusercontent.com/108666572/194309906-d7dc5108-2cb4-4005-baf7-b0d88af69c50.png)

[**Example**](https://github.com/readyplayerme/UnrealExamples/tree/main/Content/ReadyPlayerMe/AnimationRetargeting#readme)

Example demonstrates the animation retargeting from the UE5 Mannequin to ReadyPlayerMe avatar, and creating a controllable character.

## Runtime Animation Retargeting

![Screenshot 2022-11-29 115934](https://user-images.githubusercontent.com/3124894/204512563-558b6d48-0fcf-433f-aa80-70f4c70f4b03.png)

[**Example**](https://github.com/readyplayerme/UnrealExamples/tree/main/Content/ReadyPlayerMe/RuntimeRetargeting#readme)

Example demonstrates how to use the runtime retargeting to retarget the animations from the Mannequin to the ReadyPlayerMe character. The runtime retargeting can be applied to retarget the animations from any character to the ReadyPlayerMe avatar.

## Custom Avatar Creator

![Screenshot 2023-03-03 165756](https://user-images.githubusercontent.com/3124894/233410933-077ec3c3-c53c-4ed1-b442-3639ed9348f8.png)

[**Example**](https://github.com/readyplayerme/UnrealExamples/tree/main/Content/ReadyPlayerMe/AvatarCreator#readme)

Example demonstrates the use of the Ready Player Me Custom Avatar Creator open-source plugin. The plugin is an in-engine implementation of the web avatar creator.

## Web View

![Screenshot 2022-10-26 121009](https://user-images.githubusercontent.com/108666572/198000086-7771d6a5-70cc-4b39-b087-b0533257d9be.png)

[**Example**](https://github.com/readyplayerme/UnrealExamples/tree/main/Content/ReadyPlayerMe/WebView#readme)

Example demonstrates the use of the Unreal Engine Web Browser module (and Web Browser Widget) to embed the ReadyPlayerMe Web Avatar Creator inside an application to create a seamless integration.

## Multiplayer

![Screenshot 2022-10-26 141117](https://user-images.githubusercontent.com/108666572/198023314-57c84fbc-6221-4cd2-b7df-743eb4485f72.png)

[**Example**](https://github.com/readyplayerme/UnrealExamples/tree/main/Content/ReadyPlayerMe/Multiplayer#readme)

Example demonstrates how to add ReadyPlayerMe avatars to a multiplayer game that requires replication in regards to avatar and mesh loading for multiple game clients.

## Live Link

![Screenshot 2022-10-26 132002](https://user-images.githubusercontent.com/108666572/198013412-b54d087e-7b87-4504-a37d-40f8a53d1edd.png)

[**Example**](https://github.com/readyplayerme/UnrealExamples/tree/main/Content/ReadyPlayerMe/LiveLink#readme)

Example demonstrates how to use the Live Link plugin to apply facial tracking and animations onto a ReadyPlayerMe Avatar.

## In-Engine Rendering

![Screenshot 2023-03-03 165756](https://user-images.githubusercontent.com/3124894/233416253-9843a7ed-c49d-447c-ba84-a99098cd13ec.png)

[**Example**](https://github.com/readyplayerme/UnrealExamples/tree/main/Content/ReadyPlayerMe/InEngineRendering#readme)

Example demonstrates how to render the ReadyPlayerMe avatars in the 2D space, to create images or 2D Animations.

## Avatar Preloading

![Screenshot 2023-03-02 121909](https://user-images.githubusercontent.com/3124894/234279340-ce5b8fce-70e9-47dd-a723-9db9989d83c8.png)

[**Example**](https://github.com/readyplayerme/UnrealExamples/tree/main/Content/ReadyPlayerMe/Preloading#readme)

Example demonstrates how to preload Ready Player Me avatars while showing a loading screen, and spawn number of preloaded avatars instantly.

## Avatar Config

![Screenshot 2023-03-02 121909](https://user-images.githubusercontent.com/3124894/234279340-ce5b8fce-70e9-47dd-a723-9db9989d83c8.png)

[**Example**](https://github.com/readyplayerme/UnrealExamples/tree/main/Content/ReadyPlayerMe/AvatarConfig#readme)

Example demonstrates the avatar config usage. By tweaking the config parameters you can achieve the desired avatar configuration.

## Dependencies
- Ready Player Me Unreal SDK
- Ready Player Me Avatar Creator 
- glTFRuntime (Third party plugin)

## Links
**Ready Player Me Unreal SDK**
- [Documentation](https://docs.readyplayer.me/ready-player-me/integration-guides/unreal-engine-4)
- [Download](https://docs.readyplayer.me/ready-player-me/integration-guides/unreal-engine-4/unreal-plugin-download)
- [Support](https://docs.readyplayer.me/ready-player-me/integration-guides/unreal-engine-4/troubleshooting)

**glTFRuntime**
- [Documentation](https://github.com/rdeioris/glTFRuntime-docs/blob/master/README.md)



