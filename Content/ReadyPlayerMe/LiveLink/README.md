# LiveLink Example

![Screenshot 2022-10-26 132002](https://user-images.githubusercontent.com/108666572/198013412-b54d087e-7b87-4504-a37d-40f8a53d1edd.png)

Example demonstrates how to use the LiveLink plugin to apply facial tracking and animations onto a Ready Player Me Avatar.

# Dependencies
To enable the LiveLink support for our project, `LiveLink` and `AppleARKitFaceSupport` plugins need to be enabled in the uproject file.

# Quick Start
By default the `LiveLinkExample` map is loaded on startup and it can be found in the `Content > Maps` folder as below.

The map itself has no custom code or logic in the Level Blueprint. If you already have a compatible Apple device set up correctly with the Live Link plugin then you should be able to just click play, wait for an avatar to load, and then you should see the avatar's face animating.

To load a different avatar you can do the following:
- select the actor in the scene named `BP_RPM_LiveLinkActor`
- in the details panel find and select the `ReadyPlayerMeComponent`
- then paste your Ready Player Me Avatar URL (or shortcode) into the field `Url Shortcode`
- make sure you press enter or save the changes

![Screenshot 2022-10-26 131037](https://user-images.githubusercontent.com/108666572/198011602-a09d8dc8-cd19-4c5b-9383-8d695de5a206.png)

Now hit play and this time it should load the new avatar from the URL you provided.

# Animation Blueprint
The animations in the example map are driven by the blueprint `BP_LiveLinkAnim`, which can be found in the `Content > Animations` folder. Lets open it up and take a look at how it works.

## Anim Graph
![Screenshot 2022-10-26 131231](https://user-images.githubusercontent.com/108666572/198011956-379a6978-ff8d-4f29-9b19-34adda37bc29.png)

In the AnimGraph window, the first two nodes simply play the `Breathing_Idle` animation and then we run the `LiveLinkPose` to add the facial tracking blendshapes from ARKit on top.

In the next group of nodes we apply the head rotation using local yaw, pitch, roll variables that we will explain in the next section. After modifying the bone transforms we finally connect to the Output Pose so that the animation pose is applied.

## Event Graph
Now lets open the Event Graph, here you can see how we get the head rotation data from the LiveLink plugin. First we retrieve the data using the Evaluate Live Link Frame node. Then we get the property for `headYaw`, `headPitch`, `headRoll` and assign them to the local variables `HeadYaw`, `HeadPitch`, `HeadRoll`. We created these local variables so that we can store the rotation information to later use it in the AnimGraph as mentioned in the previous section.

![Screenshot 2022-10-26 131559](https://user-images.githubusercontent.com/108666572/198012545-c0ac9e8d-65cb-48da-a80e-254d4f61ad24.png)

## Livelink Actor

In the LiveLink Actor we add a ReadyPlayerMe Component. For the AvatarConfig property of the component we set a custom avatar config that contains ARKit MorphTargetGroup.
This way the loaded avatar will have the ARKit MorphTargets that we can use for the facial animations.
We load an avatar using the ReadyPlayerMe component, and when it's completed, we set the subject name of the Livelink animation using `Get Live Link Enabled Subject Names` function.

## Built Application

For the LiveLink to work on the built application, make sure you run the application with the **-messaging** command line argument.
