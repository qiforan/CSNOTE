find_package(Threads REQUIRED)

add_executable(server server.c)
target_link_libraries(
        server
        Threads::Threads
)