#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_effective_date_after_stop_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_effective_date_after_stop_date() { }
		~CIFast_IFast_ifastcbo_warn_effective_date_after_stop_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_EFFECTIVE_DATE_AFTER_STOP_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Effective date may be after stop date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'entrée en vigueur pourrait être postérieure à la date d'arrêt.")); }

        // Actions
	};
}



