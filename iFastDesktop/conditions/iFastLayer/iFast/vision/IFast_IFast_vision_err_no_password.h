#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_vision_err_no_password : public CConditionObject
	{
	public:
		CIFast_IFast_vision_err_no_password() { }
		~CIFast_IFast_vision_err_no_password() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_PASSWORD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("vision")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The logon request doesn't contain a password")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The logon request doesn't contain a password")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Anmelde-Anfrage enthält kein Kennwort")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La solicitud de inicio de sesión no contiene una contraseña")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La demande d'ouverture de session ne contient pas de mot de passe.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De aanmeldingsaanvraag bevat geen wachtwoord")); }

        // Actions
	};
}



