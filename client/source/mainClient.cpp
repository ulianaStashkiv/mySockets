#include "client.hpp"

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

    Client myClient {std::move(clientPtr), path};

    myClient.connectToServer();
    myClient.sendMessage(comp);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    myClient.sendMessage(comp);
    return 0;
}