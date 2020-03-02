#include "client.hpp"

Client::Client(std::unique_ptr<ClientSocket> socket, const std::string& path) :
    m_socket{std::move(socket)},
    m_domain{AF_UNIX},
    m_type{SOCK_STREAM},
    m_servAddr{}
{
    m_servAddr.sun_family = AF_UNIX;
    path.copy(m_servAddr.sun_path, path.length());
}

void Client::createSocket(int domain, int type, int protocol)
{
    m_socketfd = m_socket->socket(domain, type, protocol);
    
    if(m_socketfd <= 0)
    {
        perror("ERRORRRRRRR createSocket");
    }
    else
    {
        std::cout << "Client socket was succesfully created" << std::endl;
    }
    
}

void Client::connectToServer()
{
    createSocket(m_domain, m_type, m_protocol);

    int result = m_socket->connect(m_socketfd, (struct sockaddr*)&m_servAddr, sizeof(m_servAddr));
    if(result < 0)
    {
        perror("Client: Connect Error");
        exit(EXIT_FAILURE);
    }
    std::cout << "Connected" << std::endl;
}

std::string Client::recvMessage(bool& empty)
{
    const int buffSize = 1000;
    char buff[buffSize];
    
    m_recvBytes = m_socket->recv(m_socketfd, buff, buffSize, 0);

    if (m_recvBytes == -1 && errno == EWOULDBLOCK)
    {
        empty = true;
    }
    
    //tmp.ParseFromArray(buff, buffSize);

    return buff;
}

Client::~Client()
{
    m_socket->close(m_socketfd);
}


int Client::getSocketfd()
{
    return m_socketfd;
}

ssize_t Client::getRecvBytes()
{
    return m_recvBytes;
}

void Client::setSocketfd(int fd)
{
    m_socketfd = fd;
}

void Client::setRecvBytes(ssize_t byte)
{
    m_recvBytes = byte;
}