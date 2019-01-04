#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicbocore_err_format_not_recognized : public CConditionObject
	{
	public:
		CIFast_IFast_dicbocore_err_format_not_recognized() { }
		~CIFast_IFast_dicbocore_err_format_not_recognized() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FORMAT_NOT_RECOGNIZED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amounts cannot be negative - enter an amount greater than 0.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Les montants ne peuvent pas être negatifs - saisissez un montant superieur a 0.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Beträge können nicht negativ sein – geben Sie einen Betrag ein, der größer als 0 ist.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Los montos no pueden ser negativos - Escriba un monto mayor que 0.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les montants ne peuvent être négatifs – veuillez saisir un montant supérieur à zéro.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bedragen kunnen niet negatief zijn - voer een bedrag in dat groter is dan nul")); }

        // Actions
	};
}



