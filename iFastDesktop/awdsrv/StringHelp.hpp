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
// ^FILE   : StringHelp.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Nov. 9, 2005
//
// ^CLASS    :StringHelp
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//********************************************************************************

#pragma once
 #include <string>


namespace StringHelp
{
     std::string& stripLeading( std::string& strIn, char stripChar = ' ' );
     std::string& stripTrailing(  std::string& strIn, char stripChar= ' ' );
     std::string& strip( std::string &strIn, char stripChar= ' ' );


}