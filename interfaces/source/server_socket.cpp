#include "server_socket.hpp"

#include <unistd.h>

int ServerSocket::socket(int domain, int type, int protocol)
{
  return ::socket(domain, type, protocol);
}

int ServerSocket::close(int fd)
{
  return ::close(fd);
}

int ServerSocket::bind(int sockfd, const struct sockaddr* addr, socklen_t addrlen)
{
  return ::bind(sockfd, addr, addrlen);
}

int ServerSocket::accept(int sockfd, struct sockaddr* addr, socklen_t* addrlen)
{
  return ::accept(sockfd, addr, addrlen);
}

int ServerSocket::listen(int sockfd, int backlog)
{
  return ::listen(sockfd, backlog);
}
