#include "client_socket.hpp"

#include "unistd.h"

int ClientSocket::socket(int domain, int type, int protocol)
{
  return ::socket(domain, type, protocol);
}

int ClientSocket::close(int fd)
{
  return ::close(fd);
}

int ClientSocket::connect(int sockfd, const struct sockaddr* addr, socklen_t addrlen)
{
    return ::connect(sockfd, addr, addrlen);
}

void ClientSocket::send(int sockfd, const void *buf, size_t len, int flags)
{
    ::send(sockfd, buf, len, flags);
}

ssize_t ClientSocket::recv(int sockfd, char *buf, size_t len, int flags)
{
  return ::recv(sockfd, buf, len, flags);
}