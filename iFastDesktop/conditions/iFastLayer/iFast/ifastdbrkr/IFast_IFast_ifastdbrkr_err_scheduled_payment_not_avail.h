#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_scheduled_payment_not_avail : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_scheduled_payment_not_avail() { }
		~CIFast_IFast_ifastdbrkr_err_scheduled_payment_not_avail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SCHEDULED_PAYMENT_NOT_AVAIL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Scheduled Payment Information not available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Information über Planmäßige Zahlung nicht verfügbar.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay disponible información de pagos programados.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'information sur le paiement prévu n'est pas disponible.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gegevens over geplande betaling zijn niet beschikbaar")); }

        // Actions
	};
}



