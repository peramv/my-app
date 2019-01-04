// DSTCCommandLine.cpp : implementation of the DSTCCommandLine class
//

#include "stdafx.h"
#ifndef CONFIGMANAGER_HPP
   #include <ConfigManager.hpp>
#endif
#ifndef DSTCOMMANDLINEINFO_H
   #include "DSTCCommandLineInfo.h"
#endif

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DSTCCommandLine

DSTCCommandLineInfo::DSTCCommandLineInfo() :
_dstrHost( NULL_STRING ),
_bRTS (true),
_bSiteXmlOverrides( false ),
_dstrSiteXml( I_("") ),
lastFlag_(I_(' '))
{
   // TODO: add one-time construction code here
}

DSTCCommandLineInfo::~DSTCCommandLineInfo()
{
}

void DSTCCommandLineInfo::ParseParam( LPCTSTR lpszParam, BOOL bFlag, BOOL bLast )
{
   if( bFlag )
   {
      lastFlag_ = I_(' ');
      switch( lpszParam[0] )
      {
         case 'm' :
            {
               DString dstrtemp (lpszParam);
               dstrtemp = dstrtemp.right (dstrtemp.length() - 1);       
               if( 0 == dstrtemp.length() ) {
                  lastFlag_ = lpszParam[0];
               } else {
                  ConfigManager::setApplication (dstrtemp);
                  _dstrHost = dstrtemp;
               }
             }
             break;
        case 'c' :
            {
               DString dstrtemp (lpszParam);
               dstrtemp = dstrtemp.right ( dstrtemp.length() - 1);
               if( dstrtemp == I_("V") ) {
                  _bRTS = false;
               }
               else {
                  _bRTS = true;
               }
            }
               break;
         case 'S':
         case 's':
            setSiteXmlOverrides( true );
            {
               DString dstrTemp( lpszParam );
               _dstrSiteXml = dstrTemp.right( dstrTemp.length() - 1 );
               if( 0 == _dstrSiteXml.length() ) {
                  lastFlag_ = 'S';
               }
            }
            break;
      }
   }
   else {
      //not a flag ... perhaps a delayed option modifier?
      switch( lastFlag_ ) {
         case 'm':
            {
            DString dstrTemp (lpszParam);
            ConfigManager::setApplication (dstrTemp);
            _dstrHost = dstrTemp;
            }
            break;
         case 'S':
         case 's':
            {
            DString dstrTemp (lpszParam);
            _dstrSiteXml = dstrTemp;
            }
            break;
     }
   }

}

