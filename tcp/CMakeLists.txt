# CMakeのバージョンを設定
cmake_minimum_required(VERSION 2.8)
# プロジェクト名と使用する言語を設定
project(tcp_sample_code C)
# a.outという実行ファイルをmain.cppとhello.cppから作成
# simple tcp server/client
add_executable(simple_client simple_client.c)
add_executable(simple_server simple_server.c)
# simple http server/client
add_executable(http_client http_client.c)
add_executable(http_server http_server.c)
