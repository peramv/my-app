#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_escrow_efective_date_less_than_current_bussines_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_escrow_efective_date_less_than_current_bussines_date() { }
		~CIFast_IFast_ifastcbo_err_escrow_efective_date_less_than_current_bussines_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ESCROW_EFECTIVE_DATE_LESS_THAN_CURRENT_BUSSINES_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Escrow/Assigned Effective Date must be after Current Business Date.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Escrow Effective Date must precede Current Business Date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Escrow-Effektivdatum muss vor dem Aktuellen Geschäftsdatum liegen. Bitte geben Sie das Escrow-Effektivdatum neu ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de entrada en vigencia de custodia debe ser anterior a la fecha de negocio actual. Por favor vuelva a introducir la fecha de entrada en vigencia de custodia.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'entrée en vigueur de la mise en garantie doit être postérieure à la date opérationnelle actuelle.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ingangsdatum pand moet voor de huidige handelsdatum liggen. Vul de ingangsdatum van het pand opnieuw in")); }

        // Actions
	};
}



