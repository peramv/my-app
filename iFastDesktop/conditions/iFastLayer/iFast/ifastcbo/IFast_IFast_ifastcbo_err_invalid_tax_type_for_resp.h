#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_tax_type_for_resp : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_tax_type_for_resp() { }
		~CIFast_IFast_ifastcbo_err_invalid_tax_type_for_resp() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_TAX_TYPE_FOR_RESP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("RESP Beneficiary may only be set up for RESP or Family plan RESP account tax types.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("RESP Beneficiary may only be set up for RESP or Family plan RESP account tax types.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("RESP-Begünstigter kann nur für RESP- oder Familienplan-RSP-Konto-Steuerarten erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El beneficiario RESP sólo puede configurarse para tipos tributarios de cuenta RESP o RESP de plan familiar")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le bénéficiaire REEE ne doit être réglé que pour les types d'imposition des comptes REEE ou REEE familial.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("RESP-begunstigde mag alleen worden ingesteld voor accountbelastingtypes RESP of Family Plan RESP")); }

        // Actions
	};
}



