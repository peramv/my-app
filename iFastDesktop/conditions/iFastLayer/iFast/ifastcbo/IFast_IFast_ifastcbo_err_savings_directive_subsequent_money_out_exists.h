#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_savings_directive_subsequent_money_out_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_savings_directive_subsequent_money_out_exists() { }
		~CIFast_IFast_ifastcbo_err_savings_directive_subsequent_money_out_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SAVINGS_DIRECTIVE_SUBSEQUENT_MONEY_OUT_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Subsequent money out trade already exists. Manual override is not allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une transaction de sortie d'argent subséquente existe. Une modification manuelle n'est pas autorisée.")); }

        // Actions
	};
}



