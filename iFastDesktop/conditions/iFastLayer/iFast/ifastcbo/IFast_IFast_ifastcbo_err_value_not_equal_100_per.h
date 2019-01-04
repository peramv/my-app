﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_value_not_equal_100_per : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_value_not_equal_100_per() { }
		~CIFast_IFast_ifastcbo_err_value_not_equal_100_per() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_VALUE_NOT_EQUAL_100_PER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The total percentage must equal one hundred percent.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Le pourcentage total doit être egal a cent pourcent. Veuillez modifier le pourcentage.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die gesamte Prozentzahl muss hundert Prozent ergeben. Bitte gleichen Sie ihre Angaben an.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El porcentaje total debe ser igual a cien por ciento. Por favor haga los ajustes necesarios.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le pourcentage total doit être égal à 100 %.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het totale percentage moet gelijk zijn aan honderd procent. Pas dit zo nodig aan")); }

        // Actions
	};
}



