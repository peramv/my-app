#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_future_deathdate : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_future_deathdate() { }
		~CIFast_Infrastructure_ifastcbo_err_future_deathdate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUTURE_DEATHDATE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The postal address format type code is invalid.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The postal address format type code is invalid.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Postadressen-Formattyp-Code ist ungültig.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo de formato de la dirección postal no es válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code du type de format de l'adresse postale est invalide.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De code voor het indelingstype van het postadres is ongeldig")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Valid values are F and U.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Valid values are F and U.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Gültige Werte sind F und U.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Valid values are F and U.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Les valeurs valides sont F et U.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Geldige waarden zijn F en U")); }
	};
}



