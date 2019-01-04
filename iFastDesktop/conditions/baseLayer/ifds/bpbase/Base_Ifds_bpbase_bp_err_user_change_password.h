#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_bpbase_bp_err_user_change_password : public CConditionObject
	{
	public:
		CBase_Ifds_bpbase_bp_err_user_change_password() { }
		~CBase_Ifds_bpbase_bp_err_user_change_password() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_ERR_USER_CHANGE_PASSWORD")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("bpbase")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The user is required to change the password.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("L'utilisateur doit modifier le mot de passe.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zugriff verweigert – Nach Kennwort-Frist-Periode")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El usuario debe cambiar la contraseña.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'utilisateur doit changer de mot de passe.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De gebruiker moet zijn wachtwoord wijzigen.")); }

        // Actions
	};
}



