BASE_PWD=`pwd`
export SDL2_DIR=${BASE_PWD}/sdl2-prefix

(cd SDL2-2.0.3 && \
./configure --prefix=${SDL2_DIR} --exec-prefix=${SDL2_DIR} --without-x --disable-render && \
make && make install)

(cd bgfx && patch -f -p1 < ../patches/bgfx-build.patch)
(cd bgfx && \
bx/tools/bin/darwin/genie --with-tools --gcc=osx --with-sdl gmake && \
make -C .build/projects/gmake-osx config=debug64)
