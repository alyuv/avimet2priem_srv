#pragma once

#include <string>
#include <fstream>
#include <iostream>

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

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

//[ example_sinks_bounded_async_init
// Complete sink type
typedef sinks::asynchronous_sink<
	sinks::text_ostream_backend,
	sinks::bounded_fifo_queue<                                               /*< log record queueing strategy >*/
	100,                                                                     /*< record queue capacity >*/
	sinks::drop_on_overflow                                                  /*< overflow handling policy >*/
	>
> sink_t;

class SinkLogging
{
public:
	SinkLogging();
	~SinkLogging();

	boost::shared_ptr< sink_t > InitIramlogging();
	void StopIramLogging(boost::shared_ptr< sink_t >& sink);
};

