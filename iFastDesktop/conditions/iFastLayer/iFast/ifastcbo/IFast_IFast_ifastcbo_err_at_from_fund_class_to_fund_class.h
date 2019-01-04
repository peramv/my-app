#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_at_from_fund_class_to_fund_class : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_at_from_fund_class_to_fund_class() { }
		~CIFast_IFast_ifastcbo_err_at_from_fund_class_to_fund_class() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AT_FROM_FUND_CLASS_TO_FUND_CLASS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transfer from %FROMFUNDNAME%, %FROMCLASS% to %TOFUNDNAME%, %TOCLASS% is not an allowable transfer.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Transfer from %FROMFUNDNAME%, %FROMCLASS% to %TOFUNDNAME%, %TOCLASS% is not an allowable transfer.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Transfer von %FROMFUNDNAME%, %FROMCLASS% nach %TOFUNDNAME%, %TOCLASS% ist nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La transferencia de %FROMFUNDNAME%, %FROMCLASS% a %TOFUNDNAME%, %TOCLASS% no está permitida.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un tranfert de %FROMFUNDNAME% et %FROMCLASS% à %TOFUNDNAME% et %TOCLASS% n'est pas autorisé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Overdracht van %FROMFUNDNAME%, %FROMCLASS% naar %TOFUNDNAME%, %TOCLASS% is geen toegestane overdracht")); }

        // Actions
	};
}



