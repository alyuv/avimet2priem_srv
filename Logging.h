#pragma once
#include <fstream>
#include <iostream>
#include <stdexcept>

#include <boost/locale.hpp>
#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sources/logger.hpp>

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/async_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sinks/bounded_fifo_queue.hpp>
#include <boost/log/sinks/drop_on_overflow.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include <boost/log/support/date_time.hpp>

#include <boost/log/core.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

namespace blogging = boost::log;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;
namespace attrs = boost::log::attributes;

using boost::shared_ptr;

typedef sinks::asynchronous_sink<
	sinks::text_ostream_backend,
	sinks::bounded_fifo_queue<                                               /*< log record queueing strategy >*/
	100,                                                                     /*< record queue capacity >*/
	sinks::drop_on_overflow                                                  /*< overflow handling policy >*/
	>
> sink_t;

typedef sinks::synchronous_sink< sinks::text_file_backend > file_sink;

class Logging
{
public:
	Logging();
	~Logging();
	std::string CheckDate(std::string message);
	std::string Logging::CurrentDate();
	boost::shared_ptr< sink_t > InitIramloggingSink();
	void StopIramLoggingSink(boost::shared_ptr< sink_t >& sink);	
	int IramRotatingFileSink(std::string message);
	
	void InitFileCollecting(boost::shared_ptr< file_sink > sink);
	void InitLogging();

	shared_ptr< file_sink > InitIramLogging();	
	void StopIramLogging(shared_ptr< file_sink > sink);
	int IramRotatingFile(std::string message);		
	
	std::string dirIRAM = "D:\\IRAM\\ARX_PROT\\";
	std::string CurrDate;
	shared_ptr< file_sink > sink;
};
