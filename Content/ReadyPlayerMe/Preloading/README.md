# Avatar Preloading Example

![Screenshot 2023-03-02 121909](https://user-images.githubusercontent.com/3124894/234279340-ce5b8fce-70e9-47dd-a723-9db9989d83c8.png)

Example demonstrates how to preload Ready Player Me avatars while showing a loading screen, and spawn number of preloaded avatars instantly.

Avatar preloading can also be used along with avatar caching, for reducing preloading time of the cached avatars.

# Preloading Map
The `PreloadingMap` map located in the `Content > ReadyPlayerMe > Preloading > Maps` folder, it contains the logic of avatar preloading as well as showing loading widget.
Avatars can be preloaded and spawned in different maps, for the simplicity, in this example we preload and spawn the avatars in the same map.

When the map opens we show the loading widget so that the player wouldn't see an empty scene.
While the widget is shown we iterate through all the avatar URLs that we want to load and make PreloadDataArray using the URLs.

![Screenshot 2023-03-03 165756](https://user-images.githubusercontent.com/3124894/233972967-c64f65fb-e16f-4686-bb5b-105921dfcbff.png)

We preload the avatars by calling Preload function of the Memory Cache class. The Memory Cache is shared and can be accessed through the ReadyPlayerMeSubsystem.
When the avatars are successfully preloaded we hide the Loading Widget and spawn 100 avatars randomly using the URLs of the preloaded avatars.

![Screenshot 2023-03-02 121909](https://user-images.githubusercontent.com/3124894/233973041-571a4226-80c2-4255-b19b-918900a31354.png)

![Screenshot 2023-03-03 165756](https://user-images.githubusercontent.com/3124894/234279510-5093de51-b954-45e5-ba12-170c6f76b7e6.png)

Now that we don't need the preloaded avatars in the memory cache we clean the Memory Cache. It's always good to clean the unneeded avatars from the memory cache to clean up the memory and always have up-to-date avatars.

![Screenshot 2023-03-13 214816](https://user-images.githubusercontent.com/3124894/233973161-350e6bb6-f50d-4e04-b201-100245cf528b.png)

# Preloaded Actor

Preloaded actor contains a simple logic of loading the avatar when it is spawned, using the provided avatar URL.

![Screenshot 2023-03-02 121909](https://user-images.githubusercontent.com/3124894/233973310-a4f30e63-2bf4-4877-b631-f6e7d77c2acb.png)

For the actor to be able to use the memory cache we need to enable **Use Memory Cache** checkbox in the **ReadyPlayeMeComponent**.

![Screenshot 2023-03-02 121909](https://user-images.githubusercontent.com/3124894/233977455-57a9323b-917c-4173-99cc-4024078d7fa1.png)

**Note:** Avatar Config and Target Skeleton need to be the same, as in the **AvatarPreloadedData** that is used to preload avatars.
