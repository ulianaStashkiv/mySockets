#ifndef CLIENT_SOCKET_HPP
#define CLIENT_SOCKET_HPP

#include "i_client_socket.hpp"

class ClientSocket : IClientSocket
{
public:  
  virtual ~ClientSocket() = default;

  int socket(int domain, int type, int protocol) override;
  int close(int sockfd) override;

  int connect(int sockfd, const struct sockaddr* addr, socklen_t addrlen) override;
  void send(int sockfd, const void *buf, size_t len, int flags) override;
  ssize_t recv(int sockfd, char *buf, size_t len, int flags) override;
};

#endif // CLIENT_SOCKET_HPP