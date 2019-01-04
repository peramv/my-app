#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_ef : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_ef() { }
		~CIFast_IFast_ifastcbo_err_ef() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EF")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cannot use redemption code EF with client accounts.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible d'utiliser les frais externes du code de rachat avec les comptes clients.")); }

        // Actions
	};
}



