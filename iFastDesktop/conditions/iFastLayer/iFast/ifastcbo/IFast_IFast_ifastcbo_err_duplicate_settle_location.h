#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_duplicate_settle_location : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_duplicate_settle_location() { }
		~CIFast_IFast_ifastcbo_err_duplicate_settle_location() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DUPLICATE_SETTLE_LOCATION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Duplicate Fund Mgmt Settlement Instruction")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Duplicate Settlement Location.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Duplicate Settlement Location.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Copie des instructions de règlement de la gestion de fonds")); }

        // Actions
	};
}



