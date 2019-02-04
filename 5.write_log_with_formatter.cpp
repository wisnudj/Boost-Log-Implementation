#define BOOST_ALL_DYN_LINK 1

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

namespace logging = boost::log;
namespace keywords = boost::log::keywords;

int main(int, char*[])
{
    logging::register_simple_formatter_factory<logging::trivial::severity_level, char>("Severity");

    // settting file name and format log
    logging::add_file_log(
        keywords::file_name = "5.write_log_with_formatter.log",
        keywords::format = "[%TimeStamp%] [%ThreadID%] [%Severity%] [%ProcessID%] [%LineID%] %Message%"
    );

    // filter severity
    logging::core::get()->set_filter(
        logging::trivial::severity >= logging::trivial::info
    );

    // helpers function adds attributes such as "Timestamp" and "ThreadID"
    logging::add_common_attributes();


    BOOST_LOG_TRIVIAL(trace) << "This is a trace severity message";
    BOOST_LOG_TRIVIAL(debug) << "This is a debug severity message";
    BOOST_LOG_TRIVIAL(info) << "This is an informational severity message";
    BOOST_LOG_TRIVIAL(warning) << "This is a warning severity message";
    BOOST_LOG_TRIVIAL(error) << "This is an error severity message";
    BOOST_LOG_TRIVIAL(fatal) << "and this is a fatal severity message";

    return 0;
}