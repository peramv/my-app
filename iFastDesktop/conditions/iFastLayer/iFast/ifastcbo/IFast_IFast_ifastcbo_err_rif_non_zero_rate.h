#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_non_zero_rate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_non_zero_rate() { }
		~CIFast_IFast_ifastcbo_err_rif_non_zero_rate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_NON_ZERO_RATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Rate must be zero if Suppress Tax is \"Yes\".")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Rate must be zero if Suppress Tax is \"Yes\".")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Satz muss Null sein, wenn Steuer unterdrücken auf \"Ja\" steht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La tasa debe ser cero si Suprimir impuesto es \"Sí\".")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le taux doit être de zéro si la suppression de l'imposition est activée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Tarief moet nul zijn als Belasting achterwege laten 'Ja' is")); }

        // Actions
	};
}



