# Ready Player Me In-Engine Rendering

![Screenshot 2023-03-03 165756](https://user-images.githubusercontent.com/3124894/233416253-9843a7ed-c49d-447c-ba84-a99098cd13ec.png)

Example demonstrates how to render the ReadyPlayerMe avatars in the 2D space, to create images or 2D Animations.

# Quick Start
By default the `InEngineRendering` map can be found in the `Content > ReadyPlayerMe > InEngineRendering > Maps` folder as below.

In the Level Blueprint of the map the `RenderOverlay` widget is added to the viewport. On the startup the images will be loaded and displayed on the RenderOverlay.

To render different avatars you can do the following. In the RenderOverlay select one of the two images and change the `Url` parameter.

![Screenshot 2022-10-26 102635](https://user-images.githubusercontent.com/108666572/197974743-2a4b0050-9c33-456f-82e8-568a57c05c05.png)

Now hit play and this time it should load the new avatar from the URL you provided.

# Render Actor
We need to prepare an actor that will be spawned outside of the visible are.
The render actor contains the following components:
- Skeletal Mesh. RPM skeletal mesh.
- Spotlight. It should point to the skeletal mesh of the RPM. There might be multiple Spotlights for the better images.
- SceneCaptureComponent2D. Captures the images or videos of the skeletal mesh.
- ReadyPlayerMe. We need it to load the Avatar and update the skeletal mesh.

![Screenshot 2022-10-25 225717](https://user-images.githubusercontent.com/108666572/197881519-43ce221c-cd79-4cff-aad2-308d1b73bbbf.png)

Additionally other effects, assets or meshes can be added to the actor, for customizing the image.

We need to set the **Animation Asset** for our skeletal mesh. Depending if we want to have an animation or an image, we can set it to a `Pose asset` or an `Animation asset`.

The SceneCaptureComponent2D should point to the skeletal mesh, we can rotate and move it to customize the rendering area.
We also need to uncheck the **Visible**, **Capture Every Frame** and **Capture On Movement** checkboxes, we will enable them from the blueprint.
**Make** sure to uncheck the Atmosphere checkbox, not to have visual artifacts in the rendered image.

### Event Graph

In the event graph we load the avatar and set the capture component to only record the actor components.

![Screenshot 2022-10-25 225809](https://user-images.githubusercontent.com/108666572/197881696-1f9fcf6c-8814-447d-921e-89cba2052cda.png)

When the avatar is loaded we create a dynamic material instance and a render target. Then we connect them so that rendered texture will be applied to the created material instance.

![Screenshot 2022-10-25 225906](https://user-images.githubusercontent.com/108666572/197881762-5ef3591b-e4dd-4818-adbd-3771745722e0.png)

We enable the scene capture component, to render images or animations.
If we render an image them we destroy the actor after the image is taken.

![Screenshot 2022-10-25 230525](https://user-images.githubusercontent.com/108666572/197881897-5e128e34-c3ec-4823-8d81-7797a9f51ee8.png)

# Render Image

To display the rendered image we need to create an widget BP and add an image to it.
Initially we hide the image, and we show it when the image is loaded.
We spawn the render actor outside of the visible area. We load the render of the actor, when it's loaded we set the brush of the image from the generated material.

![Screenshot 2023-03-13 214725](https://user-images.githubusercontent.com/3124894/233417212-b56eaae4-04d5-4067-9583-27ed73828eeb.png)

When the widget is destroyed we destroy the render actor.
Additionally we add **Url** and **Capture Animation** parameters to have customizable images.

![Screenshot 2022-10-26 102113](https://user-images.githubusercontent.com/108666572/197973402-ac61c86c-9300-4fe6-a510-5b13b39bf158.png)

# Render Overlay

We can add `RenderImages` to any widget. Render Overlay contains two instances of the RenderImage.
