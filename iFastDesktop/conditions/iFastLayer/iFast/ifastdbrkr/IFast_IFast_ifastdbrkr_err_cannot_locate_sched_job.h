#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_cannot_locate_sched_job : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_cannot_locate_sched_job() { }
		~CIFast_IFast_ifastdbrkr_err_cannot_locate_sched_job() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CANNOT_LOCATE_SCHED_JOB")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cannot locate scheduled job.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Job kann nicht lokalisiert werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se puede localizar la tarea programada.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de localiser le travail prévu.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Geplande taak kan niet worden gevonden")); }

        // Actions
	};
}



