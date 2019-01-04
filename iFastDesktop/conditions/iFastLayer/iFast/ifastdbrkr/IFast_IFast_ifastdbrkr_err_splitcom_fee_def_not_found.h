#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_splitcom_fee_def_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_splitcom_fee_def_not_found() { }
		~CIFast_IFast_ifastdbrkr_err_splitcom_fee_def_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SPLITCOM_FEE_DEF_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("SplitComm-FeeDefn not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("SplitComm-FeeDefn nicht gefunden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró SplitComm-FeeDefn")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La définition des frais de partage de commission est introuvable.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("SplitComm-FeeDefn is niet gevonden")); }

        // Actions
	};
}



