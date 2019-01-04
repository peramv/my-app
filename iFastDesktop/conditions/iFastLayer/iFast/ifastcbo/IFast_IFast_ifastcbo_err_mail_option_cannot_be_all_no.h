#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_mail_option_cannot_be_all_no : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_mail_option_cannot_be_all_no() { }
		~CIFast_IFast_ifastcbo_err_mail_option_cannot_be_all_no() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MAIL_OPTION_CANNOT_BE_ALL_NO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Mail, Fax, CD, Email and Epost can not all be set to NO for %DOCTYPE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Mail, Fax, CD, E-Mail können nicht alle auf NEIN gesetzt werden für %DOCTYPE%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Correo, Fax, CD, E-mail no pueden configurarse en NO para %DOCTYPE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les champs Courrier, Télécopieur, CD, Courriel et Postel ne peuvent être tous réglés à Non pour %DOCTYPE%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Mail, Fax, CD en e-mail kunnen niet allemaal op NEE worden ingesteld voor documenttype %DOCTYPE%")); }

        // Actions
	};
}



