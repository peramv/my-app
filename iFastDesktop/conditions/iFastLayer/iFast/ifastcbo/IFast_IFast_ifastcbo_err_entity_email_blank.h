#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_entity_email_blank : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_entity_email_blank() { }
		~CIFast_IFast_ifastcbo_err_entity_email_blank() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EMAIL_IS_MISSING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Email is blank.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le Email est vide.")); }

        // Actions
	};
}



