set gameinput=source/main.cpp source/basedata.cpp source/wordinput.cpp
set llibinput=C:/dev/projects/liamlib/src/storages.cpp C:/dev/projects/liamlib/src/rayextended.cpp C:/dev/projects/liamlib/src/button.cpp

call C:/dev/emsdk/emsdk_env.bat
call em++ -o index.html %gameinput% %llibinput% -Os -Wall C:/dev/raylib/srcweb/libraylib.a -IC:/dev/raylib/srcweb -Iheaders -IC:/dev/projects/liamlib/headers -L C:/dev/raylib/srcweb/libraylib.a -s USE_GLFW=3 -s EXPORTED_RUNTIME_METHODS=ccall -s EXPORTED_FUNCTIONS="['_malloc', '_main']" -s ALLOW_MEMORY_GROWTH=1 --shell-file C:/dev/raylib/srcweb/minshell.html -DPLATFORM_WEB --preload-file res -Wno-narrowing -std=c++20