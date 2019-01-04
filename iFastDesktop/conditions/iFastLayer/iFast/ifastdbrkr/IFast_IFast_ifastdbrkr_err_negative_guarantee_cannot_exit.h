#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_negative_guarantee_cannot_exit : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_negative_guarantee_cannot_exit() { }
		~CIFast_IFast_ifastdbrkr_err_negative_guarantee_cannot_exit() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NEGATIVE_GUARANTEE_CANNOT_EXIT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Negative Guarantees cannot exist when cancelling Initializing Deposit.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Negative Guarantees cannot exist when cancelling Initializing Deposit.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Des garanties négatives ne peuvent exister lors de l'annulation de l'initialisation du dépôt.")); }

        // Actions
	};
}



