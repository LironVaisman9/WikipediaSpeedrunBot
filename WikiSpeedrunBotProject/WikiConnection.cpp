#include "WikiConnection.h"

WikiConnection::WikiConnection() = default;

WikiConnection::WikiConnection(const std::string& pageName)
	: _pageName(pageName)
{
}

WikiConnection::~WikiConnection() = default;

std::string WikiConnection::getPageName() const
{
	return _pageName;
}

bool WikiConnection::isConnected() const
{
	return _connected;
}
