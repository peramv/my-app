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
//    AUTHOR : Serban Popescu
//    DATE   : January 2003
//
//
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

#include <bfdata\BFFieldId.hpp>

class BFContainerId;
class DString;

struct HistoricalElement {
public:
   HistoricalElement( DString record, DString table, DString key ): 
      dstrRecord( record ), dstrTableId( table ), dstrKey( key ) 
   {
   }
   DString dstrRecord;
   DString dstrTableId;
   DString dstrKey;
};

typedef std::vector< HistoricalElement > HISTORICAL_VECTOR;

namespace 
{
   // Trace literals
   const I_CHAR * const GETHISTORICALPARAMETERS = I_( "getHistoricalParameters" );
}

/**
 * Base class for the IFast processes that support historical information
 *
 * @author Serban Popescu
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 01/24/2003</dd></dl>
 * @version 0.1
 */

class IFASTBP_LINKAGE IFastHistoricalParameters
{
// Construction
public:
   /**
    * Default constructor
    */
   virtual ~IFastHistoricalParameters();
   /**
     * Returns the record id and name of the id of the 
     * table for which the historical data is pulled out
     * This method should be overriden in the processes that care about
     * historical information
     */
    virtual SEVERITY getHistoricalParameters(const BFContainerId& idContainer, 
       BFFieldId &recordIdField, DString& tableId, DString& keys);

    virtual SEVERITY getHistoricalParameters(const BFContainerId& idContainer, HISTORICAL_VECTOR &) = 0;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ifasthistoricalparameters.hpp-arc  $
//
//   Rev 1.5   Mar 15 2004 17:50:44   HERNANDO
//PET965 FN11 - Made getHistoricalParameters abstract.
//
//   Rev 1.4   Mar 01 2004 09:55:44   HERNANDO
//PET965 FN11 - Added an additional getHistoricalParameters.  Changed from pure abstract class to abstract class.
//
//   Rev 1.3   Aug 18 2003 16:09:58   HERNANDO
//Added keys to getHistoricalParameters.
//
//   Rev 1.2   Jul 31 2003 21:34:24   popescu
//minor code formatting
//
//   Rev 1.1   Mar 21 2003 17:42:36   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.0   Mar 05 2003 11:14:02   PURDYECH
//Initial revision.
//
//   Rev 1.0   Jan 28 2003 13:13:20   popescu
//Initial revision.
 * 
 */
