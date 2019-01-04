#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_disessn_disessn_child_not_removed : public CConditionObject
	{
	public:
		CIFast_Infrastructure_disessn_disessn_child_not_removed() { }
		~CIFast_Infrastructure_disessn_disessn_child_not_removed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DISESSN_CHILD_NOT_REMOVED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("disessn")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem. Subsession was not removed from parent session's list.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem. Subsession was not removed from parent session's list.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem. Untergeordnete Sitzung wurde nicht aus der Liste der übergeordneten Sitzungen entfernt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno. No se eliminó la subsesión de la lista de la sesión matriz.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. La sous-session n'a pas été retirée de la liste de la session mère.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem. Subsessie is niet verwijderd uit bovenliggende sessielijst")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



