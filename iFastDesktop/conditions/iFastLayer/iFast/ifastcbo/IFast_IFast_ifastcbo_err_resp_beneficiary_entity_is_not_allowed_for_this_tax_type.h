#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_resp_beneficiary_entity_is_not_allowed_for_this_tax_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_resp_beneficiary_entity_is_not_allowed_for_this_tax_type() { }
		~CIFast_IFast_ifastcbo_err_resp_beneficiary_entity_is_not_allowed_for_this_tax_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RESP_BENEFICIARY_ENTITY_IS_NOT_ALLOWED_FOR_THIS_TAX_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("RESP Beneficiary Entity is not allowed for this tax type.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("RESP Beneficiary Entity is not allowed for this tax type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("RESP-Begünstigten-Objekt ist nicht zugelassen für diese Steuerart.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite una entidad Beneficiario RESP para este tipo tributario")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Entité bénéficiaire REEE non autorisée pour ce type d'imposition")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Eenheid RESP-begunstigde is niet toegestaan voor dit belastingtype")); }

        // Actions
	};
}



