#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_fund_class_not_effective : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_fund_class_not_effective() { }
		~CIFast_Infrastructure_ifastcbo_err_fund_class_not_effective() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_CLASS_NOT_EFFECTIVE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This is not considered to be a valid date value.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("This is not considered to be a valid date value.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Dies wird nicht als gültiger Datenwert anerkannt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Éste no se considera un valor de fecha válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Ceci n'est pas considéré comme une valeur de date valide.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Dit wordt niet gezien als een geldige datumwaarde")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check the date length, month/day combo or date ranges.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Check the date length, month/day combo or date ranges.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Länge des Datums, die Kombination Monat/Tag oder die Datumsbereiche.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Check the date length, month/day combo or date ranges.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez la longueur de la date, la combinaison mois/jour ou les plages de dates.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de lengte van de datum, de combinatie maand/dag of het datumbereik")); }
	};
}



