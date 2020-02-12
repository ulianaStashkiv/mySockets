#ifndef SERVER
#define SERVER

#include <server_socket.hpp>
#include <i_server.hpp>
#include <client.hpp>

#include <atomic>
#include <mutex>
#include <poll.h>
#include <sys/un.h>
#include <thread>
#include <vector>

class Server : public IServer
{
public:
    Server(std::unique_ptr<ServerSocket>, const std::string&);
    
    void start() override;
    void stop() override;

    int acceptConnection();
    void readFromSocket(std::shared_ptr<Client>);
    void running();
    void read();

    ~Server() override;

private:
    void createServer();
    void createSocket();
    void bindSocket();
    void listenSocket();

private:
    std::unique_ptr<ServerSocket> m_socket;
    int m_domain, m_type, m_protocol = 0;
    int m_socketfd;

    struct sockaddr_un m_address;

    std::atomic_bool m_isSevrerStarted;
    
    std::vector<std::shared_ptr<Client>> m_activeConnections;
    
    std::thread m_serverThread;
    std::thread m_serverThread1;
    std::mutex mtx;
    std::mutex mtx1;
};

#endif // SERVER