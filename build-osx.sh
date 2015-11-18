BASE_PWD=`pwd`
export SDL2_DIR=${BASE_PWD}/sdl2-prefix

(cd SDL2-2.0.3 && \
./configure --prefix=${SDL2_DIR} --exec-prefix=${SDL2_DIR} --without-x && \
make && make install)

(cd bgfx && patch -f -p1 < ../patches/bgfx-build.patch)
(cd bgfx && \
../bx/tools/bin/darwin/genie --with-tools --gcc=osx --with-sdl gmake && \
make -C .build/projects/gmake-osx config=debug64)

g++ src/entry/input.cpp \
    src/entry/entry.cpp \
	src/entry/entry_sdl.cpp \
    src/entry/dbg.cpp \
    src/entry/cmd.cpp \
    src/helloworld.cpp \
    -Ibx/include \
    -Ibx/include/compat/osx \
    -Ibgfx/include \
    -Ibgfx/3rdparty \
    -Isdl2-prefix/include \
    -framework Cocoa -framework QuartzCore -framework OpenGL \
    bgfx/.build/osx64_clang/bin/libbgfxDebug.a \
    `sdl2-prefix/bin/sdl2-config --libs` \
    -DENTRY_CONFIG_USE_SDL=1 \
    -o helloworld