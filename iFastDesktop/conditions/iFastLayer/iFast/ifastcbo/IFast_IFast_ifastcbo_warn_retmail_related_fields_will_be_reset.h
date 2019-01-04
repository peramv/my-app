#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_retmail_related_fields_will_be_reset : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_retmail_related_fields_will_be_reset() { }
		~CIFast_IFast_ifastcbo_warn_retmail_related_fields_will_be_reset() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_RETMAIL_RELATED_FIELDS_WILL_BE_RESET")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Return mail flag will be turned off and related fields cleared.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le signal de retour de courrier sera désactivé et les champs associés seront effacés.")); }

        // Actions
	};
}



