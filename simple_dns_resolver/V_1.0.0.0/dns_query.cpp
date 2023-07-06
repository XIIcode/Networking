#include <iostream>
#include "dns_resolve.hh"
using namespace std;


int main(int argc, char** argv)
{
    for(int i = 1; i <argc; i++)
    {
        ip_address address("","443",argv[i]);
        ip_address additional_address("-a","443",argv[i]);
    }
    return 0;
}