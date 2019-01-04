#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_effective_date_backward : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_effective_date_backward() { }
		~CIFast_IFast_ifastcbo_warn_effective_date_backward() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_EFFECTIVE_DATE_BACKWARD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account effective date being set back to earlier then the shareholder effective date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Account effective date being set back to earlier then the shareholder effective date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'entrée en vigueur du compte est en cours de réglage pour une date antérieure à la date d'entrée en vigueur de l'actionnaire.")); }

        // Actions
	};
}



