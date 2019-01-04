#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_diawd23_diawd23_comment_fail : public CConditionObject
	{
	public:
		CIFast_IFast_diawd23_diawd23_comment_fail() { }
		~CIFast_IFast_diawd23_diawd23_comment_fail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIAWD23_COMMENT_FAIL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("diawd23")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No session for the user with the id %id%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("No session for the user with the id %id%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Keine Sitzung für den Benutzer mit der ID %id%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay sesión para el usuario con la identificación %id%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune session pour l'utilisateur %id%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Geen sessie voor de gebruiker met het ID %id%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check system.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verifiez le systeme.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie das System.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Check system.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le système.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het systeem")); }
	};
}



