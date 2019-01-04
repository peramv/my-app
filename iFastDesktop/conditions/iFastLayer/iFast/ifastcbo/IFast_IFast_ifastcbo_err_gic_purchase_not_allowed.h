#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_gic_purchase_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_gic_purchase_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_gic_purchase_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_GIC_PURCHASE_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("GIC Fund Purchase not allowed for this account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("GIC Fund Purchase not allowed for this account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("GIC-Fondskauf ist für dieses Konto nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite la compra de fondo GIC para esta cuenta.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'achat de fonds CPG n'est pas autorisé pour ce compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Aankoop GIC-fonds is niet toegestaan voor dit account")); }

        // Actions
	};
}



