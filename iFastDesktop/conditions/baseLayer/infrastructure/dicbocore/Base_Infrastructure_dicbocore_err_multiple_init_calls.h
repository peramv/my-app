#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dicbocore_err_multiple_init_calls : public CConditionObject
	{
	public:
		CBase_Infrastructure_dicbocore_err_multiple_init_calls() { }
		~CBase_Infrastructure_dicbocore_err_multiple_init_calls() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MULTIPLE_INIT_CALLS")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem.  Method init for object %OBJECT% has already been called.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Information not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem.  Methoden-Initialisierung für Objekt  %OBJECT% wurde bereits aufgerufen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno.  Ya se llamó el método init para el objeto %OBJECT%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Information introuvable")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem.  Methode init voor object %OBJECT% is al aangeroepen")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify search criteria.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le critère de recherche.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



