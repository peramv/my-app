#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_clearingfirm_already_equal_to_broker : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_clearingfirm_already_equal_to_broker() { }
		~CIFast_IFast_ifastcbo_err_clearingfirm_already_equal_to_broker() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CLEARINGFIRM_ALREADY_EQUAL_TO_BROKER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Agent For Firm and TPA must be blank if ClearingFirm equals to Broker")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Agent For Firm and TPA must be blank if ClearingFirm equals to Broker")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les champs de l'agent de cabinet et du TPA doivent être vides si le cabinet de compensation est identique au courtier.")); }

        // Actions
	};
}



