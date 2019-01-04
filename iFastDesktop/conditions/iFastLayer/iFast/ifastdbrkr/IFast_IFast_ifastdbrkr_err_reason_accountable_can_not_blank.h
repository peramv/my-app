#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_reason_accountable_can_not_blank : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_reason_accountable_can_not_blank() { }
		~CIFast_IFast_ifastdbrkr_err_reason_accountable_can_not_blank() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REASON_ACCOUNTABLE_CAN_NOT_BLANK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Dilution Reason Code and Accountable code cannot be blank.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Dilution Reason Code and Accountable code cannot be blank.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de raison de la dilution et le code comptable sont requis.")); }

        // Actions
	};
}



