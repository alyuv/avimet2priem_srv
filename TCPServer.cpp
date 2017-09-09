#include "stdafx.h"

#include "TCPServer.h"

#include <boost/asio.hpp>

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/lexical_cast.hpp>

using boost::asio::ip::tcp;
Logging logging;
//SinkLogging sinklogging;

Session::Session(tcp::socket socket) : socket_(std::move(socket))
{
	//strstream << "Receive data from " << soc
	//logging.IramRotatingFile("Start tcp server on port 10024");
}

void Session::start()
{	
	do_read();
}


void Session::do_read()
{
	auto self(shared_from_this());
	socket_.async_read_some(boost::asio::buffer(data_, max_length),
		[this, self](boost::system::error_code ec, std::size_t length)
	{
		if (!ec)
		{
			std::string message(data_);
			message.erase(message.length() - (message.length() - length));			
			strstream << "Receive data from " << socket_.remote_endpoint().address().to_string() << ":" << socket_.remote_endpoint().port() << " " << message;
			logging.IramRotatingFile(strstream.str());	
			std::ofstream outfile("D:\\IRAM\\TEK\\Priem7\\AWOS\\last.dat");
			outfile << message << std::endl;
			outfile.close();		
		}
	});
}

TCPServer::TCPServer(boost::asio::io_service& io_service, short port)
: acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
socket_(io_service)
{
	do_accept();	
}

void TCPServer::do_accept()
{
	acceptor_.async_accept(socket_,
		[this](boost::system::error_code ec)
	{
		if (!ec)
		{
			std::make_shared<Session>(std::move(socket_))->start();			
		}

		do_accept();		
	});
}