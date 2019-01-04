#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_user_id_exist : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_user_id_exist() { }
		~CIFast_IFast_ifastdbrkr_err_user_id_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_USER_ID_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("User-Id already exists.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Benutzer-ID existiert bereits")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Esta identificación de usuario ya existe")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code d'utilisateur déjà existant")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gebruikers-ID bestaat al")); }

        // Actions
	};
}



