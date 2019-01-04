#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_sin_effective_date_cannot_be_unknown : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_sin_effective_date_cannot_be_unknown() { }
		~CIFast_IFast_ifastcbo_err_sin_effective_date_cannot_be_unknown() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SIN_EFFECTIVE_DATE_CANNOT_BE_UNKNOWN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("SIN Effective date cannot be unknown.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'entrée en vigueur du NAS ne peut être inconnue.")); }

        // Actions
	};
}



