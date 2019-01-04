#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_splitcom_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_splitcom_exists() { }
		~CIFast_IFast_ifastdbrkr_err_splitcom_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SPLITCOM_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Split-Commission record already exists.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Eintrag für verteilte Agenturvergütung-existiert bereits.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El registro de comisión dividida ya existe.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement de partage de commission existe déjà.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Record gedeelde commissie bestaat al")); }

        // Actions
	};
}



