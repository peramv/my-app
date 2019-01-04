#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ditabuscore_err_invalid_city_name_wrt_state_code : public CConditionObject
	{
	public:
		CIFast_IFast_ditabuscore_err_invalid_city_name_wrt_state_code() { }
		~CIFast_IFast_ditabuscore_err_invalid_city_name_wrt_state_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_CITY_NAME_WRT_STATE_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ditabuscore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount Type is mandatory.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Amount Type is mandatory.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Betragsart ist obligatorisch")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo de monto es obligatorio")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de montant est requis.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bedragtype is verplicht")); }

        // Actions
	};
}



