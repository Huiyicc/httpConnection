#ifndef SOCKETIMPLFACTORY_H
#define SOCKETIMPLFACTORY_H
class SocketImplFactory {
    public:
    SocketImplFactory() { }
    virtual ~SocketImplFactory() { }
    SocketImpl *createSocketImpl() = 0;
};
#endif
