![image](https://user-images.githubusercontent.com/53759287/150963688-497e5f63-fcb5-45e7-aa6b-9a6cc6d00623.png)![image](https://user-images.githubusercontent.com/53759287/150963396-02407643-f98e-40a3-aff2-6a483e5a97e7.png)![image](https://user-images.githubusercontent.com/53759287/150963471-7c3f3872-5cb7-48b4-b39b-daf88c0ddb40.png)![image](https://user-images.githubusercontent.com/53759287/150963574-55bca4cf-08d7-4f70-89aa-082408ca4891.png)



A custom plug-in based on the Resolume fork of the FFGL repository. 
It is up to date and has Visual Studio and Xcode projects to compile 64 bit plugins that can be loaded by Resolume 7.0.3 and up.

You can find some help to get started with FFGL plugin development on the [wiki](https://github.com/resolume/ffgl/wiki).

Also more examples are available on this [repo](https://github.com/flyingrub/ffgl/tree/more/).

## Master branch changes since FFGL 2.2
- Replaced glload by glew, enabling OpenGL 4.6 extensions to be used inside plugins. Plugins may need to add deps/glew.props to their project's property pages for them to link to the binary.
- Implemented parameter display names. Parameter names are used as identification during serialization, display names can be used to override the name that is shown in the ui. The display name can also be changed dynamically by raising a display name changed event. (Requires Resolume 7.4.0 and up)
- Implemented value change events. Plugins can change their own parameter values and make the host pick up the change. See the new Events example on how to do this. (Requires Resolume 7.4.0 and up)
- Implemented dynamic option elements. Plugins can add/remove/rename option elements on the fly. (Requires Resolume 7.4.1 and up)

*You can suggest a change by creating an issue. In the issue describe the problem that has to be solved and if you want, a suggestion on how it could be solved.*

## Quickstart

Below are the first steps you need to create and test an FFGL plugin for Resolume. This assumes you have experience with git and C++ development.

### Windows 

This assumes you use Visual Studio 2017

- Go to `<repo>/build/windows`, duplicate a `.vcxproj` and the corresponding `.vcxproj.filters` file, and rename them.
- Open `FFGLPlugins.sln`. Then right-click the Solution in the solution explorer (top of the tree), and choose Add > Existing Project and select the new file.
- Remove the original `.cpp` and `.h` source files from the newly added project, i.e. if you duplicated `Gradient.vcxproj`, remove `FFGLGradients.h` and `FFGLGradients.cpp`
- In Explorer, go to `<repo>/source/`, duplicate a plugin folder and rename the files. Choose a corresponding plugin type, i.e. copy `AddSubtract` if you want to build an Effect plugin or `Gradients` if you want to build a Source plugin.
- Add the new source files to the project by dragging them into Visual Studio, onto your new project.
- If you want to start the build with Visual Studio's Build command (F5), right-click the project and select Set as Startup Project. Altenatively, you can right-click the project and select Build.
- After building, find the resulting `.dll` file in `\binaries\x64\Debug`. Copy it to `<user folder>/Documents/Resolume/Extra Effects`

