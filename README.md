# engine

OpenGL 3.3 Engine written from _scratch_ (not really), built as a side hobby and to toy around with OpenGL.

Vulkan support is comming soon once i get the time and energy to be able to learn it.

Before that time comes lighting shaders, support for shipping and an editor will come.

### Building

- **Windows**
1. Open the .sln file inside Visual Studio
2. Build

- **Linux**
1. [Build a STATIC (.a) copy of assimp](https://github.com/assimp/assimp/blob/master/Build.md)
2. Place it to Vendor/assimp/libassimp.a
3. `$ cmake . && make`

### Credits
- [docs.gl](https://docs.hl)
- [learnopengl.com](https://learnopengl.com)
- [The Cherno's amazing youtube series](https://www.youtube.com/watch?v=W3gAzLwfIP0&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2)

_And many more which ill add once i remember_