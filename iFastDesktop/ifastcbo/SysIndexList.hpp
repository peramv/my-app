#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2001 by DST Canada, Inc.
//
//******************************************************************************
//
// ^FILE   : SysIndexList.hpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 5/1/01
//
// ^CLASS  : SysIndexList
// ^PARENT : BFBase
//
// ^CLASS DESCRIPTION :
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

class SysIndexList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE SysIndexList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   SysIndexList( BFAbstractCBO &parent );
   ~SysIndexList( void );

   // Initialize function
   SEVERITY init( const DString& dstrAccountNum,
                  const DString& dstrTransNum,
                  const DString& dstrTransType,
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING );

   SEVERITY  doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   bool activeIndex (const BFDataGroupId& idDataGroup);
   void markReadOnly ( const BFDataGroupId& idDataGroup );
protected:
   SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
   SEVERITY doCreateNewObject(BFCBO *& pBase, DString & strKey, const BFDataGroupId& idDataGroup );
private:
   void validateDateRanage (const BFDataGroupId& idDataGroup);
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/SysIndexList.hpp-arc  $
//
//   Rev 1.13   Nov 14 2004 14:56:26   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.12   Mar 21 2003 18:25:44   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.11   Oct 09 2002 23:55:04   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.10   Aug 29 2002 12:53:44   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.9   22 May 2002 18:19:44   PURDYECH
//BFData Implementation
//
//   Rev 1.8   19 Mar 2002 13:18:38   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.7   02 Aug 2001 18:26:52   HSUCHIN
//added function to mark SysIndex readonly
//
//   Rev 1.6   11 Jul 2001 15:08:58   HSUCHIN
//added activeindex function
//
//   Rev 1.5   06 Jun 2001 13:38:02   HSUCHIN
//code cleanup and additional business logic added
//
//   Rev 1.4   31 May 2001 16:52:12   HSUCHIN
//changed init requirements
//
//   Rev 1.3   31 May 2001 11:41:54   HSUCHIN
//changed init function
//
//   Rev 1.2   23 May 2001 12:32:18   HSUCHIN
//validation rules added
//
//   Rev 1.1   11 May 2001 09:31:50   HSUCHIN
//Session management restructuring
//
//   Rev 1.0   03 May 2001 13:42:12   BUZILAMI
//Initial revision.
 * 
 *
*/
