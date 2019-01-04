#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_dif_does_not_allow_cash_sweep : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_dif_does_not_allow_cash_sweep() { }
		~CIFast_IFast_ifastcbo_err_dif_does_not_allow_cash_sweep() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DIF_DOES_NOT_ALLOW_CASH_SWEEP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("DIF does not allow cash sweep.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il n’est pas permis de spécifier un TAI pour ce fonds.")); }

        // Actions
	};
}



