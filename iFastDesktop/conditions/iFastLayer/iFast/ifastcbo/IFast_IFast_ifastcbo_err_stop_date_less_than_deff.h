﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_stop_date_less_than_deff : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_stop_date_less_than_deff() { }
		~CIFast_IFast_ifastcbo_err_stop_date_less_than_deff() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_STOP_DATE_LESS_THAN_DEFF")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Effective date must precede Stop date.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("La date d'effet doit être anterieure a la date d'arret. Veuillez ressaisir la date d'arret.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Vor dem Stopdatum muss das Effektivdatum kommen. Bitte geben Sie das Stopdatum neu ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de entrada en vigencia debe ser anterior a la fecha de baja. Por favor vuelva a introducir la fecha de baja.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'entrée en vigueur doit être antérieure à la date d'arrêt.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ingangsdatum moet voor de einddatum liggen. Vul de einddatum opnieuw in")); }

        // Actions
	};
}



