#define BOOST_ALL_DYN_LINK 1

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

namespace logging = boost::log;
namespace keywords = boost::log::keywords;
namespace attrs = boost::log::attributes;

void init_logging() 
{
    logging::register_simple_formatter_factory<logging::trivial::severity_level, char>("Severity");

    // setting file log format
    logging::add_file_log
    (
        keywords::file_name = "6.write_log_custom_attr.log",
        keywords::format = "[%TimeStamp%] [%ThreadID%] [%Severity%] [%ProcessID%] [%LineID%] [%MyAttr%] [%CountDown%] %Message%"
    );

    // filter severity
    logging::core::get()->set_filter
    (
        logging::trivial::severity >= logging::trivial::info
    );

    // add common attribute
    logging::add_common_attributes();

    // add custom attribute
    logging::core::get()->add_global_attribute("MyAttr", attrs::constant<int>(42));
    logging::core::get()->add_global_attribute("CountDown", attrs::counter<int>(100, -1));
}

int main(int, char*[])
{
    init_logging();

    BOOST_LOG_TRIVIAL(trace) << "This is a trace severity message";
    BOOST_LOG_TRIVIAL(debug) << "This is a debug severity message";
    BOOST_LOG_TRIVIAL(info) << "This is an informational severity message";
    BOOST_LOG_TRIVIAL(warning) << "This is a warning severity message";
    BOOST_LOG_TRIVIAL(error) << "This is an error severity message";
    BOOST_LOG_TRIVIAL(fatal) << "and this is a fatal severity message";
    
    return 0;
}