#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rrif_cannot_besetup : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rrif_cannot_besetup() { }
		~CIFast_IFast_ifastcbo_err_rrif_cannot_besetup() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RRIF_CANNOT_BESETUP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("A RRIF cannot be set up when there is an existing SWP with Amount Type G or L.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un FERR ne peut pas être réglé lorsqu'un PRP existe avec un MRV ou un MRG.")); }

        // Actions
	};
}



