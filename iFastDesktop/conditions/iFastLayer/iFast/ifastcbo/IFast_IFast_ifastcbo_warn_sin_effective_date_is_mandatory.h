#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_sin_effective_date_is_mandatory : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_sin_effective_date_is_mandatory() { }
		~CIFast_IFast_ifastcbo_warn_sin_effective_date_is_mandatory() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_SIN_EFFECTIVE_DATE_IS_MANDATORY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("SIN Effective Date is mandatory.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'entrée en vigueur du NAS est requise.")); }

        // Actions
	};
}



