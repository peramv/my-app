#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_no_setup_record : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_no_setup_record() { }
		~CIFast_Infrastructure_ifastdbrkr_err_no_setup_record() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_SETUP_RECORD")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Return NASU account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Return NASU account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ertrags-NASU-Konto.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Cuenta NASU de retorno.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Compte de réglage de nouveau compte de remboursement")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Rendement NASU-account")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a supervisor and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contact a supervisor and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Supervisor und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a supervisor and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un superviseur et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supervisor en meld dit bericht")); }
	};
}



