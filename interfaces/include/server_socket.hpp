#ifndef SERVER_SOCKET_HPP
#define SERVER_SOCKET_HPP

#include "i_server_socket.hpp"

class ServerSocket : public ISocketServer
{
public:  
  virtual ~ServerSocket() = default;

  int socket(int domain, int type, int protocol) override;
  int close(int sockfd) override;

  int bind(int sockfd, const struct sockaddr* addr, socklen_t addrlen) override;
  int listen(int sockfd, int backlog) override;
  int accept(int sockfd, struct sockaddr* addr, socklen_t* addrlen) override;
};

#endif // SERVER_SOCKET_HPP