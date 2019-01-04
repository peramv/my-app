#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_userid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_userid() { }
		~CIFast_IFast_ifastdbrkr_err_no_userid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_USERID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The logon request doesn't contain a user id")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Cannot create batch, no user id.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Batch kann nicht erstellt werden, keine Benutzer-ID")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La solicitud de inicio de sesión no contiene una identificación de usuario")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La demande d'ouverture de session ne contient pas de code d'utilisateur.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De aanmeldingsaanvraag bevat geen gebruikers-ID")); }

        // Actions
	};
}



