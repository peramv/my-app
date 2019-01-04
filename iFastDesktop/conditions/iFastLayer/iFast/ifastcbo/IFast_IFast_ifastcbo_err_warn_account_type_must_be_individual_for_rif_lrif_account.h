#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_account_type_must_be_individual_for_rif_lrif_account : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_account_type_must_be_individual_for_rif_lrif_account() { }
		~CIFast_IFast_ifastcbo_err_warn_account_type_must_be_individual_for_rif_lrif_account() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_ACCOUNT_TYPE_MUST_BE_INDIVIDUAL_FOR_RIF_LRIF_ACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The Account type must be individual for LIF/LRIF/RLIF account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Kontoart muss speziell für LIF/LRIF–Konten geeignet sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo de cuenta debe ser Individual para la cuenta LIF/LRIF.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de compte doit être Individuel pour les comptes FRV, FRRI, FRVR.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het accounttype moet individueel zijn voor LIF/LRIF-account")); }

        // Actions
	};
}



