#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_mail_cannot_be_no_for_no_waive : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_mail_cannot_be_no_for_no_waive() { }
		~CIFast_IFast_ifastcbo_warn_mail_cannot_be_no_for_no_waive() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_MAIL_CANNOT_BE_NO_FOR_NO_WAIVE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Mail can not be set to NO before consent is set to YES for %DOCTYPE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le consentement doit être « oui » avant de mettre le courrier à « non » pour %DOCTYPE%.")); }

        // Actions
	};
}



