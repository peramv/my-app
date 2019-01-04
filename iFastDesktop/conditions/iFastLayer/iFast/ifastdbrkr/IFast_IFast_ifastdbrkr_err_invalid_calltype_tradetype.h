#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_invalid_calltype_tradetype : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_invalid_calltype_tradetype() { }
		~CIFast_IFast_ifastdbrkr_err_invalid_calltype_tradetype() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_CALLTYPE_TRADETYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Call Type and Trade Type combination.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Combinaison de type d'appel et de type de transaction invalide")); }

        // Actions
	};
}



