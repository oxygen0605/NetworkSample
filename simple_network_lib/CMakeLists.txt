# CMakeのバージョンを設定
cmake_minimum_required(VERSION 2.8)
# プロジェクト名と使用する言語を設定
project(simple_network_lib_and_code C)

#build libraries
add_subdirectory(lib)

#build client app
add_executable(client client_app.c)
target_link_libraries(client PRIVATE mynetlib_client)

#build server app
add_executable(server server_app.c)
target_link_libraries(server PRIVATE mynetlib_server)
