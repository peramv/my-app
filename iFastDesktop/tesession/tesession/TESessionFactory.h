// TESessionFactory.h: interface for the TESessionFactory class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <tesession\TESession.h>

class TESessionFactory  
{
public:

   static TESession *CreateTESession(HWND hWnd, const std::string &TEKey, const std::string &param, const std::string &host);
   static void ReleaseTESession(TESession *session);

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/tesession/tesession/TESessionFactory.h-arc  $
 * 
 *    Rev 1.3   Nov 24 2003 16:00:58   HSUCHIN
 * PTS 10020087 - Enhanced to take host information.
 */