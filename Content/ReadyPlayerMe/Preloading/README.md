# Avatar Preloading Example

![Screenshot 2023-03-02 121909](https://user-images.githubusercontent.com/3124894/234279340-ce5b8fce-70e9-47dd-a723-9db9989d83c8.png)

Example demonstrates how to preload Ready Player Me avatars while showing a loading screen, and spawn preloaded avatars instantly.

Avatar preloading can also be used along with avatar caching, to reduce the preloading time of the cached avatars.

## Preloading Map
The `PreloadingMap` map is located in the `Content > ReadyPlayerMe > Preloading > Maps` folder, it contains the logic of avatar preloading as well as showing the loading widget.
Avatars can be preloaded and spawned on different maps, for simplicity, in this example we preload and spawn the avatars in the same map.

When the map opens we show the loading widget so that the player wouldn't see an empty scene.
While the widget is shown we use the PreloadAsyncAction node to preload all of the avatars, we need to provide the list of avatar IDs, AvatarConfig, and target skeleton parameters.
The preloaded avatars would stay in the runtime memory cache and can be used across different levels. Internally, the lifetime of the preloaded avatars is connected with the game instance.

![Screenshot 2023-11-20 181851](https://github.com/readyplayerme/UnrealExamples/assets/3124894/bac68893-6198-4c9b-b12c-e890681a2dc3)

When the avatars are successfully preloaded we hide the Loading Widget and spawn 100 avatars randomly using the URLs of the preloaded avatars.

![Screenshot 2023-03-03 165756](https://user-images.githubusercontent.com/3124894/234279510-5093de51-b954-45e5-ba12-170c6f76b7e6.png)

Now that we don't need the preloaded avatars in the memory we remove all avatars from the memory by calling the `RemoveAvatarsFromMemory` node.
It's always good to clean the unneeded avatars from the memory to clean up the memory and always have up-to-date avatars.

![Screenshot 2023-11-20 181903](https://github.com/readyplayerme/UnrealExamples/assets/3124894/1efcb644-0b02-4b01-8ac9-ca34fd76d95e)

## Preloaded Actor

The preloaded actor contains a simple logic of loading the avatar when it is spawned, using the provided avatar URL.

![Screenshot 2023-03-02 121909](https://user-images.githubusercontent.com/3124894/233973310-a4f30e63-2bf4-4877-b631-f6e7d77c2acb.png)

**Note:** Avatar Config and Target Skeleton need to be the same, as in the **AvatarPreloadedData** that is used to preload avatars.

## Keep Loaded Avatars In Memory (Optional)

Besides preloading, there is also an option to keep the loaded avatars in memory when loading the avatars from the ReadyPlayerMeComponent component.
To enable this functionality, go to the `project settings > Ready Player Me` and enable the **Keep Loaded Avatars In Memory** checkbox.
