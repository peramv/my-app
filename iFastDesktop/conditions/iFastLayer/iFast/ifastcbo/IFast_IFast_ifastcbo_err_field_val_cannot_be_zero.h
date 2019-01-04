#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_field_val_cannot_be_zero : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_field_val_cannot_be_zero() { }
		~CIFast_IFast_ifastcbo_err_field_val_cannot_be_zero() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FIELD_VAL_CANNOT_BE_ZERO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The field cannot be zero.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Feld darf nicht Null sein. Bitte geben Sie neu ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Este campo no puede ser cero. Por favor vuelva a introducir los datos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Ce champ ne peut être réglé à zéro.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het veld kan niet nul zijn. Vul opnieuw in")); }

        // Actions
	};
}



