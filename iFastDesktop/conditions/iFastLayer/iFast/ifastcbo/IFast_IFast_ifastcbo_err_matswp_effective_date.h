#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_matswp_effective_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_matswp_effective_date() { }
		~CIFast_IFast_ifastcbo_err_matswp_effective_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MATSWP_EFFECTIVE_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Effective Date must be after Account Effective Date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'entrée en vigueur doit être postérieure à la date d'entrée en vigueur du compte.")); }

        // Actions
	};
}



