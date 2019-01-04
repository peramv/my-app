#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_death_notif_before_death_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_death_notif_before_death_date() { }
		~CIFast_IFast_ifastcbo_err_death_notif_before_death_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DEATH_NOTIF_BEFORE_DEATH_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Death notification date must be after or equal to the death date.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("La date de declaration de deces doit être posterieure ou identique a la date de deces.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Todesbenachrichtigungs-Datum muss nach dem Todesdatum liegen oder mit diesem übereinstimmen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de notificación de fallecimiento debe ser posterior o igual a la fecha de fallecimiento.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de notification du décès doit être postérieure ou identique à la date de décès.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Datum overlijdensbericht moet later zijn dan of gelijk zijn aan de overlijdensdatum")); }

        // Actions
	};
}



