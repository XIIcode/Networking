#include <iostream>
#include <boost/asio.hpp>

using namespace std;
using namespace boost;

int main(int argc,char** argv)
{
    string host = "www.google.com";
    string port_num = "3333";
    host = argv[1];
    asio::io_service ios;
    boost::system::error_code ec;

    asio::ip::tcp::resolver::query resolver_query(host, port_num,asio::ip::tcp::resolver::query::numeric_service);

    asio::ip::tcp::resolver resolver(ios);
    asio::ip::tcp::resolver::iterator it = resolver.resolve(resolver_query,ec);

    asio::ip::tcp::resolver::iterator end_it;
    cout << "Addresses for : " << host <<endl;
    for(; it != end_it; ++it)
    {
        asio::ip::tcp::endpoint endpoint = it->endpoint();
        string address = endpoint.address().to_string();
        cout << address << endl;
    }

}