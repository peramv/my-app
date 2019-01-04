#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dicbocore_err_retreiving_date : public CConditionObject
	{
	public:
		CBase_Infrastructure_dicbocore_err_retreiving_date() { }
		~CBase_Infrastructure_dicbocore_err_retreiving_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RETREIVING_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to retrieve system date and time.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Unable to retrieve system date and time.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Systemdatum und –zeit können nicht ausgelesen werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Imposible recuperar la fecha y hora del sistema.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de récupérer la date et l'heure du système.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Systeemdatum en -tijd konden niet worden opgehaald")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Notifique de este mensaje a un representante de soporte técnico.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



