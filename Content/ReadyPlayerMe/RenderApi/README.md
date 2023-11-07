# Ready Player Me Render API

![Screenshot 2023-11-07 141826](https://github.com/readyplayerme/UnrealExamples/assets/3124894/0db4ae2e-1536-4d76-a1c0-f99b8735a216)

The example demonstrates how to use the render API to load the ReadyPlayerMe 2D avatar images.

## Quick Start
The `RenderApiMap` map can be found in the `Content > ReadyPlayerMe > RenderApi > Maps` folder. The map adds a RenderApiOverlay widget to the viewport, for render API demonstration.

## Render Api Image Widget

When the widget is constructed, we first create a **ReadyPlayerMeRenderLoader** object and call it's **Load** function.
In the load function, we provide the model URL, RenderProperties, and the callback that will be called when the image is downloaded.
When the callback is called, we set the texture to the already existing image.

![Screenshot 2023-11-07 142149](https://github.com/readyplayerme/UnrealExamples/assets/3124894/6a989765-ad90-4594-b94d-84444eaa6fa8)

# Render Api Overlay

Render Api Overlay contains several instances of the RenderApiImage widget, each with different render properties.

![Screenshot 2023-11-07 142251](https://github.com/readyplayerme/UnrealExamples/assets/3124894/e1c1dba3-705b-4524-a2d9-7c0aa32c2c96)
