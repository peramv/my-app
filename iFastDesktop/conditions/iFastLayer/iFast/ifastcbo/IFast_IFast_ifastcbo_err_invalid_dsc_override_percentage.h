#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_dsc_override_percentage : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_dsc_override_percentage() { }
		~CIFast_IFast_ifastcbo_err_invalid_dsc_override_percentage() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_DSC_OVERRIDE_PERCENTAGE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Percentage can not be over 100.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Prozentsatz darf nicht über 100 sein")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El porcentaje no puede ser más de 100")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le pourcentage ne peut être supérieur à 100.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Percentage kan niet meer dan 100 zijn")); }

        // Actions
	};
}



