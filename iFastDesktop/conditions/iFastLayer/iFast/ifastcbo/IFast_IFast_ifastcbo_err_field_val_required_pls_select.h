#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_field_val_required_pls_select : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_field_val_required_pls_select() { }
		~CIFast_IFast_ifastcbo_err_field_val_required_pls_select() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FIELD_VAL_REQUIRED_PLS_SELECT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This field is required.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Dieses Feld ist notwendig. Bitte wählen Sie einen Wert.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Este campo es obligatorio. Por favor seleccione un valor.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Ce champ doit être rempli.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Dit veld is vereist. Selecteer een waarde")); }

        // Actions
	};
}



