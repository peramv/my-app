#ifndef AWDOFF_H
#define AWDOFF_H

// awdoff.h : header file
//

#include <awdapp.xh>

#define AWD_LOGGING_OFF_STR "AWD Logging Off"

/////////////////////////////////////////////////////////////////////////////
// AWDLogoff Class

class AWDLogoff
{
   public:
      __declspec(dllexport) AWDLogoff( boolean showLogoffMsgbox = TRUE );
      __declspec(dllexport) virtual ~AWDLogoff();
      __declspec(dllexport) boolean logoff();

private:
      /*----------------------------------------------------------------------*\
      |* Private methods:                                                     *|
      \*----------------------------------------------------------------------*/
      void initialize();

      /*----------------------------------------------------------------------*\
      |* Private data:                                                        *|
      \*----------------------------------------------------------------------*/
      Environment*            ev;
      AWDApplication*         pApp;
      boolean                 showLogoffMsg;

};

#endif
