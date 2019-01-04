#pragma once
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
//    Copyright 1999 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : MFCanCbo.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : MFCanCbo
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************
#pragma warning (disable : 4786)  

#include <bfcbo\bfcbo.hpp>


class DSTCWorkSession;
class DSTCUserSession;
class DSTCGlobalSession;
class DSTCHost;
class DSTCSecurity;
class MgmtCo;
class CConditionObject;

// Import/Export resolution
#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE MFCanBFCbo : public BFCBO
{
public:
   virtual const BFSession &getSession() const; 
   virtual BFSession &getSession(); 


   Condition* getNotifyCondition() const;

protected:
   MFCanBFCbo(BFAbstractCBO &parent);
   virtual ~MFCanBFCbo();

   Condition* _notifyCondition;
   virtual void donotifyResponse ( SEVERITY severity, 
                                   const Condition *condition, 
                                   BFData *receivedData, 
                                   bool moreAvailable,
                                   int callBackOption = 0 );

   const DSTCWorkSession &getWorkSession() const;
   DSTCWorkSession &getWorkSession();

   const DSTCGlobalSession &getGlobalSession() const;
   DSTCGlobalSession &getGlobalSession();

   const DSTCUserSession &getUserSession() const;
   DSTCUserSession &getUserSession();

   const DSTCSecurity *getSecurity (const DSTCHost &host) const;
   const DSTCSecurity *getSecurity() const;

   const MgmtCo &getMgmtCo() const;
   MgmtCo &getMgmtCo();
   DString &getMgmtCoId (DString &outString) const;

   bool loadSubstitutionList ( const BFFieldId &idField, 
                               const BFDataGroupId &idDataGroup,
                               const DString &strCodesList,
                               bool bStripLeadingZeros = false,
                               bool bAddCodeToDescription = false
                             );
	DString removeItemFromAllSubtList ( const BFFieldId &idField, 
		                                 const DString &dstrValue, 
		                                 const BFDataGroupId &idDataGroup
                                     );
	DString removeItemFromSubtList ( const BFFieldId &idField, 
		                              const DString &dstrValue, 
		                              const BFDataGroupId &idDataGroup
                                  );
   DString removeItemFromSubtList ( const DString &substList, 
                                    const DString &value
                                  );
	DString addItemToSubtList ( const BFFieldId &idField, 
									    const DString &dstrValue, 
										 const BFDataGroupId &idDataGroup
                             );
   void setAllSubstituteValuesForField ( const BFFieldId &idField, 
                                         const BFDataGroupId &idDataGroup, 
                                         const BFFieldId &idField2
                                       );
   int isCodeAllowed ( const DString &dstrCode, 
                       const DString &dstrCodeList
                     );
   bool isCodeInList ( const DString &dstrCode, 
                       const DString &dstrCodeList
                     );

   SEVERITY getErrMsg ( const DString &errorCode,
                        long lErrConditionId, 
                        long lWarnConditionId, 
                        const BFDataGroupId &idDataGroup, 
                        const DString &idiStr = NULL_STRING
                       );
  SEVERITY getErrMsg ( const DString &errorCode,
                       CConditionObject &errrObject, 
                       CConditionObject &warnObject, 
                       const BFDataGroupId &idDataGroup, 
                       const DString &idiStr = NULL_STRING
                     );
   virtual SEVERITY ReceiveData ( const BFRequest &request,
                                  BFData &queryData,
                                  BFData &receivedData,
                                  BFRequestor &requestor,
                                  bool bInsertLast = false
                                );
   virtual SEVERITY ReceiveData ( const BFRequest &request,
                                  BFData &queryData,
                                  long responseDataSetId,
                                  BFRequestor &requestor,
                                  bool bInsertLast = false
                                );
   //P0186486_FN15_The Source of Funds                            
   void replaceSubstitutionList(const DString &newList, 
                                    const BFFieldId& idFieldFrom,
                                    const BFFieldId& idFieldTo, 
                                    const BFDataGroupId& idDataGroup);                           
private:
   BFSession &_session;

   void getSubstitutionList ( const DString &strAllSubstList, 
                              DString strCodesList, 
                              bool bStripLeadingZeros, 
                              bool bAddCodeToDescription,
                              DString &strSubstListOut
                            );
};

// The following code is an attempt to further specialize MFCanBFCbo 
// into Work/Global/User-Session specific types. There are however a few
// BCO's that appear under both the Global and User trees. Will try again later.
//
//DS//******************************************************************************
//DSclass MFCanWSCbo : public MFCanBFCbo
//DS{
//DSpublic:
//DS  virtual const BFSession &getSession() const; 
//DS  virtual BFSession &getSession(); 
//DS
//DSprotected:
//DS  MFCanWSCbo (DSTCWorkSession &parent);
//DS  MFCanWSCbo (MFCanWSCbo &parent);
//DS  virtual ~MFCanWSCbo();
//DS
//DS  const DSTCWorkSession &getWorkSession() const;
//DS  DSTCWorkSession &getWorkSession();
//DS
//DS  const DSTCGlobalSession &getGlobalSession() const;
//DS  DSTCGlobalSession &getGlobalSession();
//DS
//DS  const DSTCUserSession &getUserSession() const;
//DS  DSTCUserSession &getUserSession();
//DS
//DS  const MgmtCo &getMgmtCo() const;
//DS  MgmtCo &getMgmtCo();
//DS
//DS  DString &getMgmtCoId(DString &outString) const;
//DS
//DSprivate:
//DS   DSTCWorkSession &workSession_;
//DS};
//DS
//DS//******************************************************************************
//DSclass MFCanGSCbo : public MFCanBFCbo
//DS{
//DSpublic:
//DS  virtual const BFSession &getSession() const; 
//DS  virtual BFSession &getSession(); 
//DS
//DSprotected:
//DS  MFCanGSCbo (DSTCGlobalSession &parent);
//DS  MFCanGSCbo (BFAbstractCBO &parent);
//DS  virtual ~MFCanGSCbo();
//DS
//DS  const DSTCGlobalSession &getGlobalSession() const;
//DS  DSTCGlobalSession &getGlobalSession();
//DS
//DS  const DSTCUserSession &getUserSession() const;
//DS  DSTCUserSession &getUserSession();
//DS
//DS  const MgmtCo &getMgmtCo() const;
//DS  MgmtCo &getMgmtCo();
//DS
//DS  DString &getMgmtCoId(DString &outString) const;
//DS
//DSprivate:
//DS   DSTCGlobalSession &globalSession_;
//DS};
//DS
//DS//******************************************************************************
//DSclass MFCanUSCbo : public MFCanBFCbo
//DS{
//DSpublic:
//DS  virtual const BFSession &getSession() const; 
//DS  virtual BFSession &getSession(); 
//DS
//DSprotected:
//DS  MFCanUSCbo (DSTCUserSession &parent);
//DS  MFCanUSCbo (MFCanUSCbo &parent);
//DS  virtual ~MFCanUSCbo();
//DS
//DS  const DSTCGlobalSession &getGlobalSession() const;
//DS  DSTCGlobalSession &getGlobalSession();
//DS
//DS  const DSTCUserSession &getUserSession() const;
//DS  DSTCUserSession &getUserSession();
//DS
//DSprivate:
//DS   DSTCUserSession &userSession_;
//DS};
//DS

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/MFCanCbo.hpp-arc  $
//
//   Rev 1.15   May 04 2012 09:41:50   panatcha
//P0186486_FN15_The Source of Funds
//
//   Rev 1.14   Oct 21 2009 10:48:20   purdyech
//LDAP Authorization Support
//
//   Rev 1.13   Nov 14 2004 14:50:10   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.12   Nov 04 2004 17:38:06   popescu
//PET 1117/06, Trade processing
//
//   Rev 1.11   May 28 2004 13:31:14   popescu
//PET 985, FN01, fixed substitution values crash when adding multiple trades on the Trade dialog
//
//   Rev 1.10   May 09 2004 20:10:20   popescu
//PET 985, FN 01, LSIF Trade Entry
//
//   Rev 1.9   Apr 05 2004 17:29:44   FENGYONG
//PET944 FN01, release 56.1 NSCC Broker Matrix
//
//   Rev 1.8   Feb 10 2004 16:35:00   VADEANUM
//PET 859 FN23 - ADL - added removeItemFromSubtList()
//
//   Rev 1.7   Mar 21 2003 18:18:40   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.6   Oct 09 2002 23:54:46   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.5   Aug 29 2002 12:53:02   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.4   22 May 2002 18:20:24   PURDYECH
//BFData Implementation
//
//   Rev 1.3   19 Mar 2002 13:17:58   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.2   Feb 25 2002 18:54:00   PURDYECH
//Phase 1 of BFData Rollout - Base Component Compatibility
//
//   Rev 1.1   10 May 2001 11:38:46   HSUCHIN
//Sync up with SSB
//
//   Rev 1.0   03 May 2001 14:50:30   SMITHDAV
//Initial revision.
 * 
 * 
 */
