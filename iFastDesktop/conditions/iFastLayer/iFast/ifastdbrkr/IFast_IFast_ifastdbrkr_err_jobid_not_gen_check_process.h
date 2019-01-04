#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_jobid_not_gen_check_process : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_jobid_not_gen_check_process() { }
		~CIFast_IFast_ifastdbrkr_err_jobid_not_gen_check_process() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_JOBID_NOT_GEN_CHECK_PROCESS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Job Id not generated - check process.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Job ld nicht erstellt – Prozess überprüfen")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Identificación de tarea no generada - verifique proceso.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de travail n'a pas été généré – vérifiez le processus.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Taak-ID is niet gegenereerd - controleer de verwerking")); }

        // Actions
	};
}



