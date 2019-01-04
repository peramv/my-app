#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_client_birthday_missing : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_client_birthday_missing() { }
		~CIFast_IFast_ifastcbo_err_warn_client_birthday_missing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_CLIENT_BIRTHDAY_MISSING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Client's Date of Birth is missing.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Geburtsdatum des Kunden fehlt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Falta la fecha de nacimiento del cliente.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de naissance du client est manquante.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Geboortedatum klant ontbreekt")); }

        // Actions
	};
}



