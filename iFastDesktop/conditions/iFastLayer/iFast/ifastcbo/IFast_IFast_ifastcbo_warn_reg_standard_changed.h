#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_reg_standard_changed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_reg_standard_changed() { }
		~CIFast_IFast_ifastcbo_warn_reg_standard_changed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_REG_STANDARD_CHANGED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Regulatory standard has been changed. Please update status of each document.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La norme réglementaire a été changée. Veuillez mettre à jour le statut de chaque document.")); }

        // Actions
	};
}



