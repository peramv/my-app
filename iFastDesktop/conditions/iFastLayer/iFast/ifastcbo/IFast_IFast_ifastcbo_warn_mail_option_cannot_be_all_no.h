#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_mail_option_cannot_be_all_no : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_mail_option_cannot_be_all_no() { }
		~CIFast_IFast_ifastcbo_warn_mail_option_cannot_be_all_no() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_MAIL_OPTION_CANNOT_BE_ALL_NO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Mail, Fax, CD, Email and Epost can not all be set to NO for %DOCTYPE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les champs Courrier, Télécopieur, CD, Courriel et Postel ne peuvent pas tous être « non » pour %DOCTYPE%.")); }

        // Actions
	};
}



