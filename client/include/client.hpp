#ifndef CLIENT
#define CLIENT

#include <client_socket.hpp>

#include <memory>
#include <string>
#include <sys/un.h>

class Client
{
public:
    Client(std::unique_ptr<ClientSocket>, const std::string&);

    void connectToServer();

    template < typename T >
    void sendMessage(const T& message)
    {
        size_t size = message.ByteSizeLong();
        uint8_t* data = new uint8_t[size]; // unique_ptr or delete[]
        if(message.SerializeToArray(data, size))
        {
            m_socket->send(m_socketfd, data, size, 0);
        }
    }

    std::string recvMessage(bool&);

    int getSocketfd();
    ssize_t getRecvBytes();

    void setSocketfd(int);
    void setRecvBytes(ssize_t byte);

    ~Client();

private:
    void createSocket(int, int, int);
    
private:
    std::unique_ptr<ClientSocket> m_socket;
    int m_socketfd;
    int m_domain, m_type, m_protocol = 0;

    struct sockaddr_un m_address;
    struct sockaddr_un m_servAddr;

    ssize_t m_recvBytes;
};


#endif //CLIENT
