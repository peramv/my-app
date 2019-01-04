#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_invalid_activity_id : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_invalid_activity_id() { }
		~CIFast_IFast_ifastdbrkr_err_invalid_activity_id() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_ACTIVITY_ID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Activity ID.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Invalid Activity ID.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code d'activité invalide")); }

        // Actions
	};
}



