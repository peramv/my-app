#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_invalid_phone_fax_number : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_invalid_phone_fax_number() { }
		~CIFast_IFast_ifastcbo_warn_invalid_phone_fax_number() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_INVALID_PHONE_FAX_NUMBER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid phone or fax number.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Numéro de téléphone ou de télécopieur invalide")); }

        // Actions
	};
}



