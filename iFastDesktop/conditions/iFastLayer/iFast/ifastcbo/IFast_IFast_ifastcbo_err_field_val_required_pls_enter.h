#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_field_val_required_pls_enter : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_field_val_required_pls_enter() { }
		~CIFast_IFast_ifastcbo_err_field_val_required_pls_enter() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FIELD_VAL_REQUIRED_PLS_ENTER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This field is required.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Feld ist notwendig. Bitte geben Sie einen Wert ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Este campo es obligatorio. Por favor introduzca un valor.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Ce champ doit être rempli.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het veld is vereist. Vul een waarde in")); }

        // Actions
	};
}



