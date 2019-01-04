#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_increase_not_allowed_missed_pacs : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_increase_not_allowed_missed_pacs() { }
		~CIFast_IFast_ifastdbrkr_err_increase_not_allowed_missed_pacs() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INCREASE_NOT_ALLOWED_MISSED_PACS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Increase not allowed when there are missed PACS")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Augmentation non autorisée lorsqu'il y a des PAC manqués")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please correct")); }
	};
}



