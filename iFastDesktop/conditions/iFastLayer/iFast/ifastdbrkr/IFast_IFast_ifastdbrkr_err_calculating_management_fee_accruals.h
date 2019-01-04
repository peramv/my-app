#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_calculating_management_fee_accruals : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_calculating_management_fee_accruals() { }
		~CIFast_IFast_ifastdbrkr_err_calculating_management_fee_accruals() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CALCULATING_MANAGEMENT_FEE_ACCRUALS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Error calculating management fee accruals.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fehler bei der Berechnung von aufgelaufenen Management-Provisionen")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Error al calcular las comisiones por administración acumuladas")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur lors du calcul des augmentations de frais de gestion")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een fout opgetreden bij het berekenen van de groei van beheerkosten")); }

        // Actions
	};
}



