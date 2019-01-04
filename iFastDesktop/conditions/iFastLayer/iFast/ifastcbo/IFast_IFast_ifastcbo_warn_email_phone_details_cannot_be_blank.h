#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_email_phone_details_cannot_be_blank : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_email_phone_details_cannot_be_blank () { }
		~ CIFast_IFast_ifastcbo_warn_email_phone_details_cannot_be_blank () { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_EMAIL_PHONE_DETAILS_CANNOT_BE_BLANK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_(" Email/Phone Details cannot be blank.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_(" Les détails du courriel/téléphone ne peuvent pas être vides.")); }

        // Actions
	};
}
