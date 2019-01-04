#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_idtype_for_country_existed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_idtype_for_country_existed() { }
		~CIFast_IFast_ifastcbo_warn_idtype_for_country_existed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_IDTYPE_FOR_COUNTRY_EXISTED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%ID_TYPE% for %COUNTRY% already exists within the same period.")); }

        // Actions
	};
}



