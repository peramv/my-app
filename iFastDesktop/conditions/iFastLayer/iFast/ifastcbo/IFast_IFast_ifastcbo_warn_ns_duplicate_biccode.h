#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_ns_duplicate_biccode : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_ns_duplicate_biccode() { }
		~CIFast_IFast_ifastcbo_warn_ns_duplicate_biccode() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_NS_DUPLICATE_BICCODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("BIC Code already exists in the system. Network Sender must have unique BIC code.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code BIC existe déjà dans le système. L'expéditeur du réseau doit avoir un code BIC unique.")); }

        // Actions
	};
}



