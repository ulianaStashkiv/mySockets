#include "client.hpp"

#include <any.pb.h>
#include <application_state_management.pb.h>

#include <thread>
#include <chrono>

using namespace ApplicationStateManagement;


int main(int argc, char const *argv[])
{
    std::unique_ptr<ClientSocket> clientPtr = std::make_unique<ClientSocket>();

    const std::string path = "/tmp/state_setter";
    const std::string message = "Hello word.";

    registerComponent comp;

    comp.set_appname(message);
    comp.set_state(enums::ApplicationState::kInitializing);

    google::protobuf::Any any;
    any.PackFrom(comp);

    Client myClient {std::move(clientPtr), path};

    std::cout<< "client connect to sertver\n";
    myClient.connectToServer();
    std::cout<< "client send to sertver\n";
    myClient.sendMessage(any);
    return 0;
}