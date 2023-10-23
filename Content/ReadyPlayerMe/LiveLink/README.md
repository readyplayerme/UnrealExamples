# LiveLink Example

![Screenshot 2022-10-26 132002](https://user-images.githubusercontent.com/108666572/198013412-b54d087e-7b87-4504-a37d-40f8a53d1edd.png)

The example demonstrates how to use the LiveLink plugin to apply facial tracking and animations to a Ready Player Me Avatar.

# Dependencies
To enable the LiveLink support for our project, `LiveLink` and `AppleARKitFaceSupport` plugins need to be enabled in the UProject file.

# Quick Start
By default, the `LiveLinkExample` map is loaded on startup and it can be found in the `Content > Maps` folder as below.

The map itself has no custom code or logic in the Level Blueprint. If you already have a compatible Apple device set correctly with the Live Link plugin then you should be able just to click play, wait for an avatar to load, and then you should see the avatar's face animating.

To load a different avatar you can do the following:
- select the actor in the scene named `BP_RPM_LiveLinkActor`
- in the details panel find and select the `ReadyPlayerMeComponent`
- then paste your Ready Player Me Avatar URL (or shortcode) into the field `Url Shortcode`
- make sure you press enter or save the changes

![Screenshot 2022-10-26 131037](https://user-images.githubusercontent.com/108666572/198011602-a09d8dc8-cd19-4c5b-9383-8d695de5a206.png)

Now hit play and this time it should load the new avatar from the URL you provided.

# Animation Blueprint
The animations in the example map are driven by the blueprint `BP_LiveLinkAnim`, which can be found in the `Content > Animations` folder. Let's open it up and take a look at how it works.

## Anim Graph
![Screenshot 2023-10-22 181704](https://github.com/readyplayerme/UnrealExamples/assets/3124894/5ddd8019-396a-4f82-a23e-2448dbe77b4e)

In the AnimGraph window, the first two nodes play the `Breathing_Idle` animation and then we run the `LiveLinkPose` to add the facial tracking blend shapes from ARKit on top.

In the next group of nodes, we apply the head rotation using local yaw, pitch, and roll variables that we will explain in the next section. After modifying the bone transforms we finally connect to the Output Pose so that the animation pose is applied.

## Event Graph
Now let's open the Event Graph, here you can see how we get the head rotation data from the LiveLink plugin. First, we retrieve the data using the Evaluate Live Link Frame node. Then we get the properties for `headYaw`, `headPitch`, and `headRoll` and assign them to the local variables `HeadYaw`, `HeadPitch`, and `HeadRoll`. We created these local variables to store the rotation information for later use in the AnimGraph as mentioned in the previous section.

![Screenshot 2023-10-22 181759](https://github.com/readyplayerme/UnrealExamples/assets/3124894/9f955650-2f0d-449d-ba13-0eed9d5d83ba)

# Livelink Actor

In the LiveLink Actor, we load the avatar and when it's completed, we set the subject name of the LiveLink animation using the `Get Live Link Enabled Subject Names` function.
![Screenshot 2023-10-22 181408](https://github.com/readyplayerme/UnrealExamples/assets/3124894/4ca8c13f-c7e1-426c-975e-328c6845257c)
