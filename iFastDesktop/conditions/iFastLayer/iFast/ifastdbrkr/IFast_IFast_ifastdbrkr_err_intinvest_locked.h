#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_intinvest_locked : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_intinvest_locked() { }
		~CIFast_IFast_ifastdbrkr_err_intinvest_locked() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INTINVEST_LOCKED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("IntInvest record is locked, try later.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement de l'investissement des intérêts est verrouillé; réessayez plus tard.")); }

        // Actions
	};
}



