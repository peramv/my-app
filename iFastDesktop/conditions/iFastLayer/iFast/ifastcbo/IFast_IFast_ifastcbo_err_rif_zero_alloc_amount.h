#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_zero_alloc_amount : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_zero_alloc_amount() { }
		~CIFast_IFast_ifastcbo_err_rif_zero_alloc_amount() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_ZERO_ALLOC_AMOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("When Accounts Amount is zero, only funds percent is allowed.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Lorsque Montant des comptes est egal a zero, seul le pourcentage des fonds est autorisé.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Wenn der Kontenbetrag null beträgt, ist nur Fonds-Prozent erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Cuando Monto de las cuentas es cero, sólo se permiten porcentajes de los fondos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Quand le montant des comptes est zéro, seul le pourcentage des fonds est autorisé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Als het accountbedrag nul is, is alleen een fondspercentage toegestaan")); }

        // Actions
	};
}



