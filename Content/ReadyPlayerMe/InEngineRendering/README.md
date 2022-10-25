# Ready Player Me In-Engine Rendering

![img-livelink-sample](https://user-images.githubusercontent.com/7085672/164030100-8063b64f-2162-4abf-a642-0193964ab04c.png)

Example demonstrates how to render the ReadyPlayerMe avatars in the 2D space, to create images or 2D Animations.

# Quick Start
By default the `InEngineRendering` map can be found in the `Content > ReadyPlayerMe > InEngineRendering > Maps` folder as below.

In the Level Blueprint of the map the RenderOverlay widget is added to the viewport. On the startup the images will be loaded and displayed on the RenderOverlay.

To render different avatars you can do the following. In the RenderOverlay select one of the two images and change the `Url` parameter.

![img-live-link-actor](https://user-images.githubusercontent.com/7085672/164033730-15220078-1597-49dd-9c40-d5e8b5410398.png)

Now hit play and this time it should load the new avatar from the URL you provided.

# Render Actor
We need to prepare an actor that will be spawned outside of the visible are.
The render actor contains the following components:
- Skeletal Mesh. RPM skeletal mesh.
- Spotlight. It should point to the skeletal mesh of the RPM. There might be multiple Spotlights for the better images.
- SceneCaptureComponent2D. Captures the images or videos of the skeletal mesh.
- ReadyPlayerMe. We need it to load the Avatar and update the skeletal mesh.

![img-anim-graph](https://user-images.githubusercontent.com/7085672/164032665-9ed72dbb-730f-4e02-8fad-e9d9558b8afb.png)

Additionally other effects, assets or meshes can be added to the actor, for customizing the image.

We need to set the **Animation Asset** for our skeletal mesh. Depending if we want to have an animation or an image, we can set it to a **Pose asset** or an **Animation asset**.

The SceneCaptureComponent2D should point to the skeletal mesh, we can rotate and move it to customize the rendering area. We also need to uncheck the **Visible**, **Capture Every Frame** and **Capture On Movement** checkboxes, we will enable them from the blueprint.

### Event Graph

In the event graph we load the avatar and set the capture component to only record the actor components.
When the avatar is loaded we create a dynamic material instance and a render target. Then we connect them so that rendered texture will be applied to the created material instance.
We enable the scene capture component, to render images or animations. If we render an image them we destroy the actor after the image is taken.

# Render Image

To display the rendered image we need to create an image BP and inherit it from the **UMG.Image**.
Initially we hide the image, and we show it when the image is loaded.
We spawn the render actor outside of the visible area. We load the render of the actor, when it's loaded we set the brush of the image from the generated material.
When the image is destroyed we destroy the render actor.
Additionally we add **Url** and **Capture Animation** parameters to have customizable images.

# Render Overlay

We can add **RenderImages** to any widget. Render Overlay contains two instances of the RenderImage.
We need to load the images when the Widget is constructed and destroy the images when the Widget is destroyed.

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
