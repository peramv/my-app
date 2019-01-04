#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ditabuscore_wrn_finalist_wrn : public CConditionObject
	{
	public:
		CIFast_IFast_ditabuscore_wrn_finalist_wrn() { }
		~CIFast_IFast_ditabuscore_wrn_finalist_wrn() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WRN_FINALIST_WRN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ditabuscore")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Total of benefit percentage of the primary beneficiary must be 100% before a secondary beneficiary can be added.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Le total du pourcentage de l'allocation du bénéficiaire principal doit être 100% avant de pouvoir ajouter un bénéficiaire secondaire.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der gesamte Nutzen-Prozentsatz des ersten Begünstigten muss 100% betragen, bevor ein zweiter Begünstigter hinzugefügt werden kann.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El total del porcentaje de beneficios del beneficiario principal debe ser 100% before a secondary beneficiary can be added.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le total de pourcentages de bénéfice du premier bénéficiaire doit être de 100 % avant qu'un deuxième bénéficiaire ne puisse être ajouté.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Totaal van het begunstigdepercentage van de eerste begunstigde moet 100% zijn voor een tweede begunstigde kan worden toegevoegd")); }

        // Actions
	};
}



