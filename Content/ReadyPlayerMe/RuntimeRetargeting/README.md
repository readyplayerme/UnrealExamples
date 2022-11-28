# Runtime Animation Retargeting Example

![Screenshot 2022-10-06 141418](https://user-images.githubusercontent.com/108666572/194309906-d7dc5108-2cb4-4005-baf7-b0d88af69c50.png)

Example demonstrates how to use the runtime retargeting to runtime retarget the animations from the Mannequin to the ReadyPlayerMe character. The runtime retargeting can be applied to retarget the animations from any character to the ReadyPlayerMe avatar.

# Use cases

Runtime retargeting comes with some performance overhead. Another downside is that two meshes will be places on the scene for a single avatar, even though one of them will never be visible.
It is very easy to use, since no new animations need to be created. It solves the IK issues between the incompatible skeletons.
For prototyping, runtime retargeting will save some development time.

# Map

By default the `RuntimeRetargetingMap` map can be found in the `Content > ReadyPlayerMe > RuntimeRetargeting > Maps` folder.

# Animation Blueprint

The runtime retargeting is done inside of the animation blueprint.
Create an animation blueprint and set the base skeleton to the `RPM_Mixamo_Skeleton`.
To be able to retarget the animations from the UE5 Manny to the RPM_FullBody avatar we need to creat an IKRetargeter. For more info about how to creat an IKRig and IKRetargeter, you can check [here](https://github.com/readyplayerme/UnrealExamples/tree/main/Content/ReadyPlayerMe/AnimationRetargeting#how-to-retarget-animations).
Create a `Retarget Pose From Mesh` node and connect it to the output pose. Set the `IKRetargeter Asset` to the `RTG_UE5_Manny_RPM_FullBody`. Make sure that `Use Attached Parent` checkbox is checked.

# Character Blueprint

You can find our character blueprint named `BP_RPM_RuntimeCharacter` in the projects `Content > ReadyPlayerMe > RuntimeRetargeting > Blueprints` folder.
The game mode for this example uses this character blueprint to as a `Default Pawn Class`.

The character was created by duplicating the example Unreal Third Person Character blueprint (that uses mannequin skeleton and mesh).

We add another skeletal mesh component as a child of the Manny skeletal mesh component. The movement of the character will be handled by the UE5 Mannequin, our character will follow the movements of the Mannequin.

We set custom animation blueprint to the newly created RpmSkeletalMesh component. The animation blueprint will runtime retarget the animations from the Mannequin to the RPM using animation retargeter.

Inside of the Blueprint in BeginPlay we override the skeletal mesh component of the ReadyPlayerMe component. This way at runtime the avatar mesh will be set to the newly created RpmSkeletalMesh component.

Now in BeginPlay we load the avatar. Make sure that the SkeletalMesh of the RpmSkeletalMesh component is not set, otherwise the animations will break after the avatar is loaded.

When running the game you will see that two meshes are shown on top of each other, RPM and the Manny. We need to hide the Manny, uncheck the `Visible` checkbox of the Manny skeletal mesh component.
Makes sure that the `Visibility Based Anim Tick Option` is set to `Always Tick Pose and Refresh Bones`, this will ensure that our character will follow the movements of the Manny character.

Since the IK for the `Manny` is properly set-up, we don't need to setup IK for our character, it will work out of the box.
Make sure that the `Retarget IK` checkbox is unchecked in the animation retargeter, so that IK will be applied only to the Manny.

![Screenshot 2022-10-10 095350](https://user-images.githubusercontent.com/108666572/194822530-ef52c70e-7e7b-4e2a-95c8-82a16b48770b.png)

Make sure to assign the Override Physical Asset in the SkeletalMeshComponent of the character blueprint. You might encounter issues with shadows otherwise.

![Screenshot 2022-10-06 144007](https://user-images.githubusercontent.com/108666572/194314869-e4453faf-7ce8-420a-831f-0a94cffa0bb2.png)
