#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_ifastdbrkr_err_gic_does_not_exist : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_ifastdbrkr_err_gic_does_not_exist() { }
		~CIFast_IFast_ifastdbrkr_ifastdbrkr_err_gic_does_not_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("IFASTDBRKR_ERR_GIC_DOES_NOT_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("GIC record does not exist.  Cannot continue.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("GIC record does not exist.  Cannot continue.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Enregistrement CPG inexistant. Impossible de continuer.")); }

        // Actions
	};
}



