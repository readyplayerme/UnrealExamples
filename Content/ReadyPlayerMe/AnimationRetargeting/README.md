# Third Person Character Animation Retargeting Example

![Screenshot 2022-10-06 141418](https://user-images.githubusercontent.com/108666572/194309906-d7dc5108-2cb4-4005-baf7-b0d88af69c50.png)

Example demonstrates how to create a character using a ReadyPlayerMe avatar and retarget animations to make the character playable with the animations from third person character.

# Avatar Loader UI Widget

When you run the application and press Q the UI panel should display as below. By changing the url the avatar for the character will be changed at runtime.

![Screenshot 2022-10-06 142208](https://user-images.githubusercontent.com/108666572/194311325-0265c0fb-d65a-420c-a3fd-93cf62db0491.png)

# Map

By default the `ThirdPersonExampleMap` map can be found in the `Content > ReadyPlayerMe > AnimationRetargeting > Maps` folder.
In the Level Blueprint of the map the we setup a whdget to be able to runtime swap the avatar by changing the avatar url.

# Character Blueprint

You can find our character blueprint named `RPM_ThirdPersonCharacter` in the projects `Content > ReadyPlayerMe > Blueprints` folder.
The game mode for this example uses this character blueprint to as a `Default Pawn Class`.

This character was created simply by duplicating the example Unreal Third Person Character blueprint (that uses mannequin skeleton and mesh), then we reassigned the skeletal mesh and the animation blueprint as well as added a ReadyPlayerMeComponent to handle the loading of our ReadyPlayerMe avatars at runtime. 

# Animations 

If you look in the folder `Content > ReadyPlayerMe > AnimationRetargeting > Animations` you will find all the animations, blendspaces and animation blueprints used in our example.

![Screenshot 2022-10-06 141851](https://user-images.githubusercontent.com/108666572/194310719-e79f8cd0-87ef-425e-a61c-a1500ed6440f.png)

# How to retarget animations

While our avatars use a skeleton rig based on the Mixamo skeleton, it is possible to retarget animations using the UE4 and UE5 Mannequin skeletons so that they work with our Ready Player Me Avatars. For this example we did exactly that, to retarget animations from the UE5 Mannequn skeleton we first had to setup the IK Rig for the RPM skeleton. Right click in the asset browser and from the `Animation > IK Rig`, now we need to pick the `RPM_Mixamo_SkeletalMesh` skeletal mesh. To do this you need to open up the `UE4_Mannequin_Skeleton` asset located at `Content > Mannequin > Character > Mesh`. 

Different skeletons have different amount of bones, we need to create **IK Chains** so that the chains will match the chains in IK Rig of the UE5 Mannequin. We may also add **IK Solver** for better retargeting. The same IK Rig can be used to retarget animations between Meshes that have different skeletons. You can find more details about UE5 retargeting in the [official UE5 Documentation](https://docs.unrealengine.com/5.0/en-US/ik-rig-animation-retargeting-in-unreal-engine/).

![Screenshot 2022-10-06 142449](https://user-images.githubusercontent.com/108666572/194311983-97560467-1bae-49d9-a7e0-0a350bed877c.png)

Now we need to create an IK Retargeter that will retarget the animations from UE5 Mannequin to RPM. In the Content Browser right click `Animation > IK Retargeter` Pick the **IK_Mannequin**. UE5 example project comes with IK Rigs for UE4 and UE5 Mannequins. In the newly created retargeter set the **TargetIKRigAsset** to our RPM IK Rig. The two meshes will appear side-by-side. We need to make sure that all the chains are assigned correctly between the two skeletons. Now we need to create a new pose and adjust the pose of the RPM avatar to be ask close to the pose of the Mannequin as possible.

![Screenshot 2022-10-06 142625](https://user-images.githubusercontent.com/108666572/194312206-36a71843-f84d-4878-9d61-665ffef3ace9.png)

We can do the same steps to create UE4_Mannequin to RPM retargeter, if we need to retarget the animations from the UE4 Mannequin.

![Screenshot 2022-10-06 142812](https://user-images.githubusercontent.com/108666572/194312580-2533ef43-06da-4cf9-9ef9-084b50e6b62f.png)

We are almost there. Now we can retarget the animations. If you retarget an **Animation Blueprint** it will retarget and create a copy of every animation and blendspaces that is used in the blueprint as well as create a new Animation Blueprint. Right click on the **ABP_Manny** `Retarget Animation Assets > Duplicate and Retarget Animation Blueprint`, This will open the retargeting window. We can add a prefix or suffix for the retargeted animations. Select the newly created IK Retargeter, set the folder the retargeted animations animations, click **Retarge**. This will create an animation blueprint along with all of the retargeted animations.

![Screenshot 2022-10-06 142946](https://user-images.githubusercontent.com/108666572/194312920-bed36f10-174b-4f43-a7d5-844ade033f64.png)

Once the process is complete we should end up with animations and/or animation blueprints that work with our Ready Player Me avatar.

When we run the game we will notice that the feet of the character are stuck to the ground.This is because the default **Control Rig** uses bones specific to the Mannequin skeleton. We need to disable the IK from our animation blueprint. Open the animation blueprint and remove the control rig from the execution chain. The RPM_Mixamo_Skeleton currently doesn't have the IK bones.

![Screenshot 2022-10-06 143729](https://user-images.githubusercontent.com/108666572/194314365-a24a88a2-2459-48e1-b513-31b03b917afb.png)

There will be proper IK support in the upcoming versions of the SDK. For now if we want to test the IK, we can add virtual bones for the IK to our **RPM_Mixamo_Skeleton** (similar to the IK bones in UE4 Mannequin) and change the control rig in the animation blueprint to use **CR_RPM_BasicFootIK**.

![Screenshot 2022-10-10 095350](https://user-images.githubusercontent.com/108666572/194822530-ef52c70e-7e7b-4e2a-95c8-82a16b48770b.png)

Make sure to assign the Override Physical Asset in the SkeletalMeshComponent of the character blueprint. You might encounter issues with shadows otherwise.

![Screenshot 2022-10-06 144007](https://user-images.githubusercontent.com/108666572/194314869-e4453faf-7ce8-420a-831f-0a94cffa0bb2.png)

## Note

Currently the runtime retargeting doesn't work with the loaded RPM avatars.

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



