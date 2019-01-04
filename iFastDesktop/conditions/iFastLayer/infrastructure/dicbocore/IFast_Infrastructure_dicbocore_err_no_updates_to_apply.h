#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dicbocore_err_no_updates_to_apply : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dicbocore_err_no_updates_to_apply() { }
		~CIFast_Infrastructure_dicbocore_err_no_updates_to_apply() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_UPDATES_TO_APPLY")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No updates to apply for %LABEL% with key %KEY%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("No updates to apply for '^' with key '^'.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Keine anwendbaren Aktualisierungen für %LABEL% mit Schlüssel %KEY%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay actualizaciones para aplicar a %LABEL% con la clave %KEY%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune mise à jour n'est applicable à %LABEL% avec la clé %KEY%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bijwerken niet nodig voor %LABEL% met sleutel %KEY%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Notifique de este mensaje a un representante de soporte técnico.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



