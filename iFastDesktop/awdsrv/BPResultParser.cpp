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
// ^FILE   : BPResultParser.cpp
// ^AUTHOR : Yongmei Feng
// ^DATE   : Oct. 31, 2005
//
// ^CLASS    : BPResultParser
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//********************************************************************************
#include "stdafx.h"
#include "BPResultParser.hpp"
#include "BPResult.hpp"

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/SaxParser.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>


#include <list>
#include <iostream>
#include <string>

#include "logging.h"

namespace
{
   const char * const CLASSNAME  = "BPResultParser";   
}

//******************************************************************************
BPResultParser::BPResultParser( ) 
: _parser()
, _elementList()
{
   _parser.setDocumentHandler( this );
   _parser.setErrorHandler( this );
   _parser.setValidationScheme( xercesc::SAXParser::Val_Never );
   _parser.setDoNamespaces( true );
}

//******************************************************************************
BPResultParser::~BPResultParser()
{

}

//******************************************************************************
void BPResultParser::parse( const xercesc::InputSource &input,BPResult& result )
{
      try 
      {
         _parser.parse( input );
		 outPut( result );
      }
    /*  catch(ConditionException& )
      {
         LOGGINGWITHTIMESTAMP( CLASSNAME );
         LOGGING( "*****parser throw Condition Exception***"  );        
      }
      */
      catch ( xercesc::SAXException &se )
      {
         LOGGINGWITHTIMESTAMP( CLASSNAME );
         LOGGING( "*****parser throw SAXException Exception***"  );
  
         std::string strIDI = "SAXMSG";
         std::string target;
         Element::xmlChToStd(target,se.getMessage());
         strIDI += " = ";
         strIDI += target;
         //addIDITagValue( strIDI, I_("SAXMSG"), se.getMessage() );
         LOGGING(  strIDI  );
      }
      catch (...)
      {
         LOGGINGWITHTIMESTAMP( CLASSNAME );
         LOGGING( "*****parser throw Other Exceptions***"  );
      } 

	
}

//******************************************************************************
// Parse from memory   
void BPResultParser::parse( const std::string &xmlIn, BPResult& result    )
{
   xercesc::MemBufInputSource buff( (const XMLByte*)xmlIn.c_str(), xmlIn.size(), "MemBuff", false );
   parse( buff, result );
}

//******************************************************************************
// Parse from file
void BPResultParser::parse( const std::string &uri )
{
//   xercesc::LocalFileInputSource input( uri.c_str() );
   //parse( input );
}

// DocumentHandler overrides
//******************************************************************************
void BPResultParser::startElement( const XMLCh *const name, xercesc::AttributeList &attributes )
{
   std::string target;
   Element::xmlChToStd(target, name);
   _currentElement = _elementList.addElement( target, attributes );      
}




//******************************************************************************
void BPResultParser::characters( const XMLCh * const chars, const unsigned int length )
{
   if( _currentElement )
   {
      _currentElement->AppendValue( chars, length );
   }
}

//******************************************************************************
void BPResultParser::endElement( const XMLCh * const name )
{
   if( _currentElement )
      _currentElement = NULL;
}

// ErrorHandler methods
//******************************************************************************
void BPResultParser::warning( const xercesc::SAXParseException &e )
{
   LOGGINGWITHTIMESTAMP( CLASSNAME );
   LOGGING(  "*****Warning at file***\n" );  
   std::string target;
   Element::xmlChToStd(target, e.getSystemId());
   LOGGING(  target );        
   LOGGING( ", line "  );   
   target.clear();
   target  = convertIntToString( e.getLineNumber() );
   LOGGING( ", = "  );    
   LOGGING(  target  );
   LOGGING( "\n"  );    
   LOGGING( " Message: "  );    
   target.clear();
   Element::xmlChToStd(target, e.getMessage());
   LOGGING( target );    
   LOGGING( "\n"  );    
}

//******************************************************************************
void BPResultParser::error( const xercesc::SAXParseException &e )
{   
   LOGGINGWITHTIMESTAMP( CLASSNAME );
   LOGGING( "*****Error at file***\n"  );        
   std::string target;
   Element::xmlChToStd(target, e.getSystemId());
   LOGGING(  target );        
   LOGGING( ", line "  );   
   target.clear();
   target  = convertIntToString( e.getLineNumber() ); 
   LOGGING( ", = "  );    
   LOGGING(  target  );
   LOGGING( "\n"  );    
   LOGGING( " Message: "  );    
   target.clear();
   Element::xmlChToStd(target, e.getMessage());
   LOGGING( target );    
   LOGGING( "\n"  );  
   throw e;
}

//******************************************************************************
void BPResultParser::fatalError( const xercesc::SAXParseException &e )
{
  
   LOGGINGWITHTIMESTAMP( CLASSNAME );
   LOGGING( "*****fatalError at file***\n"  );        
   std::string target;
   Element::xmlChToStd(target, e.getSystemId());
   LOGGING(  target );        
   LOGGING( ", line "  );   
   target.clear();
   target  = convertIntToString( e.getLineNumber() ); 
   LOGGING( " =  "  );    
   LOGGING( target  );
   LOGGING( "\n"  );    
   LOGGING( " Message: "  );    
   target.clear();
   Element::xmlChToStd(target, e.getMessage());
   LOGGING( target );    
   LOGGING( "\n"  );  
   throw e;
}

//******************************************************************************
void BPResultParser::outPut( BPResult& result)
{
	std::string name, value, attribute;
	std::string severity, code, message;
	std::string status, account;
	ElementList::iterator Iter;
	Iter = _elementList.begin();
	while( Iter != _elementList.end() )
	{
		name = (*Iter)->getName();
		attribute = (*Iter)->getAttribute();
		value = (*Iter)->getValue();
		if( name == "AccountNum")
		{
         account = value;
		   result.setAccountNum( account );
			
		}
		if( name == "Successful" )
		{
            status = value;
			result.setStatus( status );			
		}
		if( name == "Condition" )
		{
			severity = attribute;       
		}
		if( name == "Code")
		{
			code = value;
		}
		if( name == "Message" )
		{
			result.addErrorMessage( severity, code, value );
			message = value;
		}
		Iter++;
	}
}
//*************************************************************
std::string BPResultParser::convertIntToString(int iNum)
{
   std::string str;
   char szValue[32];
   itoa(iNum, szValue,10 );
   str=szValue;
   return str;
}

//******************************************************************************
//  Private methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/awdsrv/BPResultParser.cpp-arc  $
// 
//    Rev 1.3   Nov 14 2005 11:03:58   yingbaol
// PET1233,FN09: if there is error in XML, we should not continue
// 
//    Rev 1.2   Nov 08 2005 14:17:44   yingbaol
// PET1332,FN09: Remove DString and Infra structure
// 
//    Rev 1.1   Oct 31 2005 15:33:52   yingbaol
// Code clean up....
// 
//    Rev 1.0   Oct 31 2005 13:14:14   yingbaol
// Initial revision.
 * 
 */