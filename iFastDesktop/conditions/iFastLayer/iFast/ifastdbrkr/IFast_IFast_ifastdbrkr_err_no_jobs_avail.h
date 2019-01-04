#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_jobs_avail : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_jobs_avail() { }
		~CIFast_IFast_ifastdbrkr_err_no_jobs_avail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_JOBS_AVAIL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No Jobs available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Keine Jobs verfügbar.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay tareas disponibles.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun emploi disponible")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen taken beschikbaar")); }

        // Actions
	};
}



