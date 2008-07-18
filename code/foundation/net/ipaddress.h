#pragma once
#ifndef NET_IPADDRESS_H
#define NET_IPADDRESS_H
//------------------------------------------------------------------------------
/**
    @class Net::IpAddress

    Represents an IP address, consisting of a IPv4 host address
    and a port number. Can extract address information from an URI and    
    automatically converts host names to addresses, and offers the special 
    hostnames "localhost", "any", "broadcast", "self" and "inetself" where:

    - "localhost" will translate to 127.0.0.1
    - "any" will translate to INADDR_ANY, which is 0.0.0.0
    - "broadcast" will translate to INADDR_BROADCAST, which is 255.255.255.255
    - "self" will translate to the first valid tcp/ip address for this host
      (there may be more then one address bound to the host)
    - "inetself" will translate to the first host address which is not 
      a LAN address (which is not a class A, B, or C network) if none such
      exists the address will fall back to "self"

    (C) 2006 Radon Labs GmbH
*/
#if __WIN32__
#include "net/win32/win32ipaddress.h"
namespace Net
{
typedef Win32::Win32IpAddress IpAddress;
}
#elif __XBOX360__
#include "net/xbox360/xbox360ipaddress.h"
namespace Net
{
typedef Xbox360::Xbox360IpAddress IpAddress;
}
#elif __APPLE__
#include "net/posix/posixipaddress.h"
namespace Net
{
typedef Posix::PosixIpAddress IpAddress;
}
#else
#error "IpAddress class not implemented on this platform"
#endif
//------------------------------------------------------------------------------
#endif
