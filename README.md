![image](https://user-images.githubusercontent.com/53759287/150963688-497e5f63-fcb5-45e7-aa6b-9a6cc6d00623.png)![image](https://user-images.githubusercontent.com/53759287/150963396-02407643-f98e-40a3-aff2-6a483e5a97e7.png)![image](https://user-images.githubusercontent.com/53759287/150963471-7c3f3872-5cb7-48b4-b39b-daf88c0ddb40.png)![image](https://user-images.githubusercontent.com/53759287/150963574-55bca4cf-08d7-4f70-89aa-082408ca4891.png)



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

Consequently, open the folder in Visual Studio, dive in `FFGLPlugins.sln`, and adjust the code in the `.cpp` and `.h` file of the desired plug-in. 
Once satisfied, right-click the folder and click 'build'. The new .dll file should now be present in `binaries/x64/Debug`, and can be employed in Resolume.


### Adding a new plug-in
- Go to `<repo>/build/windows`, duplicate a `.vcxproj` and the corresponding `.vcxproj.filters` file, and rename them.
- Open `FFGLPlugins.sln`. Then right-click the Solution in the solution explorer (top of the tree), and choose Add > Existing Project and select the new file.
- Remove the original `.cpp` and `.h` source files from the newly added project, i.e. if you duplicated `Gradient.vcxproj`, remove `FFGLGradients.h` and `FFGLGradients.cpp`
- In Explorer, go to `<repo>/source/`, duplicate a plugin folder and rename the files. Choose a corresponding plugin type, i.e. copy `AddSubtract` if you want to build an Effect plugin or `Gradients` if you want to build a Source plugin.
- Add the new source files to the project by dragging them into Visual Studio, onto your new project.
- If you want to start the build with Visual Studio's Build command (F5), right-click the project and select Set as Startup Project. Altenatively, you can right-click the project and select Build.
- After building, find the resulting `.dll` file in `\binaries\x64\Debug`. Copy it to `<user folder>/Documents/Resolume/Extra Effects`

<iframe src="https://blueprintue.com/render/bbi09fgf/" scrolling="no" allowfullscreen></iframe>
