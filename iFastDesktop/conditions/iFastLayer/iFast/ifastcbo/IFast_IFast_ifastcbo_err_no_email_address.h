#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_no_email_address : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_no_email_address() { }
		~CIFast_IFast_ifastcbo_err_no_email_address() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_EMAIL_ADDRESS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Email has not been set up for the account holder.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("E-Mail wurde für den Kontoinhaber nicht erstellt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se ha configurado el e-mail para el titular de la cuenta.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le courriel n'a pas été réglé pour le titulaire du compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("E-mail is niet ingesteld voor de accounthouder")); }

        // Actions
	};
}



