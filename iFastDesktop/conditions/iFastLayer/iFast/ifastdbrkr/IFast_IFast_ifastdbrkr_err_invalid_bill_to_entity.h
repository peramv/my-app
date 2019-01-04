#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_invalid_bill_to_entity : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_invalid_bill_to_entity() { }
		~CIFast_IFast_ifastdbrkr_err_invalid_bill_to_entity() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_BILL_TO_ENTITY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid bill to entity.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Facturation à l'entité invalide")); }

        // Actions
	};
}



