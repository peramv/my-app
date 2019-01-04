#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_wrong_verify_status : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_wrong_verify_status() { }
		~CIFast_IFast_ifastcbo_err_wrong_verify_status() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WRONG_VERIFY_STATUS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Verified status cannot be changed to Unverified.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un statut Vérifié ne peut être changé pour Non vérifié.")); }

        // Actions
	};
}



