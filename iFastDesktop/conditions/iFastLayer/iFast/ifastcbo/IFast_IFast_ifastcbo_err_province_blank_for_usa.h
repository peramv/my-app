#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_province_blank_for_usa : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_province_blank_for_usa() { }
		~CIFast_IFast_ifastcbo_err_province_blank_for_usa() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PROVINCE_BLANK_FOR_USA")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("US state must be provided.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'État des États-Unis est requis.")); }

        // Actions
	};
}



