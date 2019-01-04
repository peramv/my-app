#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_blank_reg_standard : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_blank_reg_standard() { }
		~CIFast_IFast_ifastcbo_warn_blank_reg_standard() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_BLANK_REG_STANDARD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Regulatory Standard value is blank.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ de la valeur de norme réglementaire est vide.")); }

        // Actions
	};
}



