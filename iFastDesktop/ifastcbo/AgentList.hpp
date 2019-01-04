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
//******************************************************************************
//
// ^FILE   : AgentList.hpp
// ^AUTHOR : Yakov Prager
// ^DATE   : November 07, 1999
//
// ^CLASS  : AgentList
// ^PARENT : ListBase
//
// ^CLASS DESCRIPTION :
//    Implements View 92.
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE AgentList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   AgentList( BFAbstractCBO &parent );
   virtual ~AgentList();

   // Initialize function
   SEVERITY init( const DString& dstrBrokerCode, 
                  const DString& dstrBranchCode, 
                  const DString& dstrSlsRep,
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING );

   SEVERITY init2( const DString& dstrBrokerCode, 
                          const DString& dstrBranchCode, 
                          const DString& dstrSlsRep,
                          const DString& dstrFundCode,
                          const DString& dstrClassCode,
                          const DString& dstrAccountNum,
                          const DString& dstrValidateType = I_( "Trade" ),
                          const DString& dstrTrack = I_("N"),
                          const DString& dstrPageName = NULL_STRING );
   SEVERITY getMore();

   SEVERITY doCreateObject( const BFData& data, BFCBO*& pObjOut );

private:
   BFData _requestData;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AgentList.hpp-arc  $
 * 
 *    Rev 1.11   Mar 21 2003 17:56:58   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.10   Mar 05 2003 11:57:36   HSUCHIN
 * PTS 10014446 - no longer using genericcbo, using agent cbo and branch cbo for effective date validation.
 * 
 *    Rev 1.9   Jan 12 2003 15:24:42   WINNIE
 * default default value for validation type
 * 
 *    Rev 1.8   Jan 03 2003 09:36:32   HSUCHIN
 * created init2 to support dynamic
 * 
 *    Rev 1.7   Oct 09 2002 23:54:00   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.6   Aug 29 2002 12:51:44   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.5   22 May 2002 18:21:54   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.4   19 Mar 2002 13:15:04   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.3   16 Oct 2001 11:20:22   HSUCHIN
 * Implemented GetMore functionality
*/