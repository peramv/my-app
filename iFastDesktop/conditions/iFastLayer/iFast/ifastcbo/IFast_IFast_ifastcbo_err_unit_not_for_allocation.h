#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_unit_not_for_allocation : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_unit_not_for_allocation() { }
		~CIFast_IFast_ifastcbo_err_unit_not_for_allocation() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNIT_NOT_FOR_ALLOCATION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trade in Unit not allowed for allocation transaction.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Trade in Unit not allowed for allocation transaction.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Handel in Anteilen für Zuweisungs-Transaktion nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite operación en unidad para transacción de asignación")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La transaction en unités n'est pas autorisée pour une transaction de répartition.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Handel in eenheid niet toegestaan voor allocatietransactie")); }

        // Actions
	};
}



