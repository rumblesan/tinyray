include_directories(include)

set(SOURCES
    "src/shapes/sphere.c"
    "src/shapes/triangle.c"
    "src/shapes/plane.c"
    "src/camera.c"
    "src/canvas.c"
    "src/colours.c"
    "src/config.c"
    "src/lights.c"
    "src/ray.c"
    "src/scene.c"
    "src/shapes.c"
    "src/textures.c"
    "src/tracing.c"
    "src/vector.c"
    )
add_library(tinyray-lib SHARED ${SOURCES})

find_package(BCLib REQUIRED)
include_directories("${BCLIB_INCLUDE_DIRS}")
target_link_libraries(tinyray-lib bclib)
