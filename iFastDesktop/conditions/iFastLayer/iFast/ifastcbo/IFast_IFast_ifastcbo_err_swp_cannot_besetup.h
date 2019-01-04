#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_swp_cannot_besetup : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_swp_cannot_besetup() { }
		~CIFast_IFast_ifastcbo_err_swp_cannot_besetup() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SWP_CANNOT_BESETUP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("A SWP cannot be set up when there is an existing RRIF with Amount Type G or L.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un PRP ne peut pas être réglé lorsqu'un FERR existe avec l'option de paiement MRV ou un MRG.")); }

        // Actions
	};
}



