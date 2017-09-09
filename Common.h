#include "stdafx.h"
#include <string>
#include <iostream>

#include <boost/algorithm/string/replace.hpp>

std::string ConvertASCII(std::string str)
{
	boost::replace_all(str, "\x00", "<NULL>");	boost::replace_all(str, "\x10", "<DLE>");
	boost::replace_all(str, "\x01", "<SOH>");	boost::replace_all(str, "\x11", "<DC1>");
	boost::replace_all(str, "\x02", "<STX>");	boost::replace_all(str, "\x12", "<DC2>");
	boost::replace_all(str, "\x03", "<ETX>");	boost::replace_all(str, "\x13", "<DC3>");
	boost::replace_all(str, "\x04", "<EOT>");	boost::replace_all(str, "\x14", "<DC4>");
	boost::replace_all(str, "\x05", "<ENQ>");	boost::replace_all(str, "\x15", "<NAK>");
	boost::replace_all(str, "\x06", "<ACK>");	boost::replace_all(str, "\x16", "<SYN>");
	boost::replace_all(str, "\x07", "<BEL>");	boost::replace_all(str, "\x17", "<ETB>");
	boost::replace_all(str, "\x08", "<BS>");	boost::replace_all(str, "\x18", "<CAN>");
	boost::replace_all(str, "\x09", "<TAB>");	boost::replace_all(str, "\x19", "<EM>");
	boost::replace_all(str, "\x0A", "<LF>");	boost::replace_all(str, "\x1A", "<SUB>");
	boost::replace_all(str, "\x0B", "<VT>");	boost::replace_all(str, "\x1B", "<ESC>");
	boost::replace_all(str, "\x0C", "<FF>");	boost::replace_all(str, "\x1C", "<FS>");
	boost::replace_all(str, "\x0D", "<CR>");	boost::replace_all(str, "\x1D", "<GS>");
	boost::replace_all(str, "\x0E", "<SO>");	boost::replace_all(str, "\x1E", "<RS>");
	boost::replace_all(str, "\x0F", "<SI>");	boost::replace_all(str, "\x1F", "<US>");

	return str;
}


