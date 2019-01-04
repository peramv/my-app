#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_calculating_dividents : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_calculating_dividents() { }
		~CIFast_IFast_ifastdbrkr_err_calculating_dividents() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CALCULATING_DIVIDENTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Error calculating dividends.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fehler bei der Berechnung der Dividenden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Error al calcular dividendos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur lors du calcul des dividendes")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een fout opgetreden bij het berekenen van het dividend")); }

        // Actions
	};
}



