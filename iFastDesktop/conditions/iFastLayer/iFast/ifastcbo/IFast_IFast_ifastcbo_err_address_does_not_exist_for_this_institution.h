#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_address_does_not_exist_for_this_institution : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_address_does_not_exist_for_this_institution() { }
		~CIFast_IFast_ifastcbo_err_address_does_not_exist_for_this_institution() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ADDRESS_DOES_NOT_EXIST_FOR_THIS_INSTITUTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Address does not exist for this institution.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Address does not exist for this institution.")); }

        // Actions
	};
}



