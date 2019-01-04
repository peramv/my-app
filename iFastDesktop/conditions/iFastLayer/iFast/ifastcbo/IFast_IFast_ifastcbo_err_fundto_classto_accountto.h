#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fundto_classto_accountto : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fundto_classto_accountto() { }
		~CIFast_IFast_ifastcbo_err_fundto_classto_accountto() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUNDTO_CLASSTO_ACCOUNTTO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("if %FIELD% is blank or zero, %FIELD_2% should be blank or zero too.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("if %FIELD% is blank or zero, %FIELD_2% should be blank or zero too.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Wenn %FIELD% leer oder Null ist, sollte %FIELD_2% ebenfalls leer oder Null sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("si %FIELD% está en blanco o es cero, %FIELD_2%  debe estar en blanco o ser cero también")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Si le champ %FIELD% est vide ou à zéro, le champ %FIELD_2% devrait aussi être vide ou à zéro.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("als %FIELD% leeg of nul is, moet %FIELD_2%  ook leeg of nul zijn")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("please re-enter")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("please re-enter")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Bitte geben Sie neu ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("please re-enter")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez recommencer la saisie.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("vul opnieuw in")); }
	};
}



