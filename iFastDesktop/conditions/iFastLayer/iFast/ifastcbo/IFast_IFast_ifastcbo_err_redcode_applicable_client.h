#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_redcode_applicable_client : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_redcode_applicable_client() { }
		~CIFast_IFast_ifastcbo_err_redcode_applicable_client() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REDCODE_APPLICABLE_CLIENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Redcode is applicable for client held account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de rachat s'applique aux comptes détenus par un client.")); }

        // Actions
	};
}



