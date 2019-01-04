#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_gui_invalid_policy : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_gui_invalid_policy() { }
		~CIFast_IFast_ifastgui_gui_invalid_policy() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_INVALID_POLICY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The contract selected has invalid policy details. Policy year and term cannot be zero.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les détails de la police du contrat sélectionné sont invalides. L'année et le terme de la police ne peuvent être zéro.")); }

        // Actions
	};
}



