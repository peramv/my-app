#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_mgmt_fee_not_allowed_for_taxtype : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_mgmt_fee_not_allowed_for_taxtype() { }
		~CIFast_IFast_ifastcbo_err_mgmt_fee_not_allowed_for_taxtype() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MGMT_FEE_NOT_ALLOWED_FOR_TAXTYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Management Fee not allowed for this tax type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Management-Provision für diese Steuerart nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite la comisión por administración para este tipo tributario")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Frais de gestion non autorisés pour ce type d'imposition")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Beheerkosten zijn niet toegestaan voor dit belastingtype")); }

        // Actions
	};
}



