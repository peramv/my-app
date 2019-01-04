#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_bfconmgr_err_privconn_create_event : public CConditionObject
	{
	public:
		CBase_Infrastructure_bfconmgr_err_privconn_create_event() { }
		~CBase_Infrastructure_bfconmgr_err_privconn_create_event() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PRIVCONN_CREATE_EVENT")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("bfconmgr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem.\n\nAWD container failed to close.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem.\n\nAWD container failed to close.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem.\n\nAWD-Container konnte nicht geschlossen werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno.\n\nEl contenedor de AWD no se cerró.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. \n\n Échec de fermeture du conteneur AWD.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het systeem herkent beginmaand niet")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Notifique de este mensaje a un representante de soporte técnico.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de beginmaand en voer deze opnieuw in")); }
	};
}



