#ifndef AWDTEMPLATES_H
#define AWDTEMPLATES_H

#pragma message( "including "__FILE__ )

/** 
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1996-2000 by DST Systems, Inc.
 */

#ifndef INCLUDED_VECTOR
#define INCLUDED_VECTOR
   #include <vector>
#endif

#ifndef AWDLOOKUPCRITERIA_HPP
   #include "awdlookupcriteria.hpp"
#endif

#ifndef AWDLOOKUPRESULT_HPP
   #include "awdlookupresult.hpp"
#endif

#ifndef AWDKEY_HPP
   #include "awdkey.hpp"
#endif

/**
 * A CriteriaVector is vector of AwdLookupCriteria used for AWD Lookups.
 *
 * <b>Example:</b>
 * <pre>
 * AwdInterface awd;
 * CriteriaVector critList;
 * ResultVector resultList;
 * ResultVector::iterator iter;
 * bool more;
 *
 * AwdLookupCriteria crit1( I_("WRKT"), AwdLookupCriteria::GREATER_THAN, I_("MAINT") );
 * AwdLookupCriteria crit2( I_("FUND"), AwdLookupCriteria::GREATER_THAN, I_("0000095") );
 * AwdLookupCriteria crit3( I_("CRDA"), AwdLookupCriteria::DESCENDING );
 *
 * critList.push_back( crit1 );
 * critList.push_back( crit2 );
 * critList.push_back( crit3 );
 *
 * resultList = awd.lookupWork( critList, more );
 *
 * for ( iter = resultList.begin(); iter != resultList.end(); ++iter )
 * {
 *    AwdLookupResult &result = *iter;
 *
 *    // TODO: do something with the result
 * }
 * </pre>
 */
typedef std::vector<AwdLookupCriteria> CriteriaVector;

/**
 * A ResultVector is a vector of AwdLookupResults returned from an AWD Lookup.
 */
typedef std::vector<AwdLookupResult> ResultVector;

/**
 * An AwdKeyVector is a vector of pointers to AwdKey objects.
 */
typedef std::vector<AwdKey *> AwdKeyVector;

#endif

//************************************************************************
//              Revision Control Entries
//************************************************************************
//
// Name:
//    %PM%
//    %PID%
//
// Description:
//    %PD%
//
// Design Parts:
//    %PIRP%
//
// Last Changed:
//    %PO%  -  %PRT%
//
// Changes:
//    %PLA%
//
//

