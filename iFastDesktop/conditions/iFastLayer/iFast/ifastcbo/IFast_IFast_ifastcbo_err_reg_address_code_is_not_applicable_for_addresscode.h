#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_reg_address_code_is_not_applicable_for_addresscode : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_reg_address_code_is_not_applicable_for_addresscode() { }
		~CIFast_IFast_ifastcbo_err_reg_address_code_is_not_applicable_for_addresscode() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REG_ADDRESS_CODE_IS_NOT_APPLICABLE_FOR_ADDRESSCODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Registry Address is not applicable to address code %ADDRCODE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Registry Address is not applicable to address code %ADDRCODE%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Registry Address is not applicable to address code %ADDRCODE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'adresse d'enregistrement n'est pas applicable au code d'adresse %ADDRCODE%.")); }

        // Actions
	};
}



