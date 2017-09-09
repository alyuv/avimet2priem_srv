#include "SinksLogging.h"

SinkLogging::SinkLogging()
{

}

SinkLogging::~SinkLogging()
{

}


enum severity_level
{
        normal,
        warning,
        error
};

boost::shared_ptr< sink_t > SinkLogging::InitIramlogging()
{
        boost::shared_ptr< logging::core > core = logging::core::get();

        // Create a backend and initialize it with a stream
        boost::shared_ptr< sinks::text_ostream_backend > backend =
                boost::make_shared< sinks::text_ostream_backend >();
        backend->add_stream(
                boost::shared_ptr< std::ostream >(&std::clog, boost::null_deleter()));

        // Wrap it into the frontend and register in the core
        boost::shared_ptr< sink_t > sink(new sink_t(backend));
        core->add_sink(sink);

        // ...
        //<-
        // You can manage filtering and formatting through the sink interface
        sink->set_filter(expr::attr< severity_level >("Severity") >= warning);
        sink->set_formatter
                (
                expr::stream
                << "Level: " << expr::attr< severity_level >("Severity")
                << " Message: " << expr::message
                );

        // You can also manage backend in a thread-safe manner
        {
                sink_t::locked_backend_ptr p = sink->locked_backend();
                p->add_stream(boost::make_shared< std::ofstream >("sample.log"));
        }
        //->

        return sink;
}
//]

void SinkLogging::StopIramLogging(boost::shared_ptr< sink_t >& sink)
{
        boost::shared_ptr< logging::core > core = logging::core::get();

        // Remove the sink from the core, so that no records are passed to it
        core->remove_sink(sink);

        // Break the feeding loop
        sink->stop();

        // Flush all log records that may have left buffered
        sink->flush();

        sink.reset();
}

