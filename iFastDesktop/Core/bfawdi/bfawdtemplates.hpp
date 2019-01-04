#pragma once

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

#include <vector>
#include <bfawdi\bfawdlookupcriteria.hpp>
#include <bfawdi\bfawdlookupresult.hpp>
#include <bfawdi\bfawdkey.hpp>

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
 * AwdLookupCriteria crit1( I_("WRKT"), AwdLookupCriteria::GREATER_THAN, I_("MAINT") );
 * AwdLookupCriteria crit2( I_("FUND"), AwdLookupCriteria::GREATER_THAN, I_("0000095") );
 * AwdLookupCriteria crit3( I_("CRDA"), AwdLookupCriteria::DESCENDING );
 * critList.push_back( crit1 );
 * critList.push_back( crit2 );
 * critList.push_back( crit3 );
 * resultList = awd.lookupWork( critList, more );
 * for ( iter = resultList.begin(); iter != resultList.end(); ++iter )
 * {
 *    AwdLookupResult &result = *iter;
 *
 *    // TODO: do something with the result
 * }
 * </pre>
 */
typedef std::vector<BFAwdLookupCriteria> CriteriaVector;

/**
 * A ResultVector is a vector of AwdLookupResults returned from an AWD Lookup.
 */
typedef std::vector<BFAwdLookupResult> ResultVector;

/**
 * An AwdKeyVector is a vector of pointers to AwdKey objects.
 */
typedef std::vector<BFAwdKey *> BFAwdKeyVector;

