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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : EntityMaintenanceDlg.cpp
// ^AUTHOR : Yingbao  Li 
// ^DATE   : 22/04/1999
//
// ----------------------------------------------------------
//
// ^CLASS    : EntityMaintenanceDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the System/MGMT selection dialog
//
//******************************************************************************

#include "stdafx.h"

#include "mfdstc.h"
#include "entitymaintenancedlg.h"
#include <ifastcbo\accountentityxref.hpp>
#include <ifastcsi\csisession.h>
#include <ifastcsi\ifastcsi.h>
#include <uibase\dstcombobox.h>
#include <uibase\dsttabctrl.h>
#include <uibase\ifdslistctrl.h>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastcbo\dstcworksession.hpp>
#include <ifastcbo\Entity.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\errmsgruleslist.hpp>
#include <uibase\dstedit.h>
#include <uibase\dstdatetime.h>
#include <uibase\dstlistctrl.h>
#include <ifastbp\entityprocessincludes.h>
#include <ifastbp\nasuprocessincludes.h>
#include <ifastbp\whereusedprocessincludes.h>
#include <ifastdataimpl\dse_dstc0050_vw.hpp>
#include <ifastdataimpl\dse_dstc0051_vw.hpp>
#include <ifastbp\respbenrelprocessincludes.h>
#include <ifastbp\addressprocessincludes.h>
#include <bfproc\abstractprocess.hpp>
#include <ifastcbo\mgmtcooptions.hpp>

#include <ifastdataimpl\dse_dstc0149_vw.hpp>
#include <ifastdataimpl\dse_dstc0050_vwrepeat_record.hpp>

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_RESPBENREL;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_WHEREUSED;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDCLASS;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_ENTITY_MAINTENANCE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ADDRESSES;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_REG_DOCUMENT_LIST;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_DEMOGRAPHICS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_TAX_JURIS_HISTORY;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_RESP_GRANTS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_RESP_GRANTS2;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ENT_REG_MAINT;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< EntityMaintenanceDlg > dlgCreator( CMD_GUI_ENTITY_MAINTENANCE );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   // trace literals
   const I_CHAR *CLASSNAME                      = I_( "EntityMaintenanceDlg" );
   const I_CHAR *LV_ENTITY_LIST                 = I_( "Entity Name List" );
   const I_CHAR *LV_ENTITY_IDS_LIST             = I_( "Entity IDS List" );
   const I_CHAR *ENTITYNAME                     = I_( "EntityName" );
   const I_CHAR *YEARS                          = I_( "yrs" );
   const I_CHAR *MONTHS                         = I_( "mths" );
   const I_CHAR *COMMA_STRING                   = I_( "," );
   const I_CHAR *SEMICOLUMN_STRING              = I_( ";" );
   const I_CHAR *EMPTY_STRING                   = I_("");
   const I_CHAR *SPACE_STRING                   = I_( " " );
   const I_CHAR *DEFAULT_DATE                   = I_("12319999");
   const I_CHAR *RETURN                         = I_( "\n" );
   const I_CHAR *YES                            = I_( "Yes" );
   const I_CHAR *Y                              = I_( "Y" );
   const I_CHAR *NO                             = I_( "No" );
   const I_CHAR *N                              = I_( "N" );
   const I_CHAR *ENTITY_TYPE_ACC_OWNER          = I_( "01" );
   const I_CHAR *ENTITY_TYPE_CLEARING_PLATFORM  = I_( "58" );
   const I_CHAR *CLEARING_ID                    = I_( "58" ); //MT535/MT536
   const I_CHAR *ENTITY_TYPE_PRIMARY_BENEF      = I_( "07" );
   const I_CHAR *ENTITY_TYPE_SECONDARY_BENEF    = I_( "08" );
   const I_CHAR *ENTITY_TYPE_SUCCESSOR          = I_( "09" );
   const I_CHAR *ENTITY_TYPE_RELATED_PARTY      = I_( "71" );
   const I_CHAR *ENTITY_TYPE_COLUMN             = I_( "EntityType" );
   const I_CHAR *SEQ_NUMBER_COLUMN              = I_( "SeqNumber" );
   const I_CHAR *ENTITY_ID_COLUMN               = I_( "EntityId" );
   const I_CHAR *EFFECTIVE_DATE_COLUMN          = I_( "EffectiveDate" );
   const I_CHAR *ESCROW_ENTITY_TYPE             = I_( "11" );
   const I_CHAR *ASSIGNEE_ENTITY_TYPE           = I_( "53" );
   const I_CHAR *ACCOUNT_OWNER_ENTITY_TYPE      = I_( "01" );
   const I_CHAR *RESP_BENEFICIARY               = I_( "50" );
   const I_CHAR *RESP_PCG_INDIV_ENTITY_TYPE     = I_( "55" );
   const I_CHAR *RESP_PCG_INST_ENTITY_TYPE      = I_( "56" );
   const I_CHAR *REGISTRATION_AGENT_ENTITY_TYPE = I_( "64" );
   const I_CHAR *ENTITY_TYPE_ANNUITANT          = I_( "05" );
   const I_CHAR *JOINT_ACCOUNT_TYPE             = I_( "2" );
   const I_CHAR *SIN                            = I_( "06" );
   const I_CHAR *BUSINESS_NUMBER                = I_( "17" );
   const I_CHAR *CODE_CATEGORY_CORPORATE        = I_( "02" );
   const I_CHAR *TAX_ID_NUM                     = I_( "08" );
   const I_CHAR *DEPOSITARY_BANK_ACCOUNT        = I_( "07" );

   const I_CHAR * const FUND_CODE               = I_( "FundCode" );
   const I_CHAR * const CLASS_CODE              = I_( "ClassCode" );
   const I_CHAR * const SHR_NUM                 = I_( "ShrNum" );

   const I_CHAR * const BENEFICIARY_TITLE          = I_( "B" );
   const I_CHAR * const ESCROW_TITLE               = I_( "E" );
   const I_CHAR * const JOINT_INFORMATION_TITLE    = I_( "J" );
   const I_CHAR * const RESP_BENEFICIARY_TITLE     = I_( "R" );
   const I_CHAR * const ASSIGNEE_TITLE             = I_( "A" );
   const I_CHAR * const ACCOUNTHOLDER_ENTITY_TYPE  = I_( "01" );
   const I_CHAR * OWNER_SPOUSAL                    = I_( "98" );
   const I_CHAR * const CHARACTERS = I_("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
   const I_CHAR * const ALPHACHARACTERS = I_(" ,abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
   const I_CHAR * const ENTITY_ID_VALUE_COLUMN     = I_( "IdValue" );
   const I_CHAR * const POLITICALLY_EXPOSED_PERSON = I_( "3" );
   const I_CHAR * const APPLICABLE_TO_ALL		   = I_( "*" );
   const I_CHAR * const RELATED_PARTY_AML		   = I_( "78" );
   const I_CHAR * const RDSP_TAX_TYPE			   = I_( "RS" );
}

namespace ENTITYDLG
{
   const I_CHAR * const ACCOUNT_NUM          = I_( "AccountNum" );
   const I_CHAR * const ENTITY_ID            = I_( "EntityId" );
   const I_CHAR * const KEY                  = I_( "Key" );
   const I_CHAR * const EXIST_ACCOUNT        = I_( "ExistAccount" );
   const I_CHAR * const CALLER               = I_( "Caller" );
   const I_CHAR * const ENTITY               = I_( "Entity" );
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
   extern const long GUI_NO_ENTITY_IN_LIST;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const ESCROW;
   extern CLASS_IMPORT I_CHAR * const UPDATE_ENTITY_PHONE_INFO;
   extern CLASS_IMPORT I_CHAR * const ENTITY_MAINTANENCE;
   extern CLASS_IMPORT I_CHAR * const ESCROW_BAND;
   extern CLASS_IMPORT I_CHAR * const ASSIGNEE_ENTITY_TYPE_SETUP;
   extern CLASS_IMPORT I_CHAR * const RESP_BENEFICIARY;
   extern CLASS_IMPORT I_CHAR * const RESP_GRANTS;
   extern CLASS_IMPORT I_CHAR * const RESP_ALLOCATION;
   extern CLASS_IMPORT I_CHAR * const ENTITY_TAX_JURIS_HISTORY;
   extern CLASS_IMPORT I_CHAR * const ENTITY_REGULATORY_MAINT;
   extern CLASS_IMPORT I_CHAR * const RESP_GRANT_INFORMATION;
   extern CLASS_IMPORT I_CHAR * const APAC_SUPREGN;
}

namespace ENTITY_IDS_CONTROLS
{
   const UINT EDIT_CNTRL   = 1;
   const UINT COMBO_CNTRL  = 2;
}

namespace EXISTING_BENEF_CONTROLS
{
   const UINT BENEF_INFO      = 3;
}

namespace RESP2_CONTROLS
{
   const UINT BENEF_INFO      = 4;
   const UINT RELATIONSHIPS   = 5;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId RES2Client;
   extern CLASS_IMPORT const BFTextFieldId QESIClient;
   extern CLASS_IMPORT const BFTextFieldId Printed; 
   extern CLASS_IMPORT const BFDecimalFieldId AllocationPercent; 
   extern CLASS_IMPORT const BFTextFieldId GrantRequest; 
   extern CLASS_IMPORT const BFTextFieldId Tainted; 
   extern CLASS_IMPORT const BFDateFieldId TaintEndDate; 
   extern CLASS_IMPORT const BFTextFieldId CreateRec511;
   extern CLASS_IMPORT const BFDateFieldId Rec511CutOffDate;
   extern CLASS_IMPORT const BFTextFieldId RES2ParentLglList;
   extern CLASS_IMPORT const BFTextFieldId RES2DesInstList;
   extern CLASS_IMPORT const BFTextFieldId RES2PCGList;
   extern CLASS_IMPORT const BFTextFieldId CLBExists;
   extern CLASS_IMPORT const BFTextFieldId GrantExists;
   extern CLASS_IMPORT const BFTextFieldId TradeExists;
   extern CLASS_IMPORT const BFTextFieldId PCGChange;
   extern CLASS_IMPORT const BFTextFieldId PCGLinkBenef;
   extern CLASS_IMPORT const BFDateFieldId IdExpireDate;
   extern CLASS_IMPORT const BFTextFieldId FATCAApplicable;
   extern CLASS_IMPORT const BFTextFieldId FATCAFFI;
   extern CLASS_IMPORT const BFTextFieldId CSSStopSINMatch;
   extern CLASS_IMPORT const BFTextFieldId MstrActActive;
   extern CLASS_IMPORT const BFTextFieldId CRSEntityList;
   extern CLASS_IMPORT const BFTextFieldId RiskHeading;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId TaxType;
   extern CLASS_IMPORT const BFTextFieldId LastNameFormat;
   extern CLASS_IMPORT const BFTextFieldId PaternalLastName;
   extern CLASS_IMPORT const BFTextFieldId MaternalLastName;
}

namespace ENTITY_IDS_VALUE
{
   const I_CHAR * const FAST                 = I_ ("30" );
   const I_CHAR * const iFAST_SICAV          = I_ ("31" );
   const I_CHAR * const iFAST_OEIC           = I_ ("32" );
}

namespace IFASTERR
{   
   extern CLASS_IMPORT I_CHAR * const JURISDICTION_NOT_SAME_AS_SHRHLDR_JURISDICTION;
}

namespace IDS
{
   extern CLASS_IMPORT const I_CHAR * const FATCA_GIIN;
   extern CLASS_IMPORT const I_CHAR * const SOCIAL_SECURITY_NUMBER;
}


//******************************************************************************
class LVRiskDetailsData : public IFDSListCtrlRowDataBase
{
public:
    virtual ~LVRiskDetailsData() {}

    DString fRiskLvl, fCntryOfExpr, fEffectiveDate, fStopDate;

    virtual void update(BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey)
    {
        pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::RiskLevel, fRiskLvl); 
        pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::CountryOfExposure, fCntryOfExpr); 
        pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::EffectiveDate, fEffectiveDate); 
        pDlg->getParent()->getField(pDlg, pCtrl->getContainerId(), ifds::StopDate, fStopDate); 
    }
};


//******************************************************************************
class LVRiskDetailsAdapter : public IFDSListCtrlAdapter< LVRiskDetailsData >
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
        } 
        else if (NULL == pFieldId) 
        {
            return (0);
        } 
        else if (*pFieldId == ifds::RiskLevel) 
        {	
            result = i_strcmp( pData1->fRiskLvl.c_str(), pData2->fRiskLvl.c_str() ); 
        }    
        else if (*pFieldId == ifds::CountryOfExposure) 
        {
            result = i_strcmp( pData1->fCntryOfExpr.c_str(), pData2->fCntryOfExpr.c_str() ); 
        }     
        else if (*pFieldId == ifds::EffectiveDate) 
        {
            if ( DSTCommonFunctions::CompareDates(pData1->fEffectiveDate.c_str(), pData2->fEffectiveDate.c_str() ) == DSTCommonFunctions::FIRST_EARLIER )
				result = 1;
            else if ( DSTCommonFunctions::CompareDates( pData2->fEffectiveDate.c_str(), pData1->fEffectiveDate.c_str() ) == DSTCommonFunctions::FIRST_EARLIER ) 
				result = -1;
        }     
        else if (*pFieldId == ifds::StopDate) 
        {
            if ( DSTCommonFunctions::CompareDates(pData1->fStopDate.c_str(), pData2->fStopDate.c_str() ) == DSTCommonFunctions::FIRST_EARLIER )
				result = 1;
            else if ( DSTCommonFunctions::CompareDates( pData2->fStopDate.c_str(), pData1->fStopDate.c_str() ) == DSTCommonFunctions::FIRST_EARLIER ) 
				result = -1;
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
            else if (*pFieldId == ifds::RiskLevel)
            {
                pDispInfo->item.pszText = (I_CHAR*)pData->fRiskLvl.c_str();
            }           
            else if (*pFieldId == ifds::CountryOfExposure)
            {
                pDispInfo->item.pszText = (I_CHAR*)pData->fCntryOfExpr.c_str();
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
// Public methods
//******************************************************************************

EntityMaintenanceDlg::EntityMaintenanceDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( EntityMaintenanceDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
, flg_add_new_item_mode( false )
, flg_ready_for_background_search( false )
, flg_tab_pressed( false )
, flg_shift_pressed( false )
, flg_joint_controls( false )
, flg_click_outside_ids_frame( true )
, m_bNewEntity(false)
,  m_bUpdateShareholder( false )

{
   m_hAccel = NULL;
}

//***************************************************************
//  Afx Data Exchange
//***************************************************************


void EntityMaintenanceDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   DDX_Check(pDX, IDC_CHK_UPDATE_SHAREHOLDER_TAX_JURIS, m_bUpdateShareholder);

   //{{AFX_DATA_MAP(EntityMaintenanceDlg)
   //}}AFX_DATA_MAP
}

//******************************************************************************

BEGIN_MESSAGE_MAP(EntityMaintenanceDlg, BaseMainDlg)
//{{AFX_MSG_MAP(EntityMaintenanceDlg)
ON_BN_CLICKED(IDC_BTN_ADM_DATES, OnBtnAdminDates)
ON_BN_CLICKED(IDC_BTN_WHERE_USED, OnBtnWhereUsed)
ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
ON_BN_CLICKED(IDC_BTN_ADD_ID, OnBtnAddId)
ON_BN_CLICKED(IDC_BTN_DELETE_ID, OnBtnDeleteId)
ON_EN_KILLFOCUS(IDC_EDT_ID_VALUE, OnKillfocusEdtIdValue)
ON_CBN_KILLFOCUS(IDC_CMB_ID_TYPE, OnKillfocusCmbIdType)
ON_CBN_KILLFOCUS(IDC_CMB_ID_VALUE, OnKillfocusCmbIdValue)
ON_CBN_KILLFOCUS(IDC_CMB_RISK_COUNTRY, OnKillfocusCmbRiskCntryOfExpr)
ON_CBN_KILLFOCUS(IDC_CMB_RISK_TYPE, OnKillfocusCmbRiskType)
ON_COMMAND(ID_ACCEL_ENTITY, OnAccelEntity)
ON_BN_CLICKED(IDC_BTN_ENTITY_DETAILS, OnBtnEntityDetails)
ON_BN_CLICKED(IDC_BTN_BEN_RELATION,OnBtnBenRelation)
ON_BN_CLICKED(IDC_BTN_ENTITY_HISTORY, OnBtnHistorical)
ON_BN_CLICKED(IDC_BTN_COPYENTITY, OnBtnCopyentity)
ON_BN_CLICKED(IDC_BTN_ENTITY_ADDRESS, OnBtnEntityAddress)
ON_MESSAGE( UM_OPENFUNDCLASSLISTDLG, OpenFundClassListDlg )
ON_BN_CLICKED( IDC_CHK_UPDATE_SHAREHOLDER_TAX_JURIS, OnChkUpdateShareholder )
ON_BN_CLICKED( IDC_BTN_DEATH_DOC, OnBtnDeathClaim )
ON_BN_CLICKED( IDC_BTN_KYC, OnBtnKYC )
ON_BN_CLICKED( IDC_BTN_TAX_JURIS_HISTORY, OnBtnTaxJurisHistory)
ON_BN_CLICKED( IDC_BTN_GRANT, OnBtnGrant )
ON_BN_CLICKED( IDC_BTN_ENT_REG_DETAIL, OnBtnEntRegDetail)
ON_BN_CLICKED(IDC_BTN_ADD_RISK, OnBtnAddRisk)
ON_BN_CLICKED(IDC_BTN_DELETE_RISK, OnBtnDelRisk)
ON_BN_CLICKED(IDC_BTN_SET_RISK_LEVEL, OnBtnSetRiskLevel)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************
// Message handlers
//******************************************************************************

//******************************************************************************
// Protected methods
//******************************************************************************

BOOL EntityMaintenanceDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, I_("OnInitDialog") );

   MgmtCoOptions *pMgmtCoOptions = NULL; 
   DString dstrLastNameFormat (NULL_STRING);
   DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());

   if (dstWorkSession->getMgmtCo().getMgmtCoOptions (pMgmtCoOptions) <= WARNING && pMgmtCoOptions)
   {
      pMgmtCoOptions->getField (ifds::LastNameFormat, dstrLastNameFormat, BF::HOST, false); 
	  dstrLastNameFormat.upperCase();
      m_bPaternalMaternal = (dstrLastNameFormat == I_("DOUBLE")) ? true : false;
   }

   BaseMainDlg::OnInitDialog();

   bool bIsRES2Client = 
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->isRES2Client();

   if( !m_hAccel )
      m_hAccel = LoadAccelerators( NULL, MAKEINTRESOURCE( IDR_ACCEL_VERIFYSEARCH ) );

   AddListControl( CLASSNAME, 
                   IDC_LV_ENTITIES, 
                   LV_ENTITY_LIST, 
                   ifds::EntityListViewHeading, 
                   IFASTBP_PROC::ENTITY_LIST);
   AddListControl( CLASSNAME, 
                   IDC_LV_ENTITY_IDS, 
                   LV_ENTITY_IDS_LIST, 
                   ifds::EntityIDSHeadingSet, 
                   IFASTBP_PROC::ENTITY_IDS_LIST, 
                   IDC_LV_ENTITIES);

   GetDlgItem( IDC_CMB_SALUTATION )->ShowWindow (m_bSalutationFreeFormat ? SW_HIDE : SW_SHOW);
   GetDlgItem( IDC_EDT_SALUTATION )->ShowWindow (m_bSalutationFreeFormat ? SW_SHOW : SW_HIDE);
   if (m_bSalutationFreeFormat)
   {
      AddControl( CTRL_EDIT,  IDC_EDT_SALUTATION,              IFASTBP_PROC::ENTITY_LIST, ifds::Salutation, 0, (UINT)IDC_LV_ENTITIES );
   }
   else 
   {
      AddControl( CTRL_COMBO,    IDC_CMB_SALUTATION,              IFASTBP_PROC::ENTITY_LIST, ifds::Salutation,            CTRLFLAG_INITCOMBO_BY_SUB_LIST | CTRLFLAG_INITCOMBO_WITH_BLANK, (UINT)IDC_LV_ENTITIES );
   }

   AddControl( CTRL_COMBO,    IDC_CMB_GENDER,                  IFASTBP_PROC::ENTITY_LIST, ifds::Gender,                CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITIES );

   AddControl( CTRL_COMBO,    IDC_CMB_NATIONALITY,             IFASTBP_PROC::ENTITY_LIST, ifds::Nationality ,          CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_COMBO,    IDC_CMB_LANGUAGE,                IFASTBP_PROC::ENTITY_LIST, ifds::LanguageCode,          CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_COMBO,    IDC_CMB_ENTITY_TYPE,             IFASTBP_PROC::ENTITY_LIST, ifds::EntityType,            CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITIES );
//Beneficiary
   AddControl( CTRL_COMBO,    IDC_CMB_RELATION,                IFASTBP_PROC::ENTITY_LIST, ifds::RelateCode,            CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_COMBO,    IDC_CMB_IRREVOCABLE,             IFASTBP_PROC::ENTITY_LIST, ifds::Irrevocable,  CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_EDIT,     IDC_EDT_PRC_BENEFIT,             IFASTBP_PROC::ENTITY_LIST, ifds::BenPercentage,         0,                              (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_STATIC,   IDC_TXT_AVAILABLE,               CTRLFLAG_GUI_FIELD );

//Escrow

   DString strMarket = DSTCommonFunctions::getMarket();
   if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
   {
      AddControl( CTRL_COMBO,    IDC_CMB_TAX_JURISDICTION,        IFASTBP_PROC::ENTITY_LIST, ifds::CountryName,            CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITIES );

      AddControl( CTRL_EDIT,     IDC_EDT_FUND_NUMBER,             IFASTBP_PROC::ENTITY_LIST, ifds::FrFundNumber,           0,                              (UINT)IDC_LV_ENTITIES );
      AddControl( CTRL_EDIT,     IDC_EDT_FUND_CODE,               IFASTBP_PROC::ENTITY_LIST, ifds::EscrowFund,             0,                              (UINT)IDC_LV_ENTITIES );
      AddControl( CTRL_EDIT,     IDC_EDT_CLASS_CODE,              IFASTBP_PROC::ENTITY_LIST, ifds::EscrowClass,            0,                              (UINT)IDC_LV_ENTITIES );
      AddControl( CTRL_EDIT,     IDC_EDT_AMOUNT_ASSIGN,           IFASTBP_PROC::ENTITY_LIST, ifds::AmtAssigned,            0,                              (UINT)IDC_LV_ENTITIES );
      AddControl( CTRL_COMBO,    IDC_CMB_AMOUNT_TYPE,             IFASTBP_PROC::ENTITY_LIST, ifds::AmountType,             CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITIES );   
      AddControl( CTRL_COMBO,    IDC_CMB_ESC_REASON,              IFASTBP_PROC::ENTITY_LIST, ifds::ReasonCode,             CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITIES );
      AddControl( CTRL_DATE,     IDC_DTP_ESC_EFFECTIVE,           IFASTBP_PROC::ENTITY_LIST, ifds::EscrowDeff,             CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITIES );
      AddControl( CTRL_DATE,     IDC_DTP_ESC_STOP,                IFASTBP_PROC::ENTITY_LIST, ifds::EscrowStopDate,         CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITIES );
      AddControl( CTRL_COMBO,    IDC_CMB_OCUPATION,               IFASTBP_PROC::ENTITY_LIST, ifds::OccupationCode,         CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITIES );
      AddControl( CTRL_EDIT,     IDC_EDT_OCCUPATION,              IFASTBP_PROC::ENTITY_LIST, ifds::OtherOccupation,        0,                              (UINT)IDC_LV_ENTITIES );
      //IN2780013 - SOC Loan Number and Loan Type
      AddControl( CTRL_COMBO,    IDC_CMB_LOAN_TYPE,              IFASTBP_PROC::ENTITY_LIST, ifds::LoanType,                CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITIES );
      AddControl( CTRL_EDIT,     IDC_EDT_LOAN_NUMBER,           IFASTBP_PROC::ENTITY_LIST, ifds::LoanNumber,			  0,                              (UINT)IDC_LV_ENTITIES );
   }
   //Joint Information
   AddControl( CTRL_COMBO,    IDC_CMB_DISPOSITION,             IFASTBP_PROC::ENTITY_LIST, ifds::DepositionCode,        CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_COMBO,    IDC_CMB_JOINT_TYPE,              IFASTBP_PROC::ENTITY_LIST, ifds::JointType,             CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITIES );
//RESP Beneficiary
   if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
   {
      AddControl( CTRL_COMBO,    IDC_CMB_RESP_TAX_JURISD,      IFASTBP_PROC::ENTITY_LIST, ifds::CountryCode,            CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITIES );
      AddControl( CTRL_STATIC,   IDC_EDT_LETTER_DATE,          IFASTBP_PROC::ENTITY_LIST, ifds::LetterDate,             0,                              (UINT)IDC_LV_ENTITIES);
      AddControl( CTRL_STATIC,   IDC_EDT_PRINTED,              IFASTBP_PROC::ENTITY_LIST, ifds::LetterReq,              0,                              (UINT)IDC_LV_ENTITIES);
      AddControl( CTRL_COMBO,    IDC_CMB_REASON,               IFASTBP_PROC::ENTITY_LIST, ifds::RESPReasonCode,         CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITIES );  
   }

   AddControl( CTRL_COMBO,    IDC_CMB_AUTHORIZED_TO_TRADE,     IFASTBP_PROC::ENTITY_LIST, ifds::AuthorizedToTrade,     CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITIES );  
   AddControl( CTRL_EDIT,     IDC_EDT_NAME,                    IFASTBP_PROC::ENTITY_LIST, ifds::LastName,              0,                              (UINT)IDC_LV_ENTITIES );

   AddControl( CTRL_EDIT,     IDC_EDT_LAST_NAME,               IFASTBP_PROC::ENTITY_LIST, ifds::LastName,              0,                              (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_EDIT,     IDC_EDT_FIRST_NAME,              IFASTBP_PROC::ENTITY_LIST, ifds::FirstName,             0,                              (UINT)IDC_LV_ENTITIES );

   if (m_bPaternalMaternal) 
   {
	   AddControl( CTRL_EDIT,     IDC_EDT_FIRST_NAME_DOUBLE, IFASTBP_PROC::ENTITY_LIST, ifds::FirstName,				0,                              (UINT)IDC_LV_ENTITIES );
	   AddControl( CTRL_EDIT,     IDC_EDT_PATERNAL_NAME,	IFASTBP_PROC::ENTITY_LIST, ifds::PaternalLastName,			0,                              (UINT)IDC_LV_ENTITIES );
	   AddControl( CTRL_EDIT,     IDC_EDT_MATERNAL_NAME,	IFASTBP_PROC::ENTITY_LIST, ifds::MaternalLastName,			0,                              (UINT)IDC_LV_ENTITIES );
   }

   AddControl( CTRL_EDIT,     IDC_EDT_HOME_TEL,                IFASTBP_PROC::ENTITY_LIST, ifds::HomePhone,             0,                              (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_EDIT,     IDC_EDT_BUSINESS_TEL,            IFASTBP_PROC::ENTITY_LIST, ifds::BusinessPhone,         0,                              (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_EDIT,     IDC_EDT_BUSINESS_EXT,            IFASTBP_PROC::ENTITY_LIST, ifds::BusinessExt,           0,                              (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_EDIT,     IDC_EDT_HOME_FAX,                IFASTBP_PROC::ENTITY_LIST, ifds::HomeFax,               0,                              (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_EDIT,     IDC_EDT_BUSINESS_FAX,            IFASTBP_PROC::ENTITY_LIST, ifds::BusinessFax,           0,                              (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_EDIT,     IDC_EDT_EMAIL,                   IFASTBP_PROC::ENTITY_LIST, ifds::Email,                 0,                              (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_EDIT,     IDC_EDT_TELEX,                   IFASTBP_PROC::ENTITY_LIST, ifds::Telex,                 0,                              (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_EDIT,     IDC_EDT_EMAIL2,                  IFASTBP_PROC::ENTITY_LIST, ifds::Email2,                0,                              (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_EDIT,     IDC_EDT_SECOND_PHONENUM,         IFASTBP_PROC::ENTITY_LIST, ifds::SecondPhoneNum,        0,                              (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_EDIT,     IDC_EDT_SECOND_PHONENUM_EXT,     IFASTBP_PROC::ENTITY_LIST, ifds::SecondPhoneNumExt,     0,                              (UINT)IDC_LV_ENTITIES );
   dynamic_cast< DSTEdit * >( GetControl( IDC_EDT_TELEX ) )->SetMaxCharNum( 13 );

   if( strMarket == MARKET_IDS::CANADA )
   {
      AddControl( CTRL_EDIT,     IDC_EDT_HOME_TEL_AREA,           IFASTBP_PROC::ENTITY_LIST, ifds::HomePhoneArea,         0,                              (UINT)IDC_LV_ENTITIES );
      AddControl( CTRL_EDIT,     IDC_EDT_BUSINESS_TEL_AREA,       IFASTBP_PROC::ENTITY_LIST, ifds::BusinessPhoneArea,     0,                              (UINT)IDC_LV_ENTITIES );
      AddControl( CTRL_EDIT,     IDC_EDT_HOME_FAX_AREA,           IFASTBP_PROC::ENTITY_LIST, ifds::HomeFaxArea,           0,                              (UINT)IDC_LV_ENTITIES );
      AddControl( CTRL_EDIT,     IDC_EDT_BUSINESS_FAX_AREA,       IFASTBP_PROC::ENTITY_LIST, ifds::BusFaxArea,            0,                              (UINT)IDC_LV_ENTITIES );
      AddControl( CTRL_COMBO,    IDC_CMB_SPOUSAL,                 IFASTBP_PROC::ENTITY_LIST, ifds::OwnerSpouseName,       CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITIES );
   }


   AddControl( CTRL_EDIT,     IDC_EDT_CONTACT_NAME,            IFASTBP_PROC::ENTITY_LIST, ifds::ContactName,           0,                              (UINT)IDC_LV_ENTITIES );

   AddControl( CTRL_COMBO,    IDC_CMB_EMPLOYEECLASS,           IFASTBP_PROC::ENTITY_LIST, ifds::EmployeeClass,         CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITIES );

   AddControl( CTRL_DATE,     IDC_DTP_BIRTH_DATE,              IFASTBP_PROC::ENTITY_LIST, ifds::DofBirth,              0,                              (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_DATE,     IDC_DTP_EFFECTIVE_DATE,          IFASTBP_PROC::ENTITY_LIST, ifds::EffectiveDate,         0,                              (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_DATE,     IDC_DTP_DEATH_DATE,              IFASTBP_PROC::ENTITY_LIST, ifds::DofDeath,              0,                              (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_DATE,     IDC_DTP_DEATHNOTIFDATE,          IFASTBP_PROC::ENTITY_LIST, ifds::DofDeathNotice,        0,                              (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_EDIT,     IDC_EDT_BIRTH_PLACE,             IFASTBP_PROC::ENTITY_LIST, ifds::BirthPlace,            0,                              (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_COMBO,    IDC_CMB_COUNTRY_OF_BIRTH,        IFASTBP_PROC::ENTITY_LIST, ifds::CountryOfBirth,        CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITIES );

   AddControl( CTRL_COMBO,     IDC_CMB_EUSD_OPTION,            IFASTBP_PROC::ENTITY_LIST, ifds::EUSDTaxOption,         CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_DATE,      IDC_DTP_TAX_JURIS_EFFECTIVE,    IFASTBP_PROC::ENTITY_LIST, ifds::TaxJurisDeff,          0,                              (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_COMBO,     IDC_EDT_TAX_JURIS,              IFASTBP_PROC::ENTITY_LIST, ifds::TaxJuris,              CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITIES );
   //AddControl( CTRL_COMBO,     IDC_CMB_FATCA_FFID,             IFASTBP_PROC::ENTITY_LIST, ifds::FATCAFFI,              CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_COMBO,     IDC_CMB_ASSOCIATED_ENTITY,      IFASTBP_PROC::ENTITY_LIST, ifds::AssocEntityId,         CTRLFLAG_INITCOMBO_BY_SUB_LIST|CTRLFLAG_INITCOMBO_WITH_BLANK, (UINT)IDC_LV_ENTITIES );
   AddControl( CTRL_COMBO,     IDC_CMB_ENTITY_ASSOCIATION,     IFASTBP_PROC::ENTITY_LIST, ifds::EntityAssociation,     CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITIES );
   
   if( strMarket == MARKET_IDS::CANADA )
   {
	   AddControl( CTRL_COMBO,     IDC_CMB_RDSP_RELN_TO_BENE,      IFASTBP_PROC::ENTITY_LIST, ifds::RDSPRelntoBene,		   CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITIES );
	   AddControl( CTRL_COMBO,     IDC_CMB_RDSP_CONSENT,		   IFASTBP_PROC::ENTITY_LIST, ifds::RDSPConsent,		   CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITIES );
	   AddControl( CTRL_DATE,      IDC_DTP_RDSP_CONSENT_DATE,      IFASTBP_PROC::ENTITY_LIST, ifds::RDSPConsentDeff,	   CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITY_IDS );
   }

   AddControl( CTRL_EDIT,      IDC_EDT_PERCENT_OWNERSHIP,      IFASTBP_PROC::ENTITY_LIST, ifds::PercentOwner,          0,                              (UINT)IDC_LV_ENTITIES );

   // id related fields
   AddControl( CTRL_COMBO,    IDC_CMB_ID_TYPE,                 IFASTBP_PROC::ENTITY_IDS_LIST, ifds::IdType,            CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITY_IDS );
   // original
   //AddControl( CTRL_EDIT,     IDC_EDT_ID_VALUE,                IFASTBP_PROC::ENTITY_IDS_LIST, ifds::IdValue,           0,                              (UINT)IDC_LV_ENTITY_IDS );

   //MT535/MT536
   //AddControl( CTRL_EDIT,     IDC_EDT_ID_VALUE,                IFASTBP_PROC::ENTITY_IDS_LIST, ifds::IdValue,           0,                               ID_VALUE_CONTROLS::EDTBOX_ENTITY_ID);
   //AddControl( CTRL_COMBO,    IDC_CMB_ID_VALUE,                IFASTBP_PROC::ENTITY_IDS_LIST, ifds::IdValue,           CTRLFLAG_INITCOMBO_BY_SUB_LIST,  ID_VALUE_CONTROLS::CMBBOX_CLEARING_ID);
   AddControl( CTRL_EDIT,     IDC_EDT_ID_VALUE,                IFASTBP_PROC::ENTITY_IDS_LIST, ifds::IdValue,           0,                              ENTITY_IDS_CONTROLS::EDIT_CNTRL  );
   AddControl( CTRL_COMBO,    IDC_CMB_ID_VALUE,                IFASTBP_PROC::ENTITY_IDS_LIST, ifds::IdValue,           CTRLFLAG_INITCOMBO_BY_SUB_LIST, ENTITY_IDS_CONTROLS::COMBO_CNTRL );
   AddControl( CTRL_DATE,     IDC_DTP_ID_DATE,                 IFASTBP_PROC::ENTITY_IDS_LIST, ifds::IdDate,            CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITY_IDS );
   AddControl( CTRL_COMBO,    IDC_ID_STATUS,                   IFASTBP_PROC::ENTITY_IDS_LIST, ifds::IdStatus,          CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITY_IDS );
   AddControl( CTRL_DATE,     IDC_DTP_ID_DATE_EXPIRE,          IFASTBP_PROC::ENTITY_IDS_LIST, ifds::IdExpireDate,      CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITY_IDS );
   AddControl( CTRL_COMBO,    IDC_CMB_COUNTRY_OF_ISSUE,        IFASTBP_PROC::ENTITY_IDS_LIST, ifds::CountryOfIssue,    CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITY_IDS );
   AddControl( CTRL_STATIC,   IDC_BTN_DELETE,                                                           CTRLFLAG_GUI_FIELD                                        );
   AddControl( CTRL_STATIC,   IDC_BTN_DELETE_ID,                                                        CTRLFLAG_GUI_FIELD                                        );
   AddControl( CTRL_STATIC,   IDC_BTN_ADD,                                                              CTRLFLAG_GUI_FIELD                                        );
   AddControl( CTRL_STATIC,   IDC_BTN_ADD_ID,                                                           CTRLFLAG_GUI_FIELD                                        );
   AddControl( CTRL_STATIC,   IDC_BTN_SEARCH,                                                           CTRLFLAG_GUI_FIELD                                        );
   AddControl( CTRL_STATIC,   IDC_BTN_RESET,                                                            CTRLFLAG_GUI_FIELD                                        );
   AddControl( CTRL_STATIC,   IDC_BTN_ENTITY_ADDRESS,                                                   CTRLFLAG_GUI_FIELD                                        ); 
   AddControl( CTRL_STATIC,   IDC_FRM_BENEFICIARY,                                                      CTRLFLAG_GUI_FIELD                                        );
   AddControl( CTRL_STATIC,   IDC_TXT_RELATIONSHIP_TO_OWNER,                                            CTRLFLAG_GUI_FIELD                                        );
   AddControl( CTRL_STATIC,   IDC_TXT_IRREVOCABLE,                                                      CTRLFLAG_GUI_FIELD                                        );
   AddControl( CTRL_STATIC,   IDC_TXT_PERCENT_OF_BENEFIT,                                               CTRLFLAG_GUI_FIELD                                        );
   AddControl( CTRL_STATIC,   IDC_TXT_AVAILABLE_PERCENT,                                                CTRLFLAG_GUI_FIELD                                        );
   AddControl( CTRL_STATIC,   IDOK,                                                                     CTRLFLAG_GUI_FIELD                                        );

   if( strMarket == MARKET_IDS::JAPAN )
   {
      AddControl( CTRL_EDIT,     IDC_EDT_BIRTH_LAST_NAME,         IFASTBP_PROC::ENTITY_LIST, ifds::BirthLastName,         0,                              (UINT)IDC_LV_ENTITIES );
      AddControl( CTRL_EDIT,     IDC_EDT_BIRTH_FIRST_NAME,        IFASTBP_PROC::ENTITY_LIST, ifds::BirthFirstName,        0,                              (UINT)IDC_LV_ENTITIES );
      AddControl( CTRL_STATIC,   IDC_BTN_ADM_DATES,                                                        CTRLFLAG_GUI_FIELD                                        );
      AddControl( CTRL_STATIC,   IDC_BTN_ENTITY_DETAILS,                                                   CTRLFLAG_GUI_FIELD                                        );

      //Kanji & Kana converting
      DSTEdit* pKanjiEdit = dynamic_cast<DSTEdit*>(GetDlgItem(IDC_EDT_LAST_NAME));
      DSTEdit* pKanaEdit  = dynamic_cast<DSTEdit*>(GetDlgItem(IDC_EDT_BIRTH_LAST_NAME));
      pKanjiEdit->SetKanaEdit(pKanaEdit);

      pKanjiEdit = dynamic_cast<DSTEdit*>(GetDlgItem(IDC_EDT_FIRST_NAME));
      pKanaEdit  = dynamic_cast<DSTEdit*>(GetDlgItem(IDC_EDT_BIRTH_FIRST_NAME));
      pKanjiEdit->SetKanaEdit(pKanaEdit);
   }
   else if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
   {
      AddControl( CTRL_STATIC, IDC_TXT_AGE, BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_GUI_FIELD, IDC_LV_ENTITIES );
      //ConnectControlToData( IDC_EDT_AMOUNT_ASSIGN, true );
   }

   // Tab enhancement
   AddControl (CTRL_STATIC, IDC_STATIC_SALUTATION, CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_CATEGORY, CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_LAST_NAME, CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_FIRST_NAME, CTRLFLAG_GUI_FIELD);

   if (m_bPaternalMaternal) 
   {
	   AddControl (CTRL_STATIC, IDC_STC_PATERNAL_NAME, CTRLFLAG_GUI_FIELD);
	   AddControl (CTRL_STATIC, IDC_STC_MATERNAL_NAME, CTRLFLAG_GUI_FIELD);
   }

   AddControl (CTRL_STATIC, IDC_STC_NAME, CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_BIRTH_DATE, CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_BIRTH_PLACE, CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_BIRTH_COUNTRY, CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_GENDER, CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_AGE, CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_NATIONALITY, CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_TXT_LANGUAGE, CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_OCCUPATION, CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_RISK_LEVEL, CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_COMBO,  IDC_CMB_RISK_LEVEL,  IFASTBP_PROC::ENTITY_LIST, ifds::RiskLevel, CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITIES );
   AddControl (CTRL_STATIC, IDC_STC_HOME_TEL, CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_BUSINESS_TEL, CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_BUSINESS_EXT, CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_HOME_FAX, CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_BUSINESS_FAX, CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_EMAIL, CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_CONTACT_NAME, CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_TELEX, CTRLFLAG_GUI_FIELD);   
   AddControl (CTRL_STATIC, IDC_STC_DATE_EFFECTIVE, CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_DATE_DEATH_NOTIF, CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_DATE_DEATH, CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_EMAIL2, CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_SECOND_PHONENUM, CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_STC_SECOND_PHONENUM_EXT, CTRLFLAG_GUI_FIELD);

   //Risk Tab
   IFDSListCtrl* ifdsListControlRiskDetails = 
       new IFDSAdaptedListCtrl< LVRiskDetailsAdapter >( this, 
       CLASSNAME, 
       IDC_LV_RISKS, 
       IDC_LV_ENTITIES,
       0, 
       true, 
       true);

   AddIFDSListControl(ifdsListControlRiskDetails, 
       I_("RISK_LIST"), 
       IFASTBP_PROC::RISK_LIST, 
       ifds::RiskHeading);

   AddControl(CTRL_STATIC, IDC_STC_HIGHEST_RISL_LVL, CTRLFLAG_GUI_FIELD);
   AddControl(CTRL_STATIC, IDC_STC_RISK_EXPOSURE, CTRLFLAG_GUI_FIELD);
   AddControl(CTRL_STATIC, IDC_STC_RISK_TYPE, CTRLFLAG_GUI_FIELD);
   AddControl(CTRL_STATIC, IDC_STC_RISK_COUNTRY, CTRLFLAG_GUI_FIELD);
   AddControl(CTRL_STATIC, IDC_STC_RISK_DEFF, CTRLFLAG_GUI_FIELD);

   AddControl(CTRL_EDIT, IDC_EDT_HIGHEST_RISK_LVL, IFASTBP_PROC::ENTITY_LIST, ifds::RiskLevel, CTRLFLAG_NOT_UPDATABLE, (UINT)IDC_LV_ENTITIES);
   AddControl(CTRL_EDIT, IDC_EDT_HIGHEST_RISK_EXPOSURE, IFASTBP_PROC::ENTITY_LIST, ifds::CountryOfExposure, CTRLFLAG_NOT_UPDATABLE, (UINT)IDC_LV_ENTITIES);

   AddControl(CTRL_COMBO, IDC_CMB_RISK_TYPE, IFASTBP_PROC::RISK_LIST, ifds::RiskLevel, CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_RISKS);
   AddControl(CTRL_COMBO, IDC_CMB_RISK_COUNTRY, IFASTBP_PROC::RISK_LIST, ifds::CountryOfExposure, CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_RISKS);
   AddControl(CTRL_DATE, IDC_DTP_RISK_DEFF, IFASTBP_PROC::RISK_LIST, ifds::EffectiveDate, CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_RISKS);

// Tax Juris
   AddControl (CTRL_STATIC,IDC_STC_TAX_JURIS, CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC,IDC_STC_TAX_JURIS_EFFECTIVE,  CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC,IDC_STC_EUSD_OPTION, CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC,IDC_CHK_UPDATE_SHAREHOLDER_TAX_JURIS, CTRLFLAG_GUI_FIELD);
   //AddControl (CTRL_STATIC,IDC_STC_FATCA_FFID, CTRLFLAG_GUI_FIELD);
   AddControl (CTRL_STATIC, IDC_BTN_TAX_JURIS_HISTORY, CTRLFLAG_GUI_FIELD );
   //RESP2 Client
   //if ( bIsRES2Client && strMarket == MARKET_IDS::CANADA )
   if (strMarket == MARKET_IDS::CANADA)
   {
      AddControl (CTRL_STATIC, IDC_STC_RESP2_RELATION_TO_OWNER, CTRLFLAG_GUI_FIELD);
      AddControl (CTRL_COMBO,  IDC_CMB_RESP2_RELATION_TO_OWNER, IFASTBP_PROC::ENTITY_LIST, ifds::HRDCRelateCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST, RESP2_CONTROLS::BENEF_INFO );
      AddControl (CTRL_STATIC, IDC_STC_RESP2_LETTER_DATE, CTRLFLAG_GUI_FIELD);
      AddControl (CTRL_DATE,   IDC_DTP_RESP2_LETTER_DATE, IFASTBP_PROC::ENTITY_LIST, ifds::LetterDate, 0, (UINT)IDC_LV_ENTITIES );
      AddControl (CTRL_STATIC, IDC_STC_RESP2_REASON, CTRLFLAG_GUI_FIELD);
      AddControl (CTRL_COMBO,  IDC_CMB_RESP2_REASON, IFASTBP_PROC::ENTITY_LIST, ifds::RESPReasonCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST, RESP2_CONTROLS::BENEF_INFO );
      AddControl (CTRL_STATIC, IDC_STC_RESP2_TAX_JUR, CTRLFLAG_GUI_FIELD);
      AddControl (CTRL_COMBO,  IDC_CMB_RESP2_TAX_JUR, IFASTBP_PROC::ENTITY_LIST, ifds::CountryCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST, RESP2_CONTROLS::BENEF_INFO );
      AddControl (CTRL_STATIC, IDC_STC_RESP2_PRINTED, CTRLFLAG_GUI_FIELD);
      AddControl (CTRL_COMBO,  IDC_CMB_RESP2_PRINTED, IFASTBP_PROC::ENTITY_LIST, ifds::LetterReq, CTRLFLAG_INITCOMBO_BY_SUB_LIST, RESP2_CONTROLS::BENEF_INFO );
      AddControl (CTRL_STATIC, IDC_STC_RESP2_ALLOCATION_PRCNT, CTRLFLAG_GUI_FIELD);
      //AddControl (CTRL_EDIT,   IDC_EDT_RESP2_ALLOCATION_PRCNT, IFASTBP_PROC::ENTITY_LIST, ifds::AllocationPercent, 0, RESP2_CONTROLS::BENEF_INFO );
      AddControl (CTRL_EDIT,   IDC_EDT_RESP2_ALLOCATION_PRCNT, IFASTBP_PROC::ENTITY_LIST, ifds::BenPercentage, 0, RESP2_CONTROLS::BENEF_INFO );
      AddControl (CTRL_STATIC, IDC_STC_RESP2_REQUEST_GRANT, CTRLFLAG_GUI_FIELD);
      AddControl (CTRL_COMBO,  IDC_CMB_RESP2_REQUEST_GRANT, IFASTBP_PROC::ENTITY_LIST, ifds::GrantRequest, CTRLFLAG_INITCOMBO_BY_SUB_LIST, RESP2_CONTROLS::BENEF_INFO );
      AddControl (CTRL_STATIC, IDC_STC_RESP2_TAINTED, CTRLFLAG_GUI_FIELD);
      AddControl (CTRL_COMBO,  IDC_CMB_RESP2_TAINTED, IFASTBP_PROC::ENTITY_LIST, ifds::Tainted, CTRLFLAG_INITCOMBO_BY_SUB_LIST, RESP2_CONTROLS::BENEF_INFO );
      AddControl (CTRL_STATIC, IDC_STC_RESP2_TAINTED_END_DATE, CTRLFLAG_GUI_FIELD);
      AddControl (CTRL_DATE,   IDC_DTP_RESP2_TAINTED_END_DATE, IFASTBP_PROC::ENTITY_LIST, ifds::TaintEndDate, 0, RESP2_CONTROLS::BENEF_INFO );
      AddControl (CTRL_STATIC, IDC_BTN_GRANT, CTRLFLAG_GUI_FIELD );
//hide the controls
      GetControl (IDC_STC_RESP2_RELATION_TO_OWNER)->Show (false);
      GetControl (IDC_CMB_RESP2_RELATION_TO_OWNER)->Show (false);
      GetControl (IDC_STC_RESP2_LETTER_DATE)->Show (false);
      GetControl (IDC_DTP_RESP2_LETTER_DATE)->Show (false);
      GetControl (IDC_STC_RESP2_REASON)->Show (false);
      GetControl (IDC_CMB_RESP2_REASON)->Show (false);
      GetControl (IDC_STC_RESP2_TAX_JUR)->Show (false);
      GetControl (IDC_CMB_RESP2_TAX_JUR)->Show (false);
      GetControl (IDC_STC_RESP2_PRINTED)->Show (false);
      GetControl (IDC_CMB_RESP2_PRINTED)->Show (false);
      GetControl (IDC_STC_RESP2_ALLOCATION_PRCNT)->Show (false);
      GetControl (IDC_EDT_RESP2_ALLOCATION_PRCNT)->Show (false);
      GetControl (IDC_STC_RESP2_REQUEST_GRANT)->Show (false);
      GetControl (IDC_CMB_RESP2_REQUEST_GRANT)->Show (false);
      GetControl (IDC_STC_RESP2_TAINTED)->Show (false);
      GetControl (IDC_CMB_RESP2_TAINTED)->Show (false);
      GetControl (IDC_STC_RESP2_TAINTED_END_DATE)->Show (false);
      GetControl (IDC_DTP_RESP2_TAINTED_END_DATE)->Show (false);
      GetControl (IDC_BTN_GRANT)->Show (false);
      GetControl (IDC_BTN_TAX_JURIS_HISTORY)->Show (false);

      AddControl (CTRL_COMBO,  IDC_CMB_RESP2_PARENT_LEGAL_GUARD, IFASTBP_PROC::ENTITY_LIST, ifds::RES2ParentLglList, CTRLFLAG_INITCOMBO_BY_SUB_LIST, RESP2_CONTROLS::RELATIONSHIPS );
      AddControl (CTRL_STATIC, IDC_STC_RESP2_PARENT_LEGAL_GUARD, CTRLFLAG_GUI_FIELD );
      AddControl (CTRL_COMBO,  IDC_CMB_RESP2_DESIGNATED_INST, IFASTBP_PROC::ENTITY_LIST, ifds::RES2DesInstList, CTRLFLAG_INITCOMBO_BY_SUB_LIST, RESP2_CONTROLS::RELATIONSHIPS );
      AddControl (CTRL_STATIC, IDC_STC_RESP2_DESIGNATED_INST, CTRLFLAG_GUI_FIELD );
      AddControl (CTRL_COMBO,  IDC_CMB_RESP2_PRIM_CARE_GIVER, IFASTBP_PROC::ENTITY_LIST, ifds::RES2PCGList, CTRLFLAG_INITCOMBO_BY_SUB_LIST, RESP2_CONTROLS::RELATIONSHIPS );
      AddControl (CTRL_STATIC, IDC_STC_RESP2_PRIM_CARE_GIVER, CTRLFLAG_GUI_FIELD );
      AddControl (CTRL_COMBO,  IDC_CMB_RESP2_GEN_RT511, IFASTBP_PROC::ENTITY_LIST, ifds::CreateRec511, CTRLFLAG_INITCOMBO_BY_SUB_LIST, RESP2_CONTROLS::RELATIONSHIPS );
      AddControl (CTRL_STATIC, IDC_STC_RESP2_GEN_RT511, CTRLFLAG_GUI_FIELD );
      AddControl (CTRL_DATE,   IDC_DTP_RESP2_CUT_OFF_DATE, IFASTBP_PROC::ENTITY_LIST, ifds::Rec511CutOffDate, 0, RESP2_CONTROLS::RELATIONSHIPS );
      AddControl (CTRL_STATIC, IDC_STC_RESP2_CUT_OFF_DATE, CTRLFLAG_GUI_FIELD );
//hide the controls
      GetControl (IDC_CMB_RESP2_PARENT_LEGAL_GUARD)->Show (false);
      GetControl (IDC_STC_RESP2_PARENT_LEGAL_GUARD)->Show (false);
      GetControl (IDC_CMB_RESP2_DESIGNATED_INST)->Show (false);
      GetControl (IDC_STC_RESP2_DESIGNATED_INST)->Show (false);
      GetControl (IDC_CMB_RESP2_PRIM_CARE_GIVER)->Show (false);
      GetControl (IDC_STC_RESP2_PRIM_CARE_GIVER)->Show (false);
      GetControl (IDC_CMB_RESP2_GEN_RT511)->Show (false);
      GetControl (IDC_STC_RESP2_GEN_RT511)->Show (false);
      GetControl (IDC_DTP_RESP2_CUT_OFF_DATE)->Show (false);
      GetControl (IDC_STC_RESP2_CUT_OFF_DATE)->Show (false);
   }

   AddControl (CTRL_STATIC, IDC_STC_DATE_DEATH_SETTLEMENT, CTRLFLAG_GUI_FIELD );
   AddControl (CTRL_DATE,   IDC_DTP_DEATH_DATE_SETTLEMENT, IFASTBP_PROC::ENTITY_LIST, ifds::DeathSettlementDate, 0, (UINT)IDC_LV_ENTITIES );

   AddControl (CTRL_STATIC, IDC_STC_COUNTRY_OF_EXPOSURE, CTRLFLAG_GUI_FIELD );
   AddControl( CTRL_COMBO, IDC_CMB_COUNTRY_OF_EXPOSURE,  IFASTBP_PROC::ENTITY_LIST, ifds::CountryOfExposure,CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITIES );

   if(strMarket == MARKET_IDS::LUXEMBOURG )
   {
      AddControl( CTRL_EDIT, IDC_EDT_REG_AGENT_ACCT_NO, IFASTBP_PROC::ENTITY_LIST, ifds::RefCode, 0, ENTITY_IDS_CONTROLS::EDIT_CNTRL  );
      AddControl( CTRL_COMBO, IDC_CMB_VERIFY_STATUS, IFASTBP_PROC::ENTITY_LIST, ifds::VerifyStat, CTRLFLAG_INITCOMBO_BY_SUB_LIST , (UINT)IDC_LV_ENTITIES);
	  AddControl( CTRL_COMBO, IDC_CMB_ID_VERIFY_STAT, IFASTBP_PROC::ENTITY_IDS_LIST, ifds::VerifyStat, CTRLFLAG_INITCOMBO_BY_SUB_LIST , (UINT)IDC_LV_ENTITY_IDS );
      AddControl( CTRL_COMBO, IDC_CMB_DETAILS_VERIFY_STAT, IFASTBP_PROC::ENTITY_LIST, ifds::VerifyStatDetails, CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LV_ENTITIES);
   }

   DString eusd;
   getParent()->getField(this, ifds::EUSDParticip,eusd,false);
   eusd.strip().upperCase();
   
   if (eusd == N)  // if it is not eusd environment,hide option
   {
      GetDlgItem (IDC_STC_EUSD_OPTION )->ShowWindow( SW_HIDE );
      GetDlgItem (IDC_CMB_EUSD_OPTION )->ShowWindow( SW_HIDE );
   }

   //tab control
   DSTTabCtrl* pTabCtrl = 
      AddTabControl(CLASSNAME, IDC_TAB_ENTITY_MAINTENANCE, I_("EntityMaintDetailsTab"));

   if (pTabCtrl)
   {
      pTabCtrl->SetMinTabWidth (200);
      pTabCtrl->AddTab (TXT_PAGE_DETAILS);
      pTabCtrl->AddTab (TXT_PAGE_CONTACTS);
      pTabCtrl->AddTab (TXT_PAGE_TAX);

      if (multipleRiskEnv())
      {
          pTabCtrl->AddTab (TXT_PAGE_RISKS);

          pTabCtrl->registerControl(IDC_STC_HIGHEST_RISL_LVL, TXT_PAGE_RISKS);
          pTabCtrl->registerControl(IDC_STC_RISK_EXPOSURE, TXT_PAGE_RISKS);
          pTabCtrl->registerControl(IDC_STC_RISK_TYPE, TXT_PAGE_RISKS);
          pTabCtrl->registerControl(IDC_STC_RISK_COUNTRY, TXT_PAGE_RISKS);
          pTabCtrl->registerControl(IDC_STC_RISK_DEFF, TXT_PAGE_RISKS);
          pTabCtrl->registerControl(IDC_EDT_HIGHEST_RISK_LVL, TXT_PAGE_RISKS);
          pTabCtrl->registerControl(IDC_EDT_HIGHEST_RISK_EXPOSURE, TXT_PAGE_RISKS);
          pTabCtrl->registerControl(IDC_CMB_RISK_TYPE, TXT_PAGE_RISKS);
          pTabCtrl->registerControl(IDC_CMB_RISK_COUNTRY, TXT_PAGE_RISKS);
          pTabCtrl->registerControl(IDC_DTP_RISK_DEFF, TXT_PAGE_RISKS);
      }

      // Details
      pTabCtrl->registerControl (IDC_STC_CATEGORY, TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_CMB_EMPLOYEECLASS, TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_STATIC_SALUTATION, TXT_PAGE_DETAILS);
      if (m_bSalutationFreeFormat)
      {
         pTabCtrl->registerControl (IDC_EDT_SALUTATION, TXT_PAGE_DETAILS);
      }
      else
      {
         pTabCtrl->registerControl (IDC_CMB_SALUTATION, TXT_PAGE_DETAILS);
      }
      pTabCtrl->registerControl (IDC_STC_LAST_NAME, TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_EDT_LAST_NAME, TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_STC_FIRST_NAME, TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_EDT_FIRST_NAME, TXT_PAGE_DETAILS);

	  if (m_bPaternalMaternal) {
		  pTabCtrl->registerControl (IDC_STC_PATERNAL_NAME, TXT_PAGE_DETAILS);
		  pTabCtrl->registerControl (IDC_EDT_PATERNAL_NAME, TXT_PAGE_DETAILS);
		  pTabCtrl->registerControl (IDC_STC_MATERNAL_NAME, TXT_PAGE_DETAILS);
		  pTabCtrl->registerControl (IDC_EDT_MATERNAL_NAME, TXT_PAGE_DETAILS);
	  }

      pTabCtrl->registerControl (IDC_STC_NAME, TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_EDT_NAME, TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_STC_BIRTH_DATE, TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_DTP_BIRTH_DATE, TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_STC_BIRTH_PLACE, TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_EDT_BIRTH_PLACE, TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_STC_BIRTH_COUNTRY, TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_CMB_COUNTRY_OF_BIRTH, TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_STC_GENDER, TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_CMB_GENDER, TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_STC_AGE, TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_TXT_AGE, TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_STC_NATIONALITY, TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_CMB_NATIONALITY, TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_TXT_LANGUAGE, TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_CMB_LANGUAGE, TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_STC_OCCUPATION, TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_CMB_OCUPATION, TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_EDT_OCCUPATION, TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_STC_RISK_LEVEL, TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_CMB_RISK_LEVEL, TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_STC_DATE_EFFECTIVE, TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_STC_DATE_DEATH_NOTIF, TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_STC_DATE_DEATH, TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_DTP_EFFECTIVE_DATE, TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_DTP_DEATHNOTIFDATE, TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_DTP_DEATH_DATE, TXT_PAGE_DETAILS);      
      pTabCtrl->registerControl (IDC_STC_DATE_DEATH_SETTLEMENT, TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_DTP_DEATH_DATE_SETTLEMENT, TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_STC_COUNTRY_OF_EXPOSURE, TXT_PAGE_DETAILS);
      pTabCtrl->registerControl (IDC_CMB_COUNTRY_OF_EXPOSURE, TXT_PAGE_DETAILS);

      // Contacts
      pTabCtrl->registerControl (IDC_STC_HOME_TEL, TXT_PAGE_CONTACTS);
      pTabCtrl->registerControl (IDC_EDT_HOME_TEL, TXT_PAGE_CONTACTS);
      pTabCtrl->registerControl (IDC_STC_EMAIL2, TXT_PAGE_CONTACTS);
      pTabCtrl->registerControl (IDC_EDT_EMAIL2, TXT_PAGE_CONTACTS);
      pTabCtrl->registerControl (IDC_STC_SECOND_PHONENUM, TXT_PAGE_CONTACTS);
      pTabCtrl->registerControl (IDC_EDT_SECOND_PHONENUM, TXT_PAGE_CONTACTS);
      pTabCtrl->registerControl (IDC_STC_SECOND_PHONENUM_EXT, TXT_PAGE_CONTACTS);
      pTabCtrl->registerControl (IDC_EDT_SECOND_PHONENUM_EXT, TXT_PAGE_CONTACTS);
      if (strMarket == MARKET_IDS::CANADA)
      {
         pTabCtrl->registerControl (IDC_EDT_HOME_TEL_AREA, TXT_PAGE_CONTACTS);
         pTabCtrl->registerControl (IDC_EDT_BUSINESS_TEL_AREA, TXT_PAGE_CONTACTS);
         pTabCtrl->registerControl (IDC_EDT_HOME_FAX_AREA, TXT_PAGE_CONTACTS);
         pTabCtrl->registerControl (IDC_EDT_BUSINESS_FAX_AREA, TXT_PAGE_CONTACTS);
      }
      pTabCtrl->registerControl (IDC_STC_BUSINESS_TEL, TXT_PAGE_CONTACTS);
      pTabCtrl->registerControl (IDC_EDT_BUSINESS_TEL, TXT_PAGE_CONTACTS);
      pTabCtrl->registerControl (IDC_STC_BUSINESS_EXT, TXT_PAGE_CONTACTS);
      pTabCtrl->registerControl (IDC_EDT_BUSINESS_EXT, TXT_PAGE_CONTACTS);
      pTabCtrl->registerControl (IDC_STC_HOME_FAX, TXT_PAGE_CONTACTS);
      pTabCtrl->registerControl (IDC_EDT_HOME_FAX, TXT_PAGE_CONTACTS);
      pTabCtrl->registerControl (IDC_STC_BUSINESS_FAX, TXT_PAGE_CONTACTS);
      pTabCtrl->registerControl (IDC_EDT_BUSINESS_FAX, TXT_PAGE_CONTACTS);
      pTabCtrl->registerControl (IDC_STC_EMAIL, TXT_PAGE_CONTACTS);
      pTabCtrl->registerControl (IDC_EDT_EMAIL, TXT_PAGE_CONTACTS);
      pTabCtrl->registerControl (IDC_STC_CONTACT_NAME, TXT_PAGE_CONTACTS);
      pTabCtrl->registerControl (IDC_EDT_CONTACT_NAME, TXT_PAGE_CONTACTS);

      pTabCtrl->registerControl (IDC_STC_TELEX, TXT_PAGE_CONTACTS);
      pTabCtrl->registerControl (IDC_EDT_TELEX, TXT_PAGE_CONTACTS);
      // Tax Juris diction
      pTabCtrl->registerControl (IDC_STC_TAX_JURIS, TXT_PAGE_TAX);
      pTabCtrl->registerControl (IDC_EDT_TAX_JURIS, TXT_PAGE_TAX);
      pTabCtrl->registerControl (IDC_STC_TAX_JURIS_EFFECTIVE, TXT_PAGE_TAX);
      pTabCtrl->registerControl (IDC_DTP_TAX_JURIS_EFFECTIVE, TXT_PAGE_TAX);
      if( eusd == Y )
      {
         pTabCtrl->registerControl (IDC_STC_EUSD_OPTION, TXT_PAGE_TAX);
         pTabCtrl->registerControl (IDC_CMB_EUSD_OPTION, TXT_PAGE_TAX);
      }
      pTabCtrl->registerControl (IDC_CHK_UPDATE_SHAREHOLDER_TAX_JURIS, TXT_PAGE_TAX);
      //pTabCtrl->registerControl (IDC_STC_FATCA_FFID,                   TXT_PAGE_TAX);
      //pTabCtrl->registerControl (IDC_CMB_FATCA_FFID,                   TXT_PAGE_TAX);
      pTabCtrl->registerControl (IDC_BTN_TAX_JURIS_HISTORY, TXT_PAGE_TAX);

      // Tab control
      ShowTabCtrl (IDC_TAB_ENTITY_MAINTENANCE, true);
      LoadTabControl (IDC_TAB_ENTITY_MAINTENANCE);
   }

   CWnd* pNameWnd = GetDlgItem(IDC_EDT_NAME);
   if (NULL != pNameWnd)
   {
       if (DSTEdit* pDSTEditName = dynamic_cast<DSTEdit*>(pNameWnd))
       {
           pDSTEditName->SetRemoveUnwantedCharsAfterPaste(true);
       }
   }

   CWnd* pFirstNameWnd = GetDlgItem(IDC_EDT_FIRST_NAME);
   if (NULL != pFirstNameWnd)
   {
       if (DSTEdit* pDSTEditFirstName = dynamic_cast<DSTEdit*>(pFirstNameWnd))
       {
           pDSTEditFirstName->SetRemoveUnwantedCharsAfterPaste(true);
       }
   }

   CWnd* pLastNameWnd = GetDlgItem(IDC_EDT_LAST_NAME);
   if (NULL != pLastNameWnd)
   {
       if (DSTEdit* pDSTEditLastName = dynamic_cast<DSTEdit*>(pLastNameWnd))
       {
           pDSTEditLastName->SetRemoveUnwantedCharsAfterPaste(true);
       }
   }

   return TRUE;
}

//******************************************************************************
void EntityMaintenanceDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );
   SetUserAccesFunctionCode(UAF::ENTITY_MAINTANENCE);
   addBtnAddForPermissionCheck(IDC_BTN_ADD, IDC_LV_ENTITIES);
//copy button should observe the same rules as the add entity button
   addBtnAddForPermissionCheck(IDC_BTN_COPYENTITY, IDC_LV_ENTITIES);
   addBtnAddForPermissionCheck(IDC_BTN_ADD_ID, IDC_LV_ENTITY_IDS);
   addBtnDeleteForPermissionCheck(IDC_BTN_DELETE, IDC_LV_ENTITIES);
   addBtnDeleteForPermissionCheck(IDC_BTN_DELETE_ID, IDC_LV_ENTITY_IDS);
   
   GetDlgItem(IDC_BTN_ADD_RISK)->EnableWindow(hasCreatePermission(UAF::ENTITY_MAINTANENCE));
   GetDlgItem(IDC_BTN_DELETE_RISK)->EnableWindow(hasDeletePermission(UAF::ENTITY_MAINTANENCE));

   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_LAST_NAME ) ) )->SetMaxCharNum( 40 );
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_FIRST_NAME ) ) )->SetMaxCharNum( 40 );
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_NAME ) ) )->SetMaxCharNum( 80 );

   DString strMarket = DSTCommonFunctions::getMarket();
   if( strMarket == MARKET_IDS::JAPAN )
   {
      ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_BIRTH_LAST_NAME ) ) )->SetMaxCharNum( 40 );
      ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_BIRTH_FIRST_NAME ) ) )->SetMaxCharNum( 40 );
   }
   else if( strMarket == MARKET_IDS::CANADA )
   {
      ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_HOME_TEL_AREA ) ) )->SetMaxCharNum( 3 );
      ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_BUSINESS_TEL_AREA ) ) )->SetMaxCharNum( 3 );
      ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_HOME_FAX_AREA ) ) )->SetMaxCharNum( 3 );
      ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_BUSINESS_FAX_AREA ) ) )->SetMaxCharNum( 3 );
      ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_RESP2_ALLOCATION_PRCNT ) ) )->SetAllowedChars(I_("0123456789."));
   }

   if (m_bPaternalMaternal) 
   {
      ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_PATERNAL_NAME ) ) )->SetMaxCharNum( 40 );
      ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_MATERNAL_NAME ) ) )->SetMaxCharNum( 40 );
   }

   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_ID_VALUE ) ) )->SetMaxCharNum( 20 );
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_HOME_TEL ) ) )->SetMaxCharNum( 22 );
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_BUSINESS_TEL ) ) )->SetMaxCharNum( 22 );
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_BUSINESS_EXT ) ) )->SetMaxCharNum( 10 );
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_HOME_FAX ) ) )->SetMaxCharNum( 22 );
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_BUSINESS_FAX ) ) )->SetMaxCharNum( 22 );
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_EMAIL ) ) )->SetMaxCharNum( 60 );
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_CONTACT_NAME ) ) )->SetMaxCharNum( 80 );
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_PRC_BENEFIT ) ) )->SetMaxCharNum( 8 );
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_BIRTH_PLACE ) ) )->SetAllowedChars( ALPHACHARACTERS );
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_BIRTH_PLACE ) ) )->SetMaxCharNum( 40 );
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_EMAIL2 ) ) )->SetMaxCharNum( 60 );

   DString str, str1;
   getParent()->getField( this, ENTPROC::PROC_CREATING_SHAREHOLDER, str, false ); 
   getParent()->getField( this, ENTPROC::PROC_CREATING_ACCOUNT, str1, false ); 

   if( strMarket == MARKET_IDS::JAPAN )
   {
      if( str1 == Y )
         EnableControl( IDC_BTN_ADM_DATES, false );
      else
         EnableControl( IDC_BTN_ADM_DATES, true );
   }
   flg_not_opended_yet = true;
   if( str == Y )
   {
      DString hasNoDummyRecords;
      getParent()->getField( this, ENTPROC::HAS_NON_DUMMY_RECORDS, hasNoDummyRecords );
      if( hasNoDummyRecords != Y )
      {
         flg_ready_for_background_search = true;
         flg_add_new_item_mode = true;
         flg_click_outside_ids_frame = false;
         EnableControl( IDC_BTN_SEARCH, true );
         FocusOnControl( IDC_CMB_ID_TYPE );
      }
      else
      {
         flg_ready_for_background_search = false;
         flg_add_new_item_mode = false;
         EnableControl( IDC_BTN_SEARCH, false );
      }
   }
   else
   {
      flg_ready_for_background_search = false;
      flg_add_new_item_mode = false;
      EnableControl( IDC_BTN_SEARCH, false );
   }
   EnableControl( IDC_BTN_ADD, m_existAccount == Y );
   EnableControl( IDC_BTN_DELETE, m_existAccount == Y );
   EnableControl( IDC_EDT_PRC_BENEFIT, m_existAccount == Y );

   ConnectControlsToData();

   if (m_existAccount == N)
   {
      ConnectControl( IDC_CMB_ENTITY_TYPE, false);
      ConnectControl( IDC_CMB_RELATION, false);
      ConnectControl( IDC_CMB_IRREVOCABLE, false);
      ConnectControl( IDC_CMB_AUTHORIZED_TO_TRADE, false);
   }

   LoadListWithSelection( IDC_LV_ENTITIES, m_dstrKeySel );

   DString dstrShrNum;
   getParent()->getField (this,ENTPROC::SHR_NUM, dstrShrNum);
   dstrShrNum.stripLeading().stripLeading(I_CHAR('0')).stripTrailing();
   DString dstrEntityName;

   DSTCWorkSession *pWorkSession = NULL;

   pWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   pWorkSession->getFirstSequenced01AccountholderEntityName( getDataGroupId(), 
                                                             m_dstrAccountNum, 
                                                             dstrEntityName, 
                                                             true);

   DString dstrNewAccount;
   getParent()->getField(this, BF::NullContainerId, ENTPROC::NEW_ACCOUNT, dstrNewAccount);
   SetAccount( m_dstrAccountNum );
   // if( dstrNewAccount == N ) // why do this?
   {
      SetShrAcctCaption (dstrShrNum, m_dstrAccountNum, dstrEntityName);
   }

   flg_not_opended_yet = false;

   if ( strMarket == MARKET_IDS::CANADA || 
        strMarket == MARKET_IDS::LUXEMBOURG)
   {

      // Rule: Entity History button is disabled during new shareholder/account set-up
      if (dstrNewAccount == Y)
      {
         GetDlgItem (IDC_BTN_ENTITY_HISTORY)->EnableWindow (false);
      }
      else
      {
         GetDlgItem (IDC_BTN_ENTITY_HISTORY)->EnableWindow (true);
      }
   }
   LoadListWithSelection( IDC_LV_ENTITIES, m_dstrKeySel );

   DString dstrEntityType;
   getParent()->getField( this, 
                          IFASTBP_PROC::ENTITY_LIST, 
                          ifds::EntityType, 
                          dstrEntityType, 
                          false);

   if ( strMarket == MARKET_IDS::CANADA )
   {
      DSTTabCtrl* pTabCtrl = GetTabCtrl (IDC_TAB_ENTITY_MAINTENANCE);

      if (pTabCtrl != NULL)
      {
         if( (dstrEntityType != ENTITY_TYPE_PRIMARY_BENEF) &&
             (dstrEntityType != ENTITY_TYPE_SECONDARY_BENEF) &&
             (dstrEntityType != RESP_BENEFICIARY))
         {
            pTabCtrl->removeControlFromPage (IDC_STC_DATE_DEATH_SETTLEMENT, TXT_PAGE_DETAILS );
            pTabCtrl->removeControlFromPage (IDC_DTP_DEATH_DATE_SETTLEMENT, TXT_PAGE_DETAILS );
            GetDlgItem( IDC_STC_DATE_DEATH_SETTLEMENT )->ShowWindow( SW_HIDE );
            GetDlgItem( IDC_DTP_DEATH_DATE_SETTLEMENT )->ShowWindow( SW_HIDE );
         }
         else
         {
            pTabCtrl->registerControl (IDC_STC_DATE_DEATH_SETTLEMENT, TXT_PAGE_DETAILS);
            pTabCtrl->registerControl (IDC_DTP_DEATH_DATE_SETTLEMENT, TXT_PAGE_DETAILS);
            GetDlgItem( IDC_STC_DATE_DEATH_SETTLEMENT )->ShowWindow( SW_SHOW );
            GetDlgItem( IDC_DTP_DEATH_DATE_SETTLEMENT )->ShowWindow( SW_SHOW );
         }
      }
   }

   DString dstrIDtype = NULL_STRING;
   getParent()->getField( this, ifds::IdType, dstrIDtype,false );
   if( dstrIDtype == IDS::BIRTH_CERTIFICATE || dstrIDtype == IDS::DRIVERS_LICENSE || 
       dstrIDtype == IDS::PASSPORT ||dstrIDtype == IDS::NATIONAL_ID || 
       dstrIDtype == IDS::TRUST_ACCOUNT_NUMBER || dstrIDtype == IDS::BUSINESS_NUMBER ||
       dstrIDtype == IDS::TAX_ID_NUMBER || dstrIDtype == IDS::EMPLOYER_NUMBER || 
       dstrIDtype == IDS::BIC_CODE || dstrIDtype == IDS::FATCA_GIIN || 
	   dstrIDtype == IDS::SOCIAL_SECURITY_NUMBER || dstrIDtype == IDS::AEOI)
   {
      GetDlgItem( IDC_CMB_COUNTRY_OF_ISSUE)->ShowWindow(SW_SHOW);	 
      GetDlgItem(IDC_STATIC_CNTRY_OF_ISSUE)->ShowWindow(SW_SHOW);
   }
   else
   {
      GetDlgItem(IDC_CMB_COUNTRY_OF_ISSUE)->ShowWindow(SW_HIDE);	 
      GetDlgItem(IDC_STATIC_CNTRY_OF_ISSUE)->ShowWindow(SW_HIDE);
   }

   GetDlgItem ( IDC_BTN_ENT_REG_DETAIL )->EnableWindow ( hasReadPermission(UAF::ENTITY_REGULATORY_MAINT) );

   /*
	  Entity Regulatory Detail has to have the read permission to access screen, 
      Also, as there is the NASUPOPUP GC to activate the screen while NASU. So no need to active the button
	*/
   GetDlgItem ( IDC_BTN_ENT_REG_DETAIL )->EnableWindow ( (hasReadPermission(UAF::ENTITY_REGULATORY_MAINT)) && (m_dstrCreatingAccount != I_("Y")) );

   DSTTabCtrl* pTabCtrl = GetTabCtrl (IDC_TAB_ENTITY_MAINTENANCE);
   if (pTabCtrl != NULL)
   {
      CString cstrDetailsPageName, cstrPageName;
      TCITEM tcItem;
      wchar_t buffer[256] = {0};
      tcItem.pszText = buffer;
      tcItem.cchTextMax = 256;
      tcItem.mask = TCIF_TEXT;

      int iPagePos = pTabCtrl->GetCurSel();
      pTabCtrl->GetItem(iPagePos, &tcItem);

      cstrPageName = tcItem.pszText;
      cstrDetailsPageName.LoadString( TXT_PAGE_DETAILS);
      if( cstrDetailsPageName == cstrPageName)
      {
         DString strRiskLevel;
         getParent()->getField (this, 
                                IFASTBP_PROC::ENTITY_LIST, 
                                ifds::RiskLevel,
                                strRiskLevel,
                                false);
         strRiskLevel.strip().upperCase();

         if (multipleRiskEnv())
         {
             GetDlgItem( IDC_STC_RISK_LEVEL )->ShowWindow( SW_HIDE );
             GetDlgItem( IDC_CMB_RISK_LEVEL )->ShowWindow( SW_HIDE );
             GetDlgItem( IDC_STC_COUNTRY_OF_EXPOSURE )->ShowWindow( SW_HIDE );
             GetDlgItem( IDC_CMB_COUNTRY_OF_EXPOSURE )->ShowWindow( SW_HIDE );
         }
         else
         {
             if (POLITICALLY_EXPOSED_PERSON != strRiskLevel) {
                 GetDlgItem( IDC_STC_COUNTRY_OF_EXPOSURE )->ShowWindow( SW_HIDE );
                 GetDlgItem( IDC_CMB_COUNTRY_OF_EXPOSURE )->ShowWindow( SW_HIDE );
             }
             else{
                 GetDlgItem( IDC_STC_COUNTRY_OF_EXPOSURE )->ShowWindow( SW_SHOW );
                 GetDlgItem( IDC_CMB_COUNTRY_OF_EXPOSURE )->ShowWindow( SW_SHOW );
             }
         }
      }
   }

   GetDlgItem(IDC_BTN_SET_RISK_LEVEL)->EnableWindow(hasUpdatePermission(UAF::ENTITY_MAINTANENCE));

   this->InvalidateRect(NULL, FALSE);
   this->UpdateWindow();
}

//******************************************************************************
SEVERITY EntityMaintenanceDlg::doInit()
{
   SEVERITY sevRtn = SEVERE_ERROR;

   getParameter( ENTITYDLG::ACCOUNT_NUM,    m_dstrAccountNum);
   getParameter( ENTITYDLG::KEY,            m_dstrKeySel);
   getParameter( ENTITYDLG::EXIST_ACCOUNT,  m_existAccount );
   getParameter( NASULIT::CREATING_ACCOUNT, m_dstrCreatingAccount );
   getParameter( NASULIT::CREATING_SHAREHOLDER, m_dstrCreatingShareholder);
   getParameter(ENTPROC::MODEL_ACCOUNT_NUM, m_dstrModelAccountNum);

   DString dstrSalutationEdit;
   getParent()->getField( this, ENTPROC::SALUTATION_EDIT, dstrSalutationEdit );
   m_bSalutationFreeFormat = (dstrSalutationEdit == I_("Y"));
   sevRtn = NO_CONDITION;
   return(sevRtn);
}

//******************************************************************************
void EntityMaintenanceDlg::OnBtnAdminDates()
{
   ShowAdminDates( IFASTBP_PROC::ENTITY_LIST );
}

//******************************************************************************
bool EntityMaintenanceDlg::doRefresh(GenericInterface *, const I_CHAR *) 
{  
   getParameter( ENTITYDLG::ACCOUNT_NUM,   m_dstrAccountNum);
   getParameter( ENTITYDLG::KEY,          m_dstrKeySel);
   getParameter( ENTITYDLG::EXIST_ACCOUNT, m_existAccount );

   // Set Window Title
   DString dstrShrNum;
   getParent()->getField(this,ENTPROC::SHR_NUM, dstrShrNum);
   dstrShrNum.stripLeading().stripLeading(I_CHAR('0')).stripTrailing();

   SetAccount( m_dstrAccountNum );

   DSTCWorkSession *pWorkSession = NULL;

   pWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   DString dstrEntityName;
   pWorkSession->getFirstSequenced01AccountholderEntityName( getDataGroupId(), 
                                                             m_dstrAccountNum, 
                                                             dstrEntityName, 
                                                             true );

   SetShrAcctCaption(dstrShrNum, m_dstrAccountNum, dstrEntityName);

   LoadListWithSelection( IDC_LV_ENTITIES, m_dstrKeySel );

   return(true);
}

//***************************************************************************
void EntityMaintenanceDlg::DoListItemChanged( UINT listControlID,
                                              const DString &strKey, 
                                              bool isNewItem,
                                              bool bIsDummyItem)
{
   DString strMarket = DSTCommonFunctions::getMarket();
   DString str, 
           str1;

   DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());

   bool bIsRES2Client = 
	   dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->isRES2Client();

   switch( listControlID )
   {
      case IDC_LV_ENTITIES:
      {
            LoadControl( IDC_CMB_EMPLOYEECLASS );
            m_bNewEntity = isNewItem;

            DString entityType;

            getParent()->getField (this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityType, entityType, false);
            bool bFlag = GetEntityEnable();

            if( ( entityType == ESCROW_ENTITY_TYPE  && 
                ( !hasUpdatePermission(UAF::ESCROW ) || !hasUpdatePermission(UAF::ESCROW_BAND ) ) ) || 
                ( entityType == ASSIGNEE_ENTITY_TYPE  && !hasUpdatePermission(UAF::ASSIGNEE_ENTITY_TYPE_SETUP ) ) )
            {
               EnableEntityControls( false );
            }
            else
            {
               EnableEntityControls( bFlag );
            }

            DString  updShrTaxJuris;

            getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::UpdShrTaxJuris, updShrTaxJuris,false);
            updShrTaxJuris.strip().upperCase();
            m_bUpdateShareholder = updShrTaxJuris == Y ? true: false ;
            UpdateData (false);
            if (strMarket == MARKET_IDS::CANADA)
            {            
               if( str == ENTITY_TYPE_ACC_OWNER)
               {
                  GetDlgItem( IDC_TXT_SPOUSAL )->ShowWindow( true );
                  GetDlgItem( IDC_TXT_SPOUSAL )->EnableWindow( true );
                  GetDlgItem( IDC_CMB_SPOUSAL )->ShowWindow( true );
                  LoadControl( IDC_CMB_SPOUSAL );
                  EnableControl(IDC_CMB_SPOUSAL, bFlag);
               }
               else
               {
                  GetDlgItem( IDC_TXT_SPOUSAL )->EnableWindow( false );
                  GetDlgItem( IDC_TXT_SPOUSAL )->ShowWindow( false );
                  EnableControl(IDC_CMB_SPOUSAL, false);
                  GetDlgItem( IDC_CMB_SPOUSAL )->ShowWindow( false );
               }
            }

            MFAccount *pModelAccount = NULL;
            if (doesSupportMstrActAMSC() && m_dstrCreatingShareholder == N && m_dstrCreatingAccount == Y)
            {
               EnableControl (IDC_CMB_ENTITY_TYPE, false);
            }
            else
            {
               EnableControl (IDC_CMB_ENTITY_TYPE, isNewItem);
            }
            LoadControl (IDC_CMB_ENTITY_TYPE);
//reset button should be enabled only if the element is new
// check if the entity is new then reset can work...
            bool bIsEntityNew = false;
            Entity* pEntity (NULL);
            DString entityId;
            DSTCWorkSession *pDSTCWorkSession = 
               dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());   
            
            getParent()->getField (this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityId, entityId, false);
            entityId.stripLeading( '0' );
            if (!entityId.empty())
            {
               if ( pDSTCWorkSession->getEntity (getDataGroupId(), entityId, pEntity) <= WARNING &&
                    pEntity)
               {
                  bIsEntityNew = pEntity->isNew ();
               }
            }
            if (!pEntity)
               bIsEntityNew = true;
            GetDlgItem (IDC_BTN_RESET)->EnableWindow (isNewItem && bIsEntityNew);
            // Historical Button
            GetDlgItem (IDC_BTN_ENTITY_HISTORY)->EnableWindow( (isNewItem || bIsDummyItem) ? FALSE : TRUE );

            // QESI enable/disable tax juris history book
            if (bIsRES2Client && strMarket == MARKET_IDS::CANADA)
            {
               DString entityType;

               getParent()->getField( this, 
                  IFASTBP_PROC::ENTITY_LIST, 
                  ifds::EntityType, 
                  entityType, 
                  false);

               bool bShowRespControl = entityType == RESP_BENEFICIARY;
               
               ConnectControlsToData (RESP2_CONTROLS::BENEF_INFO, bShowRespControl);
               ConnectControlsToData (RESP2_CONTROLS::RELATIONSHIPS, bShowRespControl);
               
               if(bShowRespControl)
               {
                  LoadControls (RESP2_CONTROLS::BENEF_INFO);
                  LoadControls (RESP2_CONTROLS::RELATIONSHIPS);
               }
               // enable/disable Grant button

               EnableControl( IDC_BTN_GRANT, !bIsEntityNew && 
                                             pDSTCWorkSession->hasReadPermission (UAF::RESP_BENEFICIARY) && 
                                             (pDSTCWorkSession->hasReadPermission (UAF::RESP_GRANTS) || pDSTCWorkSession->hasReadPermission (UAF::RESP_GRANT_INFORMATION)));
            } //end if bIsRES2Client && strMarket == MARKET_IDS::CANADA

            //IN3308549
            bool bTaxJurisError = false;
            const BFDataGroupId& idDataGroup = getParent()->getDataGroupId();
            ErrMsgRulesList *pErrMsgRulesList = NULL;

            if ( pDSTCWorkSession->getMgmtCo().getErrMsgRulesList (pErrMsgRulesList) <= WARNING &&
               pErrMsgRulesList)
            {
               DString strErrValue;

               pErrMsgRulesList->getEWIValue (IFASTERR::JURISDICTION_NOT_SAME_AS_SHRHLDR_JURISDICTION, idDataGroup, strErrValue);
               if (strErrValue == I_("I"))
               {
                  bTaxJurisError = true;
               }
            }

            if ( !hasReadPermission(UAF::ENTITY_TAX_JURIS_HISTORY) ){
               GetDlgItem (IDC_BTN_TAX_JURIS_HISTORY)->EnableWindow (false);
            }
            else{
               if ( strMarket != MARKET_IDS::CANADA && bTaxJurisError ) {
                  GetDlgItem (IDC_BTN_TAX_JURIS_HISTORY)->EnableWindow (false);
               }
               else {
                  BOOL bEnableJurisHistory = (isNewItem || bIsEntityNew) ? FALSE : TRUE;	
                  GetDlgItem (IDC_BTN_TAX_JURIS_HISTORY)->EnableWindow (bEnableJurisHistory);
               }
            }

            DString dstrEntityType;
            getParent()->getField( this, 
                                   IFASTBP_PROC::ENTITY_LIST, 
                                   ifds::EntityType, 
                                   dstrEntityType, 
                                   false);

            if ( strMarket == MARKET_IDS::CANADA )
            {
               DSTTabCtrl* pTabCtrl = GetTabCtrl (IDC_TAB_ENTITY_MAINTENANCE);

               if (pTabCtrl != NULL)
               {
                  if( (dstrEntityType != ENTITY_TYPE_PRIMARY_BENEF) &&
                     (dstrEntityType != ENTITY_TYPE_SECONDARY_BENEF) &&
                     (dstrEntityType != RESP_BENEFICIARY))
                  {
                     pTabCtrl->removeControlFromPage (IDC_STC_DATE_DEATH_SETTLEMENT, TXT_PAGE_DETAILS );
                     pTabCtrl->removeControlFromPage (IDC_DTP_DEATH_DATE_SETTLEMENT, TXT_PAGE_DETAILS );
                     GetDlgItem( IDC_STC_DATE_DEATH_SETTLEMENT )->ShowWindow( SW_HIDE );
                     GetDlgItem( IDC_DTP_DEATH_DATE_SETTLEMENT )->ShowWindow( SW_HIDE );
                  }
                  else
                  {
                     pTabCtrl->registerControl (IDC_STC_DATE_DEATH_SETTLEMENT, TXT_PAGE_DETAILS);
                     pTabCtrl->registerControl (IDC_DTP_DEATH_DATE_SETTLEMENT, TXT_PAGE_DETAILS);
                     GetDlgItem( IDC_STC_DATE_DEATH_SETTLEMENT )->ShowWindow( SW_SHOW );
                     GetDlgItem( IDC_DTP_DEATH_DATE_SETTLEMENT )->ShowWindow( SW_SHOW );
                  }
               }
            }

            LoadTabControl (IDC_TAB_ENTITY_MAINTENANCE );

            DSTTabCtrl* pTabCtrl = GetTabCtrl (IDC_TAB_ENTITY_MAINTENANCE);
            if (pTabCtrl != NULL)
            {
               CString cstrDetailsPageName, cstrPageName;
               TCITEM tcItem;
               wchar_t buffer[256] = {0};
               tcItem.pszText = buffer;
               tcItem.cchTextMax = 256;
               tcItem.mask = TCIF_TEXT;

               int iPagePos = pTabCtrl->GetCurSel();
               pTabCtrl->GetItem(iPagePos, &tcItem);

               cstrPageName = tcItem.pszText;
               cstrDetailsPageName.LoadString( TXT_PAGE_DETAILS);
               if( cstrDetailsPageName == cstrPageName)
               {
                  DString strRiskLevel;
                  getParent()->getField (this, 
                                         IFASTBP_PROC::ENTITY_LIST, 
                                         ifds::RiskLevel,
                                         strRiskLevel,
                                         false);
                  strRiskLevel.strip().upperCase();
                  if (multipleRiskEnv())
                  {
                      GetDlgItem( IDC_STC_RISK_LEVEL )->ShowWindow( SW_HIDE );
                      GetDlgItem( IDC_CMB_RISK_LEVEL )->ShowWindow( SW_HIDE );
                      GetDlgItem( IDC_STC_COUNTRY_OF_EXPOSURE )->ShowWindow( SW_HIDE );
                      GetDlgItem( IDC_CMB_COUNTRY_OF_EXPOSURE )->ShowWindow( SW_HIDE );
                  }
                  else
                  {
                      if (POLITICALLY_EXPOSED_PERSON != strRiskLevel) {
                          GetDlgItem( IDC_STC_COUNTRY_OF_EXPOSURE )->ShowWindow( SW_HIDE );
                          GetDlgItem( IDC_CMB_COUNTRY_OF_EXPOSURE )->ShowWindow( SW_HIDE );
                      }
                      else{
                          GetDlgItem( IDC_STC_COUNTRY_OF_EXPOSURE )->ShowWindow( SW_SHOW );
                          GetDlgItem( IDC_CMB_COUNTRY_OF_EXPOSURE )->ShowWindow( SW_SHOW );
                      }
                  }
               }
            }
            break;
      }
      case IDC_LV_ENTITY_IDS:
      {
            //MT535/MT536
            DString strEntityIDType,
                    strIdValueFmt;
            getParent()->getField (this, IFASTBP_PROC::ENTITY_IDS_LIST, ifds::IdType, strEntityIDType, false );
            getParent()->getField (this, IFASTBP_PROC::ENTITY_IDS_LIST, ifds::IdValue, strIdValueFmt, true );

			EnableEntityIdsControls(UAF::ENTITY_MAINTANENCE, isNewItem);
			if (strEntityIDType == IDS::TAX_FILE_NUMBER )
			{
				EnableEntityIdsControls(UAF::APAC_SUPREGN, isNewItem);
			}
            if (strEntityIDType == IDS::CLEARING_PLATFORM )
            {
               ConnectControlsToData (ENTITY_IDS_CONTROLS::EDIT_CNTRL, false);
               // MT53X
               ReInitControl (IDC_CMB_ID_VALUE, IFASTBP_PROC::ENTITY_IDS_LIST, ifds::IdValue, CTRLFLAG_INITCOMBO_BY_SUB_LIST, ENTITY_IDS_CONTROLS::COMBO_CNTRL);

               ConnectControlsToData (ENTITY_IDS_CONTROLS::COMBO_CNTRL,true );
               LoadControls (ENTITY_IDS_CONTROLS::COMBO_CNTRL);
			}			
            else
            {
               ConnectControlsToData (ENTITY_IDS_CONTROLS::COMBO_CNTRL, false);
               ConnectControlsToData (ENTITY_IDS_CONTROLS::EDIT_CNTRL,true );
               LoadControls (ENTITY_IDS_CONTROLS::EDIT_CNTRL);	
               ControlUpdated(IDC_EDT_ID_VALUE, strIdValueFmt );

            }
            LoadControls (IDC_LV_ENTITY_IDS);
            break;
      }
      case IDC_LV_RISKS:
      {
          GetDlgItem(IDC_BTN_DELETE_RISK)->EnableWindow(hasDeletePermission(UAF::ENTITY_MAINTANENCE) || isNewItem);

          DString dstrRiskDeffAppl;
          getParent()->getField(this, IFASTBP_PROC::RISK_LIST, ENTPROC::RISK_DEFF_DATE_APPL, dstrRiskDeffAppl, false);
          bool riskDeffAppl = dstrRiskDeffAppl == I_("Y");

          GetDlgItem(IDC_STC_RISK_DEFF)->ShowWindow(riskDeffAppl && riskTabSelected());
          GetDlgItem(IDC_DTP_RISK_DEFF)->ShowWindow(riskDeffAppl && riskTabSelected());
      }
      default:
      {
         break;
      }
   
   }

   this->InvalidateRect(NULL, FALSE);
   this->UpdateWindow();
}

//******************************************************************************
bool EntityMaintenanceDlg::riskTabSelected()
{
    bool risktabSel = false;
    DSTTabCtrl* pTabCtrl = GetTabCtrl (IDC_TAB_ENTITY_MAINTENANCE);
    
    if (pTabCtrl != NULL)
    {
        CString cstrRiskPageName, cstrPageName;
        TCITEM tcItem;
        wchar_t buffer[256] = {0};
        tcItem.pszText = buffer;
        tcItem.cchTextMax = 256;
        tcItem.mask = TCIF_TEXT;

        int iPagePos = pTabCtrl->GetCurSel();
        pTabCtrl->GetItem(iPagePos, &tcItem);

        cstrPageName = tcItem.pszText;
        cstrRiskPageName.LoadString(TXT_PAGE_RISKS);

        risktabSel = cstrPageName == cstrRiskPageName;
    }

    return risktabSel;
}

//******************************************************************************
void EntityMaintenanceDlg::DoPreListItemChanged( UINT listControlID, const DString &strKey, bool isNewItem,  bool bIsDummyItem)
{
   switch( listControlID )
   {
      case IDC_LV_ENTITIES:
      {
         if (flg_add_new_item_mode && !flg_not_opended_yet)
         {
            flg_add_new_item_mode = false;
            flg_not_opended_yet = false;
         }

         DSTTabCtrl* pTabCtrl = GetTabCtrl (IDC_TAB_ENTITY_MAINTENANCE);
         if (pTabCtrl != NULL)
            pTabCtrl->SelectTab (TXT_PAGE_DETAILS,true);

         break;
      }
      default:
         break;
   }
}

//******************************************************************************
void EntityMaintenanceDlg::EnableEntityControls( bool bFlag )
{
   EnableControl( IDC_EDT_LAST_NAME, bFlag );
   EnableControl( IDC_EDT_FIRST_NAME, bFlag );

   if (DSTCommonFunctions::getMarket() == MARKET_IDS::JAPAN)
   {
      EnableControl (IDC_EDT_BIRTH_LAST_NAME, bFlag);
      EnableControl (IDC_EDT_BIRTH_FIRST_NAME, bFlag);
   }
   EnableControl( m_bSalutationFreeFormat ? IDC_EDT_SALUTATION : IDC_CMB_SALUTATION, bFlag );
   EnableControl( IDC_DTP_BIRTH_DATE, bFlag );
   EnableControl( IDC_EDT_BIRTH_PLACE, bFlag );
   EnableControl( IDC_CMB_COUNTRY_OF_BIRTH, bFlag );
   EnableControl( IDC_CMB_GENDER, bFlag );   
   EnableControl( IDC_CMB_ENTITY_TYPE, bFlag );
   EnableControl( IDC_CMB_AUTHORIZED_TO_TRADE, bFlag );
   EnableControl( IDC_CMB_NATIONALITY, bFlag );
   EnableControl( IDC_CMB_LANGUAGE, bFlag );
   EnableControl( IDC_DTP_EFFECTIVE_DATE, bFlag );
   EnableControl( IDC_DTP_DEATH_DATE, bFlag );
   EnableControl( IDC_DTP_DEATHNOTIFDATE, bFlag );
   EnableControl( IDC_CMB_ID_TYPE, bFlag );
   EnableControl( IDC_EDT_ID_VALUE, bFlag );
   //EnableControl( IDC_CMB_ID_VALUE, bFlag ); //MT535/MT536
   EnableControl( IDC_DTP_ID_DATE, bFlag );
   EnableControl( IDC_BTN_ADD_ID, bFlag);  
   EnableControl( IDC_BTN_DELETE_ID, bFlag);
   EnableControl( IDC_CMB_EMPLOYEECLASS, bFlag);
   EnableControl( IDC_EDT_NAME, bFlag);
   EnableEntityPhoneControls( bFlag );

   if (DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA)
   {
      EnableControl( IDC_CMB_SPOUSAL, bFlag);
   }
   
   if (DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA || 
       DSTCommonFunctions::getMarket() == MARKET_IDS::LUXEMBOURG)
   {
      EnableControl( IDC_CMB_TAX_JURISDICTION, bFlag);
      EnableControl( IDC_EDT_FUND_NUMBER, bFlag);
      EnableControl( IDC_EDT_FUND_CODE, bFlag);
      EnableControl( IDC_EDT_CLASS_CODE, bFlag);
      EnableControl( IDC_EDT_AMOUNT_ASSIGN, bFlag);
      EnableControl( IDC_CMB_AMOUNT_TYPE, bFlag);
      EnableControl( IDC_CMB_ESC_REASON, bFlag);
      EnableControl( IDC_DTP_ESC_EFFECTIVE, bFlag);
      EnableControl( IDC_DTP_ESC_STOP, bFlag);
      EnableControl( IDC_CMB_OCUPATION, bFlag);
      EnableControl( IDC_EDT_OCCUPATION, bFlag);
      //IN2780013 - SOC Loan Number and Loan Type
      EnableControl( IDC_CMB_LOAN_TYPE, bFlag);
      EnableControl( IDC_EDT_LOAN_NUMBER, bFlag);
   }
   if( DSTCommonFunctions::getMarket() == MARKET_IDS::LUXEMBOURG)
   	  EnableControl( IDC_CMB_VERIFY_STATUS, bFlag);
    
   bool bEntityFlag = GetEntityEnable();

   EnableControl(IDC_CMB_RESP_TAX_JURISD, bEntityFlag);
   EnableControl(IDC_CMB_EUSD_OPTION, bEntityFlag);
   EnableControl(IDC_DTP_TAX_JURIS_EFFECTIVE, bEntityFlag);
   EnableControl(IDC_EDT_TAX_JURIS, bEntityFlag);
   EnableControl(IDC_BTN_ENTITY_ADDRESS, bEntityFlag && m_dstrCreatingAccount != Y);
}

//******************************************************************************
void EntityMaintenanceDlg::EnableEntityPhoneControls( bool bFlag )
{
   EnableControl( IDC_EDT_HOME_TEL, bFlag );
   EnableControl( IDC_EDT_BUSINESS_TEL, bFlag );
   EnableControl( IDC_EDT_BUSINESS_EXT, bFlag );
   EnableControl( IDC_EDT_HOME_FAX, bFlag );
   EnableControl( IDC_EDT_BUSINESS_FAX, bFlag );
   EnableControl( IDC_EDT_EMAIL, bFlag );
   EnableControl( IDC_EDT_CONTACT_NAME, bFlag );
   EnableControl( IDC_EDT_TELEX, bFlag );
   EnableControl( IDC_EDT_EMAIL2, bFlag );
   EnableControl( IDC_EDT_SECOND_PHONENUM, bFlag );
   EnableControl( IDC_EDT_SECOND_PHONENUM_EXT, bFlag );

   if (DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA)
   {
      EnableControl( IDC_EDT_HOME_TEL_AREA,     bFlag );
      EnableControl( IDC_EDT_BUSINESS_TEL_AREA, bFlag );
      EnableControl( IDC_EDT_HOME_FAX_AREA,     bFlag );
      EnableControl( IDC_EDT_BUSINESS_FAX_AREA, bFlag );
   }
}

//******************************************************************************
void EntityMaintenanceDlg::EnableEntityIdsControls( const I_CHAR * functionCode, bool isNewItem )
{
	bool bRead = hasReadPermission(functionCode);
	bool bCreate = hasCreatePermission(functionCode);
	bool bUpdate = hasUpdatePermission(functionCode);
	bool bDel  = hasDeletePermission(functionCode);

  // For APAC_SUPREGN band, user is able to add new TFN Number.
  if(!isNewItem || functionCode != UAF::APAC_SUPREGN)
  {
	  EnableControl(IDC_CMB_ID_TYPE, bRead && bUpdate);
	  EnableControl(IDC_EDT_ID_VALUE, bRead && bUpdate);
	  EnableControl(IDC_DTP_ID_DATE, bRead && bUpdate);
	  EnableControl(IDC_ID_STATUS, bRead && bUpdate);
	  EnableControl(IDC_DTP_ID_DATE_EXPIRE, bRead && bUpdate);
	  EnableControl(IDC_BTN_DELETE_ID, bDel);
  }
}
void EntityMaintenanceDlg::FillBeneficiarySection()
{
   DString str, strOut;
   getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityType, str, false );
   if( ( str == ENTITY_TYPE_PRIMARY_BENEF || str == ENTITY_TYPE_SECONDARY_BENEF || str == ENTITY_TYPE_SUCCESSOR) && m_existAccount == Y )
   {
      EnableControl( IDC_FRM_BENEFICIARY, true );

      EnableControl( IDC_TXT_RELATIONSHIP_TO_OWNER, true );
      ConnectControl( IDC_CMB_RELATION, true );

      EnableControl( IDC_TXT_IRREVOCABLE, true );
      ConnectControl( IDC_CMB_IRREVOCABLE, true );

      EnableControl( IDC_TXT_PERCENT_OF_BENEFIT, true );
      ConnectControl( IDC_EDT_PRC_BENEFIT, true );

      EnableControl( IDC_TXT_AVAILABLE_PERCENT, true );
      EnableControl( IDC_TXT_AVAILABLE, true );

      LoadControl( IDC_TXT_AVAILABLE );
   }
   else
   {
      EnableControl( IDC_FRM_BENEFICIARY, false );
      EnableControl( IDC_TXT_RELATIONSHIP_TO_OWNER, false );
      ConnectControl( IDC_CMB_RELATION, false );
      EnableControl( IDC_TXT_IRREVOCABLE, false );
      ConnectControl( IDC_CMB_IRREVOCABLE, false );
      EnableControl( IDC_TXT_PERCENT_OF_BENEFIT, false );
      ConnectControl( IDC_EDT_PRC_BENEFIT, false );
      EnableControl( IDC_TXT_AVAILABLE_PERCENT, false );
      EnableControl( IDC_TXT_AVAILABLE, false );
   }
}

//******************************************************************************
void EntityMaintenanceDlg::DisplayJoinInfoControls( bool visible )
{
   bool bFlag = GetEntityEnable();

   if( visible )
   {
      flg_joint_controls = true;
      EnableControl( IDC_FRM_BENEFICIARY, true );
      EnableControl( IDC_TXT_RELATIONSHIP_TO_OWNER, true );
      EnableControl( IDC_TXT_PERCENT_OF_BENEFIT, true );
      LoadControl( IDC_FRM_BENEFICIARY );
      LoadControl( IDC_TXT_RELATIONSHIP_TO_OWNER );
      LoadControl( IDC_TXT_PERCENT_OF_BENEFIT );
/*
      ShowControl( IDC_CMB_DISPOSITION, true );
      ShowControl( IDC_CMB_JOINT_TYPE, true );
      ShowControl( IDC_CMB_RELATION, false );
      ShowControl( IDC_TXT_IRREVOCABLE, false );
      ShowControl( IDC_CMB_IRREVOCABLE, false );
      ShowControl( IDC_EDT_PRC_BENEFIT, false );
      ShowControl( IDC_TXT_AVAILABLE_PERCENT, false );
      ShowControl( IDC_TXT_AVAILABLE, false );
*/
  
   }
   else
   {
      flg_joint_controls = false;
      LoadControl( IDC_FRM_BENEFICIARY );
      LoadControl( IDC_TXT_RELATIONSHIP_TO_OWNER );
      LoadControl( IDC_TXT_PERCENT_OF_BENEFIT );
/*
      ShowControl( IDC_CMB_DISPOSITION, false );
      ShowControl( IDC_CMB_JOINT_TYPE, false );
      ShowControl( IDC_CMB_RELATION, true );
      ShowControl( IDC_TXT_IRREVOCABLE, true );
      ShowControl( IDC_CMB_IRREVOCABLE, true );
      ShowControl( IDC_EDT_PRC_BENEFIT, true );
      ShowControl( IDC_TXT_AVAILABLE_PERCENT, true );
      ShowControl( IDC_TXT_AVAILABLE, true );
*/
   }
   ConnectControlToData(IDC_CMB_DISPOSITION,          visible,true );
   ConnectControlToData(IDC_CMB_JOINT_TYPE,           visible,true );
   ConnectControlToData(IDC_CMB_RELATION,            !visible,true );
   ConnectControlToData(IDC_TXT_IRREVOCABLE,         !visible,true );
   ConnectControlToData(IDC_CMB_IRREVOCABLE,         !visible,true );
   ConnectControlToData(IDC_EDT_PRC_BENEFIT,         !visible,true );
   ConnectControlToData(IDC_TXT_AVAILABLE_PERCENT,   !visible,true );
   ConnectControlToData(IDC_TXT_AVAILABLE,           !visible,true );

   LoadControl(IDC_CMB_DISPOSITION         );
   LoadControl(IDC_CMB_JOINT_TYPE          );
   LoadControl(IDC_CMB_RELATION            );
   LoadControl(IDC_TXT_IRREVOCABLE         );
   LoadControl(IDC_CMB_IRREVOCABLE         );
   LoadControl(IDC_EDT_PRC_BENEFIT         );
   LoadControl(IDC_TXT_AVAILABLE_PERCENT   );
   LoadControl(IDC_TXT_AVAILABLE           );

   EnableControl (IDC_CMB_DISPOSITION,        bFlag);
   EnableControl (IDC_CMB_JOINT_TYPE,         bFlag);
   EnableControl (IDC_CMB_RELATION,           bFlag);
   EnableControl (IDC_CMB_IRREVOCABLE,        bFlag);
   EnableControl (IDC_EDT_PRC_BENEFIT,        bFlag);

}

//*****************************************************************************
void EntityMaintenanceDlg::OnBtnBenRelation()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnBenRelation()" ) );
   try
   {
      E_COMMANDRETURN eRtn;
      setParameter( ENTPROC::ACCOUNT_NUM, m_dstrAccountNum ); 
      DString dstrEntityId;
      getParent()->getField(this,IFASTBP_PROC::ENTITY_LIST,ifds::EntityId,dstrEntityId,false);
      setParameter( ENTPROC::ENTITY_ID, dstrEntityId ); 
      DString dstrNewAccount;
      getParent()->getField(this, BF::NullContainerId, ENTPROC::PROC_CREATING_ACCOUNT,dstrNewAccount,false);
      setParameter( NASULIT::CREATING_ACCOUNT, dstrNewAccount ); 


//    setParameter( RESPBEN::CURRENT_RESP_BEN, 
//                              getParent()->getCurrentListItemKey( this, ENTITY_LIST ) );
      eRtn = getParentProcess()->invokeProcessFromChild( this, CMD_BPROC_RESPBENREL, PROC_SUPPORT );     
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_CANCEL:
            break;
         case CMD_MODELESS_INPROCESS:

            break;
         default:
            // Display error
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
            break;
      }
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }

}

//******************************************************************************
void EntityMaintenanceDlg::OnBtnWhereUsed() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnWhereUsed()" ) );
   DString last_name;
   DString first_name;

   getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::LastName, last_name );
   getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::FirstName, first_name );
   DString dstrEntityName = last_name.strip() + SEMICOLUMN_STRING + first_name.strip();
   getParent()->setParameter( WHEREUSEDPROC::ENTITY_NAME, dstrEntityName ); 

   getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::BirthLastName, last_name );
   getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::BirthFirstName, first_name );
   dstrEntityName = last_name.strip() + SEMICOLUMN_STRING + first_name.strip();
   getParent()->setParameter( WHEREUSEDPROC::BIRTHENTITY_NAME, dstrEntityName );  
   getParent()->setParameter( WHEREUSEDPROC::CALLER, WHEREUSEDPROC::WHEREUSEDLG);  

   E_COMMANDRETURN rtn = CMD_FAILURE;
   DString dstrEntityId;
   getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityId, dstrEntityId );
   getParent()->setParameter( WHEREUSEDPROC::ENTITY_ID,dstrEntityId ); 

   try
   {
      E_COMMANDRETURN eRtn;
      DString str;

      eRtn = invokeCommand( getParent(), CMD_BPROC_WHEREUSED, PROC_NO_TYPE, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_CANCEL:
            break;
         case CMD_MODELESS_INPROCESS:

            break;
         default:
            // Display error
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
            break;
      }
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }

}

//******************************************************************************
void EntityMaintenanceDlg::OnBtnAdd() 
{
   flg_add_new_item_mode = false; //if we were in add new item mode we switch it off
   AddToListControl( IDC_LV_ENTITIES );
   DString key;
   getParent()->getField( this, ENTPROC::SELECTION_KEY, key );
   LoadListWithSelection( IDC_LV_ENTITIES, key );
   EnableControl( IDOK, true );
   EnableControl( IDC_BTN_SEARCH, true );
   FocusOnControl( IDC_CMB_ID_TYPE );
   flg_add_new_item_mode = true; //this is false until the selection on the entities list goes on another item
   flg_ready_for_background_search = true;
   flg_click_outside_ids_frame = false;
}

//******************************************************************************
void EntityMaintenanceDlg::OnBtnDelete() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnDelete()" ) );

   DString dstrEntityType;
   getParent()->getField(this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityType, dstrEntityType, false);
   
   if (dstrEntityType == I_("05"))
   {
      CString cstrWarn;
      cstrWarn.LoadString(TXT_ANNUITANT_ENTITY_WARN);
      int result = AfxMessageBox(
            cstrWarn,
            MB_YESNO|MB_ICONWARNING|MB_DEFBUTTON2);
      if (result != IDYES)
         return;
   }
   
   int nr = GetList( IDC_LV_ENTITIES )->GetItemCount();
   DeleteFromListControl( IDC_LV_ENTITIES );
   if( nr == 1 ) //that means a dummy entity will be added after deletion of the last entity in the list
   {
      EnableControl( IDC_BTN_SEARCH, true );
      FocusOnControl( IDC_CMB_ID_TYPE );
      flg_add_new_item_mode = true; //this is false until the selection on the entities list goes on another item
      flg_ready_for_background_search = true;
      flg_click_outside_ids_frame = false;
   }
}
//********************************************
void EntityMaintenanceDlg::OnBtnDeathClaim() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnDeathClaim()" ) );

   try
   {
      DString dstrEntityId;
      getParent()->getField(this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityId, dstrEntityId, false);         
      setParameter (ENTITYDLG::ENTITY_ID, dstrEntityId );
      setParameter (ENTPROC::ACCOUNT_NUM, m_dstrAccountNum ); 

      E_COMMANDRETURN eRtn;
      eRtn = invokeCommand ( getParent(), CMD_BPROC_REG_DOCUMENT_LIST, PROC_SUPPORT, true, NULL );

      switch( eRtn )
      {
         case CMD_OK:
         case CMD_CANCEL:
            break;
         case CMD_MODELESS_INPROCESS:
            break;
         default:
            // Display error
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
            break;
       }
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
}

//******************************************************************************
void EntityMaintenanceDlg::OnBtnDeleteId() 
{
      bool bFlag = GetEntityEnable();
	I_CHAR* szMessage=I_( "CallView490" );
      if( bFlag )
      {
		bool bRet = getParent()->send( this,szMessage );
		if(bRet)
		{
			CString WarnMessage;
			WarnMessage.LoadString(TXT_BICCODE_WARN);
			int choice = AfxMessageBox( WarnMessage, MB_YESNO|MB_ICONWARNING|MB_DEFBUTTON2 );
			if( choice == IDYES )
			{
         DeleteFromListControl( IDC_LV_ENTITY_IDS );
      }
}
		else
         DeleteFromListControl( IDC_LV_ENTITY_IDS );
      }
}

//******************************************************************************
void EntityMaintenanceDlg::LoadListWithSelection( UINT listControlID, const DString &strKey )
{
   const DString *key;
   key = &getParent()->getFirstListItemKey( this, IFASTBP_PROC::ENTITY_LIST );

   bool flg_found = false;
   if( *key != NULL_STRING && strKey != NULL_STRING )
   {
      do
      {
         if( *key == strKey )
         {
            flg_found = true;
            break;
         }
      }
      while( *( key = &getParent()->getNextListItemKey( this, IFASTBP_PROC::ENTITY_LIST ) ) != EMPTY_STRING );
   }

   if( flg_found )
      LoadListControl( IDC_LV_ENTITIES, key );
   else
      LoadListControl( IDC_LV_ENTITIES );
}

//******************************************************************************
void EntityMaintenanceDlg::OnBtnAddId() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnAddId" ) );
      bool bFlag = GetEntityEnable();
      if( bFlag )
      {
         AddToListControl( IDC_LV_ENTITY_IDS );
      }
}

//******************************************************************************
void EntityMaintenanceDlg::OnBtnReset() 
{
  // Set the flags back as they were initialized in OnPostInitDialog()
   DString str, str1;
   getParent()->getField( this, ENTPROC::PROC_CREATING_SHAREHOLDER, str, false ); 
   getParent()->getField( this, ENTPROC::PROC_CREATING_ACCOUNT, str1, false ); 
   
   //flg_not_opended_yet = true;
   if( str == Y )
   {
      /*
      DString hasNoDummyRecords;
      getParent()->getField( this, ENTPROC::HAS_NON_DUMMY_RECORDS, hasNoDummyRecords );
      if( hasNoDummyRecords != Y )
      {
         flg_ready_for_background_search = true;
         flg_add_new_item_mode = true;
         flg_click_outside_ids_frame = false;
         EnableControl( IDC_BTN_SEARCH, true );
         FocusOnControl( IDC_CMB_ID_TYPE );
      }
      else
      {
         flg_ready_for_background_search = false;
         flg_add_new_item_mode = false;
         EnableControl( IDC_BTN_SEARCH, false );
      }
     */

      flg_ready_for_background_search = true;
      flg_add_new_item_mode = true;    //this is false until the selection on the entities list goes on another item
      flg_click_outside_ids_frame = false;

      EnableControl( IDC_BTN_SEARCH, GetEntityEnable() );
   
   }
   else
   {
      flg_ready_for_background_search = false;
      flg_add_new_item_mode = false;
      EnableControl( IDC_BTN_SEARCH, false );

   }   

   //We do reset for the selected Entity CBO first (which is not register as container in the process)

   ResetListItem (IDC_LV_ENTITIES);
   LoadTabControl (IDC_TAB_ENTITY_MAINTENANCE);

   if (multipleRiskEnv())
   {
       GetDlgItem( IDC_STC_RISK_LEVEL )->ShowWindow( SW_HIDE );
       GetDlgItem( IDC_CMB_RISK_LEVEL )->ShowWindow( SW_HIDE );
       GetDlgItem( IDC_STC_COUNTRY_OF_EXPOSURE )->ShowWindow( SW_HIDE );
       GetDlgItem( IDC_CMB_COUNTRY_OF_EXPOSURE )->ShowWindow( SW_HIDE );
   }
/*   DString strYears, strMonths;
   getParent()->getField( this, ENTPROC::AGE_YEARS, strYears );
   getParent()->getField( this, ENTPROC::AGE_MONTHS, strMonths );
   CString yrs, mnths, comma;
   yrs.LoadString( TXT_YEARS );
   mnths.LoadString( TXT_MONTHS );
   comma.LoadString( TXT_COMMA );

   DString strAge = strYears + SPACE_STRING + ( LPCTSTR ) yrs + ( LPCTSTR ) comma + SPACE_STRING + strMonths + SPACE_STRING + ( LPCTSTR ) mnths;
   GetDlgItem( IDC_TXT_AGE )->SetWindowText( strAge.c_str() );*/
}

//******************************************************************************
void EntityMaintenanceDlg::OnBtnSearch() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnSearch" ) );

   if (getParent()->performSearch (this, IFASTBP_PROC::BACKGROUND_ON_BTN_SEARCH, SEARCH_START) > WARNING)
   {
      ConditionMessageBox (MYFRAME(), GETCURRENTHIGHESTSEVERITY());
   }
   else
   {   
      DString key;

      getParent()->getField (this, ENTPROC::SELECTION_KEY, key);
      LoadListControl (IDC_LV_ENTITIES, &key);
   }
}

//******************************************************************************
bool EntityMaintenanceDlg::GetOverrideItemString(long lSubstituteId, const DString &ColumnKey, DString &strOut)
{
   if( lSubstituteId == ifds::EntityListViewHeading.getId() )
   {
      if( ColumnKey == ENTITY_TYPE_COLUMN )
      {
         if( m_existAccount == N )
         {
            strOut = NULL_STRING;
            return(true);
         }
      }
      else if( ColumnKey == SEQ_NUMBER_COLUMN )
      {
         if( m_existAccount == N )
         {
            strOut = NULL_STRING;
            return(true);
         }
      }
      else if( ColumnKey == ENTITY_ID_COLUMN )
      {
         getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityId, strOut );
         strOut.stripLeading( '0' );
         return(true);
      }
      else if( ColumnKey == EFFECTIVE_DATE_COLUMN )
      {
         getParent()->getField(this,IFASTBP_PROC::ENTITY_LIST,ifds::EffectiveDate,strOut);
         strOut.strip();
         return(true);        
      }
   }
   else if( lSubstituteId == ifds::EntityIDSHeadingSet.getId() )
   {
      if ( ColumnKey == ENTITY_ID_VALUE_COLUMN )
      {
         DString strIDType;
         getParent()->getField( this, IFASTBP_PROC::ENTITY_IDS_LIST, ifds::IdType, strIDType, false );
	
         if ( strIDType == IDS::CLEARING_PLATFORM )
         {
            getParent()->getField( this, IFASTBP_PROC::ENTITY_IDS_LIST, ifds::IdValue, strOut, true );
         }
         else
         {
            getParent()->getField( this, IFASTBP_PROC::ENTITY_IDS_LIST, ifds::IdValue, strOut, false );
         }
         strOut.strip();
         return(true);
      }
      else
      {
         return ( false );
      }
   }
   return(false);
}

//******************************************************************************
bool EntityMaintenanceDlg::PreOk()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("PreOk" ) );

/*   DString isRespBeneDeleted,
      isLetterRequired;

   getParent()->getField (this, ENTPROC::IS_RESPBENE_DELETED, isRespBeneDeleted);
   getParent()->getField (this, ENTPROC::LETTER_REQUIRED, isLetterRequired);
   
   if (isRespBeneDeleted == I_("Y") && isLetterRequired == I_("N"))
   {
   //should pop-up the question...
      CString generate;

      generate.LoadString (TXT_GENERATE_LETTER_OF_NOTIFICATION);
      int choice = AfxMessageBox (generate, MB_YESNO | MB_ICONQUESTION);

      if (choice == IDYES) //should turn the create rep flag on
      {
         getParent ()->setField (this, ENTPROC::LETTER_REQUIRED, I_("Y"), false);
      }
   }
*/
   bool rtn;
   DString hasNoDummyRecords;
   getParent()->getField (this, ENTPROC::HAS_NON_DUMMY_RECORDS, hasNoDummyRecords);
   
   if (hasNoDummyRecords == Y)
   {
      rtn = true;
      getParent()->getField (this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityId, _entityId);
   }
   else
   {
      ADDCONDITIONFROMFILE (CND::GUI_NO_ENTITY_IN_LIST);
      rtn = false;
   }
   
   return rtn;
}

//******************************************************************************
void EntityMaintenanceDlg::PostOk( bool /*bOkStatus*/ )
{
   setParameter( ENTPROC::ENTITY_ID, _entityId );
   DString key = getParent()->getCurrentListItemKey(this, IFASTBP_PROC::ENTITY_LIST);
   getParent()->setCurrentListItem(this, IFASTBP_PROC::ENTITY_LIST, key);
}

//******************************************************************************
BOOL EntityMaintenanceDlg::PreTranslateMessage(MSG* pMsg) 
{
   // TODO: Add your specialized code here and/or call the base class

   BOOL   IsTranslated = FALSE;
   bool bSearchBtnClicked = false;
   bool bSearchAccel = false;
   bool bEdtIdValueHasFocus = false;

   // make certain accelerator keys are processed correctly
   if( m_hAccel != NULL )
      IsTranslated = ::TranslateAccelerator( m_hWnd, m_hAccel, pMsg );


   if( !IsTranslated )
   {
      // pass message down the chain
      switch( pMsg->message )
      {
         case WM_SYSKEYDOWN:
            {
               CWnd* pWndWithFocus = NULL;
               pWndWithFocus = CWnd::GetFocus();
               if( pWndWithFocus && (pWndWithFocus->GetDlgCtrlID() == IDC_EDT_ID_VALUE) )//the focus is on id value
                  bEdtIdValueHasFocus = true;
               if( pMsg->lParam & 0x20000000 )//ALT is pressed
               {
                  if( ( pMsg->wParam == 83 ) ||  ( pMsg->wParam == 115 ) )//S
                  {
                     bSearchAccel = true;
                     //force the setField for the current field
                     GetDlgItem( IDC_BTN_SEARCH)->SetFocus();
                  }
               }
            }
            break;
         case WM_LBUTTONDOWN:
            {
               CWnd* pWndWithFocus = NULL;
               pWndWithFocus = CWnd::GetFocus();
               if( pWndWithFocus && (pWndWithFocus->GetDlgCtrlID() == IDC_EDT_ID_VALUE) )//the focus is on id value
                  bEdtIdValueHasFocus = true;
               RECT rect1, rect2, rect3;
               GetDlgItem( IDC_CMB_ID_TYPE )->GetClientRect( &rect1 );
               GetDlgItem( IDC_EDT_ID_VALUE )->GetClientRect( &rect2 );
               GetDlgItem( IDC_BTN_SEARCH )->GetClientRect( &rect3 );

               POINT point1, point2, point3;
               POINTSTOPOINT( point1, MAKEPOINTS( pMsg->lParam ) );
               POINTSTOPOINT( point2, MAKEPOINTS( pMsg->lParam ) );
               POINTSTOPOINT( point3, MAKEPOINTS( pMsg->lParam ) );
               HWND hWnd1, hWnd2, hWnd3;
               GetDlgItem( IDC_CMB_ID_TYPE, &hWnd1 );
               GetDlgItem( IDC_EDT_ID_VALUE, &hWnd2 );
               GetDlgItem( IDC_BTN_SEARCH, &hWnd3 );
               ::MapWindowPoints( pMsg->hwnd, hWnd1, &point1, 1 ); 
               ::MapWindowPoints( pMsg->hwnd, hWnd2, &point2, 1 ); 
               ::MapWindowPoints( pMsg->hwnd, hWnd3, &point3, 1 ); 

               if( PtInRect( &rect1, point1 ) || PtInRect( &rect2, point2 ) )
                  flg_click_outside_ids_frame = false;
               else
                  flg_click_outside_ids_frame = true;
               if( PtInRect( &rect3, point3 ) )
                  bSearchBtnClicked = true;
            }
            break;
         case WM_KEYDOWN:
            {
               switch( pMsg->wParam )
               {
                  case 9:
                     flg_tab_pressed = true;
                     break;
                  case 16:
                     flg_shift_pressed = true;
                     break;
                  case VK_F4:
                     {
                        DString strMarket = DSTCommonFunctions::getMarket();
                        if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
                        {
                           if( GetFocus() == GetDlgItem( IDC_EDT_FUND_NUMBER ) )
                              PostMessage( UM_OPENFUNDCLASSLISTDLG );
                           else if( GetFocus() == GetDlgItem( IDC_EDT_FUND_CODE ) )
                              PostMessage( UM_OPENFUNDCLASSLISTDLG );
                           else if( GetFocus() == GetDlgItem( IDC_EDT_CLASS_CODE ) )
                              PostMessage( UM_OPENFUNDCLASSLISTDLG );
                        }
                     }
                     break;
               }
            }
            break;
         case WM_KEYUP:
            {
               switch( pMsg->wParam )
               {
                  case 9:
                     flg_tab_pressed = false;
                     break;
                  case 16:
                     flg_shift_pressed = false;
                  default:
                     break;
               }
            }
            break;

         default:
            break;
      }

      if( bEdtIdValueHasFocus )
      {
         if( bSearchBtnClicked || bSearchAccel )
            getParent()->setField(this, IFASTBP_PROC::ENTITY_IDS_LIST, ifds::DuplicateSINcheck, N );
         else
            getParent()->setField(this, IFASTBP_PROC::ENTITY_IDS_LIST, ifds::DuplicateSINcheck, Y);
      }

      IsTranslated = BaseMainDlg::PreTranslateMessage( pMsg );
   }

   return( IsTranslated );
}

//******************************************************************************
void EntityMaintenanceDlg::OnKillfocusEdtIdValue() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnKillfocusEdtIdValue") );
   if (IsCancelInProgress())
      return;

   CWaitCursor wait;
   if (flg_ready_for_background_search && flg_add_new_item_mode && ( flg_click_outside_ids_frame  || ( !flg_shift_pressed && flg_tab_pressed )))
   {
      flg_tab_pressed = false;
      
      if (getParent()->performSearch (this, IFASTBP_PROC::BACKGROUND_ON_BTN_SEARCH, SEARCH_START) <= WARNING)
      {
         DString key;

         getParent()->getField (this, ENTPROC::SELECTION_KEY, key);
         LoadListControl (IDC_LV_ENTITIES, &key);
      }
      flg_ready_for_background_search = false;
   }
   // This will trigger SIN check for both new entities and existing ones (when SIN has been changed)
   getParent()->setField(this, IFASTBP_PROC::ENTITY_IDS_LIST, ifds::DuplicateSINcheck, Y );
}

//******************************************************************************
void EntityMaintenanceDlg::OnKillfocusCmbIdType() 
{
   if (IsCancelInProgress())
      return;

   CWaitCursor wait;
   if( flg_ready_for_background_search && flg_add_new_item_mode && ( flg_click_outside_ids_frame  || ( flg_shift_pressed && flg_tab_pressed ) ) )
   {
      flg_tab_pressed = false;
      flg_shift_pressed = false;
      if (getParent()->performSearch (this, IFASTBP_PROC::BACKGROUND_ON_BTN_SEARCH, SEARCH_START) <= WARNING)
      {
         DString key;

         getParent()->getField (this, ENTPROC::SELECTION_KEY, key);
         LoadListControl (IDC_LV_ENTITIES, &key);
      }
      flg_ready_for_background_search = false;
   }
}

//******************************************************************************
bool EntityMaintenanceDlg::multipleRiskEnv()
{
    DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession()); 
    return dstWorkSession->multipleRiskEnv();
}

//******************************************************************************
void EntityMaintenanceDlg::OnKillfocusCmbRiskCntryOfExpr()
{
    LoadControl(IDC_EDT_HIGHEST_RISK_LVL);
    LoadControl(IDC_EDT_HIGHEST_RISK_EXPOSURE);
}

//******************************************************************************
void EntityMaintenanceDlg::OnKillfocusCmbRiskType()
{
    LoadControl(IDC_EDT_HIGHEST_RISK_LVL);
    LoadControl(IDC_EDT_HIGHEST_RISK_EXPOSURE);
}

//******************************************************************************
void EntityMaintenanceDlg::OnKillfocusCmbIdValue () 
{
   if (IsCancelInProgress())
      return;

   CWaitCursor wait;
   if( flg_ready_for_background_search && flg_add_new_item_mode && ( flg_click_outside_ids_frame  || ( flg_shift_pressed && flg_tab_pressed ) ) )
   {
      flg_tab_pressed = false;
      flg_shift_pressed = false;
      if (getParent()->performSearch (this, IFASTBP_PROC::BACKGROUND_ON_BTN_SEARCH, SEARCH_START) <= WARNING)
      {
         DString key;

         getParent()->getField (this, ENTPROC::SELECTION_KEY, key);
         LoadListControl (IDC_LV_ENTITIES, &key);
      }
      flg_ready_for_background_search = false;
   }
}

//******************************************************************************
void EntityMaintenanceDlg::OnKillfocusCmbEntityType() 
{
   // TODO: Add your control notification handler code here
   DString key = getParent()->getCurrentListItemKey( this, IFASTBP_PROC::ENTITY_LIST );
   LoadListWithSelection( IDC_LV_ENTITIES, key );
   //RefreshListItem( IDC_LV_ENTITIES );
}

//******************************************************************************
bool EntityMaintenanceDlg::GetDataForControl( UINT controlID, DString &strValueOut, bool bFormatted, int index ) const
{
   strValueOut = NULL_STRING;
   CString str;

   switch( controlID )
   {
      case IDC_TXT_RELATIONSHIP_TO_OWNER:
         if( flg_joint_controls )
            str.LoadString( TXT_DISPOSITION );
         else
            str.LoadString( TXT_RELATIONSHIP_TO_OWNER );
         strValueOut = ( LPCTSTR ) str;
         break;

      case IDC_TXT_PERCENT_OF_BENEFIT:
         if( flg_joint_controls )
            str.LoadString( TXT_JOINT_TYPE );
         else
            str.LoadString( TXT_PERCENT_OF_BENEFIT );
         strValueOut = ( LPCTSTR ) str;
         break;

      case IDC_FRM_BENEFICIARY:
         if( flg_joint_controls )
            str.LoadString( TXT_FRM_JOINT );
         else
            str.LoadString( TXT_FRM_BENEFICIARY );
         strValueOut = ( LPCTSTR ) str;
         break;

      case IDC_TXT_AVAILABLE:
         getParent()->getField( this, ENTPROC::PERCENT_AVAILABLE, strValueOut );
         break;

      case IDC_TXT_AGE:
         {
            DString strYears, strMonths;
            getParent()->getField( this, ENTPROC::AGE_YEARS, strYears );
            getParent()->getField( this, ENTPROC::AGE_MONTHS, strMonths );
            CString yrs, mnths, comma;
            yrs.LoadString( TXT_YEARS );
            mnths.LoadString( TXT_MONTHS );
            comma.LoadString( TXT_COMMA );
            if( !strYears.empty() && strYears.asInteger() >= 0 )
               strValueOut = strYears + SPACE_STRING + ( LPCTSTR ) yrs + ( LPCTSTR ) comma + SPACE_STRING + strMonths + SPACE_STRING + ( LPCTSTR ) mnths;
            else
               strValueOut = NULL_STRING;
         }
         break;

      default :
         return(false);
   }
   strValueOut.strip();
   return(true);
}

//******************************************************************************
void EntityMaintenanceDlg::OnAccelEntity() 
{
   FocusOnControl( IDC_LV_ENTITIES );
}

//******************************************************************************
void EntityMaintenanceDlg::OnBtnEntityDetails() 
{
   // TODO: Add your control notification handler code here

   setCsiParameter( DcCsiParameters::ACCOUNT_NUMBER, DStringA(m_dstrAccountNum) );
   executeCsiProcess( DcCsiProcesses::ACCOUNT_INFORMATION );

}

//*************************************************************
void EntityMaintenanceDlg::DisplayRespBeneficiaryControls ()
{
   DString dstrEntityType;
   
   getParent()->getField (this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityType, dstrEntityType, false);
   dstrEntityType.strip();
   bool bShowRespControl = dstrEntityType == RESP_BENEFICIARY;
   int iShowRespLabel = bShowRespControl ? SW_SHOW : SW_HIDE;

   bool bIsRES2Client = 
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->isRES2Client();

   hideAllExistingRESPControls ();
   if (bShowRespControl)
   {
      if (bIsRES2Client)
      {
         addTabPage (TXT_PAGE_BENEFICIARY);
         addTabPage (TXT_PAGE_RELATIONSHIPS);
      }
      else
      {
         removeTabPage (TXT_PAGE_BENEFICIARY);
         removeTabPage (TXT_PAGE_RELATIONSHIPS);

         GetDlgItem( IDC_FRM_BENEFICIARY )->ShowWindow( SW_SHOW );
         DString strTitle = DSTCommonFunctions::getDescription( RESP_BENEFICIARY_TITLE, ifds::BeneficiaryTitleDisplay );
         GetDlgItem( IDC_FRM_BENEFICIARY )->SetWindowText( strTitle.c_str() );

         EnableControl( IDC_FRM_BENEFICIARY, bShowRespControl );
         CString cstrRelOwn;
		 cstrRelOwn.LoadString(TXT_RELATIONSHIP_TO_OWNER);
         GetDlgItem( IDC_TXT_RELATIONSHIP_TO_OWNER )->SetWindowText (cstrRelOwn);
         GetDlgItem( IDC_TXT_RELATIONSHIP_TO_OWNER )->ShowWindow( iShowRespLabel );
         GetDlgItem( IDC_TXT_RELATIONSHIP_TO_OWNER )->EnableWindow( iShowRespLabel );
         ReInitControl( IDC_CMB_RELATION,IFASTBP_PROC::ENTITY_LIST,ifds::HRDCRelateCode,CTRLFLAG_INITCOMBO_BY_SUB_LIST ); 
         ConnectControlToData( IDC_CMB_RELATION, true,true );

         GetDlgItem( IDC_TXT_TAX_JURISD )->ShowWindow( SW_SHOW );

         //ShowControl( IDC_CMB_RELATION, bShowRespControl );
         EnableControl( IDC_CMB_RELATION, bShowRespControl );
         //LoadControl( IDC_CMB_RELATION );

         DString strMarket = DSTCommonFunctions::getMarket();
         if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
         {
            ConnectControlToData( IDC_EDT_LETTER_DATE, true );
            ConnectControlToData( IDC_EDT_PRINTED, true );
            ConnectControlToData( IDC_CMB_REASON, true );
            ConnectControlToData( IDC_CMB_RESP_TAX_JURISD, true );
            GetDlgItem( IDC_TXT_LETTER_DATE )->ShowWindow( SW_SHOW );
            GetDlgItem( IDC_EDT_LETTER_DATE )->ShowWindow( SW_SHOW );
            GetDlgItem( IDC_TXT_PRINTED )->ShowWindow( SW_SHOW);
            GetDlgItem( IDC_EDT_PRINTED )->ShowWindow( SW_SHOW );
            GetDlgItem( IDC_TXT_REASON )->ShowWindow( SW_SHOW );
            GetDlgItem( IDC_CMB_REASON )->ShowWindow( SW_SHOW );
            GetDlgItem( IDC_TXT_TAX_JURISD )->ShowWindow( SW_SHOW );
            GetDlgItem( IDC_CMB_RESP_TAX_JURISD )->ShowWindow( SW_SHOW );
            GetDlgItem( IDC_BTN_BEN_RELATION )->ShowWindow( SW_SHOW );
            
            LoadControl( IDC_CMB_REASON );
         }
      }
   }
   else
   {
      GetDlgItem( IDC_FRM_BENEFICIARY )->ShowWindow( SW_SHOW );
      removeTabPage (TXT_PAGE_BENEFICIARY);
      removeTabPage (TXT_PAGE_RELATIONSHIPS);

      bool bEnable = (dstrEntityType == ENTITY_TYPE_PRIMARY_BENEF) || 
                     (dstrEntityType == ENTITY_TYPE_SECONDARY_BENEF || dstrEntityType == ENTITY_TYPE_SUCCESSOR );
      ReInitControl( IDC_CMB_RELATION,IFASTBP_PROC::ENTITY_LIST,ifds::RelateCode,CTRLFLAG_INITCOMBO_BY_SUB_LIST );
      ConnectControlToData (IDC_CMB_RELATION, bEnable);
      ConnectControlToData(IDC_EDT_PRC_BENEFIT,bEnable );

      if (bEnable)
      {
         GetDlgItem( IDC_TXT_RELATIONSHIP_TO_OWNER )->ShowWindow( SW_SHOW );
         GetDlgItem( IDC_CMB_RELATION )->ShowWindow( SW_SHOW );
         GetDlgItem( IDC_EDT_PRC_BENEFIT )->ShowWindow( SW_SHOW );
      }

      LoadControl( IDC_CMB_RELATION );
      LoadControl( IDC_EDT_PRC_BENEFIT );
   }

   //LoadControl( IDC_CMB_RELATION );
   
   //DString strMarket = DSTCommonFunctions::getMarket();
   //if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
   //{
   //      //ShowControl( IDC_EDT_LETTER_DATE, bShowRespControl );
   //      //ShowControl( IDC_EDT_PRINTED, bShowRespControl );

   //   ConnectControlToData( IDC_EDT_LETTER_DATE, bShowRespControl,true );
   //   ConnectControlToData( IDC_EDT_PRINTED, bShowRespControl,true );
   //   LoadControl( IDC_EDT_LETTER_DATE );
   //   LoadControl( IDC_EDT_PRINTED );

   //   GetDlgItem( IDC_CMB_REASON )->ShowWindow( iShowRespLabel );
   //   GetDlgItem( IDC_CMB_RESP_TAX_JURISD )->ShowWindow( iShowRespLabel );
   //   GetDlgItem( IDC_TXT_TAX_JURISD )->ShowWindow( iShowRespLabel );
   //   GetDlgItem( IDC_TXT_LETTER_DATE )->ShowWindow( iShowRespLabel );    
   //   GetDlgItem( IDC_TXT_PRINTED )->ShowWindow( iShowRespLabel);
   //   GetDlgItem( IDC_TXT_REASON )->ShowWindow( iShowRespLabel );
   //   GetDlgItem( IDC_BTN_BEN_RELATION )->ShowWindow( iShowRespLabel );
   //}
}
//***************************************************************************** 
void EntityMaintenanceDlg::DisplayRegistrationAgentControls()
{
   DString strMarket = DSTCommonFunctions::getMarket();
   if( strMarket == MARKET_IDS::LUXEMBOURG )
   {
      bool bShowRegistrationAgent = false;
   
      DString dstrEntityType;
      getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityType, dstrEntityType, false );
      dstrEntityType.strip();
      int iShowRegistrationAgent = dstrEntityType == REGISTRATION_AGENT_ENTITY_TYPE ? SW_SHOW : SW_HIDE;

      ConnectControlToData(IDC_EDT_REG_AGENT_ACCT_NO, dstrEntityType == REGISTRATION_AGENT_ENTITY_TYPE);

      GetDlgItem( IDC_EDT_REG_AGENT_ACCT_NO )->ShowWindow( iShowRegistrationAgent );
      GetDlgItem( IDC_TXT_REG_AGENT_ACCT_NUM )->ShowWindow( iShowRegistrationAgent );
   }

}

//***************************************************************************** 
void EntityMaintenanceDlg::DisplayEscrowControls()
{
   DString dstrEntityType;
   getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityType, dstrEntityType, false );
   dstrEntityType.strip();
   bool bShowAssignee = false;
   DString dstrAssignee;

   DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());   
   if ( dstWorkSession->getOption( ifds::AssigneeScreen, dstrAssignee, getParent()->getDataGroupId(), false ) <= WARNING 
        && dstrAssignee.strip().upperCase() == Y 
        && dstrEntityType == ASSIGNEE_ENTITY_TYPE )
   {
      bShowAssignee = true;
   }

   bool bShowEscrowControl = ( dstrEntityType == ESCROW_ENTITY_TYPE || bShowAssignee );
   int iShowEscrowLabel = bShowEscrowControl ? SW_SHOW : SW_HIDE;
   DString strTitle;
   if( bShowEscrowControl )
   {
      if ( dstrEntityType == ESCROW_ENTITY_TYPE )
      {
         strTitle = DSTCommonFunctions::getDescription( ESCROW_TITLE, ifds::BeneficiaryTitleDisplay );
      }
      else if ( dstrEntityType == ASSIGNEE_ENTITY_TYPE )
      {
         strTitle = DSTCommonFunctions::getDescription( ASSIGNEE_TITLE, ifds::BeneficiaryTitleDisplay );
      }
      GetDlgItem( IDC_FRM_BENEFICIARY )->SetWindowText( strTitle.c_str() );
      
      GetDlgItem( IDC_FRM_BENEFICIARY )->EnableWindow( bShowEscrowControl );
   }

   DString strMarket = DSTCommonFunctions::getMarket();
   if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
   {

      ConnectControlToData(IDC_EDT_FUND_NUMBER,bShowEscrowControl,true );
      ConnectControlToData(IDC_EDT_FUND_CODE,bShowEscrowControl,true );
      ConnectControlToData(IDC_EDT_CLASS_CODE,bShowEscrowControl,true );
      ConnectControlToData(IDC_EDT_AMOUNT_ASSIGN,bShowEscrowControl,true );
      ConnectControlToData(IDC_CMB_ESC_REASON,bShowEscrowControl,true );
      ConnectControlToData(IDC_CMB_AMOUNT_TYPE,bShowEscrowControl,true );
      ConnectControlToData(IDC_DTP_ESC_EFFECTIVE,bShowEscrowControl,true );
      ConnectControlToData(IDC_DTP_ESC_STOP,bShowEscrowControl,true );
      //IN2780013 - SOC Loan Number and Loan Type
      ConnectControlToData(IDC_CMB_LOAN_TYPE,bShowEscrowControl,true );
      ConnectControlToData(IDC_EDT_LOAN_NUMBER,bShowEscrowControl,true );

      if( bShowEscrowControl )
      {   
         LoadControl( IDC_EDT_FUND_NUMBER );
         LoadControl( IDC_EDT_FUND_CODE );
         LoadControl( IDC_EDT_CLASS_CODE );
         LoadControl( IDC_EDT_AMOUNT_ASSIGN );
         LoadControl( IDC_CMB_ESC_REASON );
         LoadControl( IDC_CMB_AMOUNT_TYPE );
         LoadControl( IDC_DTP_ESC_EFFECTIVE );
         LoadControl( IDC_DTP_ESC_STOP );
         //IN2780013 - SOC Loan Number and Loan Type
         LoadControl( IDC_CMB_LOAN_TYPE );
         LoadControl( IDC_EDT_LOAN_NUMBER );
      }

    // we have to disconnect controls before hiding control 
/*
      ShowControl( IDC_EDT_FUND_NUMBER, bShowEscrowControl );
      ShowControl( IDC_EDT_FUND_CODE, bShowEscrowControl );
      ShowControl( IDC_EDT_CLASS_CODE, bShowEscrowControl );
      ShowControl( IDC_EDT_AMOUNT_ASSIGN, bShowEscrowControl );
      ShowControl( IDC_CMB_AMOUNT_TYPE, bShowEscrowControl );
      ShowControl( IDC_CMB_ESC_REASON, bShowEscrowControl );
      ShowControl( IDC_DTP_ESC_EFFECTIVE, bShowEscrowControl );
      ShowControl( IDC_DTP_ESC_STOP, bShowEscrowControl );
*/
      GetDlgItem( IDC_TXT_FUND )->ShowWindow( iShowEscrowLabel );
      GetDlgItem( IDC_TXT_CLASS_CODE )->ShowWindow( iShowEscrowLabel );
      GetDlgItem( IDC_TXT_AMOUNT_ASSIGN )->ShowWindow( iShowEscrowLabel );
      GetDlgItem( IDC_TXT_AMOUNT_TYPE )->ShowWindow( iShowEscrowLabel );
      GetDlgItem( IDC_TXT__ESC_REASON )->ShowWindow( iShowEscrowLabel );
      GetDlgItem( IDC_TXT_ESC_EFFECTIVE )->ShowWindow( iShowEscrowLabel );
      GetDlgItem( IDC_TXT_ESC_STOP )->ShowWindow( iShowEscrowLabel );
      //IN2780013 - SOC Loan Number and Loan Type
      GetDlgItem( IDC_TXT_LOAN_TYPE )->ShowWindow( iShowEscrowLabel );
      GetDlgItem( IDC_TXT_LOAN_NUMBER )->ShowWindow( iShowEscrowLabel );
   }
}

//******************************************************************************
void EntityMaintenanceDlg::DisplayBeneficiaryControls()
{
   int iShowBenLabel = SW_SHOW;
   DString dstrEntityType, dstrAcctType;
   getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityType, dstrEntityType, false );
   dstrEntityType.strip();
   getParent()->getField( this, ENTPROC::ACCOUNT_TYPE_FIELD, dstrAcctType, false ); 
               
   bool bEnableBenControl = (dstrEntityType == ENTITY_TYPE_PRIMARY_BENEF) || 
                            (dstrEntityType == ENTITY_TYPE_SECONDARY_BENEF) || 
                            (dstrEntityType == ENTITY_TYPE_SUCCESSOR);
   if (  !bEnableBenControl                     ||
         dstrEntityType == ESCROW_ENTITY_TYPE   || 
         dstrEntityType == RESP_BENEFICIARY     ||
         dstrEntityType == ASSIGNEE_ENTITY_TYPE ||
        (dstrAcctType   == JOINT_ACCOUNT_TYPE && dstrEntityType == ACCOUNT_OWNER_ENTITY_TYPE) 
      )
   {
      iShowBenLabel = SW_HIDE;
   }

   bool bFlag = GetEntityEnable();

   bFlag = bFlag && bEnableBenControl;

   bool bShowControl = (iShowBenLabel == SW_SHOW); 
   if( bShowControl )
   {
      ReInitControl( IDC_CMB_RELATION,IFASTBP_PROC::ENTITY_LIST,ifds::RelateCode,CTRLFLAG_INITCOMBO_BY_SUB_LIST );

      DString strTitle = DSTCommonFunctions::getDescription( BENEFICIARY_TITLE, ifds::BeneficiaryTitleDisplay );
      GetDlgItem( IDC_FRM_BENEFICIARY )->SetWindowText( strTitle.c_str() );

      EnableControl( IDC_FRM_BENEFICIARY, bEnableBenControl );
      LoadControl( IDC_CMB_RELATION );
   }

   ConnectControlToData( IDC_CMB_RELATION, bEnableBenControl,true );
   LoadControl( IDC_CMB_RELATION );

   GetDlgItem( IDC_FRM_BENEFICIARY )->EnableWindow( bEnableBenControl );

   ShowControl( IDC_CMB_RELATION, bShowControl );


   EnableControl( IDC_CMB_RELATION, bFlag );
   GetDlgItem( IDC_TXT_RELATIONSHIP_TO_OWNER )->ShowWindow( iShowBenLabel );
   GetDlgItem( IDC_TXT_RELATIONSHIP_TO_OWNER )->EnableWindow( bEnableBenControl );
   ConnectControlToData(IDC_TXT_RELATIONSHIP_TO_OWNER, bShowControl, true);
   LoadControl (IDC_TXT_RELATIONSHIP_TO_OWNER );

   if( dstrEntityType != ENTITY_TYPE_SUCCESSOR )
   {
      ConnectControlToData(IDC_CMB_IRREVOCABLE,bShowControl,true );
      ConnectControlToData(IDC_EDT_PRC_BENEFIT,bShowControl,true );
      ConnectControlToData(IDC_TXT_AVAILABLE,bShowControl,true );
      if( bShowControl )
      {
         LoadControl( IDC_CMB_IRREVOCABLE );
         LoadControl( IDC_EDT_PRC_BENEFIT );
         LoadControl( IDC_TXT_AVAILABLE );      
      }      
/*      
      ShowControl( IDC_CMB_IRREVOCABLE, bShowControl );
      ShowControl( IDC_EDT_PRC_BENEFIT, bShowControl );
      ShowControl( IDC_TXT_AVAILABLE, bShowControl );
*/
      DString strMarket = DSTCommonFunctions::getMarket();
      if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
      {
         ConnectControlToData(IDC_CMB_TAX_JURISDICTION,bShowControl,true );

         if( bShowControl )
         {
            LoadControl( IDC_CMB_TAX_JURISDICTION );
         }
//       ShowControl( IDC_CMB_TAX_JURISDICTION, bShowControl );
         EnableControl( IDC_CMB_TAX_JURISDICTION, bFlag );
         GetDlgItem( IDC_TXT_TAX_JURISDICTION )->ShowWindow( iShowBenLabel );
         GetDlgItem( IDC_TXT_TAX_JURISDICTION )->EnableWindow( bEnableBenControl ); 

      }
      EnableControl( IDC_CMB_IRREVOCABLE, bFlag );
      EnableControl( IDC_EDT_PRC_BENEFIT, bFlag );
      EnableControl( IDC_TXT_AVAILABLE, bFlag );

      GetDlgItem( IDC_TXT_PERCENT_OF_BENEFIT )->ShowWindow( iShowBenLabel );
      GetDlgItem( IDC_TXT_IRREVOCABLE )->ShowWindow( iShowBenLabel );
      GetDlgItem( IDC_TXT_AVAILABLE_PERCENT )->ShowWindow( iShowBenLabel );
      ConnectControlToData (IDC_TXT_PERCENT_OF_BENEFIT, bShowControl, true);
      LoadControl (IDC_TXT_PERCENT_OF_BENEFIT );

      GetDlgItem( IDC_TXT_PERCENT_OF_BENEFIT )->EnableWindow( bEnableBenControl );
      GetDlgItem( IDC_TXT_IRREVOCABLE )->EnableWindow( bEnableBenControl );
      GetDlgItem( IDC_TXT_AVAILABLE_PERCENT )->EnableWindow( bEnableBenControl );
   }
}

//******************************************************************************************
void EntityMaintenanceDlg::DisplayJointInfomationControls()
{
   DString dstrAcctType, 
      dstrEntityType;

   getParent()->getField (this, ENTPROC::ACCOUNT_TYPE_FIELD, 
      dstrAcctType, false); 
   getParent()->getField (this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityType, 
      dstrEntityType, false);   
/*   flg_joint_controls = 
      m_existAccount == Y && 
      dstrAcctType == JOINT_ACCOUNT_TYPE && 
      dstrEntityType == ACCOUNT_OWNER_ENTITY_TYPE;
*/

      bool bFlag = GetEntityEnable();

   if (flg_joint_controls)
   {

      bFlag = flg_joint_controls && bFlag;

      DString strTitle = 
         DSTCommonFunctions::getDescription (JOINT_INFORMATION_TITLE, 
         ifds::BeneficiaryTitleDisplay);

      GetDlgItem (IDC_FRM_BENEFICIARY)->SetWindowText (strTitle.c_str());
      EnableControl (IDC_FRM_BENEFICIARY, flg_joint_controls);
      ConnectControlToData (IDC_TXT_RELATIONSHIP_TO_OWNER, flg_joint_controls, true);
      //ShowControl( IDC_TXT_RELATIONSHIP_TO_OWNER, flg_joint_controls );
      EnableControl (IDC_TXT_RELATIONSHIP_TO_OWNER, flg_joint_controls);
      LoadControl (IDC_TXT_RELATIONSHIP_TO_OWNER);

      ConnectControlToData (IDC_TXT_PERCENT_OF_BENEFIT, flg_joint_controls, true);
      EnableControl (IDC_TXT_PERCENT_OF_BENEFIT, flg_joint_controls);
      LoadControl (IDC_TXT_PERCENT_OF_BENEFIT);

   }
   ConnectControlToData (IDC_CMB_DISPOSITION, flg_joint_controls, true);
   ConnectControlToData (IDC_CMB_JOINT_TYPE, flg_joint_controls, true);

   LoadControl (IDC_CMB_DISPOSITION);
   LoadControl (IDC_CMB_JOINT_TYPE);

   EnableControl (IDC_CMB_DISPOSITION, bFlag);
   EnableControl (IDC_CMB_JOINT_TYPE, bFlag);

   //ShowControl (IDC_CMB_DISPOSITION, true);
   //ShowControl (IDC_CMB_JOINT_TYPE, true);
}

//*********************************************************************************
void EntityMaintenanceDlg::ShowOverLappedPart ()
{
   DString entityType,
      acctType;
   getParent()->getField (this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityType, 
      entityType, false);   
   getParent()->getField( this, ENTPROC::ACCOUNT_TYPE_FIELD, acctType, false ); 

   flg_joint_controls = 
      m_existAccount == Y && 
      acctType == JOINT_ACCOUNT_TYPE && 
      entityType == ACCOUNT_OWNER_ENTITY_TYPE;

   DisplayBeneficiaryControls ();
   DisplayRespBeneficiaryControls ();
   DisplayEscrowControls ();
   DisplayJointInfomationControls ();
   DisplayRegistrationAgentControls();

   if( DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA )
   {
	   DisplayRDSPControls ();
   }
}

void EntityMaintenanceDlg::UpdateDetailsVerifyStat()
{
	DString strMarket = DSTCommonFunctions::getMarket();
	if( strMarket == MARKET_IDS::LUXEMBOURG ) 
	{
		LoadControl(IDC_CMB_DETAILS_VERIFY_STAT);
	}
}
//**********************************************************************************
void EntityMaintenanceDlg::ControlUpdated (UINT controlID, const DString &dstrValue)
{
   DString str;

   bool bIsRES2Client = 
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->isRES2Client();

   switch( controlID )
   {
      case IDC_CMB_ENTITY_TYPE:
      {
         DSTTabCtrl* pTabCtrl = GetTabCtrl (IDC_TAB_ENTITY_MAINTENANCE);

         ShowOverLappedPart();
         //LoadControl (IDC_CMB_ENTITY_TYPE);
         LoadControl (IDC_TXT_AVAILABLE);
         DString dstrEntityType;
         getParent()->getField (this, ifds::EntityType, dstrEntityType, false);

         bool bFlag = GetEntityEnable();

         DString strMarket = DSTCommonFunctions::getMarket();
         if( strMarket == MARKET_IDS::CANADA ) 
         {
            if( dstrEntityType == ENTITY_TYPE_ACC_OWNER)
            {
               GetDlgItem( IDC_TXT_SPOUSAL )->ShowWindow( true );
               GetDlgItem( IDC_TXT_SPOUSAL )->EnableWindow( true );
               GetDlgItem( IDC_CMB_SPOUSAL )->ShowWindow( true );
               EnableControl(IDC_CMB_SPOUSAL, bFlag);
            }
            else
            {
               GetDlgItem( IDC_TXT_SPOUSAL )->EnableWindow( false );
               GetDlgItem( IDC_TXT_SPOUSAL )->ShowWindow( false );
               EnableControl(IDC_CMB_SPOUSAL, false);
               GetDlgItem( IDC_CMB_SPOUSAL )->ShowWindow( false );
            }
         }

         {
            DString str, str1;
            getParent()->getField( this, ENTPROC::PROC_CREATING_SHAREHOLDER, str, false ); 
            getParent()->getField( this, ENTPROC::PROC_CREATING_ACCOUNT, str1, false );

            if ( flg_ready_for_background_search == false )
            {
               if (str == I_("Y") || str1 == I_("Y"))
               {
                  flg_ready_for_background_search = true;
               }
            }
         }

         if ( dstrEntityType == ENTITY_TYPE_CLEARING_PLATFORM )
         {
            ConnectControlToData (IDC_CMB_EMPLOYEECLASS, true);
            LoadControl (IDC_CMB_EMPLOYEECLASS);
         }

         if (dstrEntityType == RESP_BENEFICIARY)
         {
            if (bIsRES2Client)
            {
               ConnectControlToData( IDC_CMB_RESP2_PARENT_LEGAL_GUARD, true );
               LoadControl( IDC_CMB_RESP2_PARENT_LEGAL_GUARD );
               ConnectControlToData( IDC_CMB_RESP2_DESIGNATED_INST, true );
               LoadControl( IDC_CMB_RESP2_DESIGNATED_INST );
               ConnectControlToData( IDC_CMB_RESP2_PRIM_CARE_GIVER, true );
               LoadControl( IDC_CMB_RESP2_PRIM_CARE_GIVER );

               GetDlgItem (IDC_CHK_UPDATE_SHAREHOLDER_TAX_JURIS)->EnableWindow( false );
            }
         }
		 
		 DString dstrCRSEntityList;
		 DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
		 dstWorkSession->getOption (ifds::CRSEntityList, dstrCRSEntityList, getParent()->getDataGroupId());		
		
		 if( dstrEntityType != ACCOUNT_OWNER_ENTITY_TYPE && (DSTCommonFunctions::codeInList( dstrEntityType, dstrCRSEntityList) || dstrCRSEntityList == APPLICABLE_TO_ALL || dstrEntityType == RELATED_PARTY_AML) ) 
         {
             GetDlgItem(IDC_TXT_ASSOCIATED_ENTITY)->ShowWindow(SW_SHOW);
             GetDlgItem(IDC_CMB_ASSOCIATED_ENTITY)->ShowWindow(SW_SHOW);
             GetDlgItem(IDC_TXT_PERCENT_OWNERSHIP)->ShowWindow(SW_SHOW);
             GetDlgItem(IDC_EDT_PERCENT_OWNERSHIP)->ShowWindow(SW_SHOW);
             GetDlgItem(IDC_CMB_ENTITY_ASSOCIATION)->ShowWindow(SW_SHOW);
             GetDlgItem(IDC_TXT_ENTITY_ASSOCIATION)->ShowWindow(SW_SHOW);
			 // Allow only number
             ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_PERCENT_OWNERSHIP) ) )->SetAllowedChars(I_("0123456789")); // do not allow precision
             ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_PERCENT_OWNERSHIP ) ) )->SetMaxCharNum (10);

             ConnectControlToData(IDC_CMB_ASSOCIATED_ENTITY, true);
             ConnectControlToData(IDC_EDT_PERCENT_OWNERSHIP, true);
             ConnectControlToData(IDC_CMB_ENTITY_ASSOCIATION, true);

             LoadControl(IDC_CMB_ASSOCIATED_ENTITY);
             LoadControl(IDC_EDT_PERCENT_OWNERSHIP);
             LoadControl(IDC_CMB_ENTITY_ASSOCIATION);
         }
         else
         {
             GetDlgItem(IDC_TXT_ASSOCIATED_ENTITY)->ShowWindow(SW_HIDE);
             GetDlgItem(IDC_CMB_ASSOCIATED_ENTITY)->ShowWindow(SW_HIDE);
             GetDlgItem(IDC_TXT_PERCENT_OWNERSHIP)->ShowWindow(SW_HIDE);
             GetDlgItem(IDC_EDT_PERCENT_OWNERSHIP)->ShowWindow(SW_HIDE);
             GetDlgItem(IDC_CMB_ENTITY_ASSOCIATION)->ShowWindow(SW_HIDE);
             GetDlgItem(IDC_TXT_ENTITY_ASSOCIATION)->ShowWindow(SW_HIDE);

             ConnectControlToData(IDC_CMB_ASSOCIATED_ENTITY, false);
             ConnectControlToData(IDC_EDT_PERCENT_OWNERSHIP, false);
         }

         DString dstrEmployeeClass;
         getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::EmployeeClass, dstrEmployeeClass, false );
         updateEmployeeClass (dstrEmployeeClass);

         bool bIsEntityNew = false;
         Entity* pEntity (NULL);
         DString entityId;
         DSTCWorkSession *pDSTCWorkSession = 
             dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());   

         getParent()->getField (this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityId, entityId, false);
         entityId.stripLeading( '0' );
         if (!entityId.empty())
         {
             if ( pDSTCWorkSession->getEntity (getDataGroupId(), entityId, pEntity) <= WARNING &&
                  pEntity)
             {
                 bIsEntityNew = pEntity->isNew ();
             }
         }

         if ( !hasReadPermission(UAF::ENTITY_TAX_JURIS_HISTORY ) ){
             GetDlgItem (IDC_BTN_TAX_JURIS_HISTORY)->EnableWindow (false);
         }
         else{
             bool bEnableJurisHistory = (bIsEntityNew) ? FALSE : TRUE;
             GetDlgItem (IDC_BTN_TAX_JURIS_HISTORY)->EnableWindow (bEnableJurisHistory);
         }

         if (pTabCtrl != NULL)
         {
            if ( strMarket == MARKET_IDS::CANADA )
            {
               if( (dstrEntityType != ENTITY_TYPE_PRIMARY_BENEF) &&
                  (dstrEntityType != ENTITY_TYPE_SECONDARY_BENEF) &&
                  (dstrEntityType != RESP_BENEFICIARY))
               {
                  pTabCtrl->removeControlFromPage (IDC_STC_DATE_DEATH_SETTLEMENT, TXT_PAGE_DETAILS );
                  pTabCtrl->removeControlFromPage (IDC_DTP_DEATH_DATE_SETTLEMENT, TXT_PAGE_DETAILS );
                  GetDlgItem( IDC_STC_DATE_DEATH_SETTLEMENT )->ShowWindow( SW_HIDE );
                  GetDlgItem( IDC_DTP_DEATH_DATE_SETTLEMENT )->ShowWindow( SW_HIDE );

               }
               else
               {
                  pTabCtrl->registerControl (IDC_STC_DATE_DEATH_SETTLEMENT, TXT_PAGE_DETAILS);
                  pTabCtrl->registerControl (IDC_DTP_DEATH_DATE_SETTLEMENT, TXT_PAGE_DETAILS);
                  GetDlgItem( IDC_STC_DATE_DEATH_SETTLEMENT )->ShowWindow( SW_SHOW );
                  GetDlgItem( IDC_DTP_DEATH_DATE_SETTLEMENT )->ShowWindow( SW_SHOW );
               }
            }

            pTabCtrl->SelectTab (TXT_PAGE_DETAILS,true);
         }

         LoadTabControl (IDC_TAB_ENTITY_MAINTENANCE);

         if (multipleRiskEnv())
         {
             GetDlgItem( IDC_STC_RISK_LEVEL )->ShowWindow( SW_HIDE );
             GetDlgItem( IDC_CMB_RISK_LEVEL )->ShowWindow( SW_HIDE );
             GetDlgItem( IDC_STC_COUNTRY_OF_EXPOSURE )->ShowWindow( SW_HIDE );
             GetDlgItem( IDC_CMB_COUNTRY_OF_EXPOSURE )->ShowWindow( SW_HIDE );
         }

		 if( strMarket == MARKET_IDS::CANADA )
		 {
			 DisplayRDSPControls();
		 }
      }
         break;
      case IDC_EDT_FUND_NUMBER:
         LoadControl(IDC_EDT_FUND_CODE);
         LoadControl(IDC_EDT_CLASS_CODE);
         break;
      case IDC_EDT_FUND_CODE:
         LoadControl(IDC_EDT_FUND_NUMBER);
         LoadControl(IDC_EDT_CLASS_CODE);
         break;
      case IDC_EDT_CLASS_CODE:
         LoadControl(IDC_EDT_FUND_NUMBER);
         LoadControl(IDC_EDT_FUND_CODE);
         break;
      case IDC_EDT_AMOUNT_ASSIGN:
         LoadControl( IDC_EDT_AMOUNT_ASSIGN );
         break;
      case IDC_CMB_ID_TYPE:
         if (dstrValue == SIN || dstrValue == BUSINESS_NUMBER)
         {
            GetDlgItem ( IDC_CMB_ID_VALUE )->ShowWindow ( false );
            GetDlgItem ( IDC_EDT_ID_VALUE )->ShowWindow ( true ); 
            GetDlgItem ( IDC_EDT_ID_VALUE )->EnableWindow ( true );
            ConnectControlsToData (ENTITY_IDS_CONTROLS::EDIT_CNTRL, true );
            ConnectControlsToData (ENTITY_IDS_CONTROLS::COMBO_CNTRL,false );
            ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_ID_VALUE ) ) )->SetMaxCharNum (dstrValue == SIN ? 9 : 15);
            if (dstrValue == SIN)
            {
               ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_ID_VALUE ) ) )->SetAllowedChars(I_("0123456789"));
            }
            else if (dstrValue == BUSINESS_NUMBER)
            {
               ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_ID_VALUE ) ) )->SetAllowedChars(CHARACTERS);
            }
            LoadControls (ENTITY_IDS_CONTROLS::EDIT_CNTRL);
         }
         else if  (dstrValue == TAX_ID_NUM)
         {
            GetDlgItem ( IDC_CMB_ID_VALUE )->ShowWindow ( false );
            GetDlgItem ( IDC_EDT_ID_VALUE )->ShowWindow ( true ); 
            GetDlgItem ( IDC_EDT_ID_VALUE )->EnableWindow ( true );
            ConnectControlsToData (ENTITY_IDS_CONTROLS::EDIT_CNTRL, true );
            ConnectControlsToData (ENTITY_IDS_CONTROLS::COMBO_CNTRL,false );
            ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_ID_VALUE ) ) )->SetMaxCharNum( 40 );
            ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_ID_VALUE ) ) )->SetAllowedChars( CHARACTERS );
            LoadControls (ENTITY_IDS_CONTROLS::EDIT_CNTRL);
         }
         else if (dstrValue == DEPOSITARY_BANK_ACCOUNT)
         {
            GetDlgItem ( IDC_CMB_ID_VALUE )->ShowWindow ( false );
            GetDlgItem ( IDC_EDT_ID_VALUE )->ShowWindow ( true ); 
            GetDlgItem ( IDC_EDT_ID_VALUE )->EnableWindow ( true );
            ConnectControlsToData (ENTITY_IDS_CONTROLS::EDIT_CNTRL, true );
            ConnectControlsToData (ENTITY_IDS_CONTROLS::COMBO_CNTRL,false );
            ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_ID_VALUE ) ) )->SetMaxCharNum( 35 );
            ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_ID_VALUE ) ) )->SetAllowedChars( CHARACTERS );
            LoadControls (ENTITY_IDS_CONTROLS::EDIT_CNTRL);
         }
         else if (dstrValue == IDS::CLEARING_PLATFORM )
         {  
            GetDlgItem ( IDC_CMB_ID_VALUE )->ShowWindow ( true );
            GetDlgItem ( IDC_EDT_ID_VALUE )->ShowWindow ( false ); 
            GetDlgItem ( IDC_CMB_ID_VALUE )->EnableWindow ( true );
            ConnectControlsToData (ENTITY_IDS_CONTROLS::EDIT_CNTRL, false);
			   //MT53X
			   ReInitControl (IDC_CMB_ID_VALUE, IFASTBP_PROC::ENTITY_IDS_LIST, ifds::IdValue, CTRLFLAG_INITCOMBO_BY_SUB_LIST,  ENTITY_IDS_CONTROLS::COMBO_CNTRL);

            ConnectControlsToData (ENTITY_IDS_CONTROLS::COMBO_CNTRL,true );
            LoadControls (ENTITY_IDS_CONTROLS::COMBO_CNTRL);
         }

		 else if ( dstrValue == ENTITY_IDS_VALUE::FAST ||
			       dstrValue == ENTITY_IDS_VALUE::iFAST_OEIC ||
				   dstrValue == ENTITY_IDS_VALUE::iFAST_SICAV)
		 {
		    GetDlgItem ( IDC_CMB_ID_VALUE )->ShowWindow ( SW_HIDE );
            GetDlgItem ( IDC_EDT_ID_VALUE )->ShowWindow ( SW_SHOW); 
            GetDlgItem ( IDC_EDT_ID_VALUE )->EnableWindow ( true );

            ConnectControlsToData (ENTITY_IDS_CONTROLS::EDIT_CNTRL, true );
            ConnectControlsToData (ENTITY_IDS_CONTROLS::COMBO_CNTRL,false );

			( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_ID_VALUE ) ) )->SetMaxCharNum( 20 );
			 LoadControls (ENTITY_IDS_CONTROLS::EDIT_CNTRL);
		 }
         else
         {
            // default to textbox.
            GetDlgItem ( IDC_CMB_ID_VALUE )->ShowWindow ( false );
            GetDlgItem ( IDC_EDT_ID_VALUE )->ShowWindow ( true ); 
            GetDlgItem ( IDC_EDT_ID_VALUE )->EnableWindow ( true );
            ConnectControlsToData (ENTITY_IDS_CONTROLS::EDIT_CNTRL, true );
            ConnectControlsToData (ENTITY_IDS_CONTROLS::COMBO_CNTRL,false );

            ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_ID_VALUE ) ) )->SetAllowedChars( NULL_STRING );
            ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_ID_VALUE ) ) )->SetMaxCharNum( 20 );
            LoadControls (ENTITY_IDS_CONTROLS::EDIT_CNTRL);           
         }

         if (dstrValue == IDS::BIRTH_CERTIFICATE || dstrValue == IDS::DRIVERS_LICENSE || 
             dstrValue == IDS::PASSPORT || dstrValue == IDS::NATIONAL_ID ||
             dstrValue == IDS::TRUST_ACCOUNT_NUMBER || dstrValue == IDS::BUSINESS_NUMBER ||
             dstrValue == IDS::TAX_ID_NUMBER || dstrValue == IDS::EMPLOYER_NUMBER ||
             dstrValue == IDS::BIC_CODE || dstrValue == IDS::FATCA_GIIN || 
             dstrValue == IDS::SOCIAL_SECURITY_NUMBER || dstrValue == IDS::AEOI)
         {
            GetDlgItem (IDC_CMB_COUNTRY_OF_ISSUE ) ->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_STATIC_CNTRY_OF_ISSUE)->ShowWindow(SW_SHOW);
         }
         else
         {
            GetDlgItem (IDC_CMB_COUNTRY_OF_ISSUE ) ->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_STATIC_CNTRY_OF_ISSUE)->ShowWindow(SW_HIDE);
         }
         LoadControls (IDC_LV_ENTITY_IDS);
         break;
      case IDC_DTP_BIRTH_DATE:
         {
            DString strMarket = DSTCommonFunctions::getMarket();
            if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
               LoadControl( IDC_TXT_AGE );
			UpdateDetailsVerifyStat();
         }
         break;
      /*case IDC_DTP_DEATH_DATE:
      case IDC_DTP_DEATHNOTIFDATE:

        {
            DString   deathDate, deathNotifDate;
            Entity   *pEntity;
            bool   bIsNewEntity = false;
            bool   bEnable = false;
            DString dstrEntityId;

            getParent()->getField(this,IFASTBP_PROC::ENTITY_LIST,ifds::EntityId,dstrEntityId,false);

            dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getEntity( getDataGroupId (), dstrEntityId, pEntity );

            if (pEntity && pEntity->isNew ())
            {
               bIsNewEntity = true;
            }

            getParent()->getField(this,IFASTBP_PROC::ENTITY_LIST,  ifds::DofDeath,deathDate,false);
            getParent()->getField(this,IFASTBP_PROC::ENTITY_LIST,  ifds::DofDeathNotice,deathNotifDate,false);

            if (bIsNewEntity)
            {
               bEnable = false;
            }
            else
            {
               bEnable = deathDate.empty () && deathNotifDate.empty () ? false : true;
            }

            GetDlgItem (IDC_BTN_DEATH_DOC )->EnableWindow( bEnable ); 
        }
        break;*/
      case IDC_EDT_PRC_BENEFIT:
         LoadControl( IDC_TXT_AVAILABLE );
         break;
      case IDC_CMB_OCUPATION:
         // Display Other Edit field if Occupation is 'Other' (Code 08)
         LoadControl( IDC_EDT_OCCUPATION );
         GetDlgItem( IDC_EDT_OCCUPATION )->ShowWindow( ( dstrValue == I_("08") ) ? SW_SHOW : SW_HIDE );
		 UpdateDetailsVerifyStat();
         break;
      case IDC_CMB_EMPLOYEECLASS:
         {
            updateEmployeeClass(dstrValue);
            //DString dstrNameLength;
            //
            //getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::NAME_LENGTH, dstrNameLength, false );

            //int iMaxCharNum = dstrNameLength.asInteger();
            //bool bShowName = dstrValue == CODE_CATEGORY_CORPORATE;

            //GetDlgItem (IDC_EDT_FIRST_NAME)->ShowWindow( bShowName ? SW_HIDE : SW_SHOW );
            //GetDlgItem (IDC_EDT_LAST_NAME)->ShowWindow( bShowName ? SW_HIDE : SW_SHOW  );
            //GetDlgItem (IDC_STC_FIRST_NAME)->ShowWindow( bShowName ? SW_HIDE : SW_SHOW  );
            //GetDlgItem (IDC_STC_LAST_NAME)->ShowWindow( bShowName ? SW_HIDE : SW_SHOW  );
            //GetDlgItem (IDC_STATIC_SALUTATION)->ShowWindow( bShowName ? SW_HIDE : SW_SHOW  );
            //GetDlgItem (m_bSalutationFreeFormat ? IDC_EDT_SALUTATION : IDC_CMB_SALUTATION )->ShowWindow( bShowName ? SW_HIDE : SW_SHOW);
            //GetDlgItem (IDC_EDT_NAME)->ShowWindow (bShowName ? SW_SHOW : SW_HIDE);
            //GetDlgItem (IDC_STC_NAME)->ShowWindow (bShowName ? SW_SHOW : SW_HIDE);
            //ConnectControlToData (IDC_EDT_LAST_NAME, !bShowName);
            //ConnectControlToData (IDC_EDT_FIRST_NAME, !bShowName);
            //ConnectControlToData (IDC_EDT_NAME, bShowName);
            //if (iMaxCharNum > 0)
            //{
            //   dynamic_cast <DSTEdit *>( GetControl( bShowName ? IDC_EDT_NAME : IDC_EDT_LAST_NAME ) )->SetMaxCharNum( iMaxCharNum );
            //}
            //else
            //{
            //   // Use default maximum number of characters if category value is 0 or undefined.
            //   if (bShowName)
            //   {
            //      dynamic_cast< DSTEdit * >( GetControl( IDC_EDT_NAME ) )->SetMaxCharNum( 80 );
            //   }
            //   else
            //   {
            //      dynamic_cast< DSTEdit * >( GetControl( IDC_EDT_LAST_NAME ) )->SetMaxCharNum( 40 );
            //   }
            //}
            //LoadControl (IDC_EDT_NAME);
            //LoadControl (IDC_EDT_FIRST_NAME);
            //LoadControl (IDC_EDT_LAST_NAME);
            //LoadControl (m_bSalutationFreeFormat ? IDC_EDT_SALUTATION : IDC_CMB_SALUTATION);
			UpdateDetailsVerifyStat();
         }
         break;
      case IDC_EDT_TAX_JURIS:
         {
            DString strMarket = DSTCommonFunctions::getMarket();
            if( strMarket == MARKET_IDS::CANADA)
            {
               LoadControl (IDC_CMB_RESP2_TAX_JUR);
            }
            LoadControl (IDC_CMB_TAX_JURISDICTION);
			LoadControl (IDC_DTP_TAX_JURIS_EFFECTIVE);
         }
      case IDC_DTP_TAX_JURIS_EFFECTIVE:
         {
            DString dstrUpdate,
                updShrTaxJuris,
                strEntityType;

            bool bEnable = false;

            getParent()->getField (this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityType, strEntityType, false);
            getParent()->getField (this, ENTPROC::UPDATE_SHAREHOLDER, dstrUpdate, false);
            strEntityType.strip().upperCase();

            bEnable = dstrUpdate == Y && strEntityType != RESP_BENEFICIARY;
            GetDlgItem (IDC_CHK_UPDATE_SHAREHOLDER_TAX_JURIS)->EnableWindow( bEnable );
			UpdateDetailsVerifyStat();
         }
         break;
      case IDC_CMB_RESP2_PRIM_CARE_GIVER:
         {
            DString dstrPCGChange, dstrRec400Sent;
            getParent()->getField (this, IFASTBP_PROC::ENTITY_LIST, ifds::PCGChange, dstrPCGChange, false);            
            getParent()->getField (this, IFASTBP_PROC::ENTITY_LIST, ifds::Rec400Sent, dstrRec400Sent, false);            
            if( dstrPCGChange.strip().upperCase() == I_("Y") &&
                dstrRec400Sent.strip().upperCase() == I_("Y") )
            {
               LoadControl( IDC_CMB_RESP2_GEN_RT511 );
               LoadControl( IDC_DTP_RESP2_CUT_OFF_DATE );

               DSTTabCtrl* pTabCtrl = GetTabCtrl (IDC_TAB_ENTITY_MAINTENANCE);
               if (pTabCtrl != NULL)
               {
                  CString cstrRelationPageName, cstrPageName;
                  TCITEM tcItem;
                  wchar_t buffer[256] = {0};
                  tcItem.pszText = buffer;
                  tcItem.cchTextMax = 256;
                  tcItem.mask = TCIF_TEXT;

                  int iPagePos = pTabCtrl->GetCurSel();
                  pTabCtrl->GetItem(iPagePos, &tcItem);

                  cstrPageName = tcItem.pszText;
                  cstrRelationPageName.LoadString( TXT_PAGE_RELATIONSHIPS );

                  if( cstrRelationPageName == cstrPageName )
                  {
                     GetDlgItem( IDC_STC_RESP2_GEN_RT511 )->ShowWindow( SW_SHOW );
                     GetDlgItem( IDC_CMB_RESP2_GEN_RT511 )->ShowWindow( SW_SHOW );
                     GetDlgItem( IDC_STC_RESP2_CUT_OFF_DATE )->ShowWindow( SW_SHOW );
                     GetDlgItem( IDC_DTP_RESP2_CUT_OFF_DATE )->ShowWindow( SW_SHOW );
                     EnableControl (IDC_CMB_RESP2_GEN_RT511 , true );
                     EnableControl (IDC_DTP_RESP2_CUT_OFF_DATE  , true );
                  }
                  else
                  {
                     GetDlgItem( IDC_STC_RESP2_GEN_RT511 )->ShowWindow( SW_HIDE );
                     GetDlgItem( IDC_CMB_RESP2_GEN_RT511 )->ShowWindow( SW_HIDE );
                     GetDlgItem( IDC_STC_RESP2_CUT_OFF_DATE )->ShowWindow( SW_HIDE );
                     GetDlgItem( IDC_DTP_RESP2_CUT_OFF_DATE )->ShowWindow( SW_HIDE );
                  }
               }
            }
            else
            {
               GetDlgItem( IDC_STC_RESP2_GEN_RT511 )->ShowWindow( SW_HIDE );
               GetDlgItem( IDC_CMB_RESP2_GEN_RT511 )->ShowWindow( SW_HIDE );
               GetDlgItem( IDC_STC_RESP2_CUT_OFF_DATE )->ShowWindow( SW_HIDE );
               GetDlgItem( IDC_DTP_RESP2_CUT_OFF_DATE )->ShowWindow( SW_HIDE );
            }
         }
         break;
      case IDC_CMB_RESP2_TAX_JUR:
         {
            LoadControl (IDC_EDT_TAX_JURIS);
            LoadControl (IDC_CMB_TAX_JURISDICTION);
         }
         break;
      case IDC_CMB_TAX_JURISDICTION:
		  {
			  LoadControl (IDC_EDT_TAX_JURIS);
			  DString strMarket = DSTCommonFunctions::getMarket();
			  if( strMarket == MARKET_IDS::CANADA)
			  {
				  LoadControl (IDC_CMB_RESP2_TAX_JUR);
			  }
			  UpdateDetailsVerifyStat();
		  }
		 break;
      case IDC_EDT_ID_VALUE:
         {
            DString dstrEntityType, dstrIdType;
            getParent()->getField (this, 
                                   IFASTBP_PROC::ENTITY_LIST, 
                                   ifds::EntityType, 
                                   dstrEntityType, 
                                   false);
            getParent()->getField (this, 
                                   IFASTBP_PROC::ENTITY_IDS_LIST, 
                                   ifds::IdType,
                                   dstrIdType,
                                   false);

            dstrEntityType.strip().upperCase();
            dstrIdType.strip().upperCase();
            if ( dstrEntityType.strip() == RESP_BENEFICIARY && dstrIdType == SIN)
            {
               LoadControl (IDC_DTP_ID_DATE);
               LoadControl (IDC_ID_STATUS);
            }
         }
         break;
		 //IN2780013 - SOC Loan Number and Loan Type
	  case IDC_EDT_LOAN_NUMBER:
		  {
			dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_LOAN_NUMBER ) ) ->SetMaxCharNum( 15 );
			//( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_LOAN_NUMBER ) ) )->SetAllowedChars(I_("0123456789"));
			LoadControl (IDC_EDT_LOAN_NUMBER); 
		  }
		break;
     case IDC_CMB_RISK_LEVEL:
        {
           DSTTabCtrl* pTabCtrl = GetTabCtrl (IDC_TAB_ENTITY_MAINTENANCE);
           if (pTabCtrl != NULL)
           {
              CString cstrDetailsPageName, cstrPageName;
              TCITEM tcItem;
              wchar_t buffer[256] = {0};
              tcItem.pszText = buffer;
              tcItem.cchTextMax = 256;
              tcItem.mask = TCIF_TEXT;

              int iPagePos = pTabCtrl->GetCurSel();
              pTabCtrl->GetItem(iPagePos, &tcItem);

              cstrPageName = tcItem.pszText;
              cstrDetailsPageName.LoadString( TXT_PAGE_DETAILS);
              if( cstrDetailsPageName == cstrPageName)
              {
                  DString strRiskLevel;
                  getParent()->getField (this, 
                                         IFASTBP_PROC::ENTITY_LIST, 
                                         ifds::RiskLevel,
                                         strRiskLevel,
                                         false);
                  strRiskLevel.strip().upperCase();
                  if (multipleRiskEnv())
                  {
                      GetDlgItem( IDC_STC_RISK_LEVEL )->ShowWindow( SW_HIDE );
                      GetDlgItem( IDC_CMB_RISK_LEVEL )->ShowWindow( SW_HIDE );
                      GetDlgItem( IDC_STC_COUNTRY_OF_EXPOSURE )->ShowWindow( SW_HIDE );
                      GetDlgItem( IDC_CMB_COUNTRY_OF_EXPOSURE )->ShowWindow( SW_HIDE );
                  }
                  else
                  {
                      if (POLITICALLY_EXPOSED_PERSON != strRiskLevel) {
                          GetDlgItem( IDC_STC_COUNTRY_OF_EXPOSURE )->ShowWindow( SW_HIDE );
                          GetDlgItem( IDC_CMB_COUNTRY_OF_EXPOSURE )->ShowWindow( SW_HIDE );
                      }
                      else{
                          GetDlgItem( IDC_STC_COUNTRY_OF_EXPOSURE )->ShowWindow( SW_SHOW );
                          GetDlgItem( IDC_CMB_COUNTRY_OF_EXPOSURE )->ShowWindow( SW_SHOW );
                      }
                  }
              }
           }
		   UpdateDetailsVerifyStat();
        }
        break;
     case IDC_CMB_RISK_TYPE:
         {
             DString dstrRiskDeffAppl;
             getParent()->getField(this, IFASTBP_PROC::RISK_LIST, ENTPROC::RISK_DEFF_DATE_APPL, dstrRiskDeffAppl, false);
             bool riskDeffAppl = dstrRiskDeffAppl == I_("Y");

             GetDlgItem(IDC_STC_RISK_DEFF)->ShowWindow(riskDeffAppl && riskTabSelected());
             GetDlgItem(IDC_DTP_RISK_DEFF)->ShowWindow(riskDeffAppl && riskTabSelected());
         }
         break;
	 case IDC_CMB_SALUTATION:
	 case IDC_EDT_FIRST_NAME:
	 case IDC_EDT_LAST_NAME:
	 case IDC_EDT_BIRTH_PLACE:
	 case IDC_CMB_COUNTRY_OF_BIRTH:
	 case IDC_CMB_NATIONALITY:
	 case IDC_CMB_LANGUAGE:
	 case IDC_CMB_GENDER:
	 case IDC_DTP_EFFECTIVE_DATE:
	 case IDC_DTP_DEATH_DATE:
	 case IDC_DTP_DEATHNOTIFDATE:
	 case IDC_DTP_DEATH_DATE_SETTLEMENT:
	 case IDC_EDT_HOME_TEL:
	 case IDC_EDT_BUSINESS_TEL:
	 case IDC_EDT_BUSINESS_EXT:
	 case IDC_EDT_HOME_FAX:
	 case IDC_EDT_BUSINESS_FAX:
	 case IDC_EDT_EMAIL:
	 case IDC_EDT_TELEX:
	 case IDC_EDT_EMAIL2:
	 case IDC_EDT_SECOND_PHONENUM:
	 case IDC_EDT_SECOND_PHONENUM_EXT:
	 case IDC_EDT_CONTACT_NAME:
	 case IDC_CMB_EUSD_OPTION:
	 case IDC_EDT_NAME:
		  {
			  UpdateDetailsVerifyStat();
		  }
		  break;
      default:
         break;
   }

}

//******************************************************************************
LRESULT EntityMaintenanceDlg::OpenFundClassListDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenFundClassListDlg" ) );

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;      
      DString dstrShareholder;      
      getParent()->getField( this, ENTPROC::SHR_NUM,    dstrShareholder );
      dstrShareholder.strip().stripLeading( I_CHAR( '0' ) );
      setParameter ( SHR_NUM , dstrShareholder );
      setParameter ( ENTPROC::ACCOUNT_NUM, m_dstrAccountNum );

      eRtn = invokeCommand( getParent(), CMD_BPROC_FUNDCLASS, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString dstrFundCode, dstrClassCode;

               getParameter ( FUND_CODE, dstrFundCode );
               getParameter ( CLASS_CODE, dstrClassCode );
               if( ( GetFocus() == GetDlgItem( IDC_EDT_FUND_NUMBER ) ) || ( GetFocus() == GetDlgItem( IDC_EDT_FUND_CODE ) )
                   || ( GetFocus() == GetDlgItem( IDC_EDT_CLASS_CODE ) ) )
               {
                  getParent()->setField( this, IFASTBP_PROC::ENTITY_LIST, ifds::EscrowFund, dstrFundCode );
                  getParent()->setField( this, IFASTBP_PROC::ENTITY_LIST, ifds::EscrowClass, dstrClassCode );
                  LoadControl ( IDC_EDT_FUND_NUMBER );
                  LoadControl ( IDC_EDT_FUND_CODE );
                  LoadControl ( IDC_EDT_CLASS_CODE );
               }
               break;
            }
         case CMD_CANCEL:
            break;
         default:
            // Display error
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
            break;
      }
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
   return(0);
}

//******************************************************************************
void  EntityMaintenanceDlg::OnBtnEntityHistory()
{
   DString dstrEntityId;
   getParent()->getField(this,IFASTBP_PROC::ENTITY_LIST,ifds::EntityId,dstrEntityId,false);
   dstrEntityId.strip().stripLeading('0');
   setCsiParameter( DcCsiParameters::ACCOUNT_NUMBER, DStringA(m_dstrAccountNum) );
   setCsiParameter( DcCsiParameters::ENTITY_ID, DStringA(dstrEntityId) );
   executeCsiProcess( DcCsiProcesses::ENTITY_MAINTAINANCE );
}

//******************************************************************************

void EntityMaintenanceDlg::OnBtnCopyentity() 
{
   // TODO: Add your control notification handler code here
   DString dstrOrgKey = GetList(IDC_LV_ENTITIES)->GetCurrentKey();
   getParent()->setField(this, BF::NullContainerId, ENTPROC::ORG_KEY, dstrOrgKey);
   AddToListControl( IDC_LV_ENTITIES );

   DString dstrDestKey = GetList(IDC_LV_ENTITIES)->GetCurrentKey();
   getParent()->setField(this, BF::NullContainerId, ENTPROC::DEST_KEY, dstrDestKey);
   LoadListWithSelection( IDC_LV_ENTITIES, dstrDestKey );
//   EnableControl( IDC_CMB_ENTITY_TYPE, true );
//   ConnectControl( IDC_CMB_ENTITY_TYPE, true );
   LoadControl( IDC_CMB_ENTITY_TYPE );  // for the error message showing up
   EnableControl( IDOK, true );

   EnableControl( IDC_BTN_SEARCH, true);
   FocusOnControl( IDC_CMB_ENTITY_TYPE );
}
//******************************************************************************

bool EntityMaintenanceDlg::doSend(
                                 GenericInterface *rpGICaller,
                                 const I_CHAR * szMessage
                                 )
{
   //I know that overwriting this method in this way looks weird for now
   //I just wanted to be sure that, if overwritten, the call to the base class for WarningConfirm will be there
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_(" doSend() " ) );
   bool bRetVal = true;

   DString str( szMessage );
   if( str == I_( "WarningConfirm" ) || str == I_( "TrxnsError" ) )
      bRetVal = AbstractBaseMainDlg::doSend(rpGICaller, szMessage);

   return(bRetVal);
}

//******************************************************************************

bool EntityMaintenanceDlg::doDisablePermCheckButton(UINT nID)
{
   TRACE_METHOD( CLASSNAME, I_( "doDisablePermCheckButtons" ));

   bool bIsRES2Client = 
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->isRES2Client();

   MFAccount *pModelAccount = NULL;

   if (nID == IDC_BTN_DELETE)
   {
	  DString dstrEntityType, dstrSeq, dstrTaxType;
	  getParent()->getField (this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityType, dstrEntityType, false);
	  getParent()->getField (this, IFASTBP_PROC::ENTITY_LIST, ifds::SeqNumber, dstrSeq, false);
	  getParent()->getField( this, ENTPROC::ACCOUNT_TAX_TYPE, dstrTaxType );
	  dstrTaxType.strip(); 
	  
	  bool bEnableDeleteAcctHolderSeq1 = (dstrTaxType == RDSP_TAX_TYPE) ? true : false;
	
	  DString dstrStatus;
	  getParent()->getField (this, IFASTBP_PROC::ENTITY_LIST, ifds::Active, dstrStatus, false);

	  if (doesSupportMstrActAMSC() && m_dstrCreatingShareholder == N && m_dstrCreatingAccount == Y)
      {
			return true;
	  }
      else if(  ( dstrEntityType.strip() == ACCOUNTHOLDER_ENTITY_TYPE && dstrSeq.strip().stripLeading('0') == I_("1") && !bEnableDeleteAcctHolderSeq1) ||
            ( dstrEntityType.strip() == ESCROW_ENTITY_TYPE  && !hasUpdatePermission(UAF::ESCROW_BAND ) ) ||
               ( dstrEntityType.strip() == ASSIGNEE_ENTITY_TYPE  && !hasUpdatePermission(UAF::ASSIGNEE_ENTITY_TYPE_SETUP ) ) 
         )
      {
         return(true);
      }
      else if ( dstrEntityType.strip() == RESP_BENEFICIARY )
      {
         if( bIsRES2Client )
         {
            if (hasUpdatePermission(UAF::RESP_BENEFICIARY))
            {
               DString dstrCLBExists, dstrGrantExists, dstrTradeExists;
               getParent()->getField (this, IFASTBP_PROC::ENTITY_LIST, ifds::CLBExists,dstrCLBExists, false);
               getParent()->getField (this, IFASTBP_PROC::ENTITY_LIST, ifds::GrantExists,dstrGrantExists, false);
               getParent()->getField (this, IFASTBP_PROC::ENTITY_LIST, ifds::TradeExists,dstrTradeExists, false);

               dstrCLBExists.strip().upperCase(); 
               dstrGrantExists.strip().upperCase(); 
               dstrTradeExists.strip().upperCase();
               
               if ( dstrCLBExists == I_("Y") ||  dstrGrantExists == I_("Y") || 
                    dstrTradeExists == I_("Y") )
               {
                  return(true);
               }
            }
            else
               return true;
         }
         else
         {
            // enable delete button
            return false;
         }
      }
      else if ( dstrEntityType.strip() == RESP_PCG_INDIV_ENTITY_TYPE || 
                dstrEntityType.strip() == RESP_PCG_INST_ENTITY_TYPE )
      {
         DString dstrPCGLinkBenef;
         getParent()->getField (this, IFASTBP_PROC::ENTITY_LIST, ifds::PCGLinkBenef,dstrPCGLinkBenef, false);

         if ( dstrPCGLinkBenef.strip().upperCase() == I_("Y") )
         {
            return(true);
         }
      }
	  else if( dstrEntityType.strip() != ACCOUNTHOLDER_ENTITY_TYPE && dstrStatus.strip() == I_("N") )
	  {
		  return(true);
   }
   }
   else if (nID == IDC_BTN_ADD)
   {
	  if (doesSupportMstrActAMSC() && m_dstrCreatingShareholder == N && m_dstrCreatingAccount == Y)
      {
			return true;
	  }
   }
   else if (nID == IDC_BTN_COPYENTITY)
   {
	   if (doesSupportMstrActAMSC() && m_dstrCreatingShareholder == N && m_dstrCreatingAccount == Y)
       {
			return true;
	   }
   }


   if (nID == IDC_BTN_ADD_ID || 
       nID == IDC_BTN_DELETE_ID)
   {
      DString entityType,
              idType;

      getParent()->getField (this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityType, entityType, false);
      getParent()->getField (this, IFASTBP_PROC::ENTITY_IDS_LIST, ifds::IdType, idType, false);
      if (!m_bNewEntity)
       {
         if ((entityType == ESCROW_ENTITY_TYPE    && !hasUpdatePermission (UAF::ESCROW_BAND)) ||
             (entityType == ASSIGNEE_ENTITY_TYPE  && !hasUpdatePermission (UAF::ASSIGNEE_ENTITY_TYPE_SETUP)) ||
             (nID == IDC_BTN_DELETE_ID && (idType == IDS::ACCESS_ID || idType == IDS::CIF)) ||
			 (nID == IDC_BTN_DELETE_ID && !hasDeletePermission (UAF::APAC_SUPREGN) && idType == IDS::TAX_FILE_NUMBER))      
         {
            return true;
         }
      }
      if (nID == IDC_BTN_DELETE_ID && entityType == ENTITY_TYPE_CLEARING_PLATFORM && idType == IDS::CLEARING_PLATFORM)
      {
         return true;
      }		  
   }

   return false;
}

//******************************************************************************

void EntityMaintenanceDlg::OnBtnHistorical()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnHistorical"));
   CWaitCursor wait;

   IFastHistoricalInfo historicalInfo;
   DString dstrShareholder;      
   getParent()->getField( this, ENTPROC::SHR_NUM, dstrShareholder );
   dstrShareholder.strip().stripLeading( I_CHAR( '0' ) );
   setParameter( SHR_NUM , dstrShareholder );
   setParameter( ENTPROC::ACCOUNT_NUM, m_dstrAccountNum ); 
   historicalInfo( this, IFASTBP_PROC::ENTITY_LIST, I_("MULTI") );
}

//******************************************************************************
void EntityMaintenanceDlg::tabSelectionChanged( UINT tabControlID, const DString& strPageName )
{ 
   CString cstrPageDetailName, cstrPageRESPBeneficiary,cstrPageRESPRelation, cstrPageRisks;
   cstrPageDetailName.LoadString( TXT_PAGE_DETAILS );
   cstrPageRESPBeneficiary.LoadString( TXT_PAGE_BENEFICIARY );
   cstrPageRESPRelation.LoadString( TXT_PAGE_RELATIONSHIPS );
   cstrPageRisks.LoadString(TXT_PAGE_RISKS);

   bool bIsRES2Client = 
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->isRES2Client();

   if( strPageName.c_str() == cstrPageDetailName )
   {
      LoadControl( IDC_CMB_OCUPATION );
      LoadControl( IDC_CMB_EMPLOYEECLASS );

      if (multipleRiskEnv())
      {
          GetDlgItem( IDC_STC_RISK_LEVEL )->ShowWindow( SW_HIDE );
          GetDlgItem( IDC_CMB_RISK_LEVEL )->ShowWindow( SW_HIDE );
          GetDlgItem( IDC_STC_COUNTRY_OF_EXPOSURE )->ShowWindow( SW_HIDE );
          GetDlgItem( IDC_CMB_COUNTRY_OF_EXPOSURE )->ShowWindow( SW_HIDE );
      }
	  else
      {
		  DString strRiskLevel;
		  getParent()->getField (this, 
                          IFASTBP_PROC::ENTITY_LIST, 
                          ifds::RiskLevel,
                          strRiskLevel,
                          false);
		  strRiskLevel.strip().upperCase();
		  if (POLITICALLY_EXPOSED_PERSON != strRiskLevel)
		  {
			  GetDlgItem( IDC_STC_COUNTRY_OF_EXPOSURE )->ShowWindow( SW_HIDE );
              GetDlgItem( IDC_CMB_COUNTRY_OF_EXPOSURE )->ShowWindow( SW_HIDE );
   }
		  else
		  {
			  GetDlgItem( IDC_STC_COUNTRY_OF_EXPOSURE )->ShowWindow( SW_SHOW );
              GetDlgItem( IDC_CMB_COUNTRY_OF_EXPOSURE )->ShowWindow( SW_SHOW );
		  }
	  }
   }
   else if ( strPageName.c_str() == cstrPageRESPRelation )
   {
      if ( bIsRES2Client )
      {
         GetDlgItem( IDC_CMB_RESP2_PRIM_CARE_GIVER )->ShowWindow( SW_SHOW );
         GetDlgItem( IDC_STC_RESP2_PRIM_CARE_GIVER )->ShowWindow( SW_SHOW );

         updateRT511RelatedControls();
      }
      else
      {
         GetDlgItem( IDC_CMB_RESP2_PRIM_CARE_GIVER )->ShowWindow( SW_HIDE );
         GetDlgItem( IDC_STC_RESP2_PRIM_CARE_GIVER )->ShowWindow( SW_HIDE );
         GetDlgItem( IDC_CMB_RESP2_GEN_RT511 )->ShowWindow( SW_HIDE );
         GetDlgItem( IDC_STC_RESP2_GEN_RT511 )->ShowWindow( SW_HIDE );
         GetDlgItem( IDC_DTP_RESP2_CUT_OFF_DATE )->ShowWindow( SW_HIDE );
         GetDlgItem( IDC_STC_RESP2_CUT_OFF_DATE )->ShowWindow( SW_HIDE );
      }
   }
   if (strPageName.c_str() == cstrPageRESPBeneficiary ||
       strPageName.c_str() == cstrPageRESPRelation )
   {
      
      DString dstrEntityType, dstrSeq;
      getParent()->getField (this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityType, dstrEntityType, false);

      if( bIsRES2Client && dstrEntityType.strip().upperCase() == RESP_BENEFICIARY )
      {
         if ( !hasUpdatePermission(UAF::RESP_BENEFICIARY ))
         {
            EnableControl (IDC_CMB_RESP2_RELATION_TO_OWNER, false);
            EnableControl (IDC_DTP_RESP2_LETTER_DATE , false);
            EnableControl (IDC_CMB_RESP2_REASON , false);
            EnableControl (IDC_CMB_RESP2_TAX_JUR , false);
            EnableControl (IDC_CMB_RESP2_PRINTED , false);
            EnableControl (IDC_EDT_RESP2_ALLOCATION_PRCNT , false);
            EnableControl (IDC_CMB_RESP2_REQUEST_GRANT , false);
            EnableControl (IDC_CMB_RESP2_TAINTED , false);
            EnableControl (IDC_DTP_RESP2_TAINTED_END_DATE  , false);
            EnableControl (IDC_CMB_RESP2_PARENT_LEGAL_GUARD  , false);
            EnableControl (IDC_CMB_RESP2_DESIGNATED_INST  , false);
            EnableControl (IDC_CMB_RESP2_PRIM_CARE_GIVER  , false);
            EnableControl (IDC_CMB_RESP2_GEN_RT511  , false);
            EnableControl (IDC_DTP_RESP2_CUT_OFF_DATE  , false);
         }
         if ( !hasUpdatePermission(UAF::RESP_ALLOCATION ) )
         {
            EnableControl (IDC_EDT_RESP2_ALLOCATION_PRCNT  , false);
         }
         if ( !(hasUpdatePermission(UAF::RESP_GRANTS) || hasUpdatePermission(UAF::RESP_GRANT_INFORMATION)) )
         {
            EnableControl (IDC_CMB_RESP2_REQUEST_GRANT  , false);
         }

         DString strPCGChange;
         getParent()->getField(this, IFASTBP_PROC::ENTITY_LIST, ifds::PCGChange, strPCGChange, false);
         strPCGChange.strip().upperCase();

         if ( strPCGChange == I_("Y") && hasUpdatePermission(UAF::RESP_BENEFICIARY ) )
         {
            EnableControl (IDC_CMB_RESP2_GEN_RT511 , true );
            EnableControl (IDC_DTP_RESP2_CUT_OFF_DATE  , true );
         }
         else
         {
            EnableControl (IDC_CMB_RESP2_GEN_RT511 , false );
            EnableControl (IDC_DTP_RESP2_CUT_OFF_DATE  , false );
         }
      }
   }

   bool isRiskTab = strPageName.c_str() == cstrPageRisks;

   GetDlgItem(IDC_LV_RISKS)->ShowWindow(isRiskTab);
   GetDlgItem(IDC_BTN_ADD_RISK)->ShowWindow(isRiskTab);
   GetDlgItem(IDC_BTN_DELETE_RISK)->ShowWindow(isRiskTab);
   GetDlgItem(IDC_BTN_SET_RISK_LEVEL)->ShowWindow(isRiskTab);
   GetDlgItem(IDC_STC_HIGHEST_RISL_LVL)->ShowWindow(isRiskTab);
   GetDlgItem(IDC_STC_RISK_EXPOSURE)->ShowWindow(isRiskTab);
   GetDlgItem(IDC_STC_RISK_TYPE)->ShowWindow(isRiskTab);
   GetDlgItem(IDC_STC_RISK_COUNTRY)->ShowWindow(isRiskTab);
   GetDlgItem(IDC_EDT_HIGHEST_RISK_LVL)->ShowWindow(isRiskTab);
   GetDlgItem(IDC_EDT_HIGHEST_RISK_EXPOSURE)->ShowWindow(isRiskTab);
   GetDlgItem(IDC_CMB_RISK_TYPE)->ShowWindow(isRiskTab);
   GetDlgItem(IDC_CMB_RISK_COUNTRY)->ShowWindow(isRiskTab);

   if (isRiskTab)
   {
       DString dstrRiskDeffAppl;
       getParent()->getField(this, IFASTBP_PROC::RISK_LIST, ENTPROC::RISK_DEFF_DATE_APPL, dstrRiskDeffAppl, false);
       bool riskDeffAppl = dstrRiskDeffAppl == I_("Y");

       GetDlgItem(IDC_STC_RISK_DEFF)->ShowWindow(riskDeffAppl);
       GetDlgItem(IDC_DTP_RISK_DEFF)->ShowWindow(riskDeffAppl);
   }
   else
   {
       GetDlgItem(IDC_STC_RISK_DEFF)->ShowWindow(false);
       GetDlgItem(IDC_DTP_RISK_DEFF)->ShowWindow(false);
   }
}

//******************************************************************************
void EntityMaintenanceDlg::OnBtnEntityAddress()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnEntityAddress()" ) );

   try
   {
      DString dstrEntityId, dstrShareholderNum, dstrEntityType, dstrSeqNum;
      getParent()->getField(this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityId, dstrEntityId, false);   
      getParent()->getField(this,ENTPROC::SHR_NUM, dstrShareholderNum );

      getParent()->getField(this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityType, dstrEntityType, false );   
      getParent()->getField(this, IFASTBP_PROC::ENTITY_LIST, ifds::SeqNumber,  dstrSeqNum, false );   

      dstrShareholderNum.stripLeading().stripLeading(I_CHAR('0')).stripTrailing();               
      
      setParameter( ADDRLIT::ENTITY_ID,        dstrEntityId );
      setParameter( ADDRLIT::ACCOUNT_NUM,      m_dstrAccountNum );      
      setParameter( NASULIT::CREATING_ACCOUNT, m_dstrCreatingAccount );
      
      setParameter( ADDRLIT::FROM_ENTITY ,    I_( "Y" ) );   
      setParameter( ADDRLIT::SHAREHOLDER_NUM, dstrShareholderNum);

      setParameter( ADDRLIT::ENTITY_TYPE, dstrEntityType );
      setParameter( ADDRLIT::SEQ_NUMBER,  dstrSeqNum );

      SetMessageStatusBar( TXT_LOAD_ADDRESS_BOOK );

      E_COMMANDRETURN eRtn;
      eRtn = invokeCommand( getParent(), CMD_BPROC_ADDRESSES, PROC_SUPPORT, true, NULL );

      switch( eRtn )
      {
         case CMD_OK:
         case CMD_CANCEL:
            break;
         case CMD_MODELESS_INPROCESS:

            break;
         default:
            // Display error
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
            break;
       }
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
}
//******************************************************************************
void EntityMaintenanceDlg::OnBtnEntRegDetail()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnEntRegDetail" ) );

   try
   {
      DString dstrEntityId;

      getParent()->getField(this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityId, dstrEntityId, false);   
		
      setParameter( I_("AccountNum") , m_dstrAccountNum ); 
      setParameter( I_("EntityId") ,  dstrEntityId); 
      setParameter( I_("Caller") ,  I_("Entity")); 

      E_COMMANDRETURN eRtn;
      eRtn = invokeCommand( getParent(), CMD_BPROC_ENT_REG_MAINT, PROC_SUPPORT, true, NULL );

      switch( eRtn )
      {
         case CMD_OK:
         case CMD_CANCEL:
            break;
         case CMD_MODELESS_INPROCESS:

            break;
         default:
            // Display error
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
            break;
       }
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
}
//******************************************************************************
void EntityMaintenanceDlg::OnChkUpdateShareholder()
{
   UpdateData(true);
   getParent()->setField( this, IFASTBP_PROC::ENTITY_LIST, ifds::UpdShrTaxJuris, 
      m_bUpdateShareholder? Y:N, false );
}

//******************************************************************************
bool EntityMaintenanceDlg::GetEntityEnable()
{
   DString status;

   getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::GoodBad, status, false );
   status.strip().upperCase();

   return (!(status == I_("N")));
}

//******************************************************************************
void EntityMaintenanceDlg::OnBtnKYC() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_(" OnBtnKYC ()" ) );   
   try
   {
      DString  dstrEntityId,
               dstrEntityType,
               dstrAcctNumber,
               dstrSeqNumber;

      getParent()->getField(this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityId, dstrEntityId, false);
      getParent()->getField(this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityType, dstrEntityType, false);
      getParent()->getField(this, IFASTBP_PROC::ENTITY_LIST, ifds::SeqNumber, dstrSeqNumber, false);

      // if entity is account owner and primary entity
      if (dstrEntityType == I_("01") && dstrSeqNumber == I_( "1" ))
      {
         dstrAcctNumber = m_dstrAccountNum;
         dstrEntityId = I_("0");
      }
      else
      {
         dstrAcctNumber = I_("0");
      }

      setParameter( ENTITYDLG::ENTITY_ID, dstrEntityId );
      setParameter( ENTPROC::ACCOUNT_NUM, m_dstrAccountNum );
      setParameter( ENTITYDLG::CALLER, ENTITYDLG::ENTITY );

      E_COMMANDRETURN eRtn;
      eRtn = invokeCommand( getParent(), CMD_BPROC_DEMOGRAPHICS, PROC_SUPPORT, true, NULL );

      switch( eRtn )
      {
         case CMD_OK:
         case CMD_CANCEL:
            break;
         case CMD_MODELESS_INPROCESS:
            break;
         default:
            // Display error
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
         break;
      }
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
}

//******************************************************************************
void EntityMaintenanceDlg::OnBtnGrant () 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnGrant" ) );
   
   try
   {
      CWaitCursor wait;   
      E_COMMANDRETURN eRtn = CMD_OK;

      DString last_name, first_name, dstrEntityName;

      getParent()->getField (this, IFASTBP_PROC::ENTITY_LIST, ifds::LastName, last_name);
      getParent()->getField (this, IFASTBP_PROC::ENTITY_LIST, ifds::FirstName, first_name);
      dstrEntityName = last_name.strip() + SEMICOLUMN_STRING + first_name.strip();
   
      CString cstrTitle;
	  cstrTitle.LoadString(TXT_GRNT_INFO_SCREEN);
	  DString screenTitle (DString(cstrTitle) + m_dstrAccountNum /*+ I_(" ") + dstrEntityName*/),
			  urlParamsIDI,
			  entityId;

	  if (!m_dstrAccountNum.empty ())
	  {
		  addIDITagValue (urlParamsIDI, I_("AccountNum"), m_dstrAccountNum);
	  }

	  getParent()->getField (this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityId, entityId, false);
	  if (!entityId.empty())
	  {
		  addIDITagValue (urlParamsIDI, I_("RESPBenefID"), entityId);
	  }

	  if (hasReadPermission( UAF::RESP_GRANT_INFORMATION )) // RESP Transformation
	  {
		  addIDITagValue (urlParamsIDI, I_("screen"), I_("RESPGrantInfo2")); //DesktopWeb conversion
	  }
	  else
	  {
		  addIDITagValue (urlParamsIDI, I_("screen"), I_("RESPGrantInfo")); //DesktopWeb conversion
		  screenTitle += I_(" ") + dstrEntityName;
	  }

	  setParameter (I_("UrlParams"), urlParamsIDI);
	  setParameter( I_("BrowserTitle"), screenTitle );
	  setParameter (I_("from_screen"), I_("EntityMaintenanceDlg"));

	  if (hasReadPermission( UAF::RESP_GRANT_INFORMATION )) // RESP Transformation
	  {
		  eRtn = invokeCommand( getParent(), CMD_BPROC_RESP_GRANTS2, PROC_SUPPORT, true, NULL );
	  }
	  else
	  {
		  eRtn = invokeCommand( getParent(), CMD_BPROC_RESP_GRANTS, PROC_SUPPORT, true, NULL );
	  }
 
	  switch (eRtn)
	  {
		case CMD_OK:
		case CMD_CANCEL:
			break;
		case CMD_MODELESS_INPROCESS:
			break;
		default:
			// Display error
			ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
			break;
	  }
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
}

//******************************************************************************
void EntityMaintenanceDlg::OnBtnAddRisk()
{
    AddToListControl(IDC_LV_RISKS);
}

//******************************************************************************
void EntityMaintenanceDlg::OnBtnDelRisk()
{
    DeleteFromListControl(IDC_LV_RISKS);

    LoadControl(IDC_EDT_HIGHEST_RISK_LVL);
    LoadControl(IDC_EDT_HIGHEST_RISK_EXPOSURE);
}

//******************************************************************************
void EntityMaintenanceDlg::OnBtnSetRiskLevel()
{
    DString dstrRiskLevel, dstrCntryExpr;

    getParent()->getField(this, IFASTBP_PROC::RISK_LIST, ifds::RiskLevel, dstrRiskLevel, false);
    getParent()->getField(this, IFASTBP_PROC::RISK_LIST, ifds::CountryOfExposure, dstrCntryExpr, false);

    getParent()->setField(this, IFASTBP_PROC::ENTITY_LIST, ifds::RiskLevel, dstrRiskLevel, false);
    getParent()->setField(this, IFASTBP_PROC::ENTITY_LIST, ifds::CountryOfExposure, dstrCntryExpr, false);

    LoadControl(IDC_EDT_HIGHEST_RISK_LVL);
    LoadControl(IDC_EDT_HIGHEST_RISK_EXPOSURE);
}

//******************************************************************************
void EntityMaintenanceDlg::OnBtnTaxJurisHistory() 
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnTaxJurisHistory "));
   
   CWaitCursor wait;   
   E_COMMANDRETURN eRtn = CMD_OK;
   DString entityId,
      last_name,
      first_name;

   getParent()->getField (this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityId, entityId, false);
   entityId.stripLeading( '0' );

   getParent()->getField (this, IFASTBP_PROC::ENTITY_LIST, ifds::LastName, last_name);
   getParent()->getField (this, IFASTBP_PROC::ENTITY_LIST, ifds::FirstName, first_name);
   DString dstrEntityName = last_name.strip() + SEMICOLUMN_STRING + first_name.strip();

   CString cstrTitle;
   cstrTitle.LoadString(TXT_TAX_JUR_HIST);
   DString screenTitle = DString(cstrTitle) + m_dstrAccountNum + I_(" ") + dstrEntityName;

   DString urlParamsIDI;

   addIDITagValue (urlParamsIDI, I_("AccountNum"), m_dstrAccountNum);
   addIDITagValue (urlParamsIDI, I_("BrowserTitle"), I_("Tax Jurisdiction History: ") );
   addIDITagValue (urlParamsIDI, I_("screen"),I_("EntTaxHist") );

   if (!entityId.empty ())
   {
      addIDITagValue (urlParamsIDI, I_("entityID"), entityId);
   }

   setParameter (I_("UrlParams"), urlParamsIDI);
   setParameter (I_("BrowserTitle"), screenTitle);
   setParameter (I_("from_screen"), I_("EntityMaintenanceDlg"));
   setParameter (I_("screen"), I_("EntTaxHist"));

   eRtn = invokeCommand (getParent(), CMD_BPROC_TAX_JURIS_HISTORY, PROC_NO_TYPE, true, NULL);
   wait.Restore();

   SetMessageStatusBar (NULL_STRING);

   switch (eRtn)
   {
      case CMD_OK:
      case CMD_MODELESS_INPROCESS:
      {
         DString dstrReturnResult;

         getParameter (I_("BrowserResults"), dstrReturnResult);
         I_CHAR *temp = const_cast<I_CHAR*> (dstrReturnResult.c_str ());
         break;
      }
      case CMD_CANCEL:
         break;
      default:
         // Display error
         ConditionMessageBox (FRAMEBELOW(), GETHIGHESTSEVERITY());
          break;
   }
}

//******************************************************************************
void EntityMaintenanceDlg::addTabPage( UINT iPageName )
{
   DSTTabCtrl* pTabCtrl = GetTabCtrl (IDC_TAB_ENTITY_MAINTENANCE);
   if (pTabCtrl == NULL)
   {
      return;
   }

   //remove controls registered with the page
   if( iPageName == TXT_PAGE_BENEFICIARY )
   {
      if (!pTabCtrl->HasTab (TXT_PAGE_BENEFICIARY))
      {
         pTabCtrl->AddTab (TXT_PAGE_BENEFICIARY);

         pTabCtrl->registerControl (IDC_STC_RESP2_RELATION_TO_OWNER, TXT_PAGE_BENEFICIARY);
         pTabCtrl->registerControl (IDC_CMB_RESP2_RELATION_TO_OWNER, TXT_PAGE_BENEFICIARY);
         pTabCtrl->registerControl (IDC_STC_RESP2_LETTER_DATE, TXT_PAGE_BENEFICIARY);
         pTabCtrl->registerControl (IDC_DTP_RESP2_LETTER_DATE, TXT_PAGE_BENEFICIARY);
         pTabCtrl->registerControl (IDC_STC_RESP2_REASON, TXT_PAGE_BENEFICIARY);
         pTabCtrl->registerControl (IDC_CMB_RESP2_REASON, TXT_PAGE_BENEFICIARY);
         pTabCtrl->registerControl (IDC_STC_RESP2_TAX_JUR, TXT_PAGE_BENEFICIARY);
         pTabCtrl->registerControl (IDC_CMB_RESP2_TAX_JUR, TXT_PAGE_BENEFICIARY);
         pTabCtrl->registerControl (IDC_STC_RESP2_PRINTED, TXT_PAGE_BENEFICIARY);
         pTabCtrl->registerControl (IDC_CMB_RESP2_PRINTED, TXT_PAGE_BENEFICIARY);
         pTabCtrl->registerControl (IDC_STC_RESP2_ALLOCATION_PRCNT, TXT_PAGE_BENEFICIARY);
         pTabCtrl->registerControl (IDC_EDT_RESP2_ALLOCATION_PRCNT, TXT_PAGE_BENEFICIARY);
         pTabCtrl->registerControl (IDC_STC_RESP2_REQUEST_GRANT, TXT_PAGE_BENEFICIARY);
         pTabCtrl->registerControl (IDC_CMB_RESP2_REQUEST_GRANT, TXT_PAGE_BENEFICIARY);
         pTabCtrl->registerControl (IDC_STC_RESP2_TAINTED, TXT_PAGE_BENEFICIARY);
         pTabCtrl->registerControl (IDC_CMB_RESP2_TAINTED, TXT_PAGE_BENEFICIARY);
         pTabCtrl->registerControl (IDC_STC_RESP2_TAINTED_END_DATE, TXT_PAGE_BENEFICIARY);
         pTabCtrl->registerControl (IDC_DTP_RESP2_TAINTED_END_DATE, TXT_PAGE_BENEFICIARY);
         pTabCtrl->registerControl (IDC_BTN_GRANT, TXT_PAGE_BENEFICIARY);
         
         ReInitControl( IDC_CMB_RESP2_RELATION_TO_OWNER,
                        IFASTBP_PROC::ENTITY_LIST,
                        ifds::HRDCRelateCode,
                        CTRLFLAG_INITCOMBO_BY_SUB_LIST );

         ConnectControlsToData (RESP2_CONTROLS::BENEF_INFO, true);
         LoadControls (RESP2_CONTROLS::BENEF_INFO);
      }
   }
   else if( iPageName == TXT_PAGE_RELATIONSHIPS )
   {
      if (!pTabCtrl->HasTab (TXT_PAGE_RELATIONSHIPS))
      {
         pTabCtrl->AddTab (TXT_PAGE_RELATIONSHIPS);

         pTabCtrl->registerControl (IDC_CMB_RESP2_PARENT_LEGAL_GUARD, TXT_PAGE_RELATIONSHIPS );
         pTabCtrl->registerControl (IDC_STC_RESP2_PARENT_LEGAL_GUARD, TXT_PAGE_RELATIONSHIPS );
         pTabCtrl->registerControl (IDC_CMB_RESP2_DESIGNATED_INST, TXT_PAGE_RELATIONSHIPS );
         pTabCtrl->registerControl (IDC_STC_RESP2_DESIGNATED_INST, TXT_PAGE_RELATIONSHIPS );
         pTabCtrl->registerControl (IDC_CMB_RESP2_PRIM_CARE_GIVER, TXT_PAGE_RELATIONSHIPS );
         pTabCtrl->registerControl (IDC_STC_RESP2_PRIM_CARE_GIVER, TXT_PAGE_RELATIONSHIPS );
         pTabCtrl->registerControl (IDC_CMB_RESP2_GEN_RT511, TXT_PAGE_RELATIONSHIPS );
         pTabCtrl->registerControl (IDC_STC_RESP2_GEN_RT511, TXT_PAGE_RELATIONSHIPS );
         pTabCtrl->registerControl (IDC_DTP_RESP2_CUT_OFF_DATE, TXT_PAGE_RELATIONSHIPS );
         pTabCtrl->registerControl (IDC_STC_RESP2_CUT_OFF_DATE, TXT_PAGE_RELATIONSHIPS );

         ReInitControl( IDC_CMB_RESP2_PARENT_LEGAL_GUARD,
                        IFASTBP_PROC::ENTITY_LIST,
                        ifds::RES2ParentLglList,
                        CTRLFLAG_INITCOMBO_BY_SUB_LIST );

         ReInitControl( IDC_CMB_RESP2_DESIGNATED_INST,
                        IFASTBP_PROC::ENTITY_LIST,
                        ifds::RES2DesInstList,
                        CTRLFLAG_INITCOMBO_BY_SUB_LIST );

         ReInitControl( IDC_CMB_RESP2_PRIM_CARE_GIVER,
                        IFASTBP_PROC::ENTITY_LIST,
                        ifds::RES2PCGList,
                        CTRLFLAG_INITCOMBO_BY_SUB_LIST );

         ConnectControlsToData (RESP2_CONTROLS::RELATIONSHIPS, true);
         LoadControls (RESP2_CONTROLS::RELATIONSHIPS);
      }
   }
}

//******************************************************************************
void EntityMaintenanceDlg::removeTabPage (UINT iPageName)
{
   DSTTabCtrl* pTabCtrl = GetTabCtrl (IDC_TAB_ENTITY_MAINTENANCE);
   if (pTabCtrl == NULL)
   {
      return;
   }

   //remove controls registered with the page
   if( iPageName == TXT_PAGE_BENEFICIARY )
   {
      if (pTabCtrl->HasTab (TXT_PAGE_BENEFICIARY))
      {
         pTabCtrl->removeControlFromPage (IDC_STC_RESP2_RELATION_TO_OWNER, TXT_PAGE_BENEFICIARY);
         pTabCtrl->removeControlFromPage (IDC_CMB_RESP2_RELATION_TO_OWNER, TXT_PAGE_BENEFICIARY);
         pTabCtrl->removeControlFromPage (IDC_STC_RESP2_LETTER_DATE, TXT_PAGE_BENEFICIARY);
         pTabCtrl->removeControlFromPage (IDC_DTP_RESP2_LETTER_DATE, TXT_PAGE_BENEFICIARY);
         pTabCtrl->removeControlFromPage (IDC_STC_RESP2_REASON, TXT_PAGE_BENEFICIARY);
         pTabCtrl->removeControlFromPage (IDC_CMB_RESP2_REASON, TXT_PAGE_BENEFICIARY);
         pTabCtrl->removeControlFromPage (IDC_STC_RESP2_TAX_JUR, TXT_PAGE_BENEFICIARY);
         pTabCtrl->removeControlFromPage (IDC_CMB_RESP2_TAX_JUR, TXT_PAGE_BENEFICIARY);
         pTabCtrl->removeControlFromPage (IDC_STC_RESP2_PRINTED, TXT_PAGE_BENEFICIARY);
         pTabCtrl->removeControlFromPage (IDC_CMB_RESP2_PRINTED, TXT_PAGE_BENEFICIARY);
         pTabCtrl->removeControlFromPage (IDC_STC_RESP2_ALLOCATION_PRCNT, TXT_PAGE_BENEFICIARY);
         pTabCtrl->removeControlFromPage (IDC_EDT_RESP2_ALLOCATION_PRCNT, TXT_PAGE_BENEFICIARY);
         pTabCtrl->removeControlFromPage (IDC_STC_RESP2_REQUEST_GRANT, TXT_PAGE_BENEFICIARY);
         pTabCtrl->removeControlFromPage (IDC_CMB_RESP2_REQUEST_GRANT, TXT_PAGE_BENEFICIARY);
         pTabCtrl->removeControlFromPage (IDC_STC_RESP2_TAINTED, TXT_PAGE_BENEFICIARY);
         pTabCtrl->removeControlFromPage (IDC_CMB_RESP2_TAINTED, TXT_PAGE_BENEFICIARY);
         pTabCtrl->removeControlFromPage (IDC_STC_RESP2_TAINTED_END_DATE, TXT_PAGE_BENEFICIARY);
         pTabCtrl->removeControlFromPage (IDC_DTP_RESP2_TAINTED_END_DATE, TXT_PAGE_BENEFICIARY);
         pTabCtrl->removeControlFromPage (IDC_BTN_GRANT, TXT_PAGE_BENEFICIARY);

         pTabCtrl->RemoveTab (TXT_PAGE_BENEFICIARY);
         //also, hide the controls
         GetControl (IDC_STC_RESP2_RELATION_TO_OWNER)->Show (false);
         GetControl (IDC_CMB_RESP2_RELATION_TO_OWNER)->Show (false);
         GetControl (IDC_STC_RESP2_LETTER_DATE)->Show (false);
         GetControl (IDC_DTP_RESP2_LETTER_DATE)->Show (false);
         GetControl (IDC_STC_RESP2_REASON)->Show (false);
         GetControl (IDC_CMB_RESP2_REASON)->Show (false);
         GetControl (IDC_STC_RESP2_TAX_JUR)->Show (false);
         GetControl (IDC_CMB_RESP2_TAX_JUR)->Show (false);
         GetControl (IDC_STC_RESP2_PRINTED)->Show (false);
         GetControl (IDC_CMB_RESP2_PRINTED)->Show (false);
         GetControl (IDC_STC_RESP2_ALLOCATION_PRCNT)->Show (false);
         GetControl (IDC_EDT_RESP2_ALLOCATION_PRCNT)->Show (false);
         GetControl (IDC_STC_RESP2_REQUEST_GRANT)->Show (false);
         GetControl (IDC_CMB_RESP2_REQUEST_GRANT)->Show (false);
         GetControl (IDC_STC_RESP2_TAINTED)->Show (false);
         GetControl (IDC_CMB_RESP2_TAINTED)->Show (false);
         GetControl (IDC_STC_RESP2_TAINTED_END_DATE)->Show (false);
         GetControl (IDC_DTP_RESP2_TAINTED_END_DATE)->Show (false);
         GetControl (IDC_BTN_GRANT)->Show (false);

         ConnectControlsToData (RESP2_CONTROLS::BENEF_INFO, false);
      }
   }
   else if (iPageName == TXT_PAGE_RELATIONSHIPS)
   {
      if (pTabCtrl->HasTab (TXT_PAGE_RELATIONSHIPS))
      {
         pTabCtrl->removeControlFromPage (IDC_CMB_RESP2_PARENT_LEGAL_GUARD, TXT_PAGE_RELATIONSHIPS );
         pTabCtrl->removeControlFromPage (IDC_STC_RESP2_PARENT_LEGAL_GUARD, TXT_PAGE_RELATIONSHIPS );
         pTabCtrl->removeControlFromPage (IDC_CMB_RESP2_DESIGNATED_INST, TXT_PAGE_RELATIONSHIPS );
         pTabCtrl->removeControlFromPage (IDC_STC_RESP2_DESIGNATED_INST, TXT_PAGE_RELATIONSHIPS );
         pTabCtrl->removeControlFromPage (IDC_CMB_RESP2_PRIM_CARE_GIVER, TXT_PAGE_RELATIONSHIPS );
         pTabCtrl->removeControlFromPage (IDC_STC_RESP2_PRIM_CARE_GIVER, TXT_PAGE_RELATIONSHIPS );
         pTabCtrl->removeControlFromPage (IDC_CMB_RESP2_GEN_RT511, TXT_PAGE_RELATIONSHIPS );
         pTabCtrl->removeControlFromPage (IDC_STC_RESP2_GEN_RT511, TXT_PAGE_RELATIONSHIPS );
         pTabCtrl->removeControlFromPage (IDC_DTP_RESP2_CUT_OFF_DATE, TXT_PAGE_RELATIONSHIPS );
         pTabCtrl->removeControlFromPage (IDC_STC_RESP2_CUT_OFF_DATE, TXT_PAGE_RELATIONSHIPS );

         pTabCtrl->RemoveTab (TXT_PAGE_RELATIONSHIPS);
         //also, hide the controls
         GetControl (IDC_CMB_RESP2_PARENT_LEGAL_GUARD)->Show (false);
         GetControl (IDC_STC_RESP2_PARENT_LEGAL_GUARD)->Show (false);
         GetControl (IDC_CMB_RESP2_DESIGNATED_INST)->Show (false);
         GetControl (IDC_STC_RESP2_DESIGNATED_INST)->Show (false);
         GetControl (IDC_CMB_RESP2_PRIM_CARE_GIVER)->Show (false);
         GetControl (IDC_STC_RESP2_PRIM_CARE_GIVER)->Show (false);
         GetControl (IDC_CMB_RESP2_GEN_RT511)->Show (false);
         GetControl (IDC_STC_RESP2_GEN_RT511)->Show (false);
         GetControl (IDC_DTP_RESP2_CUT_OFF_DATE)->Show (false);
         GetControl (IDC_STC_RESP2_CUT_OFF_DATE)->Show (false);

         ConnectControlsToData (RESP2_CONTROLS::RELATIONSHIPS, false);
      }
   }
}

//******************************************************************************
void EntityMaintenanceDlg::hideAllExistingRESPControls ()
{
   ConnectControlToData (IDC_CMB_RELATION, false);
   ConnectControlToData (IDC_EDT_PRC_BENEFIT, false);
   
   GetDlgItem( IDC_FRM_BENEFICIARY )->ShowWindow( SW_HIDE );
   GetDlgItem( IDC_TXT_RELATIONSHIP_TO_OWNER )->ShowWindow( SW_HIDE );
   GetDlgItem( IDC_CMB_RELATION )->ShowWindow( SW_HIDE );
   GetDlgItem( IDC_TXT_TAX_JURISD )->ShowWindow( SW_HIDE );
   
   DString strMarket = DSTCommonFunctions::getMarket();

   if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
   {
      ConnectControlToData( IDC_EDT_LETTER_DATE, false );
      ConnectControlToData( IDC_EDT_PRINTED, false );
      ConnectControlToData( IDC_CMB_REASON, false );
      ConnectControlToData( IDC_CMB_RESP_TAX_JURISD, false );
      GetDlgItem( IDC_TXT_LETTER_DATE )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_EDT_LETTER_DATE )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_TXT_PRINTED )->ShowWindow( SW_HIDE);
      GetDlgItem( IDC_EDT_PRINTED )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_TXT_REASON )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_CMB_REASON )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_TXT_TAX_JURISD )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_CMB_RESP_TAX_JURISD )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_BTN_BEN_RELATION )->ShowWindow( SW_HIDE );
   }
}

//******************************************************************************
void EntityMaintenanceDlg::updateEmployeeClass(const DString &dstrValue)
{
   DString dstrNameLength;

   getParent()->getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::NAME_LENGTH, dstrNameLength, false );

   int iMaxCharNum = dstrNameLength.asInteger();
   bool bShowName = dstrValue == CODE_CATEGORY_CORPORATE;

   DSTTabCtrl* pTabCtrl = GetTabCtrl (IDC_TAB_ENTITY_MAINTENANCE);
   if (pTabCtrl != NULL)
   {
      CString cstrRelationPageName, cstrPageName;
      TCITEM tcItem;
      wchar_t buffer[256] = {0};
      tcItem.pszText = buffer;
      tcItem.cchTextMax = 256;
      tcItem.mask = TCIF_TEXT;

      int iPagePos = pTabCtrl->GetCurSel();
      pTabCtrl->GetItem(iPagePos, &tcItem);

      cstrPageName = tcItem.pszText;
      cstrRelationPageName.LoadString( TXT_PAGE_DETAILS );

      if( cstrRelationPageName == cstrPageName )
      {
         if ( bShowName )
         {
            GetDlgItem (IDC_EDT_FIRST_NAME)->ShowWindow( SW_HIDE );
            GetDlgItem (IDC_EDT_LAST_NAME)->ShowWindow( SW_HIDE );
            GetDlgItem (IDC_STC_FIRST_NAME)->ShowWindow( SW_HIDE );
            GetDlgItem (IDC_STC_LAST_NAME)->ShowWindow( SW_HIDE );
            GetDlgItem (IDC_STATIC_SALUTATION)->ShowWindow( SW_HIDE );
            GetDlgItem (IDC_EDT_NAME)->ShowWindow( SW_SHOW );
            GetDlgItem (IDC_STC_NAME)->ShowWindow( SW_SHOW );

			if (m_bPaternalMaternal)
			{
				GetDlgItem (IDC_EDT_FIRST_NAME_DOUBLE)->ShowWindow( SW_HIDE);
				GetDlgItem (IDC_EDT_PATERNAL_NAME)->ShowWindow( SW_HIDE );
				GetDlgItem (IDC_EDT_MATERNAL_NAME)->ShowWindow( SW_HIDE );
				GetDlgItem (IDC_STC_PATERNAL_NAME)->ShowWindow( SW_HIDE );
				GetDlgItem (IDC_STC_MATERNAL_NAME)->ShowWindow( SW_HIDE );
			}

            pTabCtrl->removeControlFromPage (IDC_EDT_FIRST_NAME, TXT_PAGE_DETAILS );
            pTabCtrl->removeControlFromPage (IDC_EDT_LAST_NAME, TXT_PAGE_DETAILS );
            pTabCtrl->removeControlFromPage (IDC_STC_FIRST_NAME, TXT_PAGE_DETAILS );
            pTabCtrl->removeControlFromPage (IDC_STC_LAST_NAME, TXT_PAGE_DETAILS );
            pTabCtrl->registerControl (IDC_EDT_NAME, TXT_PAGE_DETAILS );
            pTabCtrl->registerControl (IDC_STC_NAME, TXT_PAGE_DETAILS );

			if (m_bPaternalMaternal)
			{
				pTabCtrl->removeControlFromPage (IDC_EDT_FIRST_NAME_DOUBLE, TXT_PAGE_DETAILS );
				pTabCtrl->removeControlFromPage (IDC_EDT_PATERNAL_NAME, TXT_PAGE_DETAILS );
				pTabCtrl->removeControlFromPage (IDC_EDT_MATERNAL_NAME, TXT_PAGE_DETAILS );
				pTabCtrl->removeControlFromPage (IDC_STC_PATERNAL_NAME, TXT_PAGE_DETAILS );
				pTabCtrl->removeControlFromPage (IDC_STC_MATERNAL_NAME, TXT_PAGE_DETAILS );
			}
         }
         else
         {
		   if (!m_bPaternalMaternal) 
		   {
            GetDlgItem (IDC_EDT_FIRST_NAME)->ShowWindow( SW_SHOW );
            GetDlgItem (IDC_EDT_LAST_NAME)->ShowWindow( SW_SHOW );
            GetDlgItem (IDC_STC_FIRST_NAME)->ShowWindow( SW_SHOW );
            GetDlgItem (IDC_STC_LAST_NAME)->ShowWindow( SW_SHOW );
            GetDlgItem (IDC_STATIC_SALUTATION)->ShowWindow( SW_SHOW );
            GetDlgItem (IDC_EDT_NAME)->ShowWindow( SW_HIDE );
            GetDlgItem (IDC_STC_NAME)->ShowWindow( SW_HIDE );

            pTabCtrl->registerControl (IDC_EDT_FIRST_NAME, TXT_PAGE_DETAILS );
            pTabCtrl->registerControl (IDC_EDT_LAST_NAME, TXT_PAGE_DETAILS );
            pTabCtrl->registerControl (IDC_STC_FIRST_NAME, TXT_PAGE_DETAILS );
            pTabCtrl->registerControl (IDC_STC_LAST_NAME, TXT_PAGE_DETAILS );
            pTabCtrl->removeControlFromPage (IDC_EDT_NAME, TXT_PAGE_DETAILS );
            pTabCtrl->removeControlFromPage (IDC_STC_NAME, TXT_PAGE_DETAILS );

			DString strMarket = DSTCommonFunctions::getMarket();
			if (strMarket == MARKET_IDS::LUXEMBOURG)
				{
					GetDlgItem (IDC_EDT_FIRST_NAME_DOUBLE)->ShowWindow( SW_HIDE);
					GetDlgItem (IDC_EDT_PATERNAL_NAME)->ShowWindow( SW_HIDE );
					GetDlgItem (IDC_EDT_MATERNAL_NAME)->ShowWindow( SW_HIDE );
					GetDlgItem (IDC_STC_PATERNAL_NAME)->ShowWindow( SW_HIDE );
					GetDlgItem (IDC_STC_MATERNAL_NAME)->ShowWindow( SW_HIDE );

					pTabCtrl->removeControlFromPage (IDC_EDT_FIRST_NAME_DOUBLE, TXT_PAGE_DETAILS );
					pTabCtrl->removeControlFromPage (IDC_EDT_PATERNAL_NAME, TXT_PAGE_DETAILS );
					pTabCtrl->removeControlFromPage (IDC_EDT_MATERNAL_NAME, TXT_PAGE_DETAILS );
					pTabCtrl->removeControlFromPage (IDC_STC_PATERNAL_NAME, TXT_PAGE_DETAILS );
					pTabCtrl->removeControlFromPage (IDC_STC_MATERNAL_NAME, TXT_PAGE_DETAILS );
				}
			}
			else {  // Double

				GetDlgItem (IDC_EDT_FIRST_NAME)->ShowWindow( SW_HIDE );
				GetDlgItem (IDC_EDT_LAST_NAME)->ShowWindow( SW_HIDE );
				GetDlgItem (IDC_STC_FIRST_NAME)->ShowWindow( SW_SHOW );
				GetDlgItem (IDC_STC_LAST_NAME)->ShowWindow( SW_HIDE );
				GetDlgItem (IDC_STATIC_SALUTATION)->ShowWindow( SW_SHOW );
				GetDlgItem (IDC_EDT_NAME)->ShowWindow( SW_HIDE );
				GetDlgItem (IDC_STC_NAME)->ShowWindow( SW_HIDE );

				GetDlgItem (IDC_EDT_FIRST_NAME_DOUBLE)->ShowWindow( SW_SHOW);
				GetDlgItem (IDC_EDT_PATERNAL_NAME)->ShowWindow( SW_SHOW );
				GetDlgItem (IDC_EDT_MATERNAL_NAME)->ShowWindow( SW_SHOW );
				GetDlgItem (IDC_STC_PATERNAL_NAME)->ShowWindow( SW_SHOW );
				GetDlgItem (IDC_STC_MATERNAL_NAME)->ShowWindow( SW_SHOW );

				pTabCtrl->registerControl (IDC_STC_FIRST_NAME, TXT_PAGE_DETAILS );
				pTabCtrl->registerControl (IDC_EDT_FIRST_NAME_DOUBLE, TXT_PAGE_DETAILS );
				pTabCtrl->registerControl (IDC_EDT_PATERNAL_NAME, TXT_PAGE_DETAILS );
				pTabCtrl->registerControl (IDC_EDT_MATERNAL_NAME, TXT_PAGE_DETAILS );
				pTabCtrl->registerControl (IDC_STC_PATERNAL_NAME, TXT_PAGE_DETAILS );
				pTabCtrl->registerControl (IDC_STC_MATERNAL_NAME, TXT_PAGE_DETAILS );

				pTabCtrl->removeControlFromPage (IDC_EDT_FIRST_NAME, TXT_PAGE_DETAILS );
				pTabCtrl->removeControlFromPage (IDC_EDT_LAST_NAME, TXT_PAGE_DETAILS );
				pTabCtrl->removeControlFromPage (IDC_STC_LAST_NAME, TXT_PAGE_DETAILS );
				pTabCtrl->removeControlFromPage (IDC_EDT_NAME, TXT_PAGE_DETAILS );
				pTabCtrl->removeControlFromPage (IDC_STC_NAME, TXT_PAGE_DETAILS );

			}
            
         }
         //GetDlgItem (IDC_EDT_FIRST_NAME)->ShowWindow( bShowName ? SW_HIDE : SW_SHOW );
         //GetDlgItem (IDC_EDT_LAST_NAME)->ShowWindow( bShowName ? SW_HIDE : SW_SHOW  );
         //GetDlgItem (IDC_STC_FIRST_NAME)->ShowWindow( bShowName ? SW_HIDE : SW_SHOW  );
         //GetDlgItem (IDC_STC_LAST_NAME)->ShowWindow( bShowName ? SW_HIDE : SW_SHOW  );
         //GetDlgItem (IDC_STATIC_SALUTATION)->ShowWindow( bShowName ? SW_HIDE : SW_SHOW  );
         
         if( m_bSalutationFreeFormat )
         {
            GetDlgItem ( IDC_EDT_SALUTATION )->ShowWindow( bShowName ? SW_HIDE : SW_SHOW);
            GetDlgItem ( IDC_CMB_SALUTATION )->ShowWindow( SW_HIDE );
         }
         else
         {
            GetDlgItem ( IDC_EDT_SALUTATION )->ShowWindow( SW_HIDE );
            GetDlgItem ( IDC_CMB_SALUTATION )->ShowWindow( bShowName ? SW_HIDE : SW_SHOW );
         }

		 if (!m_bPaternalMaternal) {
			 ConnectControlToData (IDC_EDT_LAST_NAME, !bShowName);
			 ConnectControlToData (IDC_EDT_FIRST_NAME, !bShowName);
			 ConnectControlToData (IDC_EDT_NAME, bShowName);
		 }
		 else {

			 ConnectControlToData (IDC_EDT_FIRST_NAME_DOUBLE, !bShowName);
			 ConnectControlToData (IDC_EDT_PATERNAL_NAME, !bShowName);
			 ConnectControlToData (IDC_EDT_MATERNAL_NAME, !bShowName);
			 ConnectControlToData (IDC_EDT_NAME, bShowName);
			 ConnectControlToData (IDC_EDT_LAST_NAME, false);
			 ConnectControlToData (IDC_EDT_FIRST_NAME, false);
		 }

         if (iMaxCharNum > 0)
         {
            dynamic_cast <DSTEdit *>( GetControl( bShowName ? IDC_EDT_NAME : IDC_EDT_LAST_NAME ) )->SetMaxCharNum( iMaxCharNum );
         }
         else
         {
            // Use default maximum number of characters if category value is 0 or undefined.
            if (bShowName)
            {
               dynamic_cast< DSTEdit * >( GetControl( IDC_EDT_NAME ) )->SetMaxCharNum( 80 );
            }
            else 
			{
				if (!m_bPaternalMaternal)
					dynamic_cast< DSTEdit * >( GetControl( IDC_EDT_LAST_NAME ) )->SetMaxCharNum( 40 );
				else  {
				 dynamic_cast< DSTEdit * >( GetControl( IDC_EDT_PATERNAL_NAME ) )->SetMaxCharNum( 40 );
				 dynamic_cast< DSTEdit * >( GetControl( IDC_EDT_MATERNAL_NAME ) )->SetMaxCharNum( 40 );
			    } 
			}  
         }

         if( bShowName )
         {
            LoadControl (IDC_EDT_NAME);
         }
         else
         {
			if (!m_bPaternalMaternal)
			{
				LoadControl (IDC_EDT_FIRST_NAME);
				LoadControl (IDC_EDT_LAST_NAME);
			}
			else 
			{
				LoadControl (IDC_EDT_FIRST_NAME_DOUBLE);
				LoadControl (IDC_EDT_PATERNAL_NAME);
				LoadControl (IDC_EDT_MATERNAL_NAME);
			}
         }

         LoadControl (m_bSalutationFreeFormat ? IDC_EDT_SALUTATION : IDC_CMB_SALUTATION);
      }
      else
      {
         GetDlgItem (IDC_EDT_FIRST_NAME)->ShowWindow( SW_HIDE );
         GetDlgItem (IDC_EDT_LAST_NAME)->ShowWindow( SW_HIDE );
         GetDlgItem (IDC_STC_FIRST_NAME)->ShowWindow( SW_HIDE );
         GetDlgItem (IDC_STC_LAST_NAME)->ShowWindow( SW_HIDE );
         GetDlgItem (IDC_STATIC_SALUTATION)->ShowWindow( SW_HIDE );
         GetDlgItem (IDC_EDT_SALUTATION )->ShowWindow( SW_HIDE );
         GetDlgItem (IDC_CMB_SALUTATION )->ShowWindow( SW_HIDE );
         GetDlgItem (IDC_EDT_NAME)->ShowWindow ( SW_HIDE );
         GetDlgItem (IDC_STC_NAME)->ShowWindow ( SW_HIDE );

		 if (m_bPaternalMaternal) {
 			 GetDlgItem (IDC_EDT_FIRST_NAME_DOUBLE)->ShowWindow( SW_HIDE);
			 GetDlgItem (IDC_EDT_PATERNAL_NAME)->ShowWindow( SW_HIDE );
			 GetDlgItem (IDC_EDT_MATERNAL_NAME)->ShowWindow( SW_HIDE );
			 GetDlgItem (IDC_STC_PATERNAL_NAME)->ShowWindow( SW_HIDE );
			 GetDlgItem (IDC_STC_MATERNAL_NAME)->ShowWindow( SW_HIDE );
		 }
      }
   }
}

//******************************************************************************
bool EntityMaintenanceDlg::doDisableControl (UINT nID, bool bIsNew)
{
   bool disable = false;
   
   bool bIsRES2Client = 
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->isRES2Client();

   DString dstrEntityType, dstrSeq;
   getParent()->getField (this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityType, dstrEntityType, false);

   if( bIsRES2Client && dstrEntityType.strip().upperCase() == RESP_BENEFICIARY )
   {
      if (!hasUpdatePermission(UAF::RESP_BENEFICIARY ))
      {
         switch( nID )
         {
            case IDC_CMB_RESP2_RELATION_TO_OWNER :
            case IDC_DTP_RESP2_LETTER_DATE :
            case IDC_CMB_RESP2_REASON :
            case IDC_CMB_RESP2_TAX_JUR :
            case IDC_CMB_RESP2_PRINTED :
            case IDC_EDT_RESP2_ALLOCATION_PRCNT :
            case IDC_CMB_RESP2_REQUEST_GRANT :
            case IDC_CMB_RESP2_TAINTED :
            case IDC_DTP_RESP2_TAINTED_END_DATE :
            case IDC_CMB_RESP2_PARENT_LEGAL_GUARD :
            case IDC_CMB_RESP2_DESIGNATED_INST :
            case IDC_CMB_RESP2_PRIM_CARE_GIVER :
            case IDC_CMB_RESP2_GEN_RT511 :
            case IDC_DTP_RESP2_CUT_OFF_DATE :
               disable = true;
               break;
            default:
               break;
         }
      }
      if ( !hasUpdatePermission(UAF::RESP_ALLOCATION ) )
      {
         if ( nID == IDC_EDT_RESP2_ALLOCATION_PRCNT )
         {
            disable = true;
         }
      }
      else if ( !(hasUpdatePermission (UAF::RESP_GRANTS) || hasUpdatePermission(UAF::RESP_GRANT_INFORMATION)) )
      {
         if ( nID == IDC_CMB_RESP2_REQUEST_GRANT )
         {
            disable = true;
         }
      }

      if( nID == IDC_CMB_RESP2_GEN_RT511 || 
          nID == IDC_DTP_RESP2_CUT_OFF_DATE )
      {
         DString strPCGChange;      
         getParent()->getField(this, IFASTBP_PROC::ENTITY_LIST, ifds::PCGChange, strPCGChange, false);
         strPCGChange.strip().upperCase();
         
         if ( strPCGChange == I_("Y") && hasUpdatePermission(UAF::RESP_BENEFICIARY ) )
         {
            disable = false;
         }
         else
         {
            disable = true;
         }
      }
      else if ( nID == IDC_CHK_UPDATE_SHAREHOLDER_TAX_JURIS)
      {
         disable = true;
      }
   }
   return disable;
}

//******************************************************************************
void EntityMaintenanceDlg::updateRT511RelatedControls()
{
   DString strRec400Sent, strPCGChange;

   getParent()->getField(this, IFASTBP_PROC::ENTITY_LIST, ifds::Rec400Sent, strRec400Sent, false);
   getParent()->getField(this, IFASTBP_PROC::ENTITY_LIST, ifds::PCGChange, strPCGChange, false);
   strRec400Sent.strip().upperCase();
   strPCGChange.strip().upperCase();

   if ( strPCGChange == I_("Y") )
   {
      // null string for NASU
      if ( strRec400Sent.strip().upperCase() == I_("N") || 
           strRec400Sent.strip().upperCase() == NULL_STRING )
      {
         GetDlgItem( IDC_CMB_RESP2_GEN_RT511 )->ShowWindow( SW_HIDE );
         GetDlgItem( IDC_STC_RESP2_GEN_RT511 )->ShowWindow( SW_HIDE );
         GetDlgItem( IDC_DTP_RESP2_CUT_OFF_DATE )->ShowWindow( SW_HIDE );
         GetDlgItem( IDC_STC_RESP2_CUT_OFF_DATE )->ShowWindow( SW_HIDE );
      }
      else if ( strRec400Sent == I_("Y") )
      {
         GetDlgItem( IDC_CMB_RESP2_GEN_RT511 )->ShowWindow( SW_SHOW );
         GetDlgItem( IDC_STC_RESP2_GEN_RT511 )->ShowWindow( SW_SHOW );
         GetDlgItem( IDC_DTP_RESP2_CUT_OFF_DATE )->ShowWindow( SW_SHOW );
         GetDlgItem( IDC_STC_RESP2_CUT_OFF_DATE )->ShowWindow( SW_SHOW );
      }
   }
   else
   {
      GetDlgItem( IDC_CMB_RESP2_GEN_RT511 )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_STC_RESP2_GEN_RT511 )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_DTP_RESP2_CUT_OFF_DATE )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_STC_RESP2_CUT_OFF_DATE )->ShowWindow( SW_HIDE );
   }
}

//******************************************************************************
bool EntityMaintenanceDlg::doesSupportMstrActAMSC()
{
   DString dstrMstrActActive, dstrCSSStopSINMatch;
   bool doesSupportMstrActAMSC = false;

   if (dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getOption(ifds::MstrActActive, dstrMstrActActive, BF::HOST, false) <= WARNING &&
	   dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getOption(ifds::CSSStopSINMatch, dstrCSSStopSINMatch, BF::HOST, false) <= WARNING){ 
		   doesSupportMstrActAMSC = dstrMstrActActive == Y && dstrCSSStopSINMatch == Y;
   }

   return doesSupportMstrActAMSC;
}

//******************************************************************************
void EntityMaintenanceDlg::DisplayRDSPControls()
{
	DString taxType, entityType;

	getParent()->getField (this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityType, entityType, false);  
	getParent()->getField( this, ENTPROC::ACCOUNT_TAX_TYPE, taxType );
	taxType.strip(); 

	bool bShowRDSPRelnToBene = (entityType == ACCOUNT_OWNER_ENTITY_TYPE);
	if (taxType == RDSP_TAX_TYPE)
	{		
		GetDlgItem(IDC_TXT_RDSP_RELN_TO_BENE)->ShowWindow(bShowRDSPRelnToBene); 
		GetDlgItem(IDC_CMB_RDSP_RELN_TO_BENE)->ShowWindow(bShowRDSPRelnToBene);
		GetDlgItem(IDC_TXT_RDSP_CONSENT)->ShowWindow(true); 
		GetDlgItem(IDC_CMB_RDSP_CONSENT)->ShowWindow(true);
		GetDlgItem(IDC_TXT_RDSP_CONSENT_DATE)->ShowWindow(true); 
		GetDlgItem(IDC_DTP_RDSP_CONSENT_DATE)->ShowWindow(true);
	}
	else
	{			
		GetDlgItem(IDC_TXT_RDSP_RELN_TO_BENE)->ShowWindow(false); 
		GetDlgItem(IDC_CMB_RDSP_RELN_TO_BENE)->ShowWindow(false);
		GetDlgItem(IDC_TXT_RDSP_CONSENT)->ShowWindow(false); 
		GetDlgItem(IDC_CMB_RDSP_CONSENT)->ShowWindow(false);
		GetDlgItem(IDC_TXT_RDSP_CONSENT_DATE)->ShowWindow(false); 
		GetDlgItem(IDC_DTP_RDSP_CONSENT_DATE)->ShowWindow(false);
	}

	ConnectControlToData (IDC_CMB_RDSP_RELN_TO_BENE, true);
	LoadControl (IDC_CMB_RDSP_RELN_TO_BENE);
	ConnectControlToData (IDC_CMB_RDSP_CONSENT, true);
	LoadControl (IDC_CMB_RDSP_CONSENT);
	ConnectControlToData (IDC_DTP_RDSP_CONSENT_DATE, true);
	LoadControl (IDC_DTP_RDSP_CONSENT_DATE);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/EntityMaintenanceDlg.cpp-arc  $
 * 
 *    Rev 1.194   Jul 17 2012 10:47:14   dchatcha
 * P0179630 FN01 FATCA Project - Entity level.
 * 
 *    Rev 1.193   Jul 17 2012 10:30:20   dchatcha
 * P0191601 FN03 - Manual T3/RL 16/NR4 Slip for Taxable Trusts, code review.
 * 
 *    Rev 1.192   Jul 16 2012 12:29:14   dchatcha
 * P0179630 FN01 FATCA Project - Entity level.
 * 
 *    Rev 1.191   Jul 12 2012 11:35:20   dchatcha
 * P0191601 FN03 - Manual T3/RL 16/NR4 Slip for Taxable Trusts.
 * 
 *    Rev 1.190   Jun 13 2012 15:23:04   if991250
 * IN:2986990 - Connect the RESP Beneficiary controls only if the entity tyoe is RESP Beneficiary
 * 
 *    Rev 1.189   May 09 2012 13:30:10   wp040132
 * IN2946622 - Desktop crashes when primary/secondary beneficiary entity type is selected - primary/secondary beneficiary will execute only for canadian market
 * 
 *    Rev 1.188   Apr 16 2012 17:28:54   if991250
 * CPF Account Setup
 * 
 *    Rev 1.187   Apr 04 2012 22:53:50   wp040039
 * PETP0187485-Entity Maintenance
 * 
 *    Rev 1.186   Feb 08 2012 04:54:26   panatcha
 * DesktopWeb conversion
 * 
 *    Rev 1.185   Feb 06 2012 04:47:50   panatcha
 * IN2780013 - SOC Loan Number and Loan Type
 * 
 *    Rev 1.184   Nov 25 2011 16:00:42   wp040168
 * P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
 * 
 *    Rev 1.183   Nov 21 2011 18:45:22   wp040168
 * P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
 * 
 *    Rev 1.182   Nov 19 2011 01:31:18   wp040143
 * P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
 * 
 *    Rev 1.181   Sep 02 2011 13:09:32   kitticha
 * PETP0186486 FN01 - RRSP Loan Program.
 * 
 *    Rev 1.180   Aug 16 2011 12:34:40   dchatcha
 * IN# 2624559 - End of TFSA and Death Settlement Date issue
 * 
 *    Rev 1.179   Jul 18 2011 20:16:44   dchatcha
 * P0180786 FN01 - TFSA Estate and Right of Rescission Tax Reporting.
 * 
 *    Rev 1.178   May 23 2011 07:54:36   wutipong
 * IN2463594 - Issue with entity linking
 * 
 *    Rev 1.177   Mar 24 2011 23:09:30   panatcha
 * IN2468888_WO603231 - BIP_IFASTDSKTOP_ERROR MESSAGE
 * 
 *    Rev 1.176   Jan 14 2011 16:23:58   dchatcha
 * IN# 2389426 - P0165541FN12 - DSK Edits and Labels
 * 
 *    Rev 1.175   Dec 08 2010 15:01:24   jankovii
 * PET0165541 FN03 - QESI Phase3. More parameter is required for Tax Jurisdiction History screen.
 * 
 *    Rev 1.174   Dec 07 2010 16:35:58   popescu
 * PET0165541 FN03 - QESI Phase3. More parameter is required for Tax Jurisdiction History screen.
 * 
 *    Rev 1.173   Nov 18 2010 21:49:48   dchatcha
 * PET0165541 FN03 - QESI Phase3. More parameter is required for Tax Jurisdiction History screen.
 * 
 *    Rev 1.172   Aug 16 2010 06:28:30   panatcha
 * P0172931_FN01_MT53X_Entity Creation
 * 
 *    Rev 1.171   Jul 09 2010 00:31:04   popescu
 * Incident 2179841 - PCG# should accept alpha-chars and 15 of them
 * 
 *    Rev 1.170   Jun 23 2010 07:05:14   panatcha
 * PET0166541_FN01_IN2157424 - Add LoadControl function for dispalying Reason combobox in RespBeneficiary. 
 * 
 *    Rev 1.169   Jun 09 2010 23:52:50   panatcha
 * PET0166541_FN02_IN2142963 - change  checking the permission of the tax juris hist button from hasUpdatePermission to hasReadPermission.
 * 
 *    Rev 1.168   Jun 09 2010 07:41:12   panatcha
 * PET0166541_FN02_IN2142963 - update enable/disable  Tax Juris Hist button for RESP2 product
 * 
 *    Rev 1.167   May 27 2010 02:41:46   dchatcha
 * Incident 2112443 - PET165541 - RT511 and Generate Notification letter - Generatr RT511 and RT511 cut-off-date is read-only when PCG is changed.
 * 
 *    Rev 1.166   May 26 2010 16:21:32   jankovii
 * IN 2130000 - PET165541 -  Access to Grant SCreen and Bene Alloc disabled
 * 
 *    Rev 1.165   May 18 2010 02:15:10   dchatcha
 * RESP/QESI fixes, disable 'update shareholder tax juris' for RESP Benef.
 * 
 *    Rev 1.164   May 11 2010 05:43:24   dchatcha
 * PET0165541 FN01 - Crash found during testing on PET17067.FN01.R1.0.
 * 
 *    Rev 1.163   May 10 2010 16:49:46   popescu
 * Incident 2112443 - PET165541 - RT511 and Generate Notification letter
 * 
 *    Rev 1.162   May 06 2010 23:36:16   popescu
 * RESP/QESI fixes
 * 
 *    Rev 1.161   May 03 2010 17:44:54   popescu
 * PET0165541 FN01 QESI RESP Trading - New account set-up fixes
 * 
 *    Rev 1.160   Apr 27 2010 21:00:20   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU, title for the browser screens
 * 
 *    Rev 1.159   Apr 26 2010 03:36:50   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU, RT511 related fields still open for chaning.
 * 
 *    Rev 1.158   Apr 26 2010 00:43:46   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU, overlapped control.
 * 
 *    Rev 1.157   Apr 12 2010 23:52:18   popescu
 * PET165541_FN01_QESI - R99 crash in international markets..
 * 
 *    Rev 1.156   Apr 06 2010 06:15:46   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU, enable delete button for non-res2 env.
 * 
 *    Rev 1.155   Apr 05 2010 00:31:00   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU, put priotity of right to update RESP beneficiary is higher than RESP Grant.
 * 
 *    Rev 1.154   Apr 03 2010 02:42:30   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.153   Mar 31 2010 08:16:46   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.152   Mar 29 2010 07:09:00   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.151   Mar 26 2010 09:09:24   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.150   Mar 25 2010 14:57:26   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.149   Mar 23 2010 12:40:22   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU, control overlapped.
 * 
 *    Rev 1.148   Mar 23 2010 13:33:50   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.147   Mar 19 2010 11:09:42   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.146   Mar 18 2010 16:50:06   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.145   Mar 18 2010 16:47:52   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.144   Mar 17 2010 06:25:18   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.143   Mar 16 2010 18:07:54   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU - browser integration
 * 
 * 
 *    Rev 1.142   Mar 12 2010 14:50:44   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.141   Jan 26 2010 13:42:28   jankovii
 * PET165541 FN01 - QESI - RESP Gap
 * 
 *    Rev 1.140   Jul 29 2009 17:16:22   wutipong
 * IIN1764677 - Issues with Annuitant Entity- ECF
 * 
 *    Rev 1.139   10 Jul 2009 12:18:04   popescu
 * Incident 1750100 - Incident 1387527 - back-out code 
 * 
 *    Rev 1.138   Apr 22 2009 15:20:04   jankovii
 * IN 1667200 - R92: Title for the drop down menu in the entity maintenance 
 * 
 *    Rev 1.137   Mar 23 2009 15:40:20   jankovii
 * IN 1623318 - R91 - Desktop - Entity field is greyed out if "Whereused" option selected
 * 
 *    Rev 1.136   Mar 23 2009 04:59:02   wutipong
 * IN#1387527 - Error when using Spousal entity type
 * 
 *    Rev 1.135   Mar 20 2009 10:46:44   jankovii
 * IN 1623163 - Entity Search button not available
 * 
 *    Rev 1.134   23 Jan 2009 16:32:44   popescu
 * Incident 	1548019 - reset button on entitymaintenance dlg, BIC Code can be valid/invalid for entitytype 58
 * 
 *    Rev 1.133   16 Jan 2009 17:23:28   popescu
 * Incident 1544134 - various fixes
 * 
 *    Rev 1.132   Jan 08 2009 05:51:54   daechach
 * IN 1545482 - R91-MT535/MT536-users should not be able to create Clearing platform entities.
 * 
 *    Rev 1.131   Jan 07 2009 04:52:58   daechach
 * IN 1544134 - R91-MT535/MT536-Clearing platform BIC code disp blank, etc.
 * 
 *    Rev 1.130   Dec 15 2008 02:06:16   phiwponp
 * PET0007773_FN01_MT535-MT536 Enhancement.
 * 
 *    Rev 1.129   31 Oct 2008 16:19:24   popescu
 * KYC/AML - joint accounts feature
 * 
 *    Rev 1.128   Oct 28 2008 08:36:10   jankovii
 * PET 59888 FN03 AML KYC.
 * 
 *    Rev 1.127   Oct 22 2008 04:13:34   daechach
 * in# 1442842 - KYC Desktop: multiple entities - KYC save issue.
 * 
 *    Rev 1.126   Sep 12 2008 07:10:10   daechach
 * PET0128026 - KYC Phase 2
 * 
 *    Rev 1.125   Aug 29 2008 14:36:10   jankovii
 * IN 1388930.
 * 
 *    Rev 1.124   Jul 25 2008 14:39:56   jankovii
 * PET 59888 - AML Enhancement.
 * 
 *    Rev 1.123   04 Sep 2007 12:49:50   popescu
 * GAP 6 - new id status added to the screen
 * 
 *    Rev 1.122   Aug 31 2007 10:39:20   smithdav
 * IN 942582
 * 
 *    Rev 1.121   Aug 10 2007 17:59:16   ivespaul
 * PET2360 - Web Integration - removed mgmt fee button.
 * 
 *    Rev 1.119   01 Aug 2007 09:45:42   popescu
 * GAP 6 - CIF - also added UpdateAllCIF for vew 85
 * 
 *    Rev 1.118   Jul 31 2007 12:06:58   kovacsro
 * PET 2372 FN02 - FDP-AIM KYC - email2, etc...
 * 
 *    Rev 1.117   17 Jul 2007 15:19:10   popescu
 * GAP 6 CIF - AIM
 * 
 *    Rev 1.116   06 Jul 2007 14:43:58   popescu
 * PET 2363 GAP 6 CIF
 * 
 *    Rev 1.115   Jul 05 2007 16:51:04   popescu
 * Incident# 929895 - create a new entity if search by SIN is used
 * 
 *    Rev 1.114   27 Jun 2007 16:47:46   popescu
 * Incident# 929895 - enable search button and create a new entity if this is used.
 * 
 *    Rev 1.113   Jun 01 2007 14:15:10   porteanm
 * PET2271 FN06 - Enable/Disable entity selelction based on gc.
 * 
 *    Rev 1.112   Aug 25 2006 16:04:20   ZHANGCEL
 * Incident #694914 -- Add permission check for "Assignee Entity Type Setup"
 * 
 *    Rev 1.111   Jul 04 2006 12:05:12   ZHANGCEL
 * PET2145 FN01 -- Add logic to allow "Assignee" entity type related fields.
 * 
 *    Rev 1.110   Mar 13 2006 09:44:02   jankovii
 * Incident #564922- Blank Effective Date in Entity Maintenance screen.
 * 
 *    Rev 1.109   Dec 13 2005 12:37:14   popescu
 * Copy entity button should observe the same rules as the add entity button
 * 
 *    Rev 1.108   Nov 28 2005 10:02:40   zhengcon
 * Incident #457932 -- Disable controls when the Entity is disabled
 * 
 *    Rev 1.107   Nov 24 2005 09:07:18   jankovii
 * PET1228_FN02 EU Saving Directive Phase 2
 * 
 *    Rev 1.106   Sep 15 2005 15:11:26   popescu
 * Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 * 
 *    Rev 1.105   Aug 26 2005 14:59:02   porteanm
 * Incident 387905 - Send Trxnserror flag when the update view comes back with an error.
 * 
 *    Rev 1.104   Apr 08 2005 15:55:44   yingbaol
 * Incident284035:fix tab refresh issue
 * 
 *    Rev 1.103   Mar 30 2005 14:42:32   porteanm
 * Incident 2375271 - SIN validation, syncup from 1.95.1.0 and 1.96.1.0
 * 
 *    Rev 1.102   Mar 16 2005 11:09:52   porteanm
 * PET 1171 FN01 - EUSD Entity Address Update support.
 * 
 *    Rev 1.101   Mar 11 2005 14:58:54   porteanm
 * PET 1171 FN01 - EUSD Entity Address Update - work in progress.
 * 
 *    Rev 1.100   Mar 09 2005 16:01:44   yingbaol
 * PET1171,FN01:EU saving  fix  check box issue
 * 
 *    Rev 1.99   Mar 05 2005 10:33:16   porteanm
 * PET 1171 FN01 - EUSD Entity Address Search.
 * 
 *    Rev 1.98   Mar 04 2005 17:13:50   yingbaol
 * PET1171,FN01:EUSD add Tax jurisdiction
 * 
 *    Rev 1.97   Feb 25 2005 13:16:24   porteanm
 * PET 1171 FN01 - EUSD Entity Address Search - work in progress.
 * 
 *    Rev 1.96   Feb 10 2005 08:17:02   porteanm
 * PTS 10038225 - Enable/Disable Entity controls for Escrow based on escrow band.
 * 
 *    Rev 1.95   Dec 22 2004 13:36:40   hernando
 * PTS10037166 - Undid the changes in 1.94.
 * 
 *    Rev 1.94   Dec 15 2004 11:11:28   hernando
 * PET910 - Hide Area Code controls for non-Canadian markets.
 * 
 *    Rev 1.93   Nov 16 2004 16:15:20   hernando
 * PTS10034703 - Removed setting the DuplicateSINCheck field.
 * 
 *    Rev 1.92   Oct 27 2004 10:13:52   AGUILAAM
 * PTS 10034664 - flg_joint_controls assignment moved to ensure overlapped controls are displayed appropriately
 * 
 *    Rev 1.91   Jun 03 2004 13:36:24   popescu
 * PTS 10030936, registered four edit controls with the tab control only for the canadian market
 * 
 *    Rev 1.90   Apr 23 2004 17:37:40   HERNANDO
 * PET1027 FN02 - Added Tabs for Details and Contacts.
 * 
 *    Rev 1.89   Mar 08 2004 17:49:50   HERNANDO
 * PTS965 FN11 - Changed Caption for Historical Screen by passing parameters.
 * 
 *    Rev 1.88   Mar 03 2004 17:03:44   HERNANDO
 * Recovered historical functionality.  Rev. 1.87 accidentally removed this functionality.
 * 
 *    Rev 1.87   Mar 01 2004 17:13:38   ZHANGCEL
 * PTS 10027650: Bug fix for the "Joint Type" not being displayed. 
 * 
 *    Rev 1.86   Feb 28 2004 16:07:12   HERNANDO
 * PET965 FN11 - Additional historical enhancement.
 * 
 *    Rev 1.85   Feb 05 2004 12:31:18   YINGBAOL
 * PTS10026870:allow user to input charaters and numeric numbers, the length will be 35 for depositary bank account number
 * 
 *    Rev 1.84   Dec 03 2003 10:53:32   linmay
 * Fix format issue for PTS#10024823
 * 
 *    Rev 1.83   Nov 24 2003 14:04:42   linmay
 * Modify ControlUpdated(), TaxIDNum only allow Numeric value.
 * 
 *    Rev 1.82   Nov 19 2003 10:22:22   linmay
 * added TaxIDNum, and BirthPlace for SSB
 * 
 *    Rev 1.81   Nov 05 2003 12:01:56   popescu
 * PTS 10023748, show Relationship to ownere list even though the Beneficary box is grayed out.
 * 
 *    Rev 1.80   Oct 22 2003 11:47:12   YINGBAOL
 * PTS10022062 and PTS 10022418(item 1)
 * 
 *    Rev 1.79   Oct 14 2003 15:28:38   HERNANDO
 * PET859 FN08 / PET893 FN08 - Account name enhancement, and Salutation enhancement.
 * 
 *    Rev 1.78   Sep 12 2003 15:42:52   HSUCHIN
 * PTS 10021247 - bug fix for Lux Market where dialog was referencing resouces found in Canadian market without market check
 * 
 *    Rev 1.77   Aug 22 2003 14:54:48   FENGYONG
 * remove delete relate rules to cbo
 * 
 *    Rev 1.76   Aug 22 2003 12:22:02   FENGYONG
 * check spouse only for onwer
 * 
 *    Rev 1.75   Aug 21 2003 19:53:14   FENGYONG
 * KYC Joint info enhancement
 * 
 *    Rev 1.74   Aug 01 2003 11:37:00   HERNANDO
 * Occupation Field enhancments.
 * 
 *    Rev 1.73   Mar 21 2003 18:36:02   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.72   Mar 12 2003 09:21:10   sanchez
 * AddControl( CTRL_COMBO,.) for Nationality
 * 
 *    Rev 1.71   Oct 09 2002 23:55:38   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.70   Sep 30 2002 11:01:40   PURDYECH
 * BFFieldId no longer has operator long(), so explicit getId() calls are needed in places.
 * 
 *    Rev 1.69   Aug 29 2002 12:57:20   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.68   Jul 18 2002 11:41:52   KOVACSRO
 * PTS10009069. Disabled Delete button for existing first sequenced accountholder.
 * 
 *    Rev 1.67   Jul 12 2002 13:01:08   KOVACSRO
 * UpdatePermission should decide if controls are updateable or readonly rather than readPermission (by the way what we do if they don't have read permission?!)
 * 
 *    Rev 1.66   22 May 2002 19:16:00   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.65   30 Apr 2002 16:31:44   HERNANDO
 * Added AddControl for Combo box IDC_CMB_EMPLOYEECLASS for EmployeeClass.
 * 
 *    Rev 1.64   01 Apr 2002 16:23:10   HSUCHIN
 * PTS 10007114 - dialog enhancement, The salutation combo box now has blank as an option.
 * 
 *    Rev 1.63   27 Mar 2002 20:01:06   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.62   Jan 28 2002 11:27:32   YINGBAOL
 * HLLAPI Change
 * 
 *    Rev 1.61   06 Dec 2001 16:20:46   KOVACSRO
 * Added doSend.
 * 
 *    Rev 1.60   Nov 07 2001 17:58:02   ZHANGCEL
 * Haspermission changes
 * 
 *    Rev 1.59   Nov 01 2001 10:04:14   YINGBAOL
 * check ESCROW_BAND together with ESCROW
 * 
 *    Rev 1.58   Oct 11 2001 14:46:56   YINGBAOL
 * fix Available Beneficiary 
 * 
 *    Rev 1.57   Aug 21 2001 18:25:44   DINACORN
 * Minor change on entity name
 * 
 *    Rev 1.56   09 Aug 2001 13:21:08   HSUCHIN
 * added support for Area code for the Canadian market
 * 
 *    Rev 1.55   Jul 29 2001 15:11:08   YINGBAOL
 * fix crash due to do reset
 * 
 *    Rev 1.54   Jul 03 2001 16:29:16   ZHANGCEL
 * Fixed the bug for SIN field 
 * 
 *    Rev 1.53   14 Jun 2001 11:58:26   SMITHDAV
 * Removed references to UserAccessProcess.
 * 
 *    Rev 1.52   Jun 12 2001 14:22:28   DINACORN
 * Sync. up with SSB (1.47.1.3)
 * 
 *    Rev 1.51   05 Jun 2001 13:45:08   YINGZ
 * fix caption problem
 * 
 *    Rev 1.50   May 24 2001 14:05:50   YINGBAOL
 * sync. version 1.47.1.5
 * 
 *    Rev 1.49   22 May 2001 16:59:40   KOVACSRO
 * Sync up SSB (1.47.1.4)
 * 
 *    Rev 1.48   03 May 2001 14:07:34   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.47   Apr 02 2001 15:27:32   DINACORN
 * Used DSTCommonFunctions MARKET_IDS constants
 * 
 *    Rev 1.46   Apr 02 2001 15:02:32   HERNANDO
 * Modified entity type 'Successor' to use 'Relationship to owner'.
 * 
 *    Rev 1.45   27 Mar 2001 16:51:42   KOVACSRO
 * perm. check stuff
 * 
 *    Rev 1.44   01 Mar 2001 16:42:00   KOVACSRO
 * Modifications for permission check.
 * 
 *    Rev 1.43   Mar 01 2001 08:45:24   JANKAREN
 * bug fix for length of e-mail
 * 
 *    Rev 1.42   Feb 22 2001 10:11:32   BUZILAMI
 * fix  CFDS_CAN problem with the Overlapping part
 * 
 *    Rev 1.41   Feb 12 2001 16:26:04   DINACORN
 * Change "MSDW - Japan" to "Japan"
 * 
 *    Rev 1.40   Feb 05 2001 10:35:44   YINGBAOL
 * fix crash for M3
 * 
 *    Rev 1.39   Jan 23 2001 14:42:40   KOVACSRO
 * More fixes for Relation to owner.
 * 
 *    Rev 1.38   Jan 23 2001 14:30:26   KOVACSRO
 * Bug fixed for Relation to owner.
 * 
 *    Rev 1.37   Jan 15 2001 12:11:46   DINACORN
 * Change AddControl for IDC_EDT_ID_VALUE
 * 
 *    Rev 1.36   Jan 04 2001 11:58:46   ZHANGCEL
 * Fixed the bug regarding EntityType error icon and error message showing up problem
 * 
 *    Rev 1.35   Dec 20 2000 10:44:22   ZHANGCEL
 * Added a new function OnBtnCopyentity for CopyEntity requirement
 * 
 *    Rev 1.34   Dec 18 2000 10:14:26   DINACORN
 * Fix a bug (only for some accounts): when click OK, without any changes, don't go in Confirmation screen
 * 
 *    Rev 1.33   Dec 15 2000 12:06:16   KOVACSRO
 * 1.Modified DoListItemChanged.
 * 2.Added dummy item logic for permission check.
 * 
 *    Rev 1.32   Dec 05 2000 17:19:18   KOVACSRO
 * Added new item permission logic.
 * 
 *    Rev 1.31   Dec 01 2000 15:00:14   ZHANGCEL
 * Fixed the bug when entity search using IdValue and IdtType -- the LastName and FirstName have to be setted into AcctEntityXrefObject
 * 
 *    Rev 1.30   Dec 01 2000 11:52:06   KOVACSRO
 * 1.Bug fixed for TaxJurisCode.
 * 2.Added permission check.
 * 
 *    Rev 1.29   Nov 28 2000 13:36:06   KOVACSRO
 * quick fix for EntityType bug.
 * 
 *    Rev 1.28   Nov 13 2000 10:28:56   KOVACSRO
 * 1.Fixed Alt+S bug. 2.Force duplicate SIN check whenever a SIN is entered and user does not hit Search button, neither hits Alt+S.
 * 
 *    Rev 1.27   Oct 31 2000 15:41:02   KOVACSRO
 * Disabled 'Search' Btn for an existing Entity. Fixed crash.
 * 
 *    Rev 1.26   Oct 30 2000 15:42:14   KOVACSRO
 * Modified  EnableEntityPhoneControls() to be always enabled.
 * 
 *    Rev 1.25   Oct 27 2000 10:57:04   DINACORN
 * Show the Age
 * 
 *    Rev 1.24   Oct 19 2000 14:22:28   ZHANGCEL
 * Fixed the bug about FirstName missing  when user hits name search button
 * 
 *    Rev 1.23   Oct 18 2000 13:59:12   ZHANGCEL
 * Add code to stop user from entering a SIN more than 9 digits
 * 
 *    Rev 1.22   Oct 12 2000 11:48:26   DINACORN
 * Enabled EffectiveDate Control
 * 
 *    Rev 1.21   Sep 29 2000 13:59:04   DINACORN
 * Modified control for AmountAssign.; Disable the EntityHistory button for NASU
 * 
 *    Rev 1.20   Sep 26 2000 11:19:26   OLTEANCR
 * .
 * 
 *    Rev 1.19   Sep 26 2000 10:59:50   OLTEANCR
 * fixed fund/class dialog, removed shr. nr. & acc. nr. for NASU
 * 
 *    Rev 1.18   Sep 25 2000 17:02:32   DINACORN
 * Change AddControl for IDC_EDT_AMOUNT_ASSIGN
 * 
 *    Rev 1.17   Sep 25 2000 15:45:36   YINGBAOL
 * add HLLAPI entry for EntityHistory
 * 
 *    Rev 1.16   Sep 24 2000 13:06:08   YINGBAOL
 * fix newItem issue
 * 
 *    Rev 1.15   Aug 23 2000 13:13:04   YINGBAOL
 * clear error cross mark, when we actually do not have error
 * 
 *    Rev 1.14   Aug 21 2000 17:08:08   YINGBAOL
 * enable search if it is new....
 * 
 *    Rev 1.13   Aug 11 2000 15:58:56   YINGBAOL
 * change effetive date
 * 
 *    Rev 1.12   Aug 08 2000 13:21:44   YINGBAOL
 * fix RESPBeneficiary and PrimaryBenificiary issues
 * 
 *    Rev 1.11   Aug 04 2000 16:43:00   YINGBAOL
 * fix chrash in NASU
 * 
 *    Rev 1.10   Aug 02 2000 13:47:30   VADEANUM
 * Title Bar Standards
 * 
 *    Rev 1.9   Aug 01 2000 16:01:22   ZHANGCEL
 * SIN problem fixed
 * 
 *    Rev 1.8   Aug 01 2000 09:36:32   YINGBAOL
 * add delete logic
 * 
 *    Rev 1.7   Jul 26 2000 15:28:10   YINGBAOL
 * pass entityId instead of currentItemKey to RespBenifit
 * 
 *    Rev 1.6   Jul 26 2000 11:11:20   YINGBAOL
 * first version for C2
 * 
 *    Rev 1.5   Jul 04 2000 16:47:42   HUANGSHA
 * fixed the first & last name opening in kanji mode
 * 
 *    Rev 1.4   Apr 05 2000 12:31:24   DT24433
 * removed unused headers
 * 
 *    Rev 1.3   Mar 13 2000 16:15:14   VASILEAD
 * Fixed Entity for M3
 * 
 *    Rev 1.2   Mar 09 2000 14:30:54   VASILEAD
 * Updated Entity screen for C2
 * 
 *    Rev 1.1   Feb 17 2000 14:52:14   YINGZ
 * telex should be 13 dig
 * 
 *    Rev 1.0   Feb 15 2000 11:01:12   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.57   Feb 08 2000 13:10:22   VASILEAD
 * Added HLLAPI for EntityDetails
 * 
 *    Rev 1.56   Jan 30 2000 17:53:14   VASILEAD
 * Limited the maximum number of characters allowed to input
 * 
 *    Rev 1.55   Jan 28 2000 15:08:10   VASILEAD
 * Fixed diplaying Kana addresses
 * 
 *    Rev 1.54   Jan 26 2000 19:43:12   VASILEAD
 * Fixes
 * 
 *    Rev 1.53   Jan 25 2000 19:20:44   VASILEAD
 * Refresh stuff
 * 
 *    Rev 1.52   Jan 23 2000 19:34:32   VASILEAD
 * Reset functionality
 * 
 *    Rev 1.51   Jan 23 2000 16:44:50   VASILEAD
 * Reset functionality
 * 
 *    Rev 1.50   Jan 19 2000 18:21:26   VASILEAD
 * Fixed background search in NASU
 * 
 *    Rev 1.49   Jan 18 2000 18:38:16   VASILEAD
 * Updates fix
 * 
 *    Rev 1.48   Jan 18 2000 17:00:06   HUANGSHA
 * added kanji-kana converting routine
 * 
 *    Rev 1.47   Jan 18 2000 16:30:28   VASILEAD
 * ?
 * 
 *    Rev 1.46   Jan 14 2000 15:59:20   VASILEAD
 * Where used fixes
 * 
 *    Rev 1.45   Jan 13 2000 18:32:12   VASILEAD
 * Fixed error promotions
 * 
 *    Rev 1.44   Jan 13 2000 17:39:42   VASILEAD
 * Added support for catching errors
 * 
 *    Rev 1.43   Jan 12 2000 11:39:04   VASILEAD
 * Fixed compilation error 
 * 
 *    Rev 1.42   Jan 11 2000 14:35:44   VASILEAD
 * Fixed entity background search
 * 
 *    Rev 1.41   Jan 11 2000 10:28:54   VASILEAD
 * Business edits for Entity screen
 * 
 *    Rev 1.40   Jan 10 2000 16:15:04   VASILEAD
 * Added Joint information in Entity screen
 * 
 *    Rev 1.39   Jan 09 2000 14:58:32   VASILEAD
 * Corrected entity screen in the NASU
 * 
 *    Rev 1.38   Jan 07 2000 17:02:50   VASILEAD
 * Validations for Entity screen
 * 
 *    Rev 1.37   Jan 03 2000 12:07:00   DT24433
 * removed unused headers, misc.
 * 
 */

