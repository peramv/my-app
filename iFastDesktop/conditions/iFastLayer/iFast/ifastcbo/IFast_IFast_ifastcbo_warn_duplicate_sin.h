#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_duplicate_sin : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_duplicate_sin() { }
		~CIFast_IFast_ifastcbo_warn_duplicate_sin() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_DUPLICATE_SIN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("SIN already exists in the system.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("SIN already exists in the system.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le NAS existe déjà dans le système.")); }

        // Actions
	};
}



