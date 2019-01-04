#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_only_one_category : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_only_one_category() { }
		~CIFast_IFast_ifastcbo_err_only_one_category() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ONLY_ONE_CATEGORY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only one entry per category allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Only one entry per category allowed.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Only one entry per category allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une seule entrée autorisée par catégorie.")); }

        // Actions
	};
}



