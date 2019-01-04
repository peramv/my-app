#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_retmail_reason_is_blank : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_retmail_reason_is_blank() { }
		~CIFast_IFast_ifastcbo_warn_retmail_reason_is_blank() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_RETMAIL_REASON_IS_BLANK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Return Mail Reason field is blank.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ de la raison du retour de courrier est vide.")); }

        // Actions
	};
}



