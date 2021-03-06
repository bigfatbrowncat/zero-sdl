BASE_PWD=`pwd`
export MINGW=/mingw
export SDL2_DIR=../${BASE_PWD}/sdl2-prefix

(cd ../SDL2-2.0.3 && \
./configure --prefix=${SDL2_DIR} --exec-prefix=${SDL2_DIR} --without-x --disable-render-d3d && \
make && make install)

(cd ../bgfx && patch -f -p1 < ../patches/bgfx-build.patch)
(cd ../bgfx && \
../bx/tools/bin/windows/genie --with-tools --gcc=mingw-gcc --with-sdl gmake && \
make -C .build/projects/gmake-mingw-gcc config=debug64 -f bgfx.make)

mkdir target-windows && \
g++ -static -static-libgcc -static-libstdc++ \
	src/helloworld.cpp \
	src/drawing.cpp \
	src/event_handler.cpp \
    -Ibx/include \
    -Ibx/include/compat/mingw \
    -Ibgfx/include \
    -Ibgfx/3rdparty \
    -Isdl2-prefix/include \
    ../bgfx/.build/win64_mingw-gcc/bin/libbgfxDebug.a \
    `sdl2-prefix/bin/sdl2-config --libs` \
    -lpsapi -lm -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lversion -luuid \
    -D__STDC_LIMIT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_CONSTANT_MACROS -DWIN32 -DENTRY_CONFIG_USE_SDL=1 \
	-mconsole \
    -o target-windows/helloworld.exe && \
strip target-windows/helloworld.exe --strip-all