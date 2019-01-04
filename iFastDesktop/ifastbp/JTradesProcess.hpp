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
//    AUTHOR : Yong Mei Feng
//    DATE   : November 2004
//
//
//    Copyright 2000 by DST Systems, Inc.
//
//******************************************************************************


#include <bfproc\abstractprocess.hpp>

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

//Forward declarations
class MFAccount;
class WorksessionTradesList;

class IFASTBP_LINKAGE JTradesProcess : public AbstractProcess
{
// Construction
public:
   JTradesProcess ( GenericInterfaceContainer* pGIC, 
                    GenericInterface* pGIParent, 
                    const Command &rCommand
                  );
   virtual ~JTradesProcess();
protected:
   virtual SEVERITY doInit();
   virtual E_COMMANDRETURN doProcess();
   virtual bool doOk (GenericInterface *rpGICaller);
   virtual bool doCancel (GenericInterface *rpGICaller);
   virtual SEVERITY deleteItemFromList ( const GenericInterface *rpGICaller,
                                         const BFContainerId& idList
                                       );
/*   virtual SEVERITY doValidateAll ( BFAbstractCBO *rpWSD,
                                      const BFDataGroupId &idDataGroup
                                    );
*/
   virtual SEVERITY doSetField ( const GenericInterface *rpGICaller, 
                                 const BFContainerId &idContainer, 
                                 const BFFieldId &idField, 
                                 const BFDataGroupId &idDataGroup, 
                                 const DString &strValue, 
                                 bool bFormatted
                               );
   virtual void doGetField ( const GenericInterface *rpGICaller,  
                             const BFContainerId &idContainer, 
                             const BFFieldId &idField, 
                             const BFDataGroupId &idDataGroup, 
                             DString &strValueOut, 
                             bool bFormtted
                           ) const;
   virtual SEVERITY doGetErrors ( const GenericInterface *rpGICaller,
                                  const BFContainerId &idContainer,
                                  const BFFieldId &idField,
                                  const BFDataGroupId &idDataGroup,
                                  CONDITIONVECTOR &conditions 
                                ) const;
   virtual const BFProperties *doGetFieldAttributes ( const GenericInterface *rpGICaller, 
                                                      const BFContainerId &idContainer, 
                                                      const BFFieldId &idField, 
                                                      const BFDataGroupId &idDataGroup
                                                    );

   virtual bool doRegisterObserver ( const GenericInterface *rpGICaller,
                                     const BFContainerId &idContainer,
                                     const BFFieldId &idField,
                                     const BFDataGroupId &idDataGroup,
                                     BFObserver &rpObserver
                                   );
   virtual bool doSend ( GenericInterface *rpGICaller, 
                         const I_CHAR *szMessage
                       );
   virtual bool doModelessChildComplete (const Command &cmd);
   virtual bool doModelessSetFocus (GenericInterface *rpGICaller);
   virtual void *getPtrForContainer ( const BFContainerId &idContainer, 
                                      const BFDataGroupId &idDataGroup
                                    );
   virtual bool setCommitDataGroupAsHost();
private:
   SEVERITY addTrade (const GenericInterface *rpGICaller);
   void removeCurrentTradeDataFromMaps();
   bool isAccountSetAndValid ( const BFContainerId &idContainer,
                               const BFDataGroupId &idDataGroup
                             );
   bool isOneSideTrade ();
// Class used as key in conditions/properties map
   class TKey
   {
   public:
      DString _tradeKey;
      BFContainerId _idContainer;
      BFFieldId _idField;
      BFDataGroupId _idDataGroup;

      TKey (
            const DString &tradeKey, 
            const BFContainerId &idContainer, 
            const BFFieldId &idField,
            const BFDataGroupId &idDataGroup
           ) :
      _tradeKey (tradeKey),
      _idContainer (idContainer),
      _idField (idField),
      _idDataGroup (idDataGroup)
      {}
   };

   // Class used for comparison of key in map
   class less_TKey
   {
   public:
      bool operator() (const TKey &a, const TKey &b ) const
      {
         if (a._tradeKey != b._tradeKey)
         {
            return (a._tradeKey < b._tradeKey);
         }
         else if (a._idContainer != b._idContainer)
         {
            return (a._idContainer < b._idContainer);
         }
         else if (a._idField != b._idField)
         {
            return (a._idField < b._idField);
         }
         else
         {
            return (a._idDataGroup < b._idDataGroup);
         }
      }
   };

   typedef std::map <TKey, CONDITIONVECTOR*, less_TKey> CONDITIONS_MAP;
   typedef std::map <TKey, DString, less_TKey> VALUES_MAP;

//a map of conditions   
   CONDITIONS_MAP _conditionsMap;

   GenericInterface *_rpChildGI;
   WorksessionTradesList *_pTradesList;
   DString _accountNum;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/JTradesProcess.hpp-arc  $
//
//   Rev 1.11   Nov 07 2004 14:06:18   popescu
//PET 1117/06, synch changes
//
//   Rev 1.10   Mar 21 2003 17:44:30   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.9   Oct 09 2002 23:53:28   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.8   Aug 29 2002 12:52:58   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.7   Aug 21 2002 15:39:48   FENGYONG
//no change
//
//   Rev 1.6   Aug 19 2002 15:28:30   FENGYONG
//add setCurrentListItem function
//
//   Rev 1.5   22 May 2002 18:20:30   PURDYECH
//BFData Implementation
//
//   Rev 1.4   19 Mar 2002 13:17:52   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.3   17 Oct 2001 15:05:24   KOVACSRO
//Added some permission class var.
//
//   Rev 1.2   Aug 27 2001 14:07:54   FENGYONG
//Rel_R42 Increment
//
//   Rev 1.1   10 Aug 2001 13:33:14   KOVACSRO
//Added some private members.
//
//   Rev 1.0   26 Jul 2001 15:55:58   KOVACSRO
//Initial revision.
 * 
 
// 
*/
