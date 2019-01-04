#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_invalid_parameter_need_brokercode : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_invalid_parameter_need_brokercode() { }
		~CIFast_IFast_ifastdbrkr_err_invalid_parameter_need_brokercode() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_PARAMETER_NEED_BROKERCODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid search parameter passed, BrokerCode must be populated.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un paramètre de recherche invalide est passé, le code de courtier est requis.")); }

        // Actions
	};
}



