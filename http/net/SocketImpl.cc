#include "HttpException.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h>
#include "NameResolver.h"
#include "InetSocketAddress.h"
#ifndef SOCKET_H
#include "Socket.h"
#endif
#ifndef SOCKETIMPL_H
#include "SocketImpl.h"
#endif
void SocketImpl::socketCreate(bool isServer) throw(IOException) {
    if (isServer) fd = socket(AF_INET, SOCK_STREAM, 0);
    else fd = socket(AF_INET, SOCK_DGRAM, 0);
}
void SocketImpl::socketConnect(InetAddress *address, int port, int timeout) throw (IOException) {
    std::string errMsg = "unable to connect to: ";
    InetSocketAddress i(address, port);
    int rc = ::connect(fd, (struct sockaddr *)i.getSockAddress(), sizeof(struct sockaddr_in));
    if (rc == 0 || errno == EINPROGRESS || errno == EAGAIN) return;
    close(fd);
    errMsg.append(address->gethostname());
    throw IOException(errMsg.c_str());
}
void SocketImpl::socketBind(InetAddress *address, int port) throw (IOException) {
}
void SocketImpl::socketListen(int count) throw (IOException) {
}
void SocketImpl::socketAccept(SocketImpl *s) throw (IOException) {
}
int SocketImpl::socketAvailable() throw (IOException) {
}
void SocketImpl::socketShutdown(int howto) throw (IOException) {
}
void SocketImpl::socketSendUrgentData(int data) throw (IOException) {
}
