#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_kiid_attestation : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_kiid_attestation() { }
		~CIFast_IFast_ifastcbo_warn_kiid_attestation() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_KIID_ATTESTATION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account KIID confirmation unavailable in iFast.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La confirmation du KIID du compte n'est pas disponible dans iFAST.")); }

        // Actions
	};
}



