#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_effective_date_before_curbusdate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_effective_date_before_curbusdate() { }
		~CIFast_IFast_ifastcbo_warn_effective_date_before_curbusdate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_EFFECTIVE_DATE_BEFORE_CURBUSDATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Effective date must be equal or after current business day.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'entrée en vigueur doit être identique ou postérieure au jour ouvrable actuel.")); }

        // Actions
	};
}



