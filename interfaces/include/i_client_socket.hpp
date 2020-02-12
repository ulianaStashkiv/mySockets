#ifndef I_CLIENT_SOCKET_HPP
#define I_CLIENT_SOCKET_HPP

#include "i_socket.hpp"

class IClientSocket : public ISocket
{
public:
  virtual ~IClientSocket() = default;

  virtual int connect(int sockfd, const struct sockaddr* addr, socklen_t addrlen) = 0;
  virtual void send(int sockfd, const void *buf, size_t len, int flags) = 0;
  virtual ssize_t recv(int sockfd, char *buf, size_t len, int flags) = 0;
};

#endif // I_CLIENT_SOCKET_HPP