# Ready Player Me Render API

![Screenshot 2023-11-07 141826](https://github.com/readyplayerme/UnrealExamples/assets/3124894/0db4ae2e-1536-4d76-a1c0-f99b8735a216)

The example demonstrates how to use the render API to load the ReadyPlayerMe 2D avatar images.

## Quick Start
The `RenderApiMap` map can be found in the `Content > ReadyPlayerMe > RenderApi > Maps` folder. The map adds a RenderApiOverlay widget to the viewport, for render API demonstration.

## Render Api Image Widget

When the widget is constructed, we create a **LoadAvatarRenderAsync** blueprint node and provide the model URL and RenderProperties inputs.
When the **OnComplete** callback is called, we set the texture to the already existing image.

![Screenshot 2023-11-08 164907](https://github.com/readyplayerme/UnrealExamples/assets/3124894/72f4d7d0-67b2-4bc0-a19f-5d19d241f6b7)

# Render Api Overlay

Render Api Overlay contains several instances of the RenderApiImage widget, each with different render properties.

![Screenshot 2023-11-07 142251](https://github.com/readyplayerme/UnrealExamples/assets/3124894/e1c1dba3-705b-4524-a2d9-7c0aa32c2c96)
