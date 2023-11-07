# Ready Player Me Render Api

![Screenshot 2023-03-03 165756](https://user-images.githubusercontent.com/3124894/233416253-9843a7ed-c49d-447c-ba84-a99098cd13ec.png)

Example demonstrates how to use the render api to load the ReadyPlayerMe 2D avatar images.

## Quick Start
The `RenderApiMap` map can be found in the `Content > ReadyPlayerMe > RenderApi > Maps` folder. The map add RenderApiOverlay widget tho the viewport, for render api demonstration.

## Render Api Image Widget

When the widget is constructed, we first create a **ReadyPlayerMeRenderLoader** object, and call it's **Load** function.
In the load function we provide the model URL, RenderProperties, and the callback that will be called when the image is downloaded.
When the callback is called we, we set the texture to already existing image.

![Screenshot 2022-10-25 225809](https://user-images.githubusercontent.com/108666572/197881696-1f9fcf6c-8814-447d-921e-89cba2052cda.png)

# Render Api Overlay

Render Api Overlay contains several instances of the RenderApiImage widget, each with different render properties.

![Screenshot 2022-10-26 102113](https://user-images.githubusercontent.com/108666572/197973402-ac61c86c-9300-4fe6-a510-5b13b39bf158.png)
