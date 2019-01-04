#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastbp_bp_err_class_empty : public CConditionObject
	{
	public:
		CIFast_IFast_ifastbp_bp_err_class_empty() { }
		~CIFast_IFast_ifastbp_bp_err_class_empty() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_ERR_CLASS_EMPTY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastbp")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Class code is empty.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Class code is empty.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Class code is empty.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ Code de classe est vide.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Please re-enter.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Please re-enter.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez recommencer la saisie.")); }
	};
}



