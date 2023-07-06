#include <iostream>
#include <boost/asio.hpp>

using namespace std;
using namespace boost;

class ip_address
{
    private:
    //Address to check details.
    string host;
    string port_num;
    boost::system::error_code ec;
    asio::io_service ios;
    asio::ip::tcp::endpoint endpoint;
    public:
    ip_address(string flag = "" , string user_port = "443",string user_host = "localhost")
    :port_num(user_port) , host(user_host)
    {
        if(flag == "")
        {
            cout << "Basic information for : [ " << host << " ]......."<<endl;
            asio::ip::tcp::resolver::iterator dns_it = ResolveDns();
            basicInformation(dns_it);
            cout<<"\n"<<endl;
        }
        if(flag == "-a")
        {
            cout << "Extra information for : [ " << host << " ]......."<<endl;
            asio::ip::tcp::resolver::iterator dns_it = ResolveDns();
            endpoint = ResolveDns()->endpoint();
            additionalInformation();
            cout<<"\n\n"<<endl;
        }

    }

    //check the ip address provided.
    string bool_verifier(bool x)
    {
        if(x == 1)
        {
            return "true";
        }
        
        return "false";
    }
    asio::ip::tcp::resolver::iterator ResolveDns();
    void additionalInformation();
    void basicInformation(asio::ip::tcp::resolver::iterator &it);

};

//For efficient implementation tcp protocol is used.
asio::ip::tcp::resolver::iterator ip_address::ResolveDns()
{
    //Create DNS query.
    asio::ip::tcp::resolver::query resolver_query(host,port_num,asio::ip::tcp::resolver::query::numeric_service);
    // A resolver for resolving DNS requests
    asio::ip::tcp::resolver resolver(ios);
    //resolve the IP address
    asio::ip::tcp::resolver::iterator it = resolver.resolve(resolver_query,ec);
    if(ec.value() != 0)
    {
        cout << "Error in resolving DNS : "<<ec.value() << " .message " <<ec.message() <<endl;
        exit(1);
    }
    else
    {
        return it;
    }
}

void ip_address::basicInformation(asio::ip::tcp::resolver::iterator &it)
{
    string  address = it->endpoint().address().to_string();
    string host_name = it->host_name();
    string service_name = it->service_name();
    cout << "ip address : " << address << endl;
    cout << "host_name : " << host_name << endl;
    cout << "service_name : " << service_name << endl;
}

void ip_address::additionalInformation()
{
    bool is_multicast = endpoint.address().is_multicast();
    bool is_ipv4 = endpoint.address().is_v4();
    bool is_ipv6 = endpoint.address().is_v6();
    bool is_loopback = endpoint.address().is_loopback();
    cout <<"Address is multicast : "<< bool_verifier(is_multicast)<<endl;
    cout <<"Address is ipv4 : "<< bool_verifier(is_ipv4)<<endl;
    cout <<"Address is ipv6 : "<< bool_verifier(is_ipv6)<<endl;
    cout <<"Address is loopback : "<< bool_verifier(is_loopback)<<endl;
}