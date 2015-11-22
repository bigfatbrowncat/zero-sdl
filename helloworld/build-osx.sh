BASE_PWD=`pwd`/..
export SDL2_DIR=${BASE_PWD}/sdl2-prefix

mkdir -p target-osx && \
g++ -g3 -O0 \
	${BASE_PWD}/common-src/start.cpp \
	src/drawing.cpp \
	src/event_handler.cpp \
    -I${BASE_PWD}/common-src \
    -I${BASE_PWD}/bx/include \
    -I${BASE_PWD}/bx/include/compat/osx \
    -I${BASE_PWD}/bgfx/include \
    -I${BASE_PWD}/bgfx/3rdparty \
    -I${BASE_PWD}/sdl2-prefix/include \
    -framework Cocoa -framework OpenGL \
    ${BASE_PWD}/bgfx/.build/osx64_clang/bin/libbgfxDebug.a \
    `../sdl2-prefix/bin/sdl2-config --libs` \
    -DENTRY_CONFIG_USE_SDL=1 -DBGFX_CONFIG_MULTITHREADED=0 \
    -o target-osx/helloworld