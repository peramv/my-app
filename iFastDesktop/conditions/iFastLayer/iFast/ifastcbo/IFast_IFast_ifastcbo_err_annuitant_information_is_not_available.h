#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_annuitant_information_is_not_available : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_annuitant_information_is_not_available() { }
		~CIFast_IFast_ifastcbo_err_annuitant_information_is_not_available() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ANNUITANT_INFORMATION_IS_NOT_AVAILABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Annuitant Information is not available.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Annuitant Information is not available.")); }

        // Actions
	};
}



