#include "server.hpp"

#include <any.pb.h>
#include <application_state_management.pb.h>
#include <execution_management.pb.h>
#include <enums.pb.h>

#include <chrono>
#include <thread>

int main(int argc, char const *argv[])
{
    std::unique_ptr<ServerSocket> serverPtr = std::make_unique<ServerSocket>();
    const std::string path = "/tmp/state_setter";

    Server myServer {std::move(serverPtr), path};
    myServer.start();
    google::protobuf::Any any;
    std::thread m_serverThread;

    std::this_thread::sleep_for(std::chrono::seconds(10));
    
        ExecutionManagement::resultRegisterComponent comp;
        comp.set_result(ExecutionManagement::StateError::kSuccess);

        google::protobuf::Any send;
        send.PackFrom(comp);
        std::cout << "Server: Send data\n";

        myServer.send(send);

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

        //m_serverThread = std::thread(&Server::send, myServer(any));
    }

    m_serverThread.join();
    std::cout << "main end" << std::endl;

    return 0;
}

