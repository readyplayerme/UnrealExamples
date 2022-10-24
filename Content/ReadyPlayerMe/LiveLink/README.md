# Ready Player Me UE4 Live Link Example

![img-livelink-sample](https://user-images.githubusercontent.com/7085672/164030100-8063b64f-2162-4abf-a642-0193964ab04c.png)

This repository contains an Unreal Engine 4 sample project demonstrates how to use the Live Link plugin to apply facial tracking and animations onto a Ready Player Me Avatar.

# Quick Start
By default the `LiveLinkExample` map is loaded on startup and it can be found in the `Content > Maps` folder as below.

The map itself has no custom code or logic in the Level Blueprint. If you already have a compatible Apple device setup correctly with the Live Link plugin then you should be able to just click play, wait for an avatar to load and then you should see the avatar's face animating.

To load a different avatar you can do the following:
- select the actor in the scene named `BP_LiveLink`
- in the details panel find and select the `ReadyPlayerMeComponent`
- then paste your Ready Player Me Avatar URL (or shortcode) into the field `Url Shortcode`
- make sure you press enter or save the changes

![img-live-link-actor](https://user-images.githubusercontent.com/7085672/164033730-15220078-1597-49dd-9c40-d5e8b5410398.png)

Now hit play and this time it should load the new avatar from the URL you provided.

# Animation Blueprint
The animations in the example map are driven by the blueprint `BP_LiveLinkAnim`, which can be found in the `Content > Animations` folder. Lets open it up and take a look at how it works.

## Anim Graph
![img-anim-graph](https://user-images.githubusercontent.com/7085672/164032665-9ed72dbb-730f-4e02-8fad-e9d9558b8afb.png)

In the AnimGraph window, the first two nodes simply play the `Breathing_Idle` animation and then we run the `LiveLinkPose` to add the facial tracking blendshapes from ARKit on top.

![img-animation-nodes](https://user-images.githubusercontent.com/7085672/164032698-948d1a7e-e721-482a-ab96-dc931f174268.png)

In the next group of nodes we apply the head rotation using local yaw, pitch, roll variables that we will explain in the next section. After modifying the bone transforms we finally connect to the Output Pose so that the animation pose is applied.

![img-apply-rotation](https://user-images.githubusercontent.com/7085672/164032756-9c2f4cad-f96d-405d-9a65-77b2c147149d.png)

## Event Graph
Now lets open the Event Graph, here you can see how we get the head rotation data from the LiveLink plugin. First we retrieve the data using the Evaluate Live Link Frame node. Then we get the property for `headYaw`, `headPitch`, `headRoll` and assign them to the local variables `HeadYaw`, `HeadPitch`, `HeadRoll`. We created these local variables so that we can store the rotation information to later use it in the AnimGraph as mentioned in the previous section.

![img-head-rotation](https://user-images.githubusercontent.com/7085672/164033094-d5300322-fec4-4175-8fab-af54ce032078.png)

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
