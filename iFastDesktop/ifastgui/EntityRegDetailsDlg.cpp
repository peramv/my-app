//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 by International Financial.
//
//******************************************************************************
//
// ^FILE   : EntityRegDetailsDlg.cpp
// ^AUTHOR : 
// ^DATE   : 23 December 2013
//
// ^CLASS    : EntityRegDetailsDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include "stdafx.h"

#include "mfdstc.h"
#include <bfproc\abstractprocess.hpp>
#include "entityregdetailsdlg.h"
#include <ifastcbo\dstcommonfunction.hpp>

#include <uibase\dstlistctrl.h>
#include <ifastcbo\dstcworksession.hpp>
#include <uibase\dstcombobox.h>
#include <uibase\dstbutton.h>
#include <ifastbp\entityregdetailsprocessincludes.h>
#include <ifastcbo\mfaccount.hpp>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_ENT_REG_MAINT;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator<EntityRegDetailsDlg> dlgCreator(CMD_GUI_ENT_REG_MAINT);

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME                  = I_("EntityRegDetailsDlg");  
   const I_CHAR * const YES                        = I_("Y");
   const I_CHAR * const NO                         = I_("N");

   const I_CHAR * const LV_ENT_REG_LIST            = I_("Entity Regulatory Details List");
   const I_CHAR * const LV_ENT_REG_JURIS_LIST      = I_("Entity Regulatory Jurisdiction List");
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId EntityRegDetailsHeading;
   extern CLASS_IMPORT const BFTextFieldId EntityRegJurisDetailsHeading;
   extern CLASS_IMPORT const BFTextFieldId AccountRegulatoryDetailsHeading;	
   extern CLASS_IMPORT const BFTextFieldId EntityName;
   extern CLASS_IMPORT const BFTextFieldId FATCACode;
   extern CLASS_IMPORT const BFTextFieldId FFIClass;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFDateFieldId StopDate;
   extern CLASS_IMPORT const BFTextFieldId FATCAConsent;
   extern CLASS_IMPORT const BFTextFieldId TaxJuris;
   extern CLASS_IMPORT const BFTextFieldId TaxPayerStat;
   extern CLASS_IMPORT const BFDateFieldId TaxPayerStartDate;
   extern CLASS_IMPORT const BFDateFieldId TaxPayerStopDate;
   extern CLASS_IMPORT const BFTextFieldId AutoResetTaxPayerStat;
   extern CLASS_IMPORT const BFTextFieldId EntityType;
   extern CLASS_IMPORT const BFTextFieldId EntRegDetlExist;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId TPSReason;

   extern CLASS_IMPORT const BFTextFieldId NoTINReason;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const ENTITY_REGULATORY_MAINT;
}

namespace CND
{  
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
class LVEntityRegDetailsData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVEntityRegDetailsData() {}

   DString fEntityName, fRegulation, fFFIClass, fEffectiveDate, fStopDate;

   virtual void update(BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey)
   {
      pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::EntityName, fEntityName); 
      pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::FATCACode, fRegulation); 
      pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::FFIClass, fFFIClass); 
      pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::EffectiveDate, fEffectiveDate);
      pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::StopDate, fStopDate);
   }
};

//******************************************************************************
class LVEntityRegJurisDetailsData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVEntityRegJurisDetailsData() {}

   DString fEntityName, fRegulation, fTaxJuris, fTaxPayerStat, fTaxPayerStartDate, fTaxPayerStopDate, fFATCAConsent, fTPSReason;

   virtual void update(BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey)
   {
      pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::EntityName, fEntityName); 		
      pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::FATCACode, fRegulation); 
      pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::TaxJuris, fTaxJuris); 
      pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::TaxPayerStat, fTaxPayerStat); 
      pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::TaxPayerStartDate, fTaxPayerStartDate); 
      pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::TaxPayerStopDate, fTaxPayerStopDate); 
      pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::FATCAConsent, fFATCAConsent); 
      pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::TPSReason, fTPSReason);
   }
};

//******************************************************************************
class LVEntityRegDetailsAdapter : public IFDSListCtrlAdapter< LVEntityRegDetailsData >
{
public:
   // required overrides
   virtual int compare(IFDSListBase* pCtrl, int iSortColumn, bool bAscending, 
      RowData* pData1, RowData* pData2, LPARAM lParam1, LPARAM lParam2)
   {
      int result = 0;
      const BFFieldId* pFieldId = pCtrl->getColumnField(iSortColumn - 1);

      if (1 == iSortColumn) 
      {
         // Condition indicator column.  Sort on image index
         result = (IFDSListBase::getColumnLVItem(lParam1, iSortColumn - 1)->iImage - 
            IFDSListBase::getColumnLVItem(lParam2, iSortColumn - 1)->iImage);	

         // Force list to sort by repeat count from view as view already sort record
         pCtrl->sortByInsertionOrder();
      } 
      else if (NULL == pFieldId) 
      {
         return (0);
      }
      else if (*pFieldId == ifds::EntityName) 
      {	
         result = i_strcmp( pData1->fEntityName.c_str(), pData2->fEntityName.c_str() );
      }
      else if (*pFieldId == ifds::FATCACode) 
      {	
         result = i_strcmp( pData1->fRegulation.c_str(), pData2->fRegulation.c_str() );
      }
      else if (*pFieldId == ifds::FFIClass) 
      {	
         result = i_strcmp( pData1->fFFIClass.c_str(), pData2->fFFIClass.c_str() );
      }
      else if (*pFieldId == ifds::EffectiveDate) 
      {	
         if ( DSTCommonFunctions::CompareDates( pData1->fEffectiveDate.c_str(), pData2->fEffectiveDate.c_str(), BFDate::DF_DISPLAY ) == DSTCommonFunctions::FIRST_EARLIER )
            result = 1;
         else if ( DSTCommonFunctions::CompareDates( pData2->fEffectiveDate.c_str(), pData1->fEffectiveDate.c_str(), BFDate::DF_DISPLAY ) == DSTCommonFunctions::FIRST_EARLIER ) 
            result = -1;
         // for equal, result will be 0              
      }    		
      else if (*pFieldId == ifds::StopDate) 
      {	
         if ( DSTCommonFunctions::CompareDates( pData1->fStopDate.c_str(), pData2->fStopDate.c_str(), BFDate::DF_DISPLAY ) == DSTCommonFunctions::FIRST_EARLIER )
            result = 1;
         else if ( DSTCommonFunctions::CompareDates( pData2->fStopDate.c_str(), pData1->fStopDate.c_str(), BFDate::DF_DISPLAY ) == DSTCommonFunctions::FIRST_EARLIER ) 
            result = -1;
         // for equal, result will be 0              
      }	

      return (bAscending ? result : -result);
   }

   virtual LRESULT onGetDispInfo(IFDSListCtrl* pCtrl, RowData* pData, LV_DISPINFO* pDispInfo)
   {
      if (pDispInfo->item.mask & LVIF_TEXT)
      {
         const BFFieldId* pFieldId = pCtrl->getColumnField(pDispInfo->item.iSubItem);

         if (NULL == pFieldId) 
         {
            pDispInfo->item.pszText = I_("");
         } 
         else if (*pFieldId == ifds::EntityName)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->fEntityName.c_str();
         }          
         else if (*pFieldId == ifds::FATCACode)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->fRegulation.c_str();
         }          
         else if (*pFieldId == ifds::FFIClass)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->fFFIClass.c_str();
         }   
         else if (*pFieldId == ifds::EffectiveDate)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->fEffectiveDate.c_str();
         }    
         else if (*pFieldId == ifds::StopDate)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->fStopDate.c_str();
         }   

         return (1);
      }

      return (0);
   }
};

//******************************************************************************
class LVEntityRegJurisDetailsAdapter : public IFDSListCtrlAdapter< LVEntityRegJurisDetailsData >
{
public:
   // required overrides
   virtual int compare(IFDSListBase* pCtrl, int iSortColumn, bool bAscending, 
      RowData* pData1, RowData* pData2, LPARAM lParam1, LPARAM lParam2)
   {
      int result = 0;
      const BFFieldId* pFieldId = pCtrl->getColumnField(iSortColumn - 1);

      if (1 == iSortColumn) 
      {
         // Condition indicator column.  Sort on image index
         result = (IFDSListBase::getColumnLVItem(lParam1, iSortColumn - 1)->iImage - 
            IFDSListBase::getColumnLVItem(lParam2, iSortColumn - 1)->iImage);

         // Force list to sort by repeat count from view as view already sort record
         pCtrl->sortByInsertionOrder();
      } 
      else if (NULL == pFieldId) 
      {
         return (0);
      } 
      else if (*pFieldId == ifds::EntityName) 
      {	
         result = i_strcmp( pData1->fEntityName.c_str(), pData2->fEntityName.c_str() );
      }
      else if (*pFieldId == ifds::FATCACode) 
      {	
         result = i_strcmp( pData1->fRegulation.c_str(), pData2->fRegulation.c_str() );
      }
      else if (*pFieldId == ifds::TaxJuris) 
      {	
         result = i_strcmp( pData1->fTaxJuris.c_str(), pData2->fTaxJuris.c_str() );
      }
      else if (*pFieldId == ifds::TaxPayerStat) 
      {	
         result = i_strcmp( pData1->fTaxPayerStat.c_str(), pData2->fTaxPayerStat.c_str() );
      }
      else if (*pFieldId == ifds::TaxPayerStartDate) 
      {	
         if ( DSTCommonFunctions::CompareDates( pData1->fTaxPayerStartDate.c_str(), pData2->fTaxPayerStartDate.c_str(), BFDate::DF_DISPLAY ) == DSTCommonFunctions::FIRST_EARLIER )
            result = 1;
         else if ( DSTCommonFunctions::CompareDates( pData2->fTaxPayerStartDate.c_str(), pData1->fTaxPayerStartDate.c_str(), BFDate::DF_DISPLAY ) == DSTCommonFunctions::FIRST_EARLIER ) 
            result = -1;
         // for equal, result will be 0                
      }    
      else if (*pFieldId == ifds::TaxPayerStopDate) 
      {	
         if ( DSTCommonFunctions::CompareDates( pData1->fTaxPayerStopDate.c_str(), pData2->fTaxPayerStopDate.c_str(), BFDate::DF_DISPLAY ) == DSTCommonFunctions::FIRST_EARLIER )
            result = 1;
         else if ( DSTCommonFunctions::CompareDates( pData2->fTaxPayerStopDate.c_str(), pData1->fTaxPayerStopDate.c_str(), BFDate::DF_DISPLAY ) == DSTCommonFunctions::FIRST_EARLIER ) 
            result = -1;
         // for equal, result will be 0                
      } 
      else if (*pFieldId == ifds::FATCAConsent) 
      {	
         result = i_strcmp( pData1->fFATCAConsent.c_str(), pData2->fFATCAConsent.c_str() );
      }
      else if (*pFieldId == ifds::TPSReason) 
      {	
         result = i_strcmp( pData1->fTPSReason.c_str(), pData2->fTPSReason.c_str() );
      }
      
      return (bAscending ? result : -result);
   }

   virtual LRESULT onGetDispInfo(IFDSListCtrl* pCtrl, RowData* pData, LV_DISPINFO* pDispInfo)
   {
      if (pDispInfo->item.mask & LVIF_TEXT)
      {
         const BFFieldId* pFieldId = pCtrl->getColumnField(pDispInfo->item.iSubItem);

         if (NULL == pFieldId) 
         {
            pDispInfo->item.pszText = I_("");
         } 			
         else if (*pFieldId == ifds::EntityName)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->fEntityName.c_str();
         }   
         else if (*pFieldId == ifds::FATCACode)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->fRegulation.c_str();
         }   
         else if (*pFieldId == ifds::TaxJuris)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->fTaxJuris.c_str();
         }          
         else if (*pFieldId == ifds::TaxPayerStat)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->fTaxPayerStat.c_str();
         }          
         else if (*pFieldId == ifds::TaxPayerStartDate)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->fTaxPayerStartDate.c_str();
         }   
         else if (*pFieldId == ifds::TaxPayerStopDate)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->fTaxPayerStopDate.c_str();
         }  
         else if (*pFieldId == ifds::FATCAConsent)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->fFATCAConsent.c_str();
         }
         else if (*pFieldId == ifds::TPSReason)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->fTPSReason.c_str();
         }

         return (1);
      }

      return (0);
   }
};


//******************************************************************************
EntityRegDetailsDlg::EntityRegDetailsDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
:BaseMainDlg( EntityRegDetailsDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );   
}


//******************************************************************************
EntityRegDetailsDlg::~EntityRegDetailsDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}


//******************************************************************************
BOOL EntityRegDetailsDlg::OnInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_("OnInitDialog"));
   BaseMainDlg::OnInitDialog();

   return TRUE;
}


//******************************************************************************
void EntityRegDetailsDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange( pDX );
}


//******************************************************************************
BEGIN_MESSAGE_MAP( EntityRegDetailsDlg, BaseMainDlg )
   //{{AFX_MSG_MAP( EntityRegDetailsDlg )
   //ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)

   ON_BN_CLICKED(IDC_RB_ENT_REG_DETL, OnRbEntityRegDetail)
   ON_BN_CLICKED(IDC_RB_ENT_REG_JURIS_DETL, OnRbEntityRegJurisDetail)
   //ON_BN_CLICKED(IDC_BTN_HISTORICAL, OnBtnHistorical)	

   ON_BN_CLICKED(IDC_BTN_ADD_ENT_REG, OnBtnEntRegAdd)
   ON_BN_CLICKED(IDC_BTN_DELETE_ENT_REG, OnBtnEntRegDelete)
   ON_BN_CLICKED(IDC_BTN_HISTORICAL_ENT_REG , OnBtnEntRegHistorical)	
   ON_BN_CLICKED(IDC_BTN_ADMIN_DATES_ENT_REG, OnBtnEntRegAdmDates)

   ON_BN_CLICKED(IDC_BTN_ADD_ENT_JURIS, OnBtnEntRegJurisAdd)
   ON_BN_CLICKED(IDC_BTN_DELETE_ENT_JURIS, OnBtnEntRegJurisDelete)
   ON_BN_CLICKED(IDC_BTN_HISTORICAL_ENT_JURIS, OnBtnEntRegJurisHistorical)		
   ON_BN_CLICKED(IDC_BTN_ADMIN_DATES_ENT_JURIS, OnBtnEntRegJurisAdmDates)
   ON_BN_CLICKED(IDC_CHK_NO_SYSTEM_RESET, OnChkNoSystemReset)

   //}}AFX_MSG_MAP
END_MESSAGE_MAP()


//******************************************************************************
void EntityRegDetailsDlg::OnPostInitDialog()
{
   TRACE_METHOD(CLASSNAME, I_( "OnPostInitDialog" ));

   //DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   DString dstrShrNum, dstrAccountNum, dstrEntityName;

   getParent()->getField(this, BF::NullContainerId, ShrCaption, dstrShrNum); 
   getParent()->getField(this, BF::NullContainerId, AccountCaption, dstrAccountNum); 
   getParent()->getField(this, BF::NullContainerId, EntityCaption, dstrEntityName); 

   SetShrAcctCaption(dstrShrNum, dstrAccountNum, dstrEntityName);

   SetUserAccesFunctionCode(UAF::ENTITY_REGULATORY_MAINT);
   addBtnAddForPermissionCheck(IDC_BTN_ADD_ENT_REG, IDC_LV_ENT_REG_LIST);
   addBtnDeleteForPermissionCheck(IDC_BTN_DELETE_ENT_REG, IDC_LV_ENT_REG_LIST);

   addBtnAddForPermissionCheck(IDC_BTN_ADD_ENT_JURIS, IDC_LV_ENT_REG_JURIS_LIST);
   addBtnDeleteForPermissionCheck(IDC_BTN_DELETE_ENT_JURIS, IDC_LV_ENT_REG_JURIS_LIST);

   addControls();

   //Automatically shows EntityRegJurisDetail when the flag is "2".
   DString dstrDefaultRadioBox;
   getParent()->getField(this, BF::NullContainerId, DefaultRadioBox, dstrDefaultRadioBox, false);

   if (dstrDefaultRadioBox.stripAll().upperCase() == I_("2"))
   {
      showEntityRegJurisDetail();
   }
}


//******************************************************************************
SEVERITY EntityRegDetailsDlg::doInit()
{
   TRACE_METHOD(CLASSNAME, I_("doInit"));

   return (NO_CONDITION);
}


//******************************************************************************
void EntityRegDetailsDlg::addControls()
{
   IFDSListCtrl* ifdsListControlEntityRegDetails = 
      new IFDSAdaptedListCtrl< LVEntityRegDetailsAdapter >( this, 
                                                            CLASSNAME, 
                                                            IDC_LV_ENT_REG_LIST, 
                                                            0, 
                                                            0, 
                                                            true, 
                                                            true );

   IFDSListCtrl* ifdsListControlEntityRegJurisDetails = 
      new IFDSAdaptedListCtrl< LVEntityRegJurisDetailsAdapter >( this, 
                                                                 CLASSNAME, 
                                                                 IDC_LV_ENT_REG_JURIS_LIST, 
                                                                 0, 
                                                                 0, 
                                                                 true, 
                                                                 true );

   AddIFDSListControl(ifdsListControlEntityRegDetails, 
                      LV_ENT_REG_LIST, 
                      IFASTBP_PROC::ENTITY_REG_DETAILS_LIST, 
                      ifds::EntityRegDetailsHeading);   

   AddIFDSListControl(ifdsListControlEntityRegJurisDetails, 
                      LV_ENT_REG_JURIS_LIST, 
                      IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST, 
                      ifds::EntityRegJurisDetailsHeading);  

   if (NULL != ifdsListControlEntityRegDetails)		
      ifdsListControlEntityRegDetails->SortOnColumn(1);

   if (NULL != ifdsListControlEntityRegJurisDetails)		
      ifdsListControlEntityRegJurisDetails->SortOnColumn(1);

   // static control for entity regulatory detail
   AddControl(CTRL_STATIC,IDC_STC_ENT_NAME);
   AddControl(CTRL_STATIC,IDC_STC_REGULATION);
   AddControl(CTRL_STATIC,IDC_STC_CLASSIFICATION);
   AddControl(CTRL_STATIC,IDC_STC_ENT_REG_DEFF);
   AddControl(CTRL_STATIC,IDC_STC_ENT_REG_STOP);


   AddControl(CTRL_COMBO,IDC_CMB_ENT_NAME,				IFASTBP_PROC::ENTITY_REG_DETAILS_LIST, ifds::EntityName,				CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_ENT_REG_LIST );
   AddControl(CTRL_STATIC,IDC_STC_ENT_TYPE,				IFASTBP_PROC::ENTITY_REG_DETAILS_LIST, ifds::EntityType,				CTRLFLAG_DEFAULT,				IDC_LV_ENT_REG_LIST );
   AddControl(CTRL_COMBO,IDC_CMB_REGULATION,			IFASTBP_PROC::ENTITY_REG_DETAILS_LIST, ifds::FATCACode,				    CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_ENT_REG_LIST );
   AddControl(CTRL_COMBO,IDC_CMB_CLASSIFICATION,		IFASTBP_PROC::ENTITY_REG_DETAILS_LIST, ifds::FFIClass,				    CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_ENT_REG_LIST );
   AddControl(CTRL_DATE, IDC_DTP_ENT_REG_DEFF,			IFASTBP_PROC::ENTITY_REG_DETAILS_LIST, ifds::EffectiveDate,			    CTRLFLAG_DEFAULT,				IDC_LV_ENT_REG_LIST );
   AddControl(CTRL_DATE, IDC_DTP_ENT_REG_STOP,			IFASTBP_PROC::ENTITY_REG_DETAILS_LIST, ifds::StopDate,  			    CTRLFLAG_DEFAULT,				IDC_LV_ENT_REG_LIST );	

   // static control for entity regulatory jurisdiction detail
   AddControl(CTRL_STATIC,IDC_STC_ENT_NAME_JURIS);
   AddControl(CTRL_STATIC,IDC_STC_REGULATION_JURIS);
   AddControl(CTRL_STATIC,IDC_STC_TAX_JURISDICTION);
   AddControl(CTRL_STATIC,IDC_STC_TAX_PAYER_STAT);
   AddControl(CTRL_STATIC,IDC_STC_ENT_JURIS_DEFF);
   AddControl(CTRL_STATIC,IDC_STC_ENT_JURIS_STOP);
   AddControl(CTRL_STATIC,IDC_STC_CONSENT);


   AddControl(CTRL_COMBO,IDC_CMB_ENT_NAME_JURIS,		IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST, ifds::EntityName,			CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_ENT_REG_JURIS_LIST );
   AddControl(CTRL_STATIC,IDC_STC_ENT_TYPE_JURIS,		IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST, ifds::EntityType,			CTRLFLAG_DEFAULT,				IDC_LV_ENT_REG_JURIS_LIST );
   AddControl(CTRL_COMBO,IDC_CMB_REGULATION_JURIS,		IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST, ifds::FATCACode,			CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_ENT_REG_JURIS_LIST );
   AddControl(CTRL_COMBO,IDC_CMB_TAX_JURISDICTION,		IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST, ifds::TaxJuris,			CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_ENT_REG_JURIS_LIST );
   AddControl(CTRL_COMBO,IDC_CMB_TAX_PAYER_STAT,		IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST, ifds::TaxPayerStat,		CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_ENT_REG_JURIS_LIST );
   AddControl(CTRL_DATE, IDC_DTP_ENT_JURIS_DEFF,		IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST, ifds::TaxPayerStartDate,	CTRLFLAG_DEFAULT,				IDC_LV_ENT_REG_JURIS_LIST );
   AddControl(CTRL_DATE, IDC_DTP_ENT_JURIS_STOP,		IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST, ifds::TaxPayerStopDate,	CTRLFLAG_DEFAULT,				IDC_LV_ENT_REG_JURIS_LIST );
   AddControl(CTRL_STATIC,IDC_CHK_NO_SYSTEM_RESET,     CTRLFLAG_GUI_FIELD );
   AddControl(CTRL_COMBO,IDC_CMB_CONSENT,		        IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST, ifds::FATCAConsent,				    CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_ENT_REG_JURIS_LIST );
   AddControl(CTRL_COMBO,IDC_CMB_TPS_REASON,		    IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST, ifds::TPSReason,     CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_ENT_REG_JURIS_LIST );

   AddControl(CTRL_COMBO,IDC_CMB_NO_TIN_REASON,		    IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST, ifds::NoTINReason,     CTRLFLAG_INITCOMBO_BY_SUB_LIST|CTRLFLAG_INITCOMBO_WITH_BLANK, IDC_LV_ENT_REG_JURIS_LIST );

   LoadListControl(IDC_LV_ENT_REG_LIST, NULL);
   LoadListControl(IDC_LV_ENT_REG_JURIS_LIST, NULL);

   ConnectControlsToData(IDC_LV_ENT_REG_LIST, true);
   ConnectControlsToData(IDC_LV_ENT_REG_JURIS_LIST, true);
   LoadControls();

   // Default is show entity regulatory detail
   showEntityRegDetail();
}

//******************************************************************************
void EntityRegDetailsDlg::showEntityRegDetail()
{
	
   ((CButton* )GetDlgItem(IDC_RB_ENT_REG_DETL))->SetCheck(1);
   ((CButton* )GetDlgItem(IDC_RB_ENT_REG_JURIS_DETL))->SetCheck(0);	

   GetDlgItem (IDC_BTN_ADD_ENT_REG)->ShowWindow(SW_SHOW);
   GetDlgItem (IDC_BTN_DELETE_ENT_REG)->ShowWindow(SW_SHOW);
   GetDlgItem (IDC_BTN_HISTORICAL_ENT_REG)->ShowWindow(SW_SHOW);
   GetDlgItem (IDC_BTN_ADMIN_DATES_ENT_REG)->ShowWindow(SW_SHOW);

   GetList    (IDC_LV_ENT_REG_LIST)->Show (true);
   GetDlgItem (IDC_STC_ENT_NAME)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STC_REGULATION)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STC_CLASSIFICATION)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STC_ENT_REG_DEFF)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STC_ENT_REG_STOP)->ShowWindow (SW_SHOW);

   GetDlgItem (IDC_CMB_ENT_NAME)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STC_ENT_TYPE)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_CMB_REGULATION)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_CMB_CLASSIFICATION)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_DTP_ENT_REG_DEFF)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_DTP_ENT_REG_STOP)->ShowWindow (SW_SHOW);

   // Entity Regulatory Jurisdiction
   GetDlgItem (IDC_BTN_ADD_ENT_JURIS)->ShowWindow(SW_HIDE);
   GetDlgItem (IDC_BTN_DELETE_ENT_JURIS)->ShowWindow(SW_HIDE);
   GetDlgItem (IDC_BTN_HISTORICAL_ENT_JURIS)->ShowWindow(SW_HIDE);
   GetDlgItem (IDC_BTN_ADMIN_DATES_ENT_JURIS)->ShowWindow(SW_HIDE);

   GetList    (IDC_LV_ENT_REG_JURIS_LIST)->Show (false);
   GetDlgItem (IDC_STC_ENT_NAME_JURIS)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STC_REGULATION_JURIS)->ShowWindow (SW_HIDE);	
   GetDlgItem (IDC_STC_TAX_JURISDICTION)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STC_TAX_PAYER_STAT)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STC_ENT_JURIS_DEFF)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STC_ENT_JURIS_STOP)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STC_CONSENT)->ShowWindow (SW_HIDE);

   GetDlgItem (IDC_CMB_ENT_NAME_JURIS)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STC_ENT_TYPE_JURIS)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_CMB_REGULATION_JURIS)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_CMB_TAX_JURISDICTION)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_CMB_TAX_PAYER_STAT)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_DTP_ENT_JURIS_DEFF)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_DTP_ENT_JURIS_STOP)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_CMB_CONSENT)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_CHK_NO_SYSTEM_RESET)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_CMB_TPS_REASON)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STC_TPS_REASON)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_CMB_NO_TIN_REASON)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STC_NO_TIN_REASON)->ShowWindow (SW_HIDE);
	    
   ConnectControlsToData(IDC_LV_ENT_REG_LIST, true, true);
   ConnectControlsToData(IDC_LV_ENT_REG_JURIS_LIST, false, true);
   LoadListControl(IDC_LV_ENT_REG_LIST);
   //LoadControls();



   //ConnectControlToData(IDC_DTP_ENT_REG_DEFF, true, true);
   //ConnectControlToData(IDC_DTP_ENT_JURIS_DEFF, false, true);

}

//******************************************************************************
void EntityRegDetailsDlg::showEntityRegJurisDetail()
{
   ((CButton* )GetDlgItem(IDC_RB_ENT_REG_DETL))->SetCheck(0);
   ((CButton* )GetDlgItem(IDC_RB_ENT_REG_JURIS_DETL))->SetCheck(1);

   GetDlgItem (IDC_BTN_ADD_ENT_REG)->ShowWindow(SW_HIDE);
   GetDlgItem (IDC_BTN_DELETE_ENT_REG)->ShowWindow(SW_HIDE);
   GetDlgItem (IDC_BTN_HISTORICAL_ENT_REG)->ShowWindow(SW_HIDE);
   GetDlgItem (IDC_BTN_ADMIN_DATES_ENT_REG)->ShowWindow(SW_HIDE);

   GetList    (IDC_LV_ENT_REG_LIST)->Show (false);
   GetDlgItem (IDC_STC_ENT_NAME)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STC_REGULATION)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STC_CLASSIFICATION)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STC_ENT_REG_DEFF)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STC_ENT_REG_STOP)->ShowWindow (SW_HIDE);

   GetDlgItem (IDC_CMB_ENT_NAME)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_STC_ENT_TYPE)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_CMB_REGULATION)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_CMB_CLASSIFICATION)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_DTP_ENT_REG_DEFF)->ShowWindow (SW_HIDE);
   GetDlgItem (IDC_DTP_ENT_REG_STOP)->ShowWindow (SW_HIDE);

   // Entity Regulatory Jurisdiction
   GetDlgItem (IDC_BTN_ADD_ENT_JURIS)->ShowWindow(SW_SHOW);
   GetDlgItem (IDC_BTN_DELETE_ENT_JURIS)->ShowWindow(SW_SHOW);
   GetDlgItem (IDC_BTN_HISTORICAL_ENT_JURIS)->ShowWindow(SW_SHOW);
   GetDlgItem (IDC_BTN_ADMIN_DATES_ENT_JURIS)->ShowWindow(SW_SHOW);

   GetList    (IDC_LV_ENT_REG_JURIS_LIST)->Show (true);
   GetDlgItem (IDC_STC_ENT_NAME_JURIS)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STC_REGULATION_JURIS)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STC_TAX_JURISDICTION)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STC_TAX_PAYER_STAT)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STC_ENT_JURIS_DEFF)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STC_ENT_JURIS_STOP)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STC_CONSENT)->ShowWindow (SW_SHOW);

   GetDlgItem (IDC_CMB_ENT_NAME_JURIS)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STC_ENT_TYPE_JURIS)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_CMB_REGULATION_JURIS)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_CMB_TAX_JURISDICTION)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_CMB_TAX_PAYER_STAT)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_DTP_ENT_JURIS_DEFF)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_DTP_ENT_JURIS_STOP)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_CMB_CONSENT)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_CHK_NO_SYSTEM_RESET)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_CMB_TPS_REASON)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STC_TPS_REASON)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_CMB_NO_TIN_REASON)->ShowWindow (SW_SHOW);
   GetDlgItem (IDC_STC_NO_TIN_REASON)->ShowWindow (SW_SHOW);

   ConnectControlsToData(IDC_LV_ENT_REG_LIST, false, true);
   ConnectControlsToData(IDC_LV_ENT_REG_JURIS_LIST, true, true);
   LoadListControl(IDC_LV_ENT_REG_JURIS_LIST);
   //LoadControls();
   //ConnectControlToData(IDC_DTP_ENT_REG_DEFF, false, true);
   //ConnectControlToData(IDC_DTP_ENT_JURIS_DEFF, true, true);

}

//******************************************************************************
void EntityRegDetailsDlg::OnRbEntityRegDetail()
{
   TRACE_METHOD( CLASSNAME, I_( "OnRbEntitiyRegDetail" ));

   showEntityRegDetail();
}

//******************************************************************************
void EntityRegDetailsDlg::OnRbEntityRegJurisDetail()
{
   TRACE_METHOD( CLASSNAME, I_( "OnRbEntitiyRegJurisDetail" ));

   showEntityRegJurisDetail();
}
//******************************************************************************
bool EntityRegDetailsDlg::doRefresh(GenericInterface * rpGICaller, 
                                    const I_CHAR * szOriginalCommand)
{
   return(true);
}

//******************************************************************************
void EntityRegDetailsDlg::OnBtnEntRegAdd()
{
   TRACE_METHOD(CLASSNAME, I_("OnBtnEntRegAdd"));

   AddToListControl(IDC_LV_ENT_REG_LIST);
/*    DString listKey = 
       getParent ()->getCurrentListItemKey (this, IFASTBP_PROC::ENTITY_REG_DETAILS_LIST);
    LoadListControl (IDC_LV_ENT_REG_LIST, &listKey);  */ 

}

//********************************************************************************
void EntityRegDetailsDlg::OnBtnEntRegDelete()
{
   TRACE_METHOD(CLASSNAME, I_("OnBtnEntRegDelete"));

   DeleteFromListControl(IDC_LV_ENT_REG_LIST);
}

//******************************************************************************
void EntityRegDetailsDlg::OnBtnEntRegJurisAdd()
{
   TRACE_METHOD(CLASSNAME, I_("OnBtnEntRegJurisAdd"));

   AddToListControl(IDC_LV_ENT_REG_JURIS_LIST);
    //DString listKey = 
    //   getParent ()->getCurrentListItemKey (this, IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST);
    //LoadListControl (IDC_LV_ENT_REG_JURIS_LIST, &listKey);
}


//********************************************************************************
void EntityRegDetailsDlg::OnBtnEntRegJurisDelete()
{
   TRACE_METHOD(CLASSNAME, I_("OnBtnEntRegJurisDelete"));

   DeleteFromListControl(IDC_LV_ENT_REG_JURIS_LIST);
}
//********************************************************************************
void EntityRegDetailsDlg::OnChkNoSystemReset()
{
   TRACE_METHOD(CLASSNAME, I_("OnChkNoSystemReset"));

   int checkStatus = 
      static_cast<CButton*>(GetDlgItem(IDC_CHK_NO_SYSTEM_RESET))->GetCheck();

   /* 
   Label and field name is a bit confuse but have to quickly fix,
   If label NoSystemReset checked that means it is AutoResetTaxPayerStatus.
   */
   getParent()->setField(this, 
                         IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST, 
                         ifds::AutoResetTaxPayerStat,
                         (checkStatus == BST_CHECKED)? I_("N"):I_("Y"),
                         false);

}

//**********************************************************************************
void EntityRegDetailsDlg::OnBtnEntRegHistorical()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnEntRegHistorical"));

   IFastHistoricalInfo historicalInfo;

   historicalInfo(this, IFASTBP_PROC::ENTITY_REG_DETAILS_LIST);
}
//**********************************************************************************
void EntityRegDetailsDlg::OnBtnEntRegJurisHistorical()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnEntRegJurisHistorical"));

   IFastHistoricalInfo historicalInfo;

   historicalInfo(this, IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST);
}

//**********************************************************************************
void EntityRegDetailsDlg::OnBtnEntRegAdmDates() 
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnAdminDates"));

   CWaitCursor wait;
   ShowAdminDates(IFASTBP_PROC::ENTITY_REG_DETAILS_LIST);
}

//**********************************************************************************
void EntityRegDetailsDlg::OnBtnEntRegJurisAdmDates() 
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnAdminDates"));

   CWaitCursor wait;
   ShowAdminDates(IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST);
}
//******************************************************************************
//void EntityRegDetailsDlg::OnBtnReset() 
//{
//	TRACE_METHOD(CLASSNAME, I_("OnBtnReset"));
//
//	ResetListItem(IDC_LV_ACCT_REGULATORY_LIST);
//}


//******************************************************************************
void EntityRegDetailsDlg::DoListItemChanged(UINT listControlID,
                                            const DString &strKey,
                                            bool bIsNewItem,
                                            bool bIsDummyItem)
{
   if(listControlID == IDC_LV_ENT_REG_LIST)
   {
      GetDlgItem(IDC_BTN_HISTORICAL_ENT_REG)->EnableWindow(!bIsNewItem); // disable if it is new item	
      GetDlgItem(IDC_BTN_ADMIN_DATES_ENT_REG)->EnableWindow(!bIsNewItem);	
   }
   else if(listControlID == IDC_LV_ENT_REG_JURIS_LIST)
   {
      GetDlgItem(IDC_BTN_HISTORICAL_ENT_JURIS)->EnableWindow(!bIsNewItem); // disable if it is new item
      GetDlgItem(IDC_BTN_ADMIN_DATES_ENT_JURIS)->EnableWindow(!bIsNewItem);	

      DString dstrAutoResetTaxPayerStat;
      getParent()->getField( this, IFASTBP_PROC::ENTITY_REG_JURIS_DETAILS_LIST, ifds::AutoResetTaxPayerStat, dstrAutoResetTaxPayerStat, false );	

      static_cast<CButton*>(GetDlgItem(IDC_CHK_NO_SYSTEM_RESET))->SetCheck( (dstrAutoResetTaxPayerStat==YES)? BST_UNCHECKED:BST_CHECKED );

   }

}

//******************************************************************************
bool EntityRegDetailsDlg::GetDataForControl( UINT controlID,
                                             DString &strValueOut,
                                             bool bFormatted,
                                             int index ) const
{
   if( controlID == IDC_STC_ENT_TYPE ||
       controlID == IDC_STC_ENT_TYPE_JURIS )
   {
      const BFFieldId& bfFieldId = GetControl(controlID)->GetFieldID();
      const BFContainerId& bfContainerId = GetControl(controlID)->GetContainerID();

      getParent()->getField( this, bfContainerId, bfFieldId, strValueOut, bFormatted );

      return true;
   }

   return false;
}

//**********************************************************************************
void EntityRegDetailsDlg::ControlUpdated(UINT controlID, const DString &strValue )
{

   switch( controlID )
   {
      case IDC_CMB_ENT_NAME:
      {
         LoadControl(IDC_STC_ENT_TYPE);
      }
      break;

      case IDC_CMB_ENT_NAME_JURIS:
      {
         LoadControl(IDC_STC_ENT_TYPE_JURIS);
      }
      break;

      default:
         break;
   }
}

//******************************************************************************
void EntityRegDetailsDlg::doDisableNonPermButtons()
{
   bool bEnableSystemReset = hasUpdatePermission(UAF::ENTITY_REGULATORY_MAINT);

   GetDlgItem(IDC_CHK_NO_SYSTEM_RESET)->EnableWindow(bEnableSystemReset);
}
