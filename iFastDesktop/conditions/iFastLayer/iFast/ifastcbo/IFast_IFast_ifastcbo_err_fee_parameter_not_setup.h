#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fee_parameter_not_setup : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fee_parameter_not_setup() { }
		~CIFast_IFast_ifastcbo_err_fee_parameter_not_setup() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FEE_PARAMETER_NOT_SETUP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fee parameter has not been set up.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fee parameter has not been set up.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les paramètres de frais n'ont pas été réglés.")); }

        // Actions
	};
}



