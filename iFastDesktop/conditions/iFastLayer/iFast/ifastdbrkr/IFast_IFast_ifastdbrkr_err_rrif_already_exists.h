#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_rrif_already_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_rrif_already_exists() { }
		~CIFast_IFast_ifastdbrkr_err_rrif_already_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RRIF_ALREADY_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("RRIF information already exists for specified year.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("RRIF information already exists for specified year.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("RRIF-Informationen für das angegebene Jahr liegen bereits vor.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La información RRIF ya existe para el año especificado")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'information FERR existe déjà pour l'année indiquée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("RRIF-gegevens bestaan al voor het opgegeven jaar")); }

        // Actions
	};
}



