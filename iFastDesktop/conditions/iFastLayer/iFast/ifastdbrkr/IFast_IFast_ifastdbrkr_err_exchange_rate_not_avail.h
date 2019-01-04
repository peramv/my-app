#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_exchange_rate_not_avail : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_exchange_rate_not_avail() { }
		~CIFast_IFast_ifastdbrkr_err_exchange_rate_not_avail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EXCHANGE_RATE_NOT_AVAIL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Exchange rate not available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Wechselkurs nicht verfügbar.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay un tipo de cambio disponible.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le taux de change n'est pas disponible")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Wisselkoers is niet beschikbaar")); }

        // Actions
	};
}



