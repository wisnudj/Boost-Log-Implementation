#define BOOST_ALL_DYN_LINK

#include <iostream>
#include <boost/log/trivial.hpp>

int main(int, char*[])
{
    BOOST_LOG_TRIVIAL(info) << "This is an informational severity message";
    return 0;
}
