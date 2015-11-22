BASE_PWD=`pwd`/..
export SDL2_DIR=${BASE_PWD}/sdl2-prefix

mkdir -p target-osx && \
../bgfx/.build/osx64_clang/bin/shadercDebug -f src/vs_raymarching.sc \
											-o target-osx/vs_raymarching.bin \
											--type vertex --platform osx -i ../bgfx/src/ && \
../bgfx/.build/osx64_clang/bin/shadercDebug -f src/fs_raymarching.sc \
											-o target-osx/fs_raymarching.bin \
											--type fragment --platform osx -i ../bgfx/src/ && \
g++ -g3 -O0 \
	${BASE_PWD}/common-src/start.cpp \
	src/drawing.cpp \
	src/bgfx_utils.cpp \
	src/event_handler.cpp \
    ${BASE_PWD}/bgfx/3rdparty/ib-compress/indexbuffercompression.cpp \
    ${BASE_PWD}/bgfx/3rdparty/ib-compress/indexbufferdecompression.cpp \
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
    -o target-osx/cube