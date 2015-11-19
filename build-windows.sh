BASE_PWD=`pwd`
export MINGW=/mingw
export SDL2_DIR=${BASE_PWD}/sdl2-prefix

(cd SDL2-2.0.3 && \
./configure --prefix=${SDL2_DIR} --exec-prefix=${SDL2_DIR} --without-x --disable-render-d3d && \
make && make install)

(cd bgfx && patch -f -p1 < ../patches/bgfx-build.patch)
(cd bgfx && \
../bx/tools/bin/windows/genie --with-tools --gcc=mingw-gcc --with-sdl gmake && \
make -C .build/projects/gmake-mingw-gcc config=debug64 -f bgfx.make)

g++ src/entry/input.cpp \
    src/entry/entry.cpp \
	src/entry/entry_sdl.cpp \
    src/entry/dbg.cpp \
    src/entry/cmd.cpp \
    src/helloworld.cpp \
    -Ibx/include \
    -Ibx/include/compat/mingw \
    -Ibgfx/include \
    -Ibgfx/3rdparty \
    -Isdl2-prefix/include \
    bgfx/.build/win64_mingw-gcc/bin/libbgfxDebug.a \
    -lpsapi \
    `sdl2-prefix/bin/sdl2-config --libs` \
    -D__STDC_LIMIT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_CONSTANT_MACROS -DWIN32 -DENTRY_CONFIG_USE_SDL=1 \
    -o helloworld