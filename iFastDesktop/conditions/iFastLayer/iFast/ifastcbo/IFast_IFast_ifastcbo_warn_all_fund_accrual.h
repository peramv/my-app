#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_all_fund_accrual : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_all_fund_accrual() { }
		~CIFast_IFast_ifastcbo_warn_all_fund_accrual() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ALL_FUND_ACCRUAL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Each Fund will be reported starting with its last dividend date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Each Fund will be reported starting with its last dividend date.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Each Fund will be reported starting with its last dividend date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Chaque fonds sera déclaré comme ayant démarré à sa dernière date de dividende.")); }

        // Actions
	};
}



