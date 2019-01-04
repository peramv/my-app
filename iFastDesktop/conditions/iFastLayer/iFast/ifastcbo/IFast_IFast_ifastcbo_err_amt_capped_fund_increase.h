#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_amt_capped_fund_increase : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_amt_capped_fund_increase() { }
		~CIFast_IFast_ifastcbo_err_amt_capped_fund_increase() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMT_CAPPED_FUND_INCREASE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The amount of a capped fund cannot be increased.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("The amount of a capped fund cannot be increased.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("The amount of a capped fund cannot be increased.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant d'un fonds plafonné ne peut être augmenté.")); }

        // Actions
	};
}



