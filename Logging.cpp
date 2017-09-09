#include "stdafx.h"
#include "Logging.h"
#include "Common.h"

Logging::Logging()
{
}

Logging::~Logging()
{
}


std::string Logging::CheckDate(std::string strdate)
{
        return strdate;
}

std::string Logging::CurrentDate()
{
        using namespace boost::posix_time;
        using namespace boost::gregorian;
        using namespace boost::local_time;
        using namespace boost::local_time;

        date today;
        ptime now;
        date_facet* date_output;
        std::stringstream ss, ssmessage;

        now = second_clock::universal_time();
        today = now.date();
        date_output = new date_facet();
        ss.imbue(std::locale(ss.getloc(), date_output));
        date_output->format("G%Y\\M%m\\D%d\\");
        ss << today;

        return ss.str();
}


enum severity_level
{
        normal,
        warning,
        error
};

boost::shared_ptr< sink_t > Logging::InitIramloggingSink()
{
        CurrDate = CurrentDate();

        boost::shared_ptr< blogging::core > core = blogging::core::get();

        boost::shared_ptr< sinks::text_ostream_backend > backend =
                boost::make_shared< sinks::text_ostream_backend >();
        backend->add_stream(
                boost::shared_ptr< std::ostream >(&std::clog, boost::null_deleter()));

        boost::shared_ptr< sink_t > sink(new sink_t(backend));
        core->add_sink(sink);   

        sink->set_filter(expr::attr< severity_level >("Severity") >= warning);
        sink->set_formatter
                (
                expr::stream
                << "Level: " << expr::attr< severity_level >("Severity")
                << expr::smessage
                );

        {
                sink_t::locked_backend_ptr p = sink->locked_backend();
                p->add_stream(boost::make_shared< std::ofstream >(dirIRAM + CurrDate + "avimet2priem7.log"));
        }

        return sink;
}

void Logging::StopIramLoggingSink(boost::shared_ptr< sink_t >& sink)
{
        boost::shared_ptr< blogging::core > core = blogging::core::get();

        core->remove_sink(sink);

        sink->stop();

        sink->flush();

        sink.reset();
}


void Logging::InitFileCollecting(boost::shared_ptr< file_sink > sink)
{
        sink->locked_backend()->set_file_collector(sinks::file::make_collector(
                keywords::target = "Logging"
                ));
}


void Logging::InitLogging()
{
        boost::shared_ptr< file_sink > sink(new file_sink(
                keywords::file_name = dirIRAM + CurrDate + "avimet2priem7.log", 
                keywords::auto_flush = true,
                keywords::open_mode = std::ios_base::app
                ));

        InitFileCollecting(sink);

        sink->locked_backend()->scan_for_files();

        sink->set_formatter(
                expr::format("%1%; %2%")
                % expr::smessage
                );
        blogging::core::get()->add_sink(sink);
        blogging::core::get()->add_global_attribute("TimeStamp", attrs::utc_clock());

}

shared_ptr< file_sink > Logging::InitIramLogging()
{               
        CurrDate = CurrentDate();
        shared_ptr< file_sink > sink(new file_sink(
                keywords::auto_flush = true,
                keywords::open_mode = std::ios_base::app,
                keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0)   /*< ...or at midnight >*/
                ));

        blogging::core::get()->add_sink(sink);

        sink->set_formatter(
                expr::format("%1%; %2%")
                % expr::smessage
                );

        blogging::core::get()->add_global_attribute("TimeStamp", attrs::utc_clock());
        return sink;
}



void Logging::StopIramLogging(shared_ptr< file_sink > sink) 
{
        blogging::core::get()->remove_sink(sink);
}

int Logging::IramRotatingFile(std::string message)
{
        try
        {               
                if      (CurrDate != CurrentDate())
                {
                        if (!sink)
                        {
                                sink = InitIramLogging();
                        }

                        else 
                        { 
                                StopIramLogging(sink);
                                sink = InitIramLogging();
                        }

                }

                src::logger lggr;               
                BOOST_LOG(lggr) << ConvertASCII((message));
                return 0;

        }
        catch (std::exception& e)
        {
                std::cout << "FAILURE: " << e.what() << std::endl;
                return 1;
        }
}

int Logging::IramRotatingFileSink(std::string message)
{
        return 0;
}


