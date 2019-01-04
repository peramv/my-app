#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_product_group_code_invalid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_product_group_code_invalid() { }
		~CIFast_IFast_ifastdbrkr_err_product_group_code_invalid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PRODUCT_GROUP_CODE_INVALID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Product Group Code Invalid.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Produktgruppen-Code ungültig")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Código de grupo de productos no válido")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de groupe de produits invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige productgroepscode")); }

        // Actions
	};
}



