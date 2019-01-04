#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_deault_share_holder_bank_info_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_deault_share_holder_bank_info_not_found() { }
		~CIFast_IFast_ifastcbo_warn_deault_share_holder_bank_info_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_DEAULT_SHARE_HOLDER_BANK_INFO_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is no shareholder bank information.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune information bancaire sur l'actionnaire")); }

        // Actions
	};
}



