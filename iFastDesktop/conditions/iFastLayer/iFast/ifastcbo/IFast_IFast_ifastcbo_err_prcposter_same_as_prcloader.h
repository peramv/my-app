#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_prcposter_same_as_prcloader : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_prcposter_same_as_prcloader() { }
		~CIFast_IFast_ifastcbo_err_prcposter_same_as_prcloader() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PRCPOSTER_SAME_AS_PRCLOADER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Price posting should be done by a different user")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement des prix devrait être fait par un autre utilisateur.")); }

        // Actions
	};
}



