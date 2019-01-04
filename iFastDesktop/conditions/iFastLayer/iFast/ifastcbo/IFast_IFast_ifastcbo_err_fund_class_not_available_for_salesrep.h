#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_class_not_available_for_salesrep : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_class_not_available_for_salesrep() { }
		~CIFast_IFast_ifastcbo_err_fund_class_not_available_for_salesrep() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_CLASS_NOT_AVAILABLE_FOR_SALESREP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund %FUND%, class %CLASS% is not eligible for agent %AGENT%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fund %FUND% and Class %CLASS% is not eligible for this Sales Representative.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Fund %FUND% and Class %CLASS% is not eligible for this Sales Representative.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds %FUND% et la classe %CLASS% ne sont pas admissibles pour l'agent %AGENT%.")); }

        // Actions
	};
}



