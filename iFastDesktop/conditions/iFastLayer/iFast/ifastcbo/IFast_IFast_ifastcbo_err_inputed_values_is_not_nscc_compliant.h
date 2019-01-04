#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_inputed_values_is_not_nscc_compliant : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_inputed_values_is_not_nscc_compliant() { }
		~CIFast_IFast_ifastcbo_err_inputed_values_is_not_nscc_compliant() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INPUTED_VALUES_IS_NOT_NSCC_COMPLIANT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%NSCC% is not a NSCC compliant.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%NSCC% is not a NSCC compliant.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("%NSCC% n'est pas conforme au NSCC.")); }

        // Actions
	};
}



