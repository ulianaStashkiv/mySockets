#include "server.hpp"

#include <chrono>
#include <thread>

int main(int argc, char const *argv[])
{
    std::unique_ptr<ServerSocket> serverPtr = std::make_unique<ServerSocket>();

    const std::string path = "/tmp/state_setter";

    Server myServer {std::move(serverPtr), path};
    std::this_thread::sleep_for(std::chrono::milliseconds(300000));

    std::cout << "main end" << std::endl;

    return 0;
}

