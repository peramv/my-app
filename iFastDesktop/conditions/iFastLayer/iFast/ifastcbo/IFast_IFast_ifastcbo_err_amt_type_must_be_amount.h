#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_amt_type_must_be_amount : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_amt_type_must_be_amount() { }
		~CIFast_IFast_ifastcbo_err_amt_type_must_be_amount() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMT_TYPE_MUST_BE_AMOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount type must be 'Amount' for Multi-Currrency purchase.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Le type de montant doit être \"Montant\" pour les souscriptions multidevises")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Betragsart muss “Betrag” sein für Mehrfach-Währungskauf.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo de monto debe ser 'Monto' para la compra en varias divisas")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de montant doit être Montant pour un achat multidevises.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bedragtype moet 'Bedrag' zijn voor aankoop van meerdere valuta")); }

        // Actions
	};
}



