#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_invalid_gross_or_net : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_invalid_gross_or_net() { }
		~CIFast_IFast_ifastcbo_err_rif_invalid_gross_or_net() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_INVALID_GROSS_OR_NET")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Gross/Net Pretax must be \"Gross\" for Pay option \"M\" and \"X\".")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Gross/Net Pretax must be \"Gross\" for Pay option \"M\" and \"X\".")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Brutto/Netto-Vorsteuer für die Zahlungsoptionen \"M\" und \"X\" muss auf \"Brutto\" stehen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Preimpuesto bruto/neto debe ser \"Bruto\" para la opción de pago \"M\" y \"X\".")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'avant impôts brut/net doit être Brut pour les options de paiement M et X.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bruto/netto voorbelasting moet 'Bruto' zijn voor betalingsopties 'M' en 'X'")); }

        // Actions
	};
}



