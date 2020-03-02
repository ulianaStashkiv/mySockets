#include "server.hpp"

#include <any.pb.h>
#include <application_state_management.pb.h>

#include <chrono>
#include <thread>

int main(int argc, char const *argv[])
{
    std::unique_ptr<ServerSocket> serverPtr = std::make_unique<ServerSocket>();
    const std::string path = "/tmp/state_setter";

    Server myServer {std::move(serverPtr), path};
    myServer.start();
    google::protobuf::Any any;
    
    while(1)
    {
        std::string recv = myServer.getQueue();

        any.ParseFromString(recv);

        if(any.Is<ApplicationStateManagement::registerComponent>())
        {
            ApplicationStateManagement::registerComponent comp;
            any.UnpackTo(&comp);
            std::cout << "Client: AppName = " << comp.appname() << " State = " << comp.state() << "\n";
            comp = {};
        }
    }
    std::cout << "main end" << std::endl;

    return 0;
}

