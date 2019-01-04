#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_ret_mail_changed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_ret_mail_changed() { }
		~CIFast_IFast_ifastcbo_warn_ret_mail_changed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_RET_MAIL_CHANGED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Mail flag has been changed, please review the hold flag in the mailing panel accordingly.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le signal de courrier a été changé, veuillez vérifier le signal de retenue dans l'écran utilitaire postal correspondant.")); }

        // Actions
	};
}



