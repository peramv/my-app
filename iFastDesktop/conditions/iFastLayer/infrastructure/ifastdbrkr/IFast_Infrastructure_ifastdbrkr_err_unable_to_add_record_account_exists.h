#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_unable_to_add_record_account_exists : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_unable_to_add_record_account_exists() { }
		~CIFast_Infrastructure_ifastdbrkr_err_unable_to_add_record_account_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNABLE_TO_ADD_RECORD_ACCOUNT_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Operator is not logged on to AWD.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Operator is not logged on to AWD.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Operator ist nicht in AWD eingeloggt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El operador no está conectado a AWD.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'opérateur n'a aucune session ouverte sur AWD.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Operator is niet aangemeld bij AWD")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Log on to AWD before accessing this application.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Log on to AWD before accessing this application.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Melden Sie sich bei AWD an, bevor Sie auf dieses Anwendung zugreifen.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Log on to AWD before accessing this application.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Ouvrez une session AWD avant d'accéder à cette application.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Meld u aan bij de AWD voordat u deze toepassing opent")); }
	};
}



