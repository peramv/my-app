#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_product_group_code : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_product_group_code() { }
		~CIFast_IFast_ifastdbrkr_err_no_product_group_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_PRODUCT_GROUP_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No Product Group Code record available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kein Produktgruppen-Code-Eintrag verfügbar")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay un registro de grupo de productos disponible")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun enregistrement de code de groupe de produits disponible")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is geen record Productgroepscode beschikbaar")); }

        // Actions
	};
}



