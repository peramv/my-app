#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_at_least_one_record_for_scale : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_at_least_one_record_for_scale() { }
		~CIFast_IFast_ifastcbo_err_at_least_one_record_for_scale() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AT_LEAST_ONE_RECORD_FOR_SCALE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("At least one record has to be created for Scale or Tier.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Mindestens ein Eintrag muss für Skala oder Rang erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe crearse al menos un registro para Escala o Nivel.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Au moins un enregistrement doit être créé pour l'échelle ou le niveau.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er moet ten minste één record zijn gemaakt voor schaal of laag")); }

        // Actions
	};
}



