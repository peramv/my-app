#pragma once

//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2000 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : ConsoleMenu.hpp
// ^AUTHOR : David B. Smith 
// ^DATE   : December 2002
//
// ^CLASS    : ConsoleMenu
// ^INHERITS FROM :          
//
// ^CLASS DESCRIPTION : 
//    This class encapsualtes and paints the menu/legend console canvas.
//    
//
//******************************************************************************
#include <win32\platform.h>

class ConsoleCanvas;

class ConsoleMenu
{
public:
   ConsoleMenu();
   virtual ~ConsoleMenu();

   ConsoleCanvas *pCanvas_;

};

class ConsoleAppInfo 
{
public:
   ConsoleAppInfo( const DString &appDesc );
   virtual ~ConsoleAppInfo();

private:
   ConsoleCanvas* pCanvas_;

};




//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbps/ConsoleMenu.hpp-arc  $
//
//   Rev 1.2   Jan 27 2005 16:32:46   smithdav
//Add console display information.
//
//   Rev 1.1   Oct 09 2002 23:53:46   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.0   10 May 2002 13:03:40   SMITHDAV
//Initial revision.
*/