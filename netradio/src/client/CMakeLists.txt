add_executable(client client.c)
target_include_directories(
        client
        PUBLIC
        client.h
)