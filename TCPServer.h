#pragma once

#include <boost/asio.hpp>

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include "Logging.h"
//#include "SinksLogging.h"


using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session>
{
public:
	Session(tcp::socket socket);
	void start();
private:
	void do_read();
	tcp::socket socket_;
	enum { max_length = 1024 };
	char data_[max_length];	
	std::stringstream strstream;
};

class TCPServer
{
public:
	TCPServer(boost::asio::io_service& io_service, short port);
	void do_accept();
private:
	tcp::acceptor acceptor_;
	tcp::socket socket_;		
};

