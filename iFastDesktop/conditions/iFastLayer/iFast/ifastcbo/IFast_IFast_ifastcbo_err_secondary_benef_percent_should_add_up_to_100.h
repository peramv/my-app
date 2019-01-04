#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_secondary_benef_percent_should_add_up_to_100 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_secondary_benef_percent_should_add_up_to_100() { }
		~CIFast_IFast_ifastcbo_err_secondary_benef_percent_should_add_up_to_100() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SECONDARY_BENEF_PERCENT_SHOULD_ADD_UP_TO_100")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

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



