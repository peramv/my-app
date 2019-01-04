#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ditabuscore_wrn_s017pe_wrn : public CConditionObject
	{
	public:
		CIFast_IFast_ditabuscore_wrn_s017pe_wrn() { }
		~CIFast_IFast_ditabuscore_wrn_s017pe_wrn() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WRN_S017PE_WRN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ditabuscore")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Total of benefit percentage of secondary beneficiary must be 100%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Le total du pourcentage de l'allocation du bénéficiaire secondaire doit être 100%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der gesamte Nutzen-Prozentsatz des zweiten Begünstigten muss 100% betragen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El total del porcentaje de beneficios del beneficiario secundario debe ser 100%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le total de pourcentages de bénéfice du deuxième bénéficiaire doit être de 100 %.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Totaal van het begunstigdepercentage van de tweede begunstigde moet 100% zijn")); }

        // Actions
	};
}



