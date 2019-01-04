#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_sys_deff_less_than_acct_deff : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_sys_deff_less_than_acct_deff() { }
		~CIFast_IFast_ifastcbo_err_sys_deff_less_than_acct_deff() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SYS_DEFF_LESS_THAN_ACCT_DEFF")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account is not active as of the input effective date.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Le compte n'est pas actif a compter de la date d'effet saisie. Veuillez ressaisir.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Konto ist nicht aktiv ab dem eingegebenen Effektivdatum. Bitte geben Sie neu ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La cuenta no está activa a la fecha de entrada en vigencia de entrada. Por favor vuelva a introducir los datos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le compte n'est pas actif à partir de la date d'entrée en vigueur saisie.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Account is niet actief vanaf de ingevoerde ingangsdatum. Vul opnieuw in")); }

        // Actions
	};
}



