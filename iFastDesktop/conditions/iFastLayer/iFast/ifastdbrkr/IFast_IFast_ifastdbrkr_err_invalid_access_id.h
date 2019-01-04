#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_invalid_access_id : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_invalid_access_id() { }
		~CIFast_IFast_ifastdbrkr_err_invalid_access_id() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_ACCESS_ID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid access id.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code d'accès invalide")); }

        // Actions
	};
}



