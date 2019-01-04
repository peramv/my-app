#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_no_email_address_for_entity : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_no_email_address_for_entity() { }
		~CIFast_IFast_ifastcbo_err_no_email_address_for_entity() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_EMAIL_ADDRESS_FOR_ENTITY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Email address has not been set up.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("E-Mail-Adresse wurde nicht erstellt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se ha configurado el e-mail.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'adresse courriel n'a pas été réglée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("E-mailadres is niet ingesteld")); }

        // Actions
	};
}



