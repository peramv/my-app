#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_corr_bank_should_be_empty : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_corr_bank_should_be_empty() { }
		~CIFast_IFast_ifastcbo_err_corr_bank_should_be_empty() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CORR_BANK_SHOULD_BE_EMPTY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Corresponding bank information should be empty for domestic wire.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Entsprechende Bankinformation für Inlandsübermittlung sollte leer sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La información bancaria correspondiente debe estar vacía para transferencia cablegráfica nacional.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ de l'information bancaire correspondante devrait être vide pour une opération électronique nationale.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bijbehorende bankgegevens moeten leeg zijn voor binnenlandse telegrafische order")); }

        // Actions
	};
}



