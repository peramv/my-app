#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_account_not_in_repository : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_account_not_in_repository() { }
		~CIFast_Infrastructure_ifastcbo_err_account_not_in_repository() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCOUNT_NOT_IN_REPOSITORY")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is a system ID error.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is a system ID error.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt einen System-ID-Fehler.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un error de identificación del sistema.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a une erreur de code de système.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een fout bij het systeem-ID")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a supervisor and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contact a supervisor and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Supervisor und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a supervisor and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un superviseur et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supervisor en meld dit bericht")); }
	};
}



