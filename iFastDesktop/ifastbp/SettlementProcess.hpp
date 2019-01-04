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
//    AUTHOR : Yingbao  Li
//    DATE   : May 24, 2002
//
//
//    Copyright 2002 by International Financial Data Service.
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>
///#endif

// Forward references
class MFCommonBusinessManager;
class SettlementTradeList;
// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif


class IFASTBP_LINKAGE SettlementProcess : public AbstractProcess
{
// Construction
public:
//CP20030319   SettlementProcess();
   SettlementProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~SettlementProcess();
   SEVERITY performSearch( GenericInterface *rpGI, 
                           const BFContainerId& idSearch, E_SEARCHACTION eSearchAction );
   SEVERITY performAPISearch( GenericInterface *rpGI, 
                                           const BFContainerId& idSearch, E_SEARCHACTION eSearchAction );
protected:

   virtual void doGetField(
                          const GenericInterface *rpGICaller,
                          const BFContainerId& idContainer,
                          const BFFieldId& idField,
                          const BFDataGroupId& idDataGroup,
                          DString &strValueOut,
                          bool bFormatted
                          ) const;
   virtual SEVERITY doInit();
   virtual bool doModelessChildComplete(
                                       const Command &cmd
                                       );
   virtual bool doModelessSetFocus(
                                  GenericInterface *rpGICaller
                                  );

   virtual bool doSend(
                      GenericInterface *rpGICaller,
                      const I_CHAR *szMessage
                      ) ;
   virtual E_COMMANDRETURN doProcess();
   //virtual SEVERITY ok2( GenericInterface *rpGICaller );
   virtual void *getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );
   virtual SEVERITY doSetField(
                              const GenericInterface *rpGICaller,
                              const BFContainerId& idContainer,
                              const BFFieldId& idField,
                              const BFDataGroupId& idDataGroup,
                              const DString& strValue,
                              bool bFormatted
                              );
   virtual bool doMoreRecordsExist(
                                  GenericInterface *rpGICaller, 
                                  const BFContainerId& idSearch );
   virtual bool doOk(
                    GenericInterface *rpGICaller
                    );

   virtual void setCurrentListItem(
                                    const GenericInterface *rpGICaller,
                                    const BFContainerId &idList,
                                    const DString &strListItemKey
                                    );
   const BFProperties *doGetFieldAttributes( const GenericInterface *rpGICaller, const BFContainerId& idContainer, 
   											 const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   void  removeItemFromSubtList( const DString &dstrSubList, const DString &dstrIDValue, DString &dstrOutSubList );
private:

   GenericInterface* _rpChildGI;
   DString _dstrAccountNum;
   DString _dstrShrNum;
   DString _dstrEntityName; 

   DString _dstrFromScr;
   SettlementTradeList* _pSettlementTradeList;
   SettlementTradeList* _pDummySettlementTradeList;
   //para for API
   DString _dstrTransNum;
   DString _dstrFundCode;
   DString _dstrClassCode;
   DString _dstrTransType;
   DString _dstrSettleDate;
   DString _dstrTradeDate;
   DString _dstrBrokerCode;
   BFProperties *_propSettlementListHeadSet;
   
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/SettlementProcess.hpp-arc  $
//
//   Rev 1.11   Aug 20 2009 12:06:08   jankovii
//IN 1803616 -  R94: "List not valid for list ID2120" received when resizing the settlements scn
//
//   Rev 1.10   May 26 2004 12:09:02   popescu
//PTS 10021623, broker address by tax type and reg adrress code
//
//   Rev 1.9   Apr 07 2003 15:15:10   FENGYONG
//Add performAPISearch and several variables
//
//   Rev 1.8   Mar 21 2003 17:48:02   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.7   Oct 09 2002 23:53:36   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.6   Aug 29 2002 12:53:36   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.5   Jul 05 2002 13:42:44   YINGBAOL
//added doOK Fundction
//
//   Rev 1.4   Jun 21 2002 13:16:00   YINGBAOL
//support window title
//
//   Rev 1.3   Jun 13 2002 15:52:16   YINGBAOL
//change view 200 and launch other screen
//
//   Rev 1.2   Jun 13 2002 09:46:22   YINGBAOL
//add doMorerecordexist
//
//   Rev 1.1   Jun 04 2002 10:52:42   YINGBAOL
//save work
//
//   Rev 1.0   May 30 2002 11:06:02   YINGBAOL
//Initial revision.
 * 


 */