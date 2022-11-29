# Runtime Animation Retargeting Example

![Screenshot 2022-11-29 115901](https://user-images.githubusercontent.com/3124894/204512386-db962d1b-9f2c-4fff-8ce4-44f76569935b.png)

Example demonstrates how to use the runtime retargeting to retarget the animations from the Mannequin to the ReadyPlayerMe character. The runtime retargeting can be applied to retarget the animations from any character to the ReadyPlayerMe avatar.

# Use cases

Runtime retargeting comes with some performance overhead. Another downside is that two meshes will be places on the scene for a single avatar, even though one of them will never be visible.
It is very easy to use, since no new animations need to be created. It solves the IK issues between the incompatible skeletons.
For prototyping, runtime retargeting will save some development time.

# Map

By default the `RuntimeRetargetingMap` map can be found in the `Content > ReadyPlayerMe > RuntimeRetargeting > Maps` folder.

# Animation Blueprint

The runtime retargeting is done inside of the animation blueprint.
For owr character we create an animation blueprint and set the base skeleton to the `RPM_Mixamo_Skeleton`.
To be able to retarget the animations from the UE5 Manny to the RPM_FullBody avatar we need to creat an IKRetargeter. For more info about how to creat an IKRig and IKRetargeter, you can check [here](https://github.com/readyplayerme/UnrealExamples/tree/main/Content/ReadyPlayerMe/AnimationRetargeting#how-to-retarget-animations).

When the retargeter is ready we create a `Retarget Pose From Mesh` node and connect it to the output pose. We need to set the `IKRetargeter Asset` to the `RTG_UE5_Manny_RPM_FullBody`. We also need to make sure that `Use Attached Parent` checkbox is checked, this way the retargeting will be done from the parent(Manny) to the child(RPM) object.

![Screenshot 2022-11-28 182840](https://user-images.githubusercontent.com/3124894/204368902-10f2aac3-5dc3-4288-b74f-63558e3574c8.png)

![Screenshot 2022-11-28 182921](https://user-images.githubusercontent.com/3124894/204368935-ec2df095-7c7e-4f1c-9468-26428648bde8.png)

# Character Blueprint

You can find our character blueprint named `BP_RPM_RuntimeCharacter` in the projects `Content > ReadyPlayerMe > RuntimeRetargeting > Blueprints` folder.
The game mode for this example uses this character blueprint to as a `Default Pawn Class`.

The character was created by duplicating the example Unreal Third Person Character blueprint (that uses mannequin skeleton and mesh).

We add another skeletal mesh component as a child of the Manny skeletal mesh component. The movement of the character will be handled by the UE5 Mannequin, our character will follow the movements of the Mannequin.

![Screenshot 2022-11-28 182227](https://user-images.githubusercontent.com/3124894/204370248-0fc256b2-c166-4806-8d2f-c9f9ec173dc1.png)

We set custom animation blueprint to the newly created RpmSkeletalMesh component. The animation blueprint will runtime retarget the animations from the Manny to the RPM using animation retargeter.

Inside of the Blueprint in `BeginPlay` we override the skeletal mesh component of the ReadyPlayerMe component. This way at runtime the avatar mesh will be set to the newly created `RpmSkeletalMesh` component.

Now in `BeginPlay` we load the avatar. The `SkeletalMesh` of the `RpmSkeletalMesh` component should not be set, otherwise the animations will break after the avatar is loaded.

![Screenshot 2022-11-28 182156](https://user-images.githubusercontent.com/3124894/204370152-dd73e8c5-5900-445b-9c4d-4f5b1783ffcd.png)

When running the game we will see that two meshes are shown on top of each other, RPM and the Manny. We need to hide the Manny, uncheck the `Visible` checkbox of the Manny skeletal mesh component.

The `Visibility Based Anim Tick Option` property should be set to `Always Tick Pose and Refresh Bones`, this will ensure that our character will follow the movements of the Manny character even though the Manny hidden.

# IK

Since the IK for the `Manny` is properly set-up, we don't need to setup IK for our character, it will work out of the box.
The `Retarget IK` checkbox should be unchecked in the animation retargeter, so that IK will be applied only to the Manny.

![Screenshot 2022-11-29 115934](https://user-images.githubusercontent.com/3124894/204512563-558b6d48-0fcf-433f-aa80-70f4c70f4b03.png)

![Screenshot 2022-11-28 182800](https://user-images.githubusercontent.com/3124894/204370102-537f8a51-ee7b-4007-bb54-afb402524cf4.png)

Make sure to assign the Override Physical Asset in the SkeletalMeshComponent of the character blueprint. You might encounter issues with shadows otherwise.

![Screenshot 2022-10-06 144007](https://user-images.githubusercontent.com/108666572/194314869-e4453faf-7ce8-420a-831f-0a94cffa0bb2.png)
