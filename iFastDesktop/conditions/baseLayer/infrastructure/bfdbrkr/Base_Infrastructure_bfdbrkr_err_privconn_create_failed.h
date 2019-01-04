#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_bfdbrkr_err_privconn_create_failed : public CConditionObject
	{
	public:
		CBase_Infrastructure_bfdbrkr_err_privconn_create_failed() { }
		~CBase_Infrastructure_bfdbrkr_err_privconn_create_failed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PRIVCONN_CREATE_FAILED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("bfdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The system does not recognize start year.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem.\n\nAWD container is not open.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem.\n\nAWD-Container ist nicht geöffnet.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El sistema no reconoce el año de inicio.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. \n\n Le conteneur AWD n'est pas ouvert.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem.\n\nAWD-container is niet geopend")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify start year and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique el año de inicio y vuelva a introducirlo.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



