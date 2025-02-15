#include "WikiConnection.h"

std::string WikiConnection::getPageName() const
{
	return _pageName;
}

bool WikiConnection::isConnected() const
{
	return _connected;
}
