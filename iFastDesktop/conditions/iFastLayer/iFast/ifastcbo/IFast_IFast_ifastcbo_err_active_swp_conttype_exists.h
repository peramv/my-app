#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_active_swp_conttype_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_active_swp_conttype_exists() { }
		~CIFast_IFast_ifastcbo_err_active_swp_conttype_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACTIVE_SWP_CONTTYPE_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("An active SWP has been set up for  the funds in this contract type.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un PRP actif a été réglé pour les fonds de ce type de contrat.")); }

        // Actions
	};
}



