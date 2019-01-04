#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_can_only_delete_on_the_date_record_is_created : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_can_only_delete_on_the_date_record_is_created() { }
		~CIFast_IFast_ifastdbrkr_err_can_only_delete_on_the_date_record_is_created() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CAN_ONLY_DELETE_ON_THE_DATE_RECORD_IS_CREATED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Can only delete on the date the record was created – Change Stop Date instead.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Sie können nur am Erstellungsdatum des Eintrages löschen – Ändern Sie stattdessen das Stoppdatum.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Sólo se puede eliminar en la fecha en que se crea el registro – Cambie la fecha de baja.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La suppression n'est possible qu'à la date où l'enregistrement a été créé – changez plutôt la date de fin.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Wissen kan alleen op de datum waarop het record is gemaakt - wijzig in plaats hiervan de einddatum")); }

        // Actions
	};
}



