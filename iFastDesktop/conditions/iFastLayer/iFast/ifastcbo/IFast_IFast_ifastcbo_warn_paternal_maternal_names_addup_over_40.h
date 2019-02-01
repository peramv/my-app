#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_paternal_maternal_names_addup_over_40 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_paternal_maternal_names_addup_over_40() { }
		~CIFast_IFast_ifastcbo_warn_paternal_maternal_names_addup_over_40() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_PATERNAL_MATERNAL_NAMES_ADD_UP_OVER_40")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("When adding up Paternal and Maternal Names, they have more than 40 characters. There would be a truncation.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Lors de la concaténation des noms paternel et maternel, ils ont plus de 40 caractères. Il y aurait une troncature.")); }

        // Actions
	};
}
