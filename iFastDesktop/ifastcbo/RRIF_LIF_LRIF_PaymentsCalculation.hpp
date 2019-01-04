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
// ^FILE   : RRIF_LIF_LRIF_PaymentsCalculation.hpp
// ^AUTHOR : Dan Petolescu
// ^DATE   : May 1, 2000
//
// ^CLASS    : RRIF_LIF_LRIF_PaymentsCalculation
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE 
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT 
#else 
   #define IFASTCBO_LINKAGE CLASS_IMPORT 
#endif

class RRIF_LIF_LRIF_Info;

class IFASTCBO_LINKAGE RRIF_LIF_LRIF_PaymentsCalculation : public MFCanBFCbo, private boost::noncopyable
{
public:
   RRIF_LIF_LRIF_PaymentsCalculation( BFAbstractCBO &parent );
   virtual ~RRIF_LIF_LRIF_PaymentsCalculation();

   SEVERITY init( const DString& strAccountNum, 
                  const DString& callNum,
                  RRIF_LIF_LRIF_Info* rrifInfo, 
                  const BFDataGroupId& idDataGroup,
                  bool bFirstCall,
                  bool bAddMode,
                  const DString& dstrTrack= I_("N"),
                  const DString& dstrPageName = NULL_STRING );

   SEVERITY init();
private:

   SEVERITY extractFieldFromDate( DString const &strField, int &field, DString strDateField = I_("yyyy") );
   SEVERITY SetDayMonthToDate( DString  &strField, DString const &strMonth, DString const &strDay );
};

///#endif
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RRIF_LIF_LRIF_PaymentsCalculation.hpp-arc  $
// 
//    Rev 1.12   Nov 14 2004 14:53:20   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.11   Mar 21 2003 18:22:50   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.10   Oct 09 2002 23:54:54   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.9   Aug 29 2002 12:53:30   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.8   22 May 2002 18:20:06   PURDYECH
// BFData Implementation
// 
//    Rev 1.7   19 Mar 2002 13:18:20   PURDYECH
// Use #pragma once as include guard
// Remove compile time "including..." message
// 
//    Rev 1.6   03 May 2001 14:04:48   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.5   Jan 18 2001 16:12:42   YINGBAOL
// add etrack
// 
//    Rev 1.4   Sep 28 2000 15:01:24   YINGBAOL
// change init logic
// 
//    Rev 1.3   Jun 28 2000 15:00:42   PETOLESC
// Added Frequency field, changed logic for view 130 call sequence and a BIG bunch of other changes.
// 
//    Rev 1.2   Jun 09 2000 18:01:40   PETOLESC
// Save work.
// 
//    Rev 1.1   May 19 2000 17:29:52   PETOLESC
// save work
// 
//    Rev 1.0   May 04 2000 13:46:26   PETOLESC
// Initial revision.
 * 
 *
 */
