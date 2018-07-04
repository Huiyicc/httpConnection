#include "HttpException.h"
#ifndef ABSTRACTPLAINSOCKETIMPL_H
#define ABSTRACTPLAINSOCKETIMPL_H
class AbstractPlainSocketImpl : public SocketImpl {
    class Lock {
        pthread_mutex_t &m;
        public:
        Lock(pthread_mutex_t &t): m(t) {
            pthread_mutex_lock(&m);
        }
        ~Lock() { 
            pthread_mutex_unlock(&m);
        }
    };
    private:
        SocketInputStream *socketInputStream;
        SocketOutputStream *socketOutputStream;
        int fd;
        int port;
        int localport;
        InetAddress *address;
        static int SHUT_RD;
        static int SHUT_WR;
        int CONNECTION_NOT_RESET;
        int CONNECTION_RESET_PENDING;
        int CONNECTION_RESET;
        int resetState;
        bool shut_rd;
        bool shut_wr;
        int trafficClass;
        int timeout;
    protected:
        pthread_mutex_t fdLock;
        pthread_mutex_t resetLock;
        int fdUseCount;
        void create(bool stream);
        void connect(std::string host, int port) throw (UnknownHostException, IOException);
        void connect(InetAddress* addr, int p) throw (IOException) ;
        void connectToAddress(InetAddress* addr, int p, int t) throw (IOException);
        void bind(InetAddress host, int port);
        void listen(int baclog);
        void accept(SocketImpl *s);
        InputStream *getInputStream();
        OutputStream *getOutputStream();
        int available();
        void close();
        void socketClose();
    public:
        AbstractPlainSocketImpl();
        void shutdownInput();
        void shutdownOutput();
        int getFileDescriptor();
        int getPort();
        InetAddress* getInetAddress();
        int getLocalPort();
        void setOption(int opt, int val);
        int getOption(int opt);
        void sendUrgentData (int data);
        int getTimeout();
        void setInputStream(SocketInputStream *in) { socketInputStream = in; }
        void setFileDescriptor(int f) { fd = f; }
        void setAddress(InetAddress *addr) { address = addr; }
        void setPort(int p) { port = p; }
        void setLocalPort(int l) { localport = l; }
        bool isConnectionReset();
        bool isConnectionResetPending();
        void setConnectionReset();
        void setConnectionResetPending();
        bool isClosedOrPending();
        void socketCreate(bool isServer) throw(IOException) = 0;
        void socketConnect(InetAddress *address, int port, int timeout) throw (IOException) = 0;
        void socketBind(InetAddress *address, int port) throw (IOException) = 0;
        void socketListen(int count) throw (IOException) = 0;
        void socketAccept(SocketImpl *s) throw (IOException) = 0;
        int socketAvailable() throw (IOException) = 0;
        void socketShutdown(int howto) throw (IOException) = 0;
        void socketSendUrgentData(int data) throw (IOException) = 0;
};
#endif