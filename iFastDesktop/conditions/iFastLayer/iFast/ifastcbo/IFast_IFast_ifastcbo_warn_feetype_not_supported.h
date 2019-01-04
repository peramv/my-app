#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_feetype_not_supported : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_feetype_not_supported() { }
		~CIFast_IFast_ifastcbo_warn_feetype_not_supported() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_FEETYPE_NOT_SUPPORTED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Environment  does not support this fee type.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'environnement ne supporte pas ce type de frais.")); }

        // Actions
	};
}



