# Avatar Preloading Example

![Screenshot 2023-03-02 121909](https://user-images.githubusercontent.com/3124894/234279340-ce5b8fce-70e9-47dd-a723-9db9989d83c8.png)

Example demonstrates how to preload Ready Player Me avatars while showing a loading screen, and spawn number of preloaded avatars instantly.

Avatar preloading can also be used along with avatar caching, for reducing preloading time of the cached avatars.

## Preloading Map
The `PreloadingMap` map located in the `Content > ReadyPlayerMe > Preloading > Maps` folder, it contains the logic of avatar preloading as well as showing loading widget.
Avatars can be preloaded and spawned in different maps, for the simplicity, in this example we preload and spawn the avatars in the same map.

When the map opens we show the loading widget so that the player wouldn't see an empty scene.
While the widget is shown we use the PreloadAsyncAction node to preload all of the avatars, we need to provide the list of avatar Ids, AvatarConfig and target skeleton parameters.
The preloaded avatars would stay in the runtime memory cache and can be used across different levels. Internally, the lifetime of the preloaded avatars is connected with the game instance.

![Screenshot 2023-03-03 165756](https://user-images.githubusercontent.com/3124894/233972967-c64f65fb-e16f-4686-bb5b-105921dfcbff.png)

When the avatars are successfully preloaded we hide the Loading Widget and spawn 100 avatars randomly using the URLs of the preloaded avatars.

![Screenshot 2023-03-03 165756](https://user-images.githubusercontent.com/3124894/234279510-5093de51-b954-45e5-ba12-170c6f76b7e6.png)

Now that we don't need the preloaded avatars in the memory we remove all avatars from the memory by calling `RemoveAvatarsFromMemory` node.
It's always good to clean the unneeded avatars from the memory to clean up the the memory and always have up-to-date avatars.

![Screenshot 2023-03-13 214816](https://user-images.githubusercontent.com/3124894/233973161-350e6bb6-f50d-4e04-b201-100245cf528b.png)

## Preloaded Actor

Preloaded actor contains a simple logic of loading the avatar when it is spawned, using the provided avatar URL.

![Screenshot 2023-03-02 121909](https://user-images.githubusercontent.com/3124894/233973310-a4f30e63-2bf4-4877-b631-f6e7d77c2acb.png)

**Note:** Avatar Config and Target Skeleton need to be the same, as in the **AvatarPreloadedData** that is used to preload avatars.

## Keep Loaded Avatars In Memory (Optional)

Besides preloading, there is also an option to keep the loaded avatars in memory when loading the avatars from the ReadyPlayerMeComponent component.
To enable this functionality, go to the `project settings > Ready Player Me` and enable the **Keep Loaded Avatars In Memory** checkbox.
