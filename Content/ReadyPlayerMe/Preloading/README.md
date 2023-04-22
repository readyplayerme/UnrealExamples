# Avatar Preloading Example

![Screenshot 2022-10-26 132002](https://user-images.githubusercontent.com/108666572/198013412-b54d087e-7b87-4504-a37d-40f8a53d1edd.png)

Example demonstrates how to preload Ready Player Me avatars while showing a loading screen, and spawn number of preloaded avatars instantly.

# Preloading Map
The `PreloadingMap` map located in the `Content > ReadyPlayerMe > Preloading > Maps` folder, it contains the logic of avatar preloading as well as showing loading widget.
Avatars can be preloaded and spawned in different maps, for the simplicity, in this example we preload and spawn the avatars in the same map.

When the map opens we show the loading widget so that the player wouldn't see an empty scene.
While the widget is shown we iterate through all the avatar URLs that we want to load and make PreloadDataArray using the URLs.

![Screenshot 2022-10-26 131037](https://user-images.githubusercontent.com/108666572/198011602-a09d8dc8-cd19-4c5b-9383-8d695de5a206.png)

We preload the avatars by calling Preload function of the Memory Cache class. The Memory Cache is shared and can be accessed through the ReadyPlayerMeSubsystem.
When the avatars are successfully preloaded we hide the Loading Widget and spawn 500 avatars randomly using the URLs of the preloaded avatars.

![Screenshot 2022-10-26 131037](https://user-images.githubusercontent.com/108666572/198011602-a09d8dc8-cd19-4c5b-9383-8d695de5a206.png)

Now that we don't need the preloaded avatars in the memory cache we clean the Memory Cache. It's always good to clean the unneeded avatars from the memory cache to clean up the memory and always have up-to-date avatars.

![Screenshot 2022-10-26 131037](https://user-images.githubusercontent.com/108666572/198011602-a09d8dc8-cd19-4c5b-9383-8d695de5a206.png)

# Preloaded Actor

Preloaded actor contains a simple logic of loading the avatar when it is spawned, using the provided avatar URL.

![Screenshot 2022-10-26 131037](https://user-images.githubusercontent.com/108666572/198011602-a09d8dc8-cd19-4c5b-9383-8d695de5a206.png)
