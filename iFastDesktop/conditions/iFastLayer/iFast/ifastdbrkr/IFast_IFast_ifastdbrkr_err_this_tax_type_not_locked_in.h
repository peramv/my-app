#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_this_tax_type_not_locked_in : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_this_tax_type_not_locked_in() { }
		~CIFast_IFast_ifastdbrkr_err_this_tax_type_not_locked_in() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_THIS_TAX_TYPE_NOT_LOCKED_IN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This tax type is not locked in.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("This tax type is not locked in.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Steuerart ist nicht festgelegt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Este tipo tributario no está bloqueado.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Ce type d'imposition n'est pas immobilisé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Dit belastingtype is niet vergrendeld")); }

        // Actions
	};
}



