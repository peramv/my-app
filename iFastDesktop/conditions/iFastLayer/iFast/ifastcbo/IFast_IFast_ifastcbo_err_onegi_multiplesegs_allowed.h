#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_onegi_multiplesegs_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_onegi_multiplesegs_allowed() { }
		~CIFast_IFast_ifastcbo_err_onegi_multiplesegs_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ONEGI_MULTIPLESEGS_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only one GI fund or multiple SEG funds are allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Seuls un FIG ou plusieurs fonds distincts sont autorisés.")); }

        // Actions
	};
}



