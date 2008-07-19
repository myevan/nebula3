#pragma once
#ifndef INPUT_INPUTSERVER_H
#define INPUT_INPUTSERVER_H
//------------------------------------------------------------------------------
/**
    @class Input::InputServer
    
    The InputServer is the central object of the Input subsystem. It 
    mainly manages a prioritized list of input handlers which process
    incoming input events.

    (C) 2007 Radon Labs GmbH
*/
#include "core/singleton.h"
#if __WIN32__
#include "input/win32/win32inputserver.h"
namespace Input
{
class InputServer : public Win32::Win32InputServer
{
    DeclareClass(InputServer);
    DeclareSingleton(InputServer);
public:
    /// constructor
    InputServer();
    /// destructor
    virtual ~InputServer();
};
} // namespace Input
#elif __XBOX360__
#include "input/xbox360/xbox360inputserver.h"
namespace Input
{
class InputServer : public Xbox360::Xbox360InputServer
{
    DeclareClass(InputServer);
    DeclareSingleton(InputServer);
public:
    /// constructor
    InputServer();
    /// destructor
    virtual ~InputServer();
};
} // namespace Input
#elif __WII__
#include "input/wii/wiiinputserver.h"
namespace Input
{
class InputServer : public Wii::WiiInputServer
{
    DeclareClass(InputServer);
    DeclareSingleton(InputServer);
public:
    /// constructor
    InputServer();
    /// destructor
    virtual ~InputServer();
};
} // namespace Input
#else
#error "InputServer class not implemented on this platform!"
#endif
//------------------------------------------------------------------------------
#endif

   