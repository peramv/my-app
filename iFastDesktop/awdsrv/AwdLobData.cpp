//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2005 by International Financial Data Services
//
//
//******************************************************************************
//******************************************************************************
//
// ^FILE   : AwdLobData.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Oct. 21, 2005
//
// ^CLASS    : AwdLobData
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//********************************************************************************

#include "stdafx.h"
#include "awdstrct.h"
#include "AwdLobData.hpp"

namespace 
{
   const int MAX_NAME_LENGTH     = 4;
   const int MAX_VALUE_LENGTH    = 75;
}

//******************************************************************************
AwdLobData::AwdLobData(PAWDLOBARRAY pAwdLobArray)
{
   _pAwdLobArray = pAwdLobArray;

}
//******************************************************************************
AwdLobData::~AwdLobData()
{
   
   
}
//*******************************************************************************
// name can not exceed 4 characters
//
std::string AwdLobData::getLobFieldValue(const std::string& name )
{
   char dataname[ MAX_NAME_LENGTH + 1 ];  
   std::string retValue = "";
   USHORT uLength = name.length();
   if( uLength > MAX_NAME_LENGTH ) uLength = MAX_NAME_LENGTH;   
   memcpy( dataname, name.c_str(), uLength );
   *(dataname + uLength ) = '\0'; 
   for ( int i = 0; i<_pAwdLobArray->usCount;i++ )
   {
      char tempname[ MAX_NAME_LENGTH + 1 ];
      memset(tempname,' ',MAX_NAME_LENGTH + 1);
      int jj = 0;
      for (; jj < MAX_NAME_LENGTH; jj++ )
      {
         if( (_pAwdLobArray->pAwdLobData + i )->dataname[jj] != ' ' )
         {
            tempname[jj] = (_pAwdLobArray->pAwdLobData + i )->dataname[jj];
         }
         else
         {
            break;
         }
      }
      tempname[ jj ] = '\0';
      char ch[ MAX_VALUE_LENGTH+1 ];
      bool bFind =  false;
      if ( strcmp(dataname, tempname ) == 0 )
      {     
         bFind = true;
         for( int j = 0; j < MAX_VALUE_LENGTH; j++ )
         {           
            if( ( _pAwdLobArray->pAwdLobData + i )->datavalue[j] != '\0' )
            {
               ch[j] = (_pAwdLobArray->pAwdLobData + i )->datavalue[j];
            }
            else
            {
               ch[j] = '\0';
               break;
            }        
         }
		 ch[MAX_VALUE_LENGTH] = '\0';
      }
      if(  bFind )
      {
            retValue.append( ch );
            break;
      }
   }
   return retValue;
}
//*******************************************************************************
// name: less or equal to 4 characters
// value: less or equal to 75 characters
//
void AwdLobData::setLobFieldValue( const std::string& name, const std::string& value )
{
   char dataname[ MAX_NAME_LENGTH + 1 ];
   char datavalue[ MAX_VALUE_LENGTH + 1 ];
   USHORT uLength = name.length();
   if( uLength > MAX_NAME_LENGTH ) uLength = MAX_NAME_LENGTH;   
   memcpy( dataname, name.c_str(), uLength );
   *(dataname + uLength ) = '\0'; 
   USHORT uValueLen = value.length();
   if( uValueLen > MAX_VALUE_LENGTH ) uValueLen = MAX_VALUE_LENGTH;   
   memcpy( datavalue, value.c_str(),uValueLen  ); 
   *(datavalue + uValueLen ) = '\0'; 
   for ( int i = 0; i<_pAwdLobArray->usCount;i++ )
   {
      char tempname[ MAX_NAME_LENGTH + 1 ];
      memset(tempname,' ',MAX_NAME_LENGTH + 1);
      int jj = 0;
      for (; jj < MAX_NAME_LENGTH; jj++ )
      {
         if( (_pAwdLobArray->pAwdLobData + i )->dataname[jj] != ' ' )
         {
            tempname[jj] = (_pAwdLobArray->pAwdLobData + i )->dataname[jj];
         }
         else
         {
            break;
         }
      }
      tempname[ jj ] = '\0';
      if ( strcmp(dataname,tempname) == 0 )
      {
         memset( ( _pAwdLobArray->pAwdLobData + i )->datavalue,' ', MAX_VALUE_LENGTH );
         memcpy( ( _pAwdLobArray->pAwdLobData + i )->datavalue,
                 (char *) datavalue, uValueLen );         
         break;
      }
   }
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/awdsrv/AwdLobData.cpp-arc  $
// 
//    Rev 1.2   Nov 14 2005 11:01:16   yingbaol
// PET1332,FN09: fix lob data format
// 
//    Rev 1.1   Nov 08 2005 14:15:06   yingbaol
// PET1332,FN09: remove DString and infra structure
// 
//    Rev 1.0   Oct 31 2005 14:49:00   yingbaol
// Initial revision.
 * 
 *

 */