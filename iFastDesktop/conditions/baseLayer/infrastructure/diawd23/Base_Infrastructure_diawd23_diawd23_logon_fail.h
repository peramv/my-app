#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_diawd23_diawd23_logon_fail : public CConditionObject
	{
	public:
		CBase_Infrastructure_diawd23_diawd23_logon_fail() { }
		~CBase_Infrastructure_diawd23_diawd23_logon_fail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIAWD23_LOGON_FAIL")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("diawd23")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AWD logon was not successful. Return Code = %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("AWD logon was not successful. Return Code = %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("AWD-Anmeldung war nicht erfolgreich. Rückgabecode = %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La conexión con AWD no fue exitosa. Código de retorno = %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'ouverture de session AWD a échoué. Code de renvoi : %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Aanmelden bij AWD is niet gelukt. Retourcode = %AWD_ERROR_MESSAGE%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Notifique de este mensaje a un representante de soporte técnico.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



