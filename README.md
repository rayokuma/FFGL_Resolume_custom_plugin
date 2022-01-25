<img src="https://user-images.githubusercontent.com/53759287/150963688-497e5f63-fcb5-45e7-aa6b-9a6cc6d00623.png" width="400"><img src="https://user-images.githubusercontent.com/53759287/150963396-02407643-f98e-40a3-aff2-6a483e5a97e7.png" width="400"> <img src="https://user-images.githubusercontent.com/53759287/150963471-7c3f3872-5cb7-48b4-b39b-daf88c0ddb40.png" width="400"> <img src="https://user-images.githubusercontent.com/53759287/150963574-55bca4cf-08d7-4f70-89aa-082408ca4891.png" width="400"> 


Contains four user interface plug-ins aimed for Resolume. These plug-ins are customizable and give an idea of the possibilities for making a UI for Resolume.
It is up to date and has Visual Studio and Xcode projects to compile 64 bit plugins that can be loaded by Resolume 7.0.3 and up.
The package contains Resolume's master branch to be found [here](https://github.com/resolume/ffgl)

You can find some help to get started with FFGL plugin development on the [wiki](https://github.com/resolume/ffgl/wiki).
Also more examples are available on this [repo](https://github.com/flyingrub/ffgl/tree/more/).

## Usage
To simply use one of the plug-ins, copy the desired plug-in (.dll file) into **(Resolume dir)/plugins/vfx** folder, or point to the folder on your pc in the **video** section in Resolume's preference window. Resolume will load in the plug-in file in the effects panel. 

## Customizing the plug-in
The project requires to be rebuilt, if it is desired to customize the plug-in(s).
To do this, the FFGL SDK plug-in needs to be installed, as well as Microsoft Visual Studio (I used [Community Edition 2019](https://my.visualstudio.com/Downloads?q=visual%20studio%202019&wt.mc_id=o~msft~vscom~older-downloads)). 

- Open the folder in Visual Studio, dive in `FFGLPlugins.sln`.
- Adjust the code in the `.cpp` and `.h` file of the desired plug-in. 
- Right-click the folder and click 'build'. The new `.dll` file should now be present in `binaries/x64/Debug`, Copy it to `<user folder>/Documents/Resolume/Extra Effects`.


### Adding a new plug-in
- In`<repo>/build/windows`, duplicate a `.vcxproj` and the corresponding `.vcxproj.filters` file, and rename them.
- Open `FFGLPlugins.sln`. Then right-click the Solution in the solution explorer, and choose Add > Existing Project and select the new file.
- Remove the original `.cpp` and `.h` source files from the newly added project.
- In Explorer, go to `<repo>/source/`, duplicate a plugin folder and rename the files. Choose a corresponding plugin type, i.e. copy `AddSubtract` if you want to build an Effect plugin or `Gradients` if you want to build a Source plugin.
- Add the new source files to the project by dragging them into Visual Studio, onto your new project.
- Right-click the project and select Build.
- After building, find the resulting `.dll` file in `\binaries\x64\Debug`. Copy it to `<user folder>/Documents/Resolume/Extra Effects`. It can now be employed in Resolume.

### Combination with Unreal Engine
This plug-in can be used to control Unreal Engine parameters via Resolume.
To attain this, you will need [these blueprints](https://blueprintue.com/blueprint/bbi09fgf/), and the [Off World Live Spout plug-in](https://plugin-auth.offworld.live/) for this.

- In resolume, make sure you are receiving and sending OSC data. Check the preference window > OSC. The settings should look like the following.
![image](https://user-images.githubusercontent.com/53759287/150968637-c92715c7-bdb3-4000-9fa0-4775b44954d3.png)
- In unreal, make a new blueprint class and paste [these blueprints](https://blueprintue.com/blueprint/bbi09fgf/) inside. This blueprint is fully customizable as well. However, it should correspond with your plug-in.
- Put the Off world camera in the scene.
<img src="https://user-images.githubusercontent.com/53759287/150969612-e06020b1-177f-4efe-a77e-8b89422189bb.png" width="250"> 
- Assign the required actors 

- When clicking on play, data should be coming in in Unreal Engine
<img src="https://user-images.githubusercontent.com/53759287/150969075-ed916c02-b277-4218-aeed-b49a63316484.png" width="250"> 
- In Resolume, you are now streaming Unreal's camera output, while you can operate its parameters, like light, camera, actor transformations, materials, and more!
<img src="https://user-images.githubusercontent.com/53759287/150969758-e405d360-020c-445d-b469-6c5a66f7d7d7.png" width="250">


