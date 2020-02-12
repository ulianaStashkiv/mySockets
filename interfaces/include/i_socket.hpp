#ifndef I_SOCKET_HPP
#define I_SOCKET_HPP

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>

class ISocket
{
public:
  virtual ~ISocket() = default;

  virtual int socket(int domain, int type, int protocol) = 0;
  virtual int close(int sockfd) = 0 ;
};

#endif // I_SOCKET_SERVER_HPP