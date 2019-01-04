#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_exch_rate_not_available : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_exch_rate_not_available() { }
		~CIFast_IFast_ifastdbrkr_err_exch_rate_not_available() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EXCH_RATE_NOT_AVAILABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Exchange rate not available for this date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Wechselkurs nicht verfügbar für dieses Datum")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay tipo de cambio disponible para esta fecha")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le taux de change n'est pas disponible pour cette date.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Wisselkoers is niet beschikbaar voor deze datum")); }

        // Actions
	};
}



