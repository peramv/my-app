#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_instr_cannot_coexist : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_instr_cannot_coexist() { }
		~CIFast_IFast_ifastcbo_err_instr_cannot_coexist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INSTR_CANNOT_COEXIST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Maturity/Interest instruction for the same fund/class cannot coexist with Maturity or Interest instruction.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les instructions à l'échéance/d'intérêt pour le même fonds/la même classe ne peuvent coexister avec les instructions à l'échéance/d'intérêt.")); }

        // Actions
	};
}



