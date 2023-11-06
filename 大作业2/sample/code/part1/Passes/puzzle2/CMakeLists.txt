get_filename_component(DIRNAME ${CMAKE_CURRENT_SOURCE_DIR} NAME_WE)
# 填写需要的代码文件名
add_library(${DIRNAME}_Pass MODULE MyPass.cpp)
add_library(${DIRNAME}_Func MyFunc.cpp)

# 以下部分勿动

# LLVM is (typically) built with no C++ RTTI. We need to match that;
# otherwise, we'll get linker errors about missing RTTI data.
set_target_properties(${DIRNAME}_Pass PROPERTIES
    COMPILE_FLAGS "-fno-rtti"
)

# Get proper shared-library behavior (where symbols are not necessarily
# resolved when the shared library is linked) on OS X.
if(APPLE)
    set_target_properties(${DIRNAME}_Pass PROPERTIES
        LINK_FLAGS "-undefined dynamic_lookup"
    )
endif(APPLE)

add_custom_target(${DIRNAME}_dummy DEPENDS ${DIRNAME}_Pass)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/../../test/puzzle2 TEST_CASES)
foreach(CASE ${TEST_CASES})
    get_filename_component(CASENAME ${CASE} NAME_WE)
    add_executable(${DIRNAME}_${CASENAME} ${CASE})
    add_dependencies(${DIRNAME}_${CASENAME} ${DIRNAME}_dummy)
    target_compile_options(${DIRNAME}_${CASENAME} PUBLIC -fpass-plugin=$<TARGET_FILE:${DIRNAME}_Pass> -Os)
    target_link_libraries(${DIRNAME}_${CASENAME} ${DIRNAME}_Func pthread)
endforeach()



