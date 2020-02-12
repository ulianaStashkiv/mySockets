#ifndef I_SERVER_SOCKET_HPP
#define I_SERVER_SOCKET_HPP

#include "i_socket.hpp"

class ISocketServer : public ISocket
{
public:
  virtual ~ISocketServer() = default;

  virtual int bind(int sockfd, const struct sockaddr* addr, socklen_t addrlen) = 0;
  virtual int listen(int sockfd, int backlog) = 0;
  virtual int accept(int sockfd, struct sockaddr* addr, socklen_t* addrlen) = 0;
};

#endif // I_SERVER_SOCKET_HPP