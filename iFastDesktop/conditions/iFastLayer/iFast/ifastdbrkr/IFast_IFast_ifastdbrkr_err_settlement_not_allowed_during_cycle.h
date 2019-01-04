#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_settlement_not_allowed_during_cycle : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_settlement_not_allowed_during_cycle() { }
		~CIFast_IFast_ifastdbrkr_err_settlement_not_allowed_during_cycle() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SETTLEMENT_NOT_ALLOWED_DURING_CYCLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Settlement is not allowed during final cycle run.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Règlement non autorisé pendant l'exécution du cycle final")); }

        // Actions
	};
}



