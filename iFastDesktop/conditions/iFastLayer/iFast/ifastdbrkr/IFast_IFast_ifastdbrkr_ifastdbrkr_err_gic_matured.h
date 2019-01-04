#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_ifastdbrkr_err_gic_matured : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_ifastdbrkr_err_gic_matured() { }
		~CIFast_IFast_ifastdbrkr_ifastdbrkr_err_gic_matured() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("IFASTDBRKR_ERR_GIC_MATURED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("GIC record matured.  Cannot continue.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("GIC record matured.  Cannot continue.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Enregistrement CPG échu. Impossible de continuer.")); }

        // Actions
	};
}



