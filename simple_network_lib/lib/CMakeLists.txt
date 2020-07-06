#build libraries
add_library(mynetlib_client SHARED src/mynetlib_client.c)
target_include_directories(mynetlib_client PUBLIC include)
add_library(mynetlib_server SHARED src/mynetlib_server.c)
target_include_directories(mynetlib_server PUBLIC include)
