include_directories(include)

find_package(BISON 3.0)
find_package(FLEX 2.5)

bison_target(TRLParser grammar/traylang.y ${CMAKE_CURRENT_BINARY_DIR}/y.tab.c)
flex_target(TRLLexer
    grammar/traylang.l ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c
    COMPILE_FLAGS --header-file=${CMAKE_CURRENT_BINARY_DIR}/lex.yy.h
)
add_flex_bison_dependency(TRLLexer TRLParser)

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
    "src/language/ast.c"
    "src/language/ast-print.c"
    )
add_library(tinyray-lib SHARED
    ${SOURCES}
    ${BISON_TRLParser_OUTPUTS}
    ${FLEX_TRLLexer_OUTPUTS}
)


find_package(BCLib REQUIRED)
include_directories("${BCLIB_INCLUDE_DIRS}")
target_link_libraries(tinyray-lib bclib)
