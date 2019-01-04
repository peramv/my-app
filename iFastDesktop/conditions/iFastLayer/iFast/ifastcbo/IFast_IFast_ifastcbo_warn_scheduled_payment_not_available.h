#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_scheduled_payment_not_available : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_scheduled_payment_not_available() { }
		~CIFast_IFast_ifastcbo_warn_scheduled_payment_not_available() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_SCHEDULED_PAYMENT_NOT_AVAILABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Scheduled Payment Information not available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Scheduled Payment Information not available.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Scheduled Payment Information not available.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'information sur le paiement prévu n'est pas disponible.")); }

        // Actions
	};
}



