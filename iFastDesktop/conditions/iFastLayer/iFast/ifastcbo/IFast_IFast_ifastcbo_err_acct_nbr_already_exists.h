#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_acct_nbr_already_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_acct_nbr_already_exists() { }
		~CIFast_IFast_ifastcbo_err_acct_nbr_already_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_NBR_ALREADY_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Duplicate Account number.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Doublon de numero de compte. Veuillez reverifier et ressaisir un numero.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Doppelte Kontonummer. Bitte überprüfen und neu eingeben.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Número de cuenta repetido. Por favor verifíquelo y vuelva a introducirlo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Copie du numéro de compte")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Identiek accountnummer. Controleer het nummer en vul het opnieuw in")); }

        // Actions
	};
}



