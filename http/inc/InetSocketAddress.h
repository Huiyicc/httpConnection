#include "HttpException.h"
#include "Comparable.h"
#ifndef INETSOCKETADDRESS_H
#define INETSOCKETADDRESS_H

class InetAddress : public Comparable <InetAddress> {
    std::string ipaddr;
    std::string hostname;
    public:
    InetAddress(std::string host);
    InetAddress(const char *str);
    InetAddress();
    InetAddress(const InetAddress &rhs);
    InetAddress& operator=(const InetAddress &rhs);
    int compareTo(InetAddress &rhs);
    void sethostname(std::string h) { hostname = h; }
    void setipaddr(std::string i) { ipaddr = i; }
    std::string gethostname() { return hostname; }
    std::string getipaddr() { return ipaddr; }
    static InetAddress* getLocalHost();
    static InetAddress* getByName(std::string name) throw (UnknownHostException);
    static void getAllByName(std::string name, vector<InetAddress *> &res) throw (UnknownHostException);
    static void getAllByName(std::string name, vector<InetAddress *> &res, InetAddress* reqAddr) throw (UnknownHostException);
};

class InetSocketAddress {
        struct sockaddr_in si_addr;
        std::string hostname;
        int port;
        bool isResolved(const char *str);
    public:
        InetSocketAddress(std::string host, int port);
        InetSocketAddress(const char *str, int port);
        InetSocketAddress(InetAddress *addr, int port);
        InetSocketAddress();
        InetSocketAddress(const InetSocketAddress &rhs);
        InetSocketAddress& operator=(const InetSocketAddress& rhs);
};
ostream& operator<<(ostream &os, InetAddress &rhs) ;
#endif