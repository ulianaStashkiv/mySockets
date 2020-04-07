#include "server.hpp" 

#include <fcntl.h>
#include <unistd.h>
#include <algorithm>


Server::Server(std::unique_ptr<ServerSocket> socket, const std::string& path) :
    m_socket{std::move(socket)},
    m_domain{AF_UNIX},
    m_type{SOCK_STREAM},
    m_address{},
    m_isSevrerStarted{false},
    m_activeConnections{},
    m_sQueue{}
{
    ::unlink(m_address.sun_path);
    m_address.sun_family = AF_UNIX;
    path.copy(m_address.sun_path, path.length());

     std::cout << "server constructor" << std::endl;

    createServer();
}

void Server::createServer()
{
    std::cout << "create server" << std::endl;

    createSocket();
    bindSocket();
    listenSocket();

    std::cout << "create server done" << std::endl;

}

void Server::createSocket()
{
    m_socketfd = m_socket->socket(m_domain, m_type, m_protocol);
    
    if(m_socketfd <= 0)
    {
        perror("ERRORRRRRRR createSocket");
        exit(EXIT_FAILURE);
    }
    else
    {
        std::cout << "Server socket was succesfully created" << std::endl;
    }
}

void Server::bindSocket()
{
    int result = m_socket->bind(m_socketfd,
                                 (struct sockaddr*)&m_address,
                                 sizeof(m_address));
    if (-1 == result)
    {
        perror("Error binding data");
        exit(EXIT_FAILURE);
    }
}

void Server::listenSocket()
{
    int result = m_socket->listen(m_socketfd, 5);

    if (-1 == result)
    {
        perror("Error listening in socket");
        exit(EXIT_FAILURE);
    }
}

void Server::start()
{
    m_isSevrerStarted = true;
    m_serverThread = std::thread(&Server::running, this);
    m_serverThread1 = std::thread(&Server::read, this);

}

void Server::send(google::protobuf::Any any)
{
    while (m_isSevrerStarted)
    {
        for (auto it : m_activeConnections)
        {
            it->sendMessage(any);
        }
    }
}

void Server::running()
{
    std::cout << "running\n";
    m_activeConnections.reserve(16);
    
    while (m_isSevrerStarted)
    {
        const std::string path{"/tmp/state_setter"};

        int a = acceptConnection();
        
        if (a > 0)
        {
            auto client = std::make_shared<Client>(std::make_unique<ClientSocket>(), path);
            client->setSocketfd(a);

            const std::lock_guard<std::mutex> lock(mtx1);
            m_activeConnections.push_back(client);
        }
    }
    
    std::cout << "running Done" << std::endl;
}

int Server::acceptConnection()
{
    sockaddr_un clientAddr;
    socklen_t cliLen = sizeof(clientAddr);
    
    int connfd = m_socket->accept(m_socketfd,
                     (struct sockaddr*)&clientAddr,
                     &cliLen);
    if(connfd < 0)
    {
        perror("Error accept connection");
        m_isSevrerStarted = false;
        return -1;
    }

    auto a = fcntl(connfd, F_SETFL, O_NONBLOCK);

    if (a == -1)
    {
        std::cout << "SocketServer: error on fcntl()" << std::endl;
        m_isSevrerStarted = false;
        return -1;
    }

    return connfd;
}

void Server::read()
{
    std::cout << "read\n";
    while (m_isSevrerStarted)
    {
        for (auto it : m_activeConnections)
        {
            readFromSocket(it);
        }
    }
    std::cout << "read done" << std::endl;
}

void Server::readFromSocket(std::shared_ptr<Client> connClient)
{
    bool emptyMes = false;
    std::string recv = connClient->recvMessage(emptyMes);
    
    if (connClient->getRecvBytes() == 0)
    {
        std::cout << "Client closed the connection\n";
        
        const std::lock_guard<std::mutex> lock(mtx);
        m_activeConnections.erase(
            std::remove(m_activeConnections.begin(),
                        m_activeConnections.end(),
                        connClient),
            m_activeConnections.end());
    }
    else if (connClient->getRecvBytes() < 0)
    {
        if (!emptyMes)
        {
            perror("Error on receiving data from client: ");            
        }
    }
    else
    {
        m_sQueue.push(recv);
    }
}

Server::~Server()
{
    std::cout << "~Server" << std::endl;
    stop();

    if (m_socket->close(m_socketfd) == -1)
    {
        std::cout << "SocketServer: error on close()" << std::endl;
    }
   
    ::unlink(m_address.sun_path);
}

void Server::stop()
{
    m_isSevrerStarted = false;
    if (m_serverThread.joinable())
        m_serverThread.join();
    if (m_serverThread1.joinable())
        m_serverThread1.join();
}

std::string Server::getQueue()
{
    return m_sQueue.pop();
}