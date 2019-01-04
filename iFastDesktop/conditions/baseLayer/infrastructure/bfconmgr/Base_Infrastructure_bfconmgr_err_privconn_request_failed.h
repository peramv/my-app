#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_bfconmgr_err_privconn_request_failed : public CConditionObject
	{
	public:
		CBase_Infrastructure_bfconmgr_err_privconn_request_failed() { }
		~CBase_Infrastructure_bfconmgr_err_privconn_request_failed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PRIVCONN_REQUEST_FAILED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("bfconmgr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem.\n\nAn unkown AWD exception was caught.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem.\n\nAn unkown AWD exception was caught.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem.\n\nEine unbekannte AWD-Ausnahme ist aufgetreten.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Aumento de DCSC no válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Plus-value DCSC invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige DCSC-waardering")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
	};
}



