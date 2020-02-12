#include "client.hpp"

int main(int argc, char const *argv[])
{
    std::unique_ptr<ClientSocket> clientPtr = std::make_unique<ClientSocket>();

    const std::string path = "/tmp/state_setter";
    const std::string message = "Client2.";

    Client myClient {std::move(clientPtr), path};

    myClient.connectToServer();
    //myClient.sendMessage(message);
    return 0;
}