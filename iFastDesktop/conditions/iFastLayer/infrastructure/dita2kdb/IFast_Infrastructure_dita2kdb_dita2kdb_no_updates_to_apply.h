#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dita2kdb_dita2kdb_no_updates_to_apply : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dita2kdb_dita2kdb_no_updates_to_apply() { }
		~CIFast_Infrastructure_dita2kdb_dita2kdb_no_updates_to_apply() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_NO_UPDATES_TO_APPLY")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There are no updates to apply.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There are no updates to apply.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt keine anwendbaren Aktualisierungen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay actualizaciones para aplicar.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune mise à jour à effectuer")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bijwerken is niet nodig")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Notifique de este mensaje a un representante de soporte técnico.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



