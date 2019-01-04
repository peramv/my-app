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
//******************************************************************************
//
// ^FILE   : PriceAdditionalProcess.cpp
// ^AUTHOR : 
// ^DATE   : 13 May 2017
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : PriceAdditionalProcess.cpp
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "PriceAdditionalProcess.hpp"
#include "PriceAdditionalProcessIncludes.h"
#include <ifastcbo\dstcworksession.hpp>
#include <ifastcbo\fundmasterlist.hpp>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastcbo\PriceAdditionalList.hpp>
#include <ifastcbo\PriceAdditional.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_PRICE_ADDITIONAL;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_PRICE_ADDITIONAL;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator<PriceAdditionalProcess> processCreator(CMD_BPROC_PRICE_ADDITIONAL);

namespace 
{
	const I_CHAR * const CLASSNAME = I_("PriceAdditionalProcess");
}

namespace CND
{
    extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{   
    extern CLASS_IMPORT const BFDateFieldId ValueAsAt;
    extern CLASS_IMPORT const BFTextFieldId FundName;
    extern CLASS_IMPORT const BFTextFieldId rxFundCode;
    extern CLASS_IMPORT const BFTextFieldId rxClassCode;

    extern CLASS_IMPORT const BFTextFieldId TransType;
    extern CLASS_IMPORT const BFTextFieldId TransTypeDesc;
    extern CLASS_IMPORT const BFDecimalFieldId UnitValue;
    extern CLASS_IMPORT const BFDecimalFieldId ChgFactor;
}

namespace PRICE_ADDI
{
    extern CLASS_EXPORT I_CHAR * const UNIT_ID     = I_("UnitId");
    extern CLASS_EXPORT I_CHAR * const TRADE_DATE  = I_("TraeDate");
    extern CLASS_EXPORT I_CHAR * const FUND_CODE   = I_("FundCode");
    extern CLASS_EXPORT I_CHAR * const CLASS_CODE  = I_("ClassCode");

    extern CLASS_EXPORT I_CHAR * const PRICE_CODE = I_("PriceCode");
    extern CLASS_EXPORT I_CHAR * const UNIT_VALUE = I_("UnitValue");
    extern CLASS_EXPORT I_CHAR * const CHG_FACTOR = I_("ChgFactor");

    extern CLASS_EXPORT I_CHAR * const PRICE_CODE2 = I_("PriceCode2");
    extern CLASS_EXPORT I_CHAR * const UNIT_VALUE2 = I_("UnitValue2");
    extern CLASS_EXPORT I_CHAR * const CHG_FACTOR2 = I_("ChgFactor2");

    extern CLASS_EXPORT I_CHAR * const PRICE_CODE3 = I_("PriceCode3");
    extern CLASS_EXPORT I_CHAR * const UNIT_VALUE3 = I_("UnitValue3");
    extern CLASS_EXPORT I_CHAR * const CHG_FACTOR3 = I_("ChgFactor3");

    extern CLASS_EXPORT I_CHAR * const PRICE_CODE4 = I_("PriceCode4");
    extern CLASS_EXPORT I_CHAR * const UNIT_VALUE4 = I_("UnitValue4");
    extern CLASS_EXPORT I_CHAR * const CHG_FACTOR4 = I_("ChgFactor4");

    extern CLASS_EXPORT I_CHAR * const PRICE_CODE5 = I_("PriceCode5");
    extern CLASS_EXPORT I_CHAR * const UNIT_VALUE5 = I_("UnitValue5");
    extern CLASS_EXPORT I_CHAR * const CHG_FACTOR5 = I_("ChgFactor5");

	extern CLASS_EXPORT I_CHAR * const PRICE_CODE6 = I_("PriceCode6");
    extern CLASS_EXPORT I_CHAR * const UNIT_VALUE6 = I_("UnitValue6");
    extern CLASS_EXPORT I_CHAR * const CHG_FACTOR6 = I_("ChgFactor6");

	extern CLASS_EXPORT I_CHAR * const PRICE_CODE7 = I_("PriceCode7");
    extern CLASS_EXPORT I_CHAR * const UNIT_VALUE7 = I_("UnitValue7");
    extern CLASS_EXPORT I_CHAR * const CHG_FACTOR7 = I_("ChgFactor7");

	extern CLASS_EXPORT I_CHAR * const PRICE_CODE8 = I_("PriceCode8");
    extern CLASS_EXPORT I_CHAR * const UNIT_VALUE8 = I_("UnitValue8");
    extern CLASS_EXPORT I_CHAR * const CHG_FACTOR8 = I_("ChgFactor8");

	extern CLASS_EXPORT I_CHAR * const PRICE_CODE9 = I_("PriceCode9");
    extern CLASS_EXPORT I_CHAR * const UNIT_VALUE9 = I_("UnitValue9");
    extern CLASS_EXPORT I_CHAR * const CHG_FACTOR9 = I_("ChgFactor9");

	extern CLASS_EXPORT I_CHAR * const PRICE_CODE10 = I_("PriceCode10");
    extern CLASS_EXPORT I_CHAR * const UNIT_VALUE10 = I_("UnitValue10");
    extern CLASS_EXPORT I_CHAR * const CHG_FACTOR10 = I_("ChgFactor10");

	extern CLASS_EXPORT I_CHAR * const PRICE_CODE11 = I_("PriceCode11");
    extern CLASS_EXPORT I_CHAR * const UNIT_VALUE11 = I_("UnitValue11");
    extern CLASS_EXPORT I_CHAR * const CHG_FACTOR11 = I_("ChgFactor11");

	extern CLASS_EXPORT I_CHAR * const PRICE_CODE12 = I_("PriceCode12");
    extern CLASS_EXPORT I_CHAR * const UNIT_VALUE12 = I_("UnitValue12");
    extern CLASS_EXPORT I_CHAR * const CHG_FACTOR12 = I_("ChgFactor12");

	extern CLASS_EXPORT I_CHAR * const PRICE_CODE13 = I_("PriceCode13");
    extern CLASS_EXPORT I_CHAR * const UNIT_VALUE13 = I_("UnitValue13");
    extern CLASS_EXPORT I_CHAR * const CHG_FACTOR13 = I_("ChgFactor13");

	

}

//****************************************************************
PriceAdditionalProcess::PriceAdditionalProcess(GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand)
: AbstractProcess(pGIC, pGIParent, rCommand),
  _rpChildGI(NULL),
  _pPriceAdditionalList(NULL)
{
	TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);

    addContainer(IFASTBP_PROC::PRICE_ADDITIONAL_LIST, true);

    addFieldDetails(ifds::ValueAsAt, IFASTBP_PROC::PRICE_ADDITIONAL_LIST, SUBCLASS_PROCESS);
    addFieldDetails(ifds::rxFundCode, IFASTBP_PROC::PRICE_ADDITIONAL_LIST, SUBCLASS_PROCESS);
    addFieldDetails(ifds::rxClassCode, IFASTBP_PROC::PRICE_ADDITIONAL_LIST, SUBCLASS_PROCESS);
    addFieldDetails(ifds::FundName, IFASTBP_PROC::PRICE_ADDITIONAL_LIST, SUBCLASS_PROCESS);

    addFieldDetails(ifds::TransType, IFASTBP_PROC::PRICE_ADDITIONAL_LIST);
    addFieldDetails(ifds::TransTypeDesc, IFASTBP_PROC::PRICE_ADDITIONAL_LIST);
    addFieldDetails(ifds::UnitValue, IFASTBP_PROC::PRICE_ADDITIONAL_LIST);
    addFieldDetails(ifds::ChgFactor, IFASTBP_PROC::PRICE_ADDITIONAL_LIST);
}


//****************************************************************
PriceAdditionalProcess::~PriceAdditionalProcess()
{
    TRACE_DESTRUCTOR(CLASSNAME);

    if (_pPriceAdditionalList)
    {
        delete _pPriceAdditionalList;
        _pPriceAdditionalList = NULL;
    }
}


//****************************************************************
SEVERITY PriceAdditionalProcess::doInit()
{
	MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOINIT);
	SEVERITY sevRtn = SEVERE_ERROR;

	try
    {
        getParameter(PRICE_ADDI::TRADE_DATE, _tradeDate);
        getParameter(PRICE_ADDI::FUND_CODE, _fundCode);
        getParameter(PRICE_ADDI::CLASS_CODE, _classCode);

        getParameter(PRICE_ADDI::PRICE_CODE, _priceCode);
        getParameter(PRICE_ADDI::UNIT_VALUE, _unitValue);
        getParameter(PRICE_ADDI::CHG_FACTOR, _chgFactor);

        getParameter(PRICE_ADDI::PRICE_CODE2, _priceCode2);
        getParameter(PRICE_ADDI::UNIT_VALUE2, _unitValue2);
        getParameter(PRICE_ADDI::CHG_FACTOR2, _chgFactor2);

        getParameter(PRICE_ADDI::PRICE_CODE3, _priceCode3);
        getParameter(PRICE_ADDI::UNIT_VALUE3, _unitValue3);
        getParameter(PRICE_ADDI::CHG_FACTOR3, _chgFactor3);

        getParameter(PRICE_ADDI::PRICE_CODE4, _priceCode4);
        getParameter(PRICE_ADDI::UNIT_VALUE4, _unitValue4);
        getParameter(PRICE_ADDI::CHG_FACTOR4, _chgFactor4);

        getParameter(PRICE_ADDI::PRICE_CODE5, _priceCode5);
        getParameter(PRICE_ADDI::UNIT_VALUE5, _unitValue5);
        getParameter(PRICE_ADDI::CHG_FACTOR5, _chgFactor5);

		getParameter(PRICE_ADDI::PRICE_CODE6, _priceCode6);
        getParameter(PRICE_ADDI::UNIT_VALUE6, _unitValue6);
        getParameter(PRICE_ADDI::CHG_FACTOR6, _chgFactor6);

		getParameter(PRICE_ADDI::PRICE_CODE7, _priceCode7);
        getParameter(PRICE_ADDI::UNIT_VALUE7, _unitValue7);
        getParameter(PRICE_ADDI::CHG_FACTOR7, _chgFactor7);

		getParameter(PRICE_ADDI::PRICE_CODE8, _priceCode8);
        getParameter(PRICE_ADDI::UNIT_VALUE8, _unitValue8);
        getParameter(PRICE_ADDI::CHG_FACTOR8, _chgFactor8);

		getParameter(PRICE_ADDI::PRICE_CODE9, _priceCode9);
        getParameter(PRICE_ADDI::UNIT_VALUE9, _unitValue9);
        getParameter(PRICE_ADDI::CHG_FACTOR9, _chgFactor9);

		getParameter(PRICE_ADDI::PRICE_CODE10, _priceCode10);
        getParameter(PRICE_ADDI::UNIT_VALUE10, _unitValue10);
        getParameter(PRICE_ADDI::CHG_FACTOR10, _chgFactor10);

		getParameter(PRICE_ADDI::PRICE_CODE11, _priceCode11);
        getParameter(PRICE_ADDI::UNIT_VALUE11, _unitValue11);
        getParameter(PRICE_ADDI::CHG_FACTOR11, _chgFactor11);

		getParameter(PRICE_ADDI::PRICE_CODE12, _priceCode12);
        getParameter(PRICE_ADDI::UNIT_VALUE12, _unitValue12);
        getParameter(PRICE_ADDI::CHG_FACTOR12, _chgFactor12);

		getParameter(PRICE_ADDI::PRICE_CODE13, _priceCode13);
        getParameter(PRICE_ADDI::UNIT_VALUE13, _unitValue13);
        getParameter(PRICE_ADDI::CHG_FACTOR13, _chgFactor13);

	}
	catch( ConditionException &ce )
	{
		SETCONDITIONFROMEXCEPTION( ce );
	}
	catch( ... )
	{
		throw EXCEPTIONFROMFILE( CND::BP_ERR_UNKNOWN_EXCEPTION );
	}
	return(GETCURRENTHIGHESTSEVERITY());
}


//****************************************************************
E_COMMANDRETURN PriceAdditionalProcess::doProcess()
{  
	MAKEFRAME2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
	E_COMMANDRETURN rtn = CMD_FAILURE;

	try
	{
		if (isXMLAPIContext())
		{
			rtn = CMD_MODELESS_INPROCESS;
		}
		else
		{
			rtn = invokeCommand(this, CMD_GUI_PRICE_ADDITIONAL, getProcessType(), isModal(), &_rpChildGI);
		}
	}
	catch( ConditionException &ce )
	{
		SETCONDITIONFROMEXCEPTION( ce );
	}
	catch( ... )
	{
		throw EXCEPTIONFROMFILE( CND::BP_ERR_UNKNOWN_EXCEPTION );
	}

	return(rtn);
}

//****************************************************************
void PriceAdditionalProcess::doGetField(const GenericInterface *rpGICaller,
                                        const BFContainerId& idContainer,
                                        const BFFieldId& idField,
                                        const BFDataGroupId& idDataGroup,
                                        DString &strValueOut,
                                        bool bFormatted) const 
{
    if (idContainer ==  IFASTBP_PROC::PRICE_ADDITIONAL_LIST)
    {
        strValueOut = NULL_STRING;

        if (idField == ifds::ValueAsAt ||
            idField == ifds::rxClassCode ||
            idField == ifds::rxFundCode ||
            idField == ifds::FundName)
        {
            (const_cast<PriceAdditionalProcess*>(this))->getCBOList(IFASTBP_PROC::PRICE_ADDITIONAL_LIST, idDataGroup)->getField(idField, strValueOut, idDataGroup, bFormatted);
        }
    }
}


//****************************************************************
bool PriceAdditionalProcess::doModelessSetFocus(GenericInterface *rpGICaller)
{  // This is implemented to pass set focus on to child dialog.
	MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
	SEVERITY sevRtn = SEVERE_ERROR;

	bool bRtn = false;
	try
	{
		assert(_rpChildGI && isValidModelessInterface(_rpChildGI));

		if (isValidModelessInterface(_rpChildGI))
		{  
            setContainer(IFASTBP_PROC::PRICE_ADDITIONAL_LIST, NULL);

			bRtn = _rpChildGI->refresh(this, NULL);
			bRtn = _rpChildGI->modelessSetFocus(rpGICaller);
		}

	}
	catch( ConditionException &ce )
	{
		SETCONDITIONFROMEXCEPTION( ce );
	}
	catch( ... )
	{
		assert( 0 );
		THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS,
			CND::BP_ERR_UNKNOWN_EXCEPTION );
	}

	return(bRtn);
}


//****************************************************************
bool PriceAdditionalProcess::doModelessChildComplete(const Command &cmd)
{
    return cmd.getKey() == CMD_GUI_PRICE_ADDITIONAL;
}


//****************************************************************
bool PriceAdditionalProcess::doRefresh(GenericInterface *rpGICaller, const I_CHAR *szOriginalCommand)
{
	TRACE_METHOD(CLASSNAME, DOREFRESH);

	return _rpChildGI->refresh(this, NULL);
}


//****************************************************************
void PriceAdditionalProcess::doPostOk(GenericInterface *rpGICaller, bool bSuccessFlag)
{
	
}


////****************************************************************
bool PriceAdditionalProcess::doOk(GenericInterface *rpGICaller)
{
   SEVERITY sevReturn = NO_CONDITION;

   return sevReturn == NO_CONDITION;
}

//****************************************************************
void *PriceAdditionalProcess::getPtrForContainer(const BFContainerId& idContainer,
											     const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer"));

	void *ptr = NULL;
	SEVERITY sevRtn = SEVERE_ERROR;

	DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession*>(getBFWorkSession());

	try
	{  
        if (idContainer == IFASTBP_PROC::PRICE_ADDITIONAL_LIST)
        {
            if (!_pPriceAdditionalList)
            {
                map<DString, DString> price, price2, price3, price4, price5,price6,price7,price8,price9,price10,price11,price12,price13;
                list<map<DString, DString>> priceList;

                price[PRICE_ADDI::PRICE_CODE] = _priceCode;
                price[PRICE_ADDI::UNIT_VALUE] = _unitValue;
                price[PRICE_ADDI::CHG_FACTOR] = _chgFactor;

                price2[PRICE_ADDI::PRICE_CODE] = _priceCode2;
                price2[PRICE_ADDI::UNIT_VALUE] = _unitValue2;
                price2[PRICE_ADDI::CHG_FACTOR] = _chgFactor2;

                price3[PRICE_ADDI::PRICE_CODE] = _priceCode3;
                price3[PRICE_ADDI::UNIT_VALUE] = _unitValue3;
                price3[PRICE_ADDI::CHG_FACTOR] = _chgFactor3;

                price4[PRICE_ADDI::PRICE_CODE] = _priceCode4;
                price4[PRICE_ADDI::UNIT_VALUE] = _unitValue4;
                price4[PRICE_ADDI::CHG_FACTOR] = _chgFactor4;

                price5[PRICE_ADDI::PRICE_CODE] = _priceCode5;
                price5[PRICE_ADDI::UNIT_VALUE] = _unitValue5;
                price5[PRICE_ADDI::CHG_FACTOR] = _chgFactor5;

				price6[PRICE_ADDI::PRICE_CODE] = _priceCode6;
                price6[PRICE_ADDI::UNIT_VALUE] = _unitValue6;
                price6[PRICE_ADDI::CHG_FACTOR] = _chgFactor6;

				price7[PRICE_ADDI::PRICE_CODE] = _priceCode7;
                price7[PRICE_ADDI::UNIT_VALUE] = _unitValue7;
                price7[PRICE_ADDI::CHG_FACTOR] = _chgFactor7;

				price8[PRICE_ADDI::PRICE_CODE] = _priceCode8;
                price8[PRICE_ADDI::UNIT_VALUE] = _unitValue8;
                price8[PRICE_ADDI::CHG_FACTOR] = _chgFactor8;

				price9[PRICE_ADDI::PRICE_CODE] = _priceCode9;
                price9[PRICE_ADDI::UNIT_VALUE] = _unitValue9;
                price9[PRICE_ADDI::CHG_FACTOR] = _chgFactor9;

				price10[PRICE_ADDI::PRICE_CODE] = _priceCode10;
                price10[PRICE_ADDI::UNIT_VALUE] = _unitValue10;
                price10[PRICE_ADDI::CHG_FACTOR] = _chgFactor10;

				price11[PRICE_ADDI::PRICE_CODE] = _priceCode11;
                price11[PRICE_ADDI::UNIT_VALUE] = _unitValue11;
                price11[PRICE_ADDI::CHG_FACTOR] = _chgFactor11;

				price12[PRICE_ADDI::PRICE_CODE] = _priceCode12;
                price12[PRICE_ADDI::UNIT_VALUE] = _unitValue12;
                price12[PRICE_ADDI::CHG_FACTOR] = _chgFactor12;

				price13[PRICE_ADDI::PRICE_CODE] = _priceCode13;
                price13[PRICE_ADDI::UNIT_VALUE] = _unitValue13;
                price13[PRICE_ADDI::CHG_FACTOR] = _chgFactor13;

				

                priceList.push_back(price);
                priceList.push_back(price2);
                priceList.push_back(price3);
                priceList.push_back(price4);
                priceList.push_back(price5);
				priceList.push_back(price6);
				priceList.push_back(price7);
				priceList.push_back(price8);
				priceList.push_back(price9);
				priceList.push_back(price10);
				priceList.push_back(price11);
				priceList.push_back(price12);
				priceList.push_back(price13);


                _pPriceAdditionalList = new PriceAdditionalList(*getBFWorkSession());

                if (_pPriceAdditionalList->init(_tradeDate, _fundCode, _classCode, priceList, idDataGroup) <= WARNING)
                {
                    ptr = _pPriceAdditionalList;
                }
                else 
                {
                    delete _pPriceAdditionalList;
                    _pPriceAdditionalList = NULL;
                }
            }
            else
                ptr = _pPriceAdditionalList;
        }
	}
	catch (ConditionException &)
	{
		throw;
	}
	catch (...)
	{
		assert(0);
		THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer"),
			CND::BP_ERR_UNKNOWN_EXCEPTION);
	}

	return ptr;
}