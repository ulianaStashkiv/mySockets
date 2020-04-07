#include "client.hpp"

#include <any.pb.h>
#include <application_state_management.pb.h>
#include <execution_management.pb.h>
#include <enums.pb.h>

#include <thread>
#include <chrono>

using namespace ApplicationStateManagement;


int main(int argc, char const *argv[])
{
    std::unique_ptr<ClientSocket> clientPtr = std::make_unique<ClientSocket>();

    const std::string path = "/tmp/state_setter";
    const std::string message = "Hello word.";

    Client myClient {std::move(clientPtr), path};
    std::cout<< "client connect to server\n";
    myClient.connectToServer();

    google::protobuf::Any recvData;
    bool isEmpty = false;
    while(1)
    {
        auto data = myClient.recvMessage(isEmpty);
        recvData.ParseFromString(data);
        
        if(recvData.Is<ExecutionManagement::resultRegisterComponent>())
        {
            ExecutionManagement::resultRegisterComponent context;
            recvData.UnpackTo(&context);
            ExecutionManagement::StateError result = context.result();
            if(result == ExecutionManagement::StateError::kSuccess)
            {
              std::cout << "Recve in client from server: kSuccess\n";
              break;
            }
            context = {};
        }
    }

    registerComponent comp;
    comp.set_appname(message);
    comp.set_state(enums::ApplicationState::kInitializing);

    google::protobuf::Any any;
    any.PackFrom(comp);

    std::cout<< "client send to server\n";
    myClient.sendMessage(any);
    std::this_thread::sleep_for(std::chrono::seconds(15));
    registerComponent comp1;

    comp1.set_appname("message.");
    comp1.set_state(enums::ApplicationState::kRunning);
    any.PackFrom(comp1);

    std::cout<< "client send to server\n";
    myClient.sendMessage(any);
    std::cout << "end\n";
    std::this_thread::sleep_for(std::chrono::seconds(15));


    std::cout << "=======================\n";
    return 0;
}