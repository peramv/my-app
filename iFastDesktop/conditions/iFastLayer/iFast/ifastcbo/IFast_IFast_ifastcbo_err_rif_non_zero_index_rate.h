#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_non_zero_index_rate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_non_zero_index_rate() { }
		~CIFast_IFast_ifastcbo_err_rif_non_zero_index_rate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_NON_ZERO_INDEX_RATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Index Rate must be always zero for pay option different than \"I\".")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Index Rate must be always zero for pay option different than \"I\".")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Indexsatz für die Zahlungsoptionen \"M\" und \"X\" muss immer Null sein, wenn die Zahlungsoption einen anderen Wert als \"I\" hat.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La tasa de índice debe ser siempre cero para cualquier opción de pago que no sea \"I\".")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le taux d'indexation doit toujours être de zéro pour une option de paiement différente de I.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Indexpercentage moet altijd nul zijn voor andere betalingsopties dan 'I'")); }

        // Actions
	};
}



