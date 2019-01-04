#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fx_rate_is_empty : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fx_rate_is_empty() { }
		~CIFast_IFast_ifastcbo_err_fx_rate_is_empty() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FX_RATE_IS_EMPTY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("F/X rate is not entered for the transaction.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le taux fixe n'a pas été saisi pour la transaction.")); }

        // Actions
	};
}



