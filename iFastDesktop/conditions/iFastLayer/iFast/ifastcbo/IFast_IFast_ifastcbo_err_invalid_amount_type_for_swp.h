#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_amount_type_for_swp : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_amount_type_for_swp() { }
		~CIFast_IFast_ifastcbo_err_invalid_amount_type_for_swp() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_AMOUNT_TYPE_FOR_SWP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount type must be settle currency for SWP.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Betragsart muss Abrechnungswährung für SWP sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo de monto debe ser divisa de liquidación para SWP.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de montant doit être une devise de règlement pour le PRP.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bedragtype moet betalingsvaluta zijn voor SWP")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("please select settle currency.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wählen Sie „settle currency“ (Währung festlegen).")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("please select settle currency.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez sélectionner une monnaie de règlement.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("selecteer een betalingsvaluta")); }
	};
}



