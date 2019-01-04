#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_reg_address_code_is_not_blank : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_reg_address_code_is_not_blank() { }
		~CIFast_IFast_ifastcbo_err_reg_address_code_is_not_blank() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REG_ADDRESS_CODE_IS_NOT_BLANK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Registry address code has to be blank for non-nominee or intermediary account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Registry address code has to be blank for non-nominee or intermediary account.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Registry address code has to be blank for non-nominee or intermediary account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ du code d'adresse d'enregistrement doit être vide pour les comptes non-nominée ou intermédiaire.")); }

        // Actions
	};
}



