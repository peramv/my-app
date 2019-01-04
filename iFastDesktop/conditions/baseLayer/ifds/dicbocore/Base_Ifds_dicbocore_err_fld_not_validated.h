#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dicbocore_err_fld_not_validated : public CConditionObject
	{
	public:
		CBase_Ifds_dicbocore_err_fld_not_validated() { }
		~CBase_Ifds_dicbocore_err_fld_not_validated() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FLD_NOT_VALIDATED")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The field is required.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("The field is required.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Este campo es obligatorio.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ doit être rempli.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het veld is vereist.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Required fields cannot be set to blank or null.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Required fields cannot be set to blank or null.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Los campos obligatorios no pueden configurarse en blanco o en cero.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Les champs requis ne peuvent être laissés vides ou réglés à zéro.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Vereiste velden kunnen niet worden ingesteld op leeg of nul.")); }
	};
}



