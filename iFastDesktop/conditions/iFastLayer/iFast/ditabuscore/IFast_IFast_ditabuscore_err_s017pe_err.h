#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ditabuscore_err_s017pe_err : public CConditionObject
	{
	public:
		CIFast_IFast_ditabuscore_err_s017pe_err() { }
		~CIFast_IFast_ditabuscore_err_s017pe_err() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_S017PE_ERR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ditabuscore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Total of benefit percentage of primary beneficiary must be 100%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Le total du pourcentage de l'allocation du bénéficiaire principal doit être 100%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der gesamte Nutzen-Prozentsatz des ersten Begünstigten muss 100% betragen, bevor ein zweiter Begünstigter hinzugefügt werden kann.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El total del porcentaje de beneficios del beneficiario principal debe ser 100%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le total de pourcentages de bénéfice du premier bénéficiaire doit être de 100 %.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Totaal van het begunstigdepercentage van de eerste begunstigde moet 100% zijn")); }

        // Actions
	};
}



