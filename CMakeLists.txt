

idf_component_register(SRCS "ads1115_cpp.cpp" "include/ads1115.c"
                    INCLUDE_DIRS "include" "../../main"
                    REQUIRES log 
                    PRIV_REQUIRES Led )

target_compile_options(${COMPONENT_LIB} PRIVATE -std=gnu++23)
