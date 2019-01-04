#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_init_contrib_must_greater_than_fee : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_init_contrib_must_greater_than_fee() { }
		~CIFast_IFast_ifastcbo_err_init_contrib_must_greater_than_fee() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INIT_CONTRIB_MUST_GREATER_THAN_FEE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The initial contribution amount must be greater than the expected fee (%INITIALVUBAMT%).")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der anfängliche Einlagenbetrag muss größer als die erwartete Provision (%INITIALVUBAMT%) sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto de aportación inicial debe ser mayor que la comisión esperada (%INITIALVUBAMT%).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant de cotisation initiale doit être supérieur aux frais escomptés (%INITIALVUBAMT%).")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het bedrag voor de eerste bijdrage moet groter zijn dan de verwachte kosten (%INITIALVUBAMT%)")); }

        // Actions
	};
}



