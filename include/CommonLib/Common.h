#pragma once

#include <qglobal.h>

/* Library definitions */
#if defined (COMMON_LIBRARY)
#  define LIBRARY Q_DECL_EXPORT
#else
#  define LIBRARY Q_DECL_IMPORT
#endif

/* Types define */
#include <QTcpServer>
#include <QTcpSocket>

class QTcpServer;
class QTcpSocket;

class Packet;
class Client;

using SocketType = QTcpSocket;
using ServerType = QTcpServer;
using DescriptorType = unsigned int;
