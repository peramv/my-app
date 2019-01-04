﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_invalid_bill_to_entity_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_invalid_bill_to_entity_type() { }
		~CIFast_IFast_ifastdbrkr_err_invalid_bill_to_entity_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_BILL_TO_ENTITY_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid bill to entity type.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Type de facturation à l'entité invalide")); }

        // Actions
	};
}



