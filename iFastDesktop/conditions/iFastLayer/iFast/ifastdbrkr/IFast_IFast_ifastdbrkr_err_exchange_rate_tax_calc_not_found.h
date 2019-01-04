#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_exchange_rate_tax_calc_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_exchange_rate_tax_calc_not_found() { }
		~CIFast_IFast_ifastdbrkr_err_exchange_rate_tax_calc_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EXCHANGE_RATE_TAX_CALC_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Exchange rate for tax calculation not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Wechselkurs für Steuerberechnung nicht gefunden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró el tipo de cambio para el cálculo de los impuestos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le taux de change pour le calcul de d'imposition est introuvable.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Wisselkoers voor belastingberekening is niet gevonden")); }

        // Actions
	};
}



