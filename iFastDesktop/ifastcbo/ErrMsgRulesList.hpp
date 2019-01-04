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
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : ErrMsgRulesList.hpp.
// ^AUTHOR : Cornel Dina
// ^DATE   : June 2000
//
// ^CLASS    : ErrMsgRulesList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : The error message rules list
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE ErrMsgRulesList : public MFCanBFCbo, private boost::noncopyable
{
public:
   ErrMsgRulesList (BFAbstractCBO &parent);
   virtual ~ErrMsgRulesList (void);
   SEVERITY init (
      const DString &dstrTrack = I_("N"), 
      const DString &dstrPageName = NULL_STRING);
   SEVERITY getEWI (
      const DString &strErrNum, 
      long lErrConditionId, 
      long lWarnConditionId, 
      const BFDataGroupId &idDataGroup, 
      const DString &idiStr = NULL_STRING);
   void getEWIValue (
      const DString &strErrNum, 
      const BFDataGroupId &idDataGroup,
      DString &strErrValue);
   SEVERITY getEWI (const DString& strErrNum, 
                    CConditionObject& errConditionObj, 
                    CConditionObject& warnConditionObj, 
                    const BFDataGroupId &idDataGroup, 
                    const DString &idiStr = NULL_STRING);
protected:
   void getStrKey (DString &strKey, const BFData *data);
private:
};

///#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ErrMsgRulesList.hpp-arc  $
// 
//    Rev 1.15   Nov 14 2004 14:36:50   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.14   Oct 30 2003 16:30:38   popescu
// PTS 10023438, RESP SIN legislative requirement
// 
//    Rev 1.13   Apr 09 2003 12:52:24   sanchez
// New function prototype ErrMsgRulesList() tor return of the following string values "I", "W", "E"
// 
//    Rev 1.12   Mar 21 2003 18:08:34   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.11   Oct 09 2002 23:54:28   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.10   Aug 29 2002 12:52:20   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.9   22 May 2002 18:21:06   PURDYECH
// BFData Implementation
// 
//    Rev 1.8   19 Mar 2002 13:16:58   PURDYECH
// Use #pragma once as include guard
// Remove compile time "including..." message
// 
//    Rev 1.7   03 May 2001 14:04:08   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.6   Jan 18 2001 16:11:56   YINGBAOL
// add etrack
// 
//    Rev 1.5   Dec 05 2000 17:13:28   DINACORN
// Synchronization to C2/C3: Modify getEWI() method
// 
//    Rev 1.4   Nov 16 2000 09:48:12   OLTEANCR
// modif. getEWI
// 
//    Rev 1.3   Nov 15 2000 17:44:14   OLTEANCR
// modified getEWI( )
// 
//    Rev 1.2   Nov 07 2000 14:15:48   OLTEANCR
// fixed typo
// 
//    Rev 1.1   Nov 06 2000 14:35:22   OLTEANCR
// added new functions: getStrKey, getEWI
// 
//    Rev 1.0   Jun 23 2000 16:48:22   DINACORN
// Initial revision.
*/