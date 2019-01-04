#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_reg_address_code_is_not_available : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_reg_address_code_is_not_available() { }
		~CIFast_IFast_ifastcbo_err_reg_address_code_is_not_available() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REG_ADDRESS_CODE_IS_NOT_AVAILABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Nominee or Intermediary address is not available for the registry address code.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Nominee or Intermediary address is not available for the registry address code.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Nominee or Intermediary address is not available for the registry address code.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'adresse de la nominée ou de l'intermédiaire n'est pas applicable au code d'adresse d'enregistrement.")); }

        // Actions
	};
}



