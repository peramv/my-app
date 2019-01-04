#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_conflict_address_exist : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_conflict_address_exist() { }
		~CIFast_IFast_ifastdbrkr_err_conflict_address_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CONFLICT_ADDRESS_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("A conflicting Address record exists.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un enregistrement d'adresse contradictoire existe.")); }

        // Actions
	};
}



