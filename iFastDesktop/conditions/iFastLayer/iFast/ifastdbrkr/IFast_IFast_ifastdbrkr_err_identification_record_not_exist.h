#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_identification_record_not_exist : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_identification_record_not_exist() { }
		~CIFast_IFast_ifastdbrkr_err_identification_record_not_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_IDENTIFICATION_RECORD_NOT_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Identification record does not exist.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Identification record does not exist.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Identifizierungseintrag existiert nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El registro de identificación no existe")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Enregistrement d'identification inexistant")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Identificatierecord bestaat niet")); }

        // Actions
	};
}



