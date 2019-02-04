#define BOOST_ALL_DYN_LINK 1

#include <iostream>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;
namespace attrs = boost::log::attributes;

void init_logging() {
    logging::register_simple_formatter_factory<logging::trivial::severity_level, char>("Severity");

        // setting file log format
    logging::add_file_log
    (
        keywords::file_name = "7.log_rotation_size_%m-%d-%Y_%H:%M:%S.log",                              /* filename */
        keywords::rotation_size = 10 * 1024 * 1024,                                                     /* rotate file every 10mb */
        keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),                 /* rotate at midnite */
        keywords::format = "[%TimeStamp%] [%ThreadID%] [%Severity%] [%ProcessID%] [%LineID%] %Message%" /* format */
    );

        // filter severity
    logging::core::get()->set_filter
    (
        logging::trivial::severity >= logging::trivial::info
    );

    // helpers function adds attributes such as "Timestamp" and "ThreadID"
    logging::add_common_attributes();
}

int main(int, char*[])
{
    init_logging();

    while(1) {
        BOOST_LOG_TRIVIAL(trace) << "This is a trace severity message";
        BOOST_LOG_TRIVIAL(debug) << "This is a debug severity message";
        BOOST_LOG_TRIVIAL(info) << "This is an informational severity message";
        BOOST_LOG_TRIVIAL(warning) << "This is a warning severity message";
        BOOST_LOG_TRIVIAL(error) << "This is an error severity message";
        BOOST_LOG_TRIVIAL(fatal) << "and this is a fatal severity message";

        std::cout << "yeah" << std::endl;

        std::cin.get();
    }

    return 0;
}