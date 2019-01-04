﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_wrong_stop_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_wrong_stop_date() { }
		~CIFast_IFast_ifastcbo_err_rif_wrong_stop_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_WRONG_STOP_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Stop Date must be after Effective Date and within the same year.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("La date d'arret doit être posterieure a la date d'effet et comprise dans la meme annee.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Stopdatum muss nach dem Effektivdatum und innerhalb des gleichen Jahres liegen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de baja debe ser posterior a la fecha de entrada en vigencia y dentro del mismo año.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'arrêt doit être postérieure à la date d'entrée en vigueur et se situer au cours de la même année.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Einddatum moet later zijn dan ingangsdatum en in hetzelfde jaar")); }

        // Actions
	};
}



