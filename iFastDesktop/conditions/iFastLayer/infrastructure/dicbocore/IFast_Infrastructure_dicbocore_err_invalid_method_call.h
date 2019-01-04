#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dicbocore_err_invalid_method_call : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dicbocore_err_invalid_method_call() { }
		~CIFast_Infrastructure_dicbocore_err_invalid_method_call() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_METHOD_CALL")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Method %METHOD% should never be called.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Method '^' should never be called.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem. Index %index% ist außerhalb des Bereichs von %props%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El método %METHOD% no debe llamarse nunca.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La méthode %METHOD% ne devrait jamais être appelée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem. Index %index%  ligt buiten bereik voor %props%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify CBO code.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify CBO code.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique el código CBO.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le code CBO.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



